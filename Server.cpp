/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 15:52:31 by dapereir          #+#    #+#             */
/*   Updated: 2023/10/13 11:49:47 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"


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
	_password(Server::_checkPassword(password))
{
	this->_clients.setDeleteOnRemove(true);
	if (DEBUG)
		std::cout << Txt::FAINT << "Server " << *this << " created." << Txt::RESET << std::endl;
	return ;
}

Server::Server(std::string portToken, std::string password):
	_port(Server::_stringToPort(portToken)),
	_password(Server::_checkPassword(password))
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