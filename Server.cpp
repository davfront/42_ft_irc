/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 15:52:31 by dapereir          #+#    #+#             */
/*   Updated: 2023/10/05 11:15:10 by dapereir         ###   ########.fr       */
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
	if (DEBUG)
		std::cout << Txt::FAINT << "Server " << *this << " created." << Txt::RESET << std::endl;
	return ;
}

Server::Server(std::string portToken, std::string password):
	_port(Server::_stringToPort(portToken)),
	_password(Server::_checkPassword(password))
{
	if (DEBUG)
		std::cout << Txt::FAINT << "Server " << *this << " created (tokens)." << Txt::RESET << std::endl;
	return ;
}

Server::Server(Server const & src):
	_port(src.getPort()),
	_password(src.getPassword())
{
	if (DEBUG)
		std::cout << Txt::FAINT << "Server " << *this << " created (copy)." << Txt::RESET << std::endl;
	return ;
}

Server::~Server(void)
{
	if (DEBUG)
		std::cout << Txt::FAINT << "Server " << *this << " destroyed." << Txt::RESET << std::endl;
	return ;
}


// Assignment operator
// ==========================================================================

Server &	Server::operator=(Server const & rhs)
{
	if (this != &rhs) {
		this->_port = rhs.getPort();
		this->_password = rhs.getPassword();
	}
	return (*this);
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


// Output stream
// ==========================================================================

std::ostream &	operator<<(std::ostream & o, Server const & x)
{
	o << "{";
	o << "port: " << x.getPort();
	o << ", ";
	o << "password: \"" << x.getPassword() << "\"";
	o << "}";
	return (o);
}
