/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 15:52:31 by dapereir          #+#    #+#             */
/*   Updated: 2023/10/15 19:57:06 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

const int	max_clients = 10;


// Constructors & destructor
// ==========================================================================

Server::Server(int port, std::string password):
	_port(Server::_checkPort(port)),
	_password(Server::_checkPassword(password)),
	_serverSocket()
{
	this->_clients.setDeleteOnRemove(true);
	this->_initCmds();
	if (DEBUG)
		std::cout << Txt::FAINT << "Server " << *this << " created." << Txt::RESET << std::endl;
	return ;
}

Server::Server(std::string portToken, std::string password):
	_port(Server::_stringToPort(portToken)),
	_password(Server::_checkPassword(password)),
	_serverSocket()
{
	this->_clients.setDeleteOnRemove(true);
	this->_initCmds();
	if (DEBUG)
		std::cout << Txt::FAINT << "Server " << *this << " created (tokens)." << Txt::RESET << std::endl;
	return ;
}

Server::~Server(void)
{
	if (DEBUG)
		std::cout << Txt::FAINT << "Server " << *this << " destroyed." << Txt::RESET << std::endl;
	return ;
}


// Getters
// ==========================================================================

int const &	Server::getPort(void) const
{
	return (this->_port);
}

std::string const &	Server::getPassword(void) const
{
	return (this->_password);
}

ClientList const &	Server::getClients(void) const
{
	return (this->_clients);
}

std::map<std::string, Channel*> const &	Server::getChannels(void) const
{
	return (this->_channels);
}


// Non-member functions
// ==========================================================================

int const &	Server::_checkPort(int const & port)
{
	if (port < 0 || port > 65535) {
		throw Server::InvalidPortException();
	}
	return (port);
}

std::string const &	Server::_checkPassword(std::string const & password)
{
	if (password.size() < 8) {
		throw Server::InvalidPasswordException();
	}
	return (password);
}

int	Server::_stringToPort(std::string const & token)
{
	if (token.empty() || token.size() > 5) {
		throw Server::InvalidPortException();
	}
	
	for (size_t i = 0; i < token.size(); i++) {
		if (!isdigit(token[i])) {
			throw Server::InvalidPortException();
		}
	}
	
	int port = atoi(token.c_str());
	return (Server::_checkPort(port));
}


// Member functions
// ==========================================================================

void	Server::_addPollfd(int fd)
{
	pollfd clientPollfd;
	clientPollfd.fd = fd;
	clientPollfd.events = POLLIN;
	clientPollfd.revents = 0;
	this->_pollfds.push_back(clientPollfd);
}

void	Server::_removePollfd(int fd)
{
	std::vector<pollfd>::iterator it, begin, end;
	begin = this->_pollfds.begin();
	end = this->_pollfds.end();
	for (it = begin; it != end; it++) {
		if (it->fd == fd) {
			close(it->fd);
			this->_pollfds.erase(it);
			break ;
		}
	}
}

void	Server::_handleNewConnection(void)
{
	// accept connection from an incoming client
	sockaddr_in clientAddr;
	socklen_t clientAddrSize = sizeof(clientAddr);
	int clientSocket = accept(this->_serverSocket, reinterpret_cast<sockaddr*>(&clientAddr), &clientAddrSize);
	if (clientSocket == -1) {
		throw std::runtime_error("accept client failed");
	}
	
	// check if client socket already exists
	if (this->_clients.get(clientSocket)) {
		throw std::runtime_error("client fd already exists");
	}
	
	// set the client socket to non-blocking mode
	int flags = fcntl(clientSocket, F_GETFL, 0);
	fcntl(clientSocket, F_SETFL, flags | O_NONBLOCK);

	// add client socket to pollfd array
	Server::_addPollfd(clientSocket);
	
	// get client ip and port
    getsockname(clientSocket, reinterpret_cast<struct sockaddr*>(&clientAddr), &clientAddrSize);
	std::string clientHost = inet_ntoa(clientAddr.sin_addr);

	// add client to client list
	Client* client = new Client(clientSocket, clientHost);
	this->_clients.add(client);
	
	std::cout << "New client connected" << std::endl;
}

void	Server::_deleteClient(int fd)
{
	close(fd);
	Server::_removePollfd(fd);
	this->_clients.remove(fd);
}

void	Server::_handleClientInput(int fd)
{
	// read data sent by client
	char buffer[1024];
	int ret = recv(fd, buffer, sizeof(buffer), 0);
	if (ret <= 0) {
		Server::_deleteClient(fd);
		std::cout << "Client disconnected" << std::endl;
		return ;
	}
	buffer[ret] = '\0';

	// add to client buffer
	Client* client = this->_clients.get(fd);
	if (!client) {
		throw std::runtime_error("client not found");
	}
	client->addToBuffer(buffer);
	
	// parse and execute commands
	std::string msg = client->extractMessage();
	while (!msg.empty()) {
		this->_executeCommand(Command(msg), *client);
		msg = client->extractMessage();
	}
}

void	Server::_initCmds(void)
{
	this->_cmds["PASS"] = &Server::_pass;
	this->_cmds["NICK"] = &Server::_nick;
	this->_cmds["USER"] = &Server::_user;
}

void	Server::_executeCommand(Command const & cmd, Client & client)
{
	std::map<std::string, cmdFn>::iterator it = this->_cmds.find(cmd.getCommand());
	if (it == this->_cmds.end()) {
		// todo: reply ERR_UNKNOWNCOMMAND
		return ;
	}
	
	cmdFn fn = it->second;
	(this->*fn)(client, cmd.getParameters());
}

void	Server::start(void)
{
	const char			*proto_name = "tcp";
	struct protoent		*pe;

	if ((pe = getprotobyname(proto_name)) == NULL) {
		// todo: reset server
		throw std::runtime_error("Error getting protocol name");
	}

	// Socket creation
	this->_serverSocket = socket(PF_INET, SOCK_STREAM, pe->p_proto);
	if ( this->_serverSocket == -1 ) {
		// todo: reset server
		close(this->_serverSocket);
		throw std::runtime_error("Error: creating socket");
	}

	int sockopt = 1; // Enable SO_REUSEADDR and SO_REUSEPORT
	if ( setsockopt( this->_serverSocket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT , &sockopt, sizeof( sockopt ) ) < 0 ) // allows to reuse server address nd port after close (protect bind from crash)
	{
		// todo: reset server
		close(this->_serverSocket);
		throw std::runtime_error("Error: setting socket options");
	}

	// Struct sockaddr initialization
	struct sockaddr_in	sa = {};
	sa.sin_family = PF_INET; // IPv4 format
	sa.sin_port = htons( _port ); // Convert port
	sa.sin_addr.s_addr = INADDR_ANY; // Bind to any available interface

	// Binding of server socket
	if ( bind( this->_serverSocket, reinterpret_cast<struct sockaddr *>( &sa ), sizeof( sa ) ) < 0 )
	{
		// todo: reset server
		close(this->_serverSocket);
		throw std::runtime_error("Error: binding server socket");
	}

	// Listening
	if ( listen( this->_serverSocket, SOMAXCONN ) < 0 ) // SOMAXCONN = constant representing the max size of the backlog
	{
		// todo: reset server
		close(this->_serverSocket);
		throw std::runtime_error("Error: listening");
	}
	
	// Including server socket
	Server::_addPollfd(this->_serverSocket);

	std::cout << "Server is listening on port " << this->_port << std::endl;
	
	while (true)
	{
		// poll for events
		int ret = poll(this->_pollfds.data(), this->_pollfds.size(), -1);
		if (ret < 0) {
			// todo: reset server
			throw std::runtime_error("Error: poll failed");
		}

		// check new connection request
		if (this->_pollfds[0].revents & POLLIN) {
			Server::_handleNewConnection();
		}

		// handle client inputs
		for (size_t i = 1; i < this->_pollfds.size(); i++) {
			if (this->_pollfds[i].revents & POLLIN) {
				Server::_handleClientInput(this->_pollfds[i].fd);
			}
		}
	}
	std::cout << "End of loop" << std::endl;
	close(this->_serverSocket);
}

void	Server::addChannel(Channel* channel)
{
	if (!channel) {
		return ;
	}

	std::map<std::string, Channel*>::iterator it = this->_channels.find(channel->getName());
	if (it == this->_channels.end()) {
		this->_channels[channel->getName()] = channel;
	}
}

void	Server::deleteChannel(std::string name)
{
	std::map<std::string, Channel*>::iterator it = this->_channels.find(name);
	if (it == this->_channels.end()) {
		return ;
	}
	delete it->second;
	this->_channels.erase(it);
}

Channel*	Server::getChannel(std::string const & name) const
{
	std::map<std::string, Channel*>::const_iterator	it, end;
	it = this->_channels.find(name);
	end = this->_channels.end();

	if (it == end) {
		return (NULL);
	}
	return (it->second);
}

void	Server::printChannels(void) const
{
	std::cout << this->_channels.size() << " channel(s)"<< std::endl;
	if (this->_channels.empty()) {
		return ;
	}
	
	std::map<std::string, Channel*>::const_iterator	it, begin, end;
	begin = this->_channels.begin();
	end = this->_channels.end();
	
	for (it = begin; it != end; it++) {
		std::cout << "Channel " << it->first << ": ";
		if (it->second) {
			std::cout << *(it->second);
		} else {
			std::cout << "NULL";
		}
		std::cout << std::endl;
	}
}


// Commands
// ==========================================================================

void	Server::_pass(Client & client, std::vector<std::string> const & params)
{
	std::cout << "Client " << client.getFd() << ": PASS ";
	for (size_t i = 0; i < params.size(); i++) {
		std::cout << params[i] << " ";
	}
	std::cout << std::endl;
}

void	Server::_nick(Client & client, std::vector<std::string> const & params)
{
	std::cout << "Client " << client.getFd() << ": NICK ";
	for (size_t i = 0; i < params.size(); i++) {
		std::cout << params[i] << " ";
	}
	std::cout << std::endl;
}

void	Server::_user(Client & client, std::vector<std::string> const & params)
{
	std::cout << "Client " << client.getFd() << ": USER ";
	for (size_t i = 0; i < params.size(); i++) {
		std::cout << params[i] << " ";
	}
	std::cout << std::endl;
}


// Output stream
// ==========================================================================

std::ostream &	operator<<(std::ostream & o, Server const & x)
{
	o << "{";
	o << "port: " << x.getPort();
	o << ", ";
	o << "password: \"" << x.getPassword() << "\"";
	o << ", ";
	o << "clients: " << x.getClients().size();
	o << "}";
	return (o);
}