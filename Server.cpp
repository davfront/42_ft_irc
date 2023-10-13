/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 15:52:31 by dapereir          #+#    #+#             */
/*   Updated: 2023/10/13 12:28:02 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

const int	max_clients = 10;

// Non-member functions (private)
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


// Constructors & destructor
// ==========================================================================

Server::Server(int port, std::string password):
	_port(Server::_checkPort(port)),
	_password(Server::_checkPassword(password)),
	_server_socket()
{
	this->_clients.setDeleteOnRemove(true);
	if (DEBUG)
		std::cout << Txt::FAINT << "Server " << *this << " created." << Txt::RESET << std::endl;
	return ;
}

Server::Server(std::string portToken, std::string password):
	_port(Server::_stringToPort(portToken)),
	_password(Server::_checkPassword(password)),
	_server_socket()
{
	this->_clients.setDeleteOnRemove(true);
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


// Member functions (public)
// ==========================================================================

int		Server::init()
{
	struct sockaddr_in	sa = {};
	const char			*proto_name = "tcp";
	struct protoent		*pe;
	int					sockopt;

	if ((pe = getprotobyname(proto_name)) == NULL)
	{
		perror( "Error getting protocol name" ); // à changer par une fonction qui close proprement, en utilisant "errno"
		return ( 1 );
	}

	// Socket creation

	_server_socket = socket(PF_INET, SOCK_STREAM, pe->p_proto);
	if ( _server_socket == -1 )
	{
		perror( "Error: creating socket" );
		close(_server_socket);
		return ( 2 );
	}

	sockopt = 1; // Enable SO_REUSEADDR and SO_REUSEPORT
	if ( setsockopt( _server_socket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT , &sockopt, sizeof( sockopt ) ) < 0 ) // allows to reuse server address nd port after close (protect bind from crash)
	{
		perror( "Error: setting socket options" );
		close(_server_socket);
		return ( 3 );
	}

	// Struct sockaddr initialization

	sa.sin_family = PF_INET; // IPv4 format
	sa.sin_port = htons( _port ); // Convert port
	sa.sin_addr.s_addr = INADDR_ANY; // Bind to any available interface

	// Binding of server socket

	if ( bind( _server_socket, reinterpret_cast<struct sockaddr *>( &sa ), sizeof( sa ) ) < 0 )
	{
		perror("Error: binding server socket");
		close( _server_socket );
		return ( 4 );
	}

	// Listening

	if ( listen( _server_socket, SOMAXCONN ) < 0 ) // SOMAXCONN = constant representing the max size of the backlog
	{
		std::cerr << "Error: listening" << std::endl;
		close( _server_socket );
		return ( 5 );
	}

	// Creating a pollfd array ===> à voir pour mettre dans main

		// Array of pollfd structs to monitor sockets
	std::vector<struct pollfd> fds( max_clients + 1 ); // including server socket, max_clients à remplacer par size ClientList + 2
	fds[0].fd = _server_socket;
	fds[0].events = POLLIN; // Monitor for incoming connections

		// Initialize other fds entries
	for( int i = 1; i <= max_clients; ++i ) // remplacer par un iterator
	{
		fds[i].fd = -1; // -1 indicates unused
	}
	std::cout << "Server is listening on port " << port << std::endl;
	
	while ( true )
	{
		int ret = poll( fds.data(), fds.size(), -1 );
		if ( ret < 0 )
		{
			perror("Error: poll failed");
			break ;
		}
		for ( size_t i = 0; i < fds.size(); ++i )
		{
			if ( fds[i].revents & POLLIN )
			{
				if ( fds[i].fd == _server_socket )
				{
					// new connection request ====> à voir si on crée une fonction 'accept'
					int client_socket = accept( _server_socket, nullptr, nullptr ); // créer une nvelle struct sockaddr_in pour remplacer les nullptr
					if ( client_socket < 0 )
						std::cerr << "Error: accept failed" << std::endl;
					else
					{
						// set the client socket to non-blocking mode
						int flags = fcntl( client_socket, F_GETFL, 0 ); // to get a new flag to set
						fcntl( client_socket, F_SETFL, flags | O_NONBLOCK );

						std::cout << "New client connected" << std::endl;

						// find an empty slot in the fds array to store the client socket
						for ( size_t j = 1; j < fds.size(); ++j )
						{
							if ( fds[j].fd == -1 )
							{
								fds[j].fd = client_socket;
								fds[j].events = POLLIN;
								break ;
							}
						}
					}
				}
				else
				{
					// data available to read from a client socket
					char buffer[1024];
					int ret = recv( fds[i].fd, buffer, sizeof( buffer ), 0 );
					if ( ret <= 0 )
					{
						// connection closed or error
						close( fds[i].fd );
						fds[i].fd = -1;
						std::cout << "Client disconnected" << std::endl;
					}
					else
					{
						buffer[ret] = '\0';
						// là où il faudra checker le buffer et lancer une cmd si nécessaire
						std::string	msg( buffer );
						std::cout << "Client " << i << ": " << msg << std::endl;
					}
				}
			}
		}
	}
	std::cout << "End of loop" << std::endl;
	close( server_socket );
	return (0);
}

void	Server::addClient(Client* client)
{
	this->_clients.add(client);
}

void	Server::removeClient(int fd)
{
	this->_clients.remove(fd);
}

Client*	Server::getClient(int const & fd) const
{
	return (this->_clients.get(fd));
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