/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaxime- <mmaxime-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 15:52:31 by dapereir          #+#    #+#             */
/*   Updated: 2023/11/25 16:51:27 by mmaxime-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

volatile int Server::receivedSignal = 0;

// Constructors & destructor
// ==========================================================================

Server::Server(int port, std::string password):
	_port(Server::_checkPort(port)),
	_password(Server::_checkPassword(password)),
	_serverSocket()
{
	this->_clients.setDeleteOnRemove(true);
	this->_channels.setDeleteOnRemove(true);
	this->_initCmds();
	Log::debug("Server created: " + stringify(*this));
	return ;
}

Server::Server(std::string portToken, std::string password):
	_port(Server::_stringToPort(portToken)),
	_password(Server::_checkPassword(password)),
	_serverSocket()
{
	this->_clients.setDeleteOnRemove(true);
	this->_channels.setDeleteOnRemove(true);
	this->_initCmds();
	Log::debug("Server created: " + stringify(*this));
	return ;
}

Server::~Server(void)
{
	Log::debug("Server destroyed");
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

ChannelList const &	Server::getChannels(void) const
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
	
	for (size_t i = 0; i < token.size(); ++i) {
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
	std::vector<pollfd>::iterator it;
	for (it = this->_pollfds.begin(); it != this->_pollfds.end(); ++it) {
		if (it->fd == fd) {
			close(it->fd);
			this->_pollfds.erase(it);
			return ;
		}
	}
}

void	Server::_handleNewConnection(void)
{
	int clientSocket = -1;
	try {
		
		// accept connection from an incoming client
		sockaddr_in clientAddr;
		memset(&clientAddr, 0, sizeof(clientAddr));
		socklen_t clientAddrSize = sizeof(clientAddr);
		clientSocket = accept(this->_serverSocket, reinterpret_cast<sockaddr*>(&clientAddr), &clientAddrSize);
		if (clientSocket == -1) {
			throw std::runtime_error("accept failed");
		}
		
		// check if client socket already exists
		if (this->_clients.get(clientSocket)) {
			throw std::runtime_error("client socket already exists");
		}
		
		// set the client socket to non-blocking mode
		fcntl(clientSocket, F_SETFL, O_NONBLOCK);

		// add client socket to pollfd array
		Server::_addPollfd(clientSocket);

		// check if max clients is reached
		if (this->_clients.size() >= MAX_CLIENTS) {
			this->_reply(clientSocket, RPL_ERROR("Connection limit reached"));
			Server::_removePollfd(clientSocket);
			throw Server::MaxClientsReachedException();
		}
		
		// get client ip and port
		getsockname(clientSocket, reinterpret_cast<struct sockaddr*>(&clientAddr), &clientAddrSize);
		std::string clientHost = inet_ntoa(clientAddr.sin_addr);
		if (clientHost == "127.0.0.1") {
			clientHost = "localhost";
		}

		// add client to client list
		Client* client = new Client(clientSocket, clientHost);
		this->_clients.add(client);
		
		Log::info("Accepted connection from " + clientHost + ":" + stringify(this->_port) + \
			" on socket " + stringify(clientSocket));
	} catch(Server::MaxClientsReachedException & e) {
		Log::error("New connection refused on socket " + stringify(clientSocket) + ": " + std::string(e.what()));
	} catch(std::exception & e) {
		Log::error("New connection failed: " + std::string(e.what()));
	}
}

void	Server::_deleteClient(int fd)
{
	// close socket
	close(fd);

	// delete pollfd
	Server::_removePollfd(fd);

	Client* client = this->_clients.get(fd);
	if (client) {
	
		// for each channel
		ChannelList::iterator it = this->_channels.begin();
		while (it != this->_channels.end()) {
			Channel* channel = it->second;
			it++;

			// remove client link
			channel->removeClientLink(client);

			// delete channel if empty
			if (channel->getMemberCount() == 0) {
				this->_channels.remove(channel->getName());
			}
		}

		// delete client
		this->_clients.remove(fd);
	}
}

void	Server::_handleClientInput(Client & client)
{
	int fd = client.getFd();

	try {

		// read data sent by client
		char buffer[1024];
		int ret = recv(fd, buffer, sizeof(buffer), 0);
		if (ret <= 0) {
			throw Server::ConnectionException("Client disconnected");
		}
		buffer[ret] = '\0';

		// add to client buffer
		client.addToBuffer(buffer);
		
		// parse and execute commands
		std::string msg;
		while (client.extractMessage(msg)) {
			Log::input(fd, msg);
			this->_executeCommand(Command(msg), client);
		}

	} catch(Command::EmptyMessageException &) {
	} catch(Server::ConnectionException &) {
		throw;
	} catch(std::exception & e) {
		Log::error("Handling client input (socket " + stringify(fd) + ") failed: " + e.what());
	}
}

void	Server::_initCmds(void)
{
	this->_cmds["PASS"] = &Server::_pass;
	this->_cmds["NICK"] = &Server::_nick;
	this->_cmds["USER"] = &Server::_user;
	this->_cmds["MODE"] = &Server::_mode;
	this->_cmds["MOTD"] = &Server::_motd;
	this->_cmds["OPER"] = &Server::_oper;
	this->_cmds["PING"] = &Server::_ping;
	this->_cmds["PONG"] = &Server::_pong;
	this->_cmds["PRIVMSG"] = &Server::_privmsg;
	this->_cmds["JOIN"] = &Server::_join;
	this->_cmds["PART"] = &Server::_part;
	this->_cmds["INVITE"] = &Server::_invite;
	this->_cmds["TOPIC"] = &Server::_topic;
	this->_cmds["NAMES"] = &Server::_names;
	this->_cmds["KICK"] = &Server::_kick;
	this->_cmds["KILL"] = &Server::_kill;
	this->_cmds["QUIT"] = &Server::_quit;
}

void	Server::_executeCommand(Command const & cmd, Client & client)
{
	try {
		std::map<std::string, cmdFn>::iterator it = this->_cmds.find(cmd.getCommand());
		if (it == this->_cmds.end()) {
			throw Server::ErrException(ERR_UNKNOWNCOMMAND(client.getNickname(), cmd.getCommand()));
		}

		// during registration process, only PASS NICK USER are accepted
		bool isRegistrationCommand = cmd.getCommand() == "PASS" || cmd.getCommand() == "NICK" || cmd.getCommand() == "USER";
		if (!client.getIsRegistered() && !isRegistrationCommand) {
			throw Server::ErrException(ERR_NOTREGISTERED(client.getNickname()));
		}
		
		// process command
		cmdFn fn = it->second;
		(this->*fn)(client, cmd.getParameters());

		// check if registration is complete
		if (!client.getIsRegistered()) {
			this->_checkRegistration(client);
		}

	} catch(Server::ErrException & e) {
		client.reply(e.what());
	} catch(std::exception &) {
		throw;
	}
}

void	Server::_checkRegistration(Client & client)
{
	bool isRegistered = client.getIsPasswordValid() && client.getNickname() != "*" && !client.getUsername().empty();
	client.setIsRegistered(isRegistered);
	
	if (isRegistered) {
		Log::info("User \"" + client.getNickname() + "!" + client.getUsername() + "@" + client.getHostname() + "\" registered" + \
			" (socket " + stringify(client.getFd()) + ")");

		std::string messages;
		messages += RPL_WELCOME(client.getNickname(), client.getUsername(), client.getHostname());
		messages += RPL_YOURHOST(client.getNickname(), HOST, VERSION);
		messages += RPL_CREATED(client.getNickname(), formatTime(this->_startTime));
		messages += RPL_MYINFO(client.getNickname(), HOST, VERSION, USERMODES, CHANNELMODES);
		messages += Server::_motdMsg(client);
		client.reply(messages);
	}
}

bool	Server::_isRegistrationTimedOut(Client & client) const
{
	if (client.getIsRegistered()) {
		return (false);
	}
	time_t const & currentTime = time(NULL);
	time_t const & connectTime = client.getConnectTime();
	return (currentTime - connectTime > REGISTRATION_TIMEOUT);
}

void	Server::_reply(int fd, std::string const & msg) const
{
	if (fd == -1) {
		return ;
	}

	Log::output(fd, msg);
	send(fd, msg.c_str(), msg.size(), 0);
}

void	Server::start(void)
{
	Log::info("Starting " + Txt::BOLD + stringify(HOST) + Txt::RESET + "...");

	const char			*proto_name = "tcp";
	struct protoent		*pe;

	try {
		if ((pe = getprotobyname(proto_name)) == NULL) {
			throw Server::ServerException("Getting protocol name");
		}

		// Socket creation
		this->_serverSocket = socket(PF_INET, SOCK_STREAM, pe->p_proto);
		if (this->_serverSocket == -1) {
			throw Server::ServerException("Creating server socket");
		}

		int sockopt = 1; // Enable SO_REUSEADDR and SO_REUSEPORT
		if (setsockopt(this->_serverSocket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT , &sockopt, sizeof(sockopt)) < 0) {
			throw Server::ServerException("Setting socket options");
		}

		// Struct sockaddr initialization
		struct sockaddr_in	sa;
		memset(&sa, 0, sizeof(sa));
		sa.sin_family = PF_INET; // IPv4 format
		sa.sin_port = htons(_port); // Convert port
		sa.sin_addr.s_addr = INADDR_ANY; // Bind to any available interface

		// Binding of server socket
		if (bind(this->_serverSocket, reinterpret_cast<struct sockaddr *>(&sa), sizeof(sa)) < 0) {
			throw Server::ServerException("Binding server socket");
		}

		// Listening
		if (listen(this->_serverSocket, SOMAXCONN) < 0) {
			throw Server::ServerException("Listening");
		}
		
		// Including server socket
		Server::_addPollfd(this->_serverSocket);

		// Update start time
		std::time(&(this->_startTime));

		Log::info("Listening on 0.0.0.0:" + stringify(this->_port) + " (socket " + stringify(this->_serverSocket) + ")");
		
		while (true)
		{
			// poll for events
			int ret = poll(this->_pollfds.data(), this->_pollfds.size(), POLL_INTERVAL);
			
			if (receivedSignal == SIGINT || receivedSignal == SIGQUIT || receivedSignal == SIGTERM) {
				break;
			}

			if (ret < 0) {
				throw Server::ServerException("Polling");
			}

			// check new connection request
			if (this->_pollfds[0].revents & POLLIN) {
				Server::_handleNewConnection();
			}

			// handle client inputs
			size_t i = 1;
			while (i < this->_pollfds.size()) {
				int fd = this->_pollfds[i].fd;
				short revents = this->_pollfds[i].revents;
				Client* client = this->_clients.get(fd);
				
				try {
				
					if (!client) {
						throw std::runtime_error("Client not found");
					}
					
					// handle client inputs
					if (revents & POLLIN) {
						Server::_handleClientInput(*client);
					}
			
					// handle registration client timeout
					if (this->_isRegistrationTimedOut(*client)) {
						throw Server::ConnectionException("Registration has timed out");
					}

					++i;
					
				} catch (Server::ConnectionException & e) {
					std::string logMsg;
					logMsg += "Connection stopped";
					if (client && client->getIsRegistered()) {
						logMsg += " with \"" + client->getNickname() + "!" + client->getUsername() + "@" + client->getHostname() + "\"";
					}
					logMsg += " (socket " + stringify(fd) + ")";
					logMsg += ": " + std::string(e.what());
					Log::info(logMsg);
					this->_deleteClient(fd);
				}
			}
		}
	}
	catch (Server::ServerException & e) {
		std::cerr << "Error: " << e.what() << std::endl;
		Server::stop(false);
	}
	Server::stop(true);

}

void	Server::stop(bool isSuccess)
{
	// To send message to clients
	for(std::map<int, Client*>::const_iterator it = this->_clients.getClients().begin(); it != this->_clients.getClients().end(); ++it) {
		this->_reply(it->second->getFd(), RPL_ERROR("Closing Link: " + it->second->getHostname() + " (Server shutdown): " + (isSuccess ? "Closed by host" : "Fatal error")));
	}
	
	// To close and clear the clients list and server properly
	for(size_t i = 0; i < this->_pollfds.size(); ++i) {
		ChannelList::iterator it = this->_channels.begin();
		while (it != this->_channels.end()) {
			Channel*  channel = it->second;
			it++;
			if (channel->isJoined(this->_clients.get(this->_pollfds[i].fd))) {
				channel->removeClientLink(this->_clients.get(this->_pollfds[i].fd));
				if (channel->getMemberCount() == 0) {
					this->_channels.remove(channel->getName());
				}
			}
		}
		close(this->_pollfds[i].fd);
	}
	this->_pollfds.clear();
	this->_clients.clear();
	this->_channels.clear();

	std::string logMsg = "Server stopped: ";
	if (isSuccess) {
		logMsg += "Closed by host";
	} else {
		logMsg += "Fatal error";
	}
	Log::info(logMsg);
	
	// to restore default signal handling
	std::signal(SIGINT, SIG_DFL);
	std::signal(SIGQUIT, SIG_DFL);
	std::signal(SIGTERM, SIG_DFL);
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
	o << x.getClients().size() << " clients";
	o << ", ";
	o << x.getChannels().size() << " channels";
	o << "}";
	return (o);
}