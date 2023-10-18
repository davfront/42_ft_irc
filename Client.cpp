/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 14:58:27 by dapereir          #+#    #+#             */
/*   Updated: 2023/10/15 14:39:40 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"


// Constructors & destructor
// ==========================================================================

Client::Client(int fd, std::string hostname):
	_fd(fd),
	_hostname(hostname),
	_nickname(""),
	_username(""),
	_realname(""),
	_isOper(false),
	_buffer("")
{
	if (DEBUG)
		std::cout << Txt::FAINT << "Client " << *this << " created." << Txt::RESET << std::endl;
	return ;
}

Client::~Client(void)
{
	if (DEBUG)
		std::cout << Txt::FAINT << "Client " << *this << " destroyed." << Txt::RESET << std::endl;
	return ;
}


// Getters
// ==========================================================================

int const &	Client::getFd(void) const
{
	return (this->_fd);
}

std::string const &	Client::getHostname(void) const
{
	return (this->_hostname);
}

std::string const &	Client::getNickname(void) const
{
	return (this->_nickname);
}

std::string const &	Client::getUsername(void) const
{
	return (this->_username);
}

std::string const &	Client::getRealname(void) const
{
	return (this->_realname);
}

bool const &	Client::getIsOper(void) const
{
	return (this->_isOper);
}

std::string const &	Client::getBuffer(void) const
{
	return (this->_buffer);
}


// Setters
// ==========================================================================

void	Client::setHostname(std::string const & hostname)
{
	this->_hostname = hostname;
}

void	Client::setNickname(std::string const & nickname)
{
	this->_nickname = nickname;
}

void	Client::setUsername(std::string const & username)
{
	this->_username = username;
}

void	Client::setRealname(std::string const & realname)
{
	this->_realname = realname;
}

void	Client::setIsOper(bool const & isOper)
{
	this->_isOper = isOper;
}

void	Client::setBuffer(std::string const & str)
{
	this->_buffer = str;
}


// Member functions
// ==========================================================================

void	Client::addToBuffer(std::string const & str)
{
	this->_buffer += str;
}

std::string	Client::extractMessage(void)
{
	size_t separatorPos = this->_buffer.find("\r\n");
	if (separatorPos == std::string::npos)
		return ("");

	std::string message = this->_buffer.substr(0, separatorPos);
	this->_buffer = this->_buffer.substr(separatorPos + 2, this->_buffer.size());
	return (message);
}


// Output stream
// ==========================================================================

std::ostream &	operator<<(std::ostream & o, Client const & x)
{
	o << "{";
	o << "fd: " << x.getFd();
	o << ", ";
	o << "host: \"" << x.getHostname() << "\"";
	o << ", ";
	o << "nick: \"" << x.getNickname() << "\"";
	o << ", ";
	o << "user: \"" << x.getUsername() << "\"";
	o << ", ";
	o << "isOper: " << (x.getIsOper() ? "true": "false");
	o << "}";
	return (o);
}
