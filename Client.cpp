/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaxime- <mmaxime-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 14:58:27 by dapereir          #+#    #+#             */
/*   Updated: 2023/11/23 17:36:00 by mmaxime-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"


// Constructors & destructor
// ==========================================================================

Client::Client(int fd, std::string hostname):
	_fd(fd),
	_connectTime(time(NULL)),
	_buffer(""),
	_hostname(hostname),
	_nickname("*"),
	_username(""),
	_realname(""),
	_mode("+"),
	_isPasswordValid(false),
	_isRegistered(false),
	_isOper(false)
{
	Log::debug("Client " + stringify(this->_fd) + " created");
	return ;
}

Client::~Client(void)
{
	Log::debug("Client " + stringify(this->_fd) + " destroyed");
	return ;
}


// Getters
// ==========================================================================

int const &	Client::getFd(void) const
{
	return (this->_fd);
}

time_t const &	Client::getConnectTime(void) const
{
	return (this->_connectTime);
}

std::string const &	Client::getBuffer(void) const
{
	return (this->_buffer);
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

std::string const &	Client::getMode(void) const
{
	return (this->_mode);
}

bool const &	Client::getIsPasswordValid(void) const
{
	return (this->_isPasswordValid);
}

bool const &	Client::getIsRegistered(void) const
{
	return (this->_isRegistered);
}

bool const &	Client::getIsOper(void) const
{
	return (this->_isOper);
}


// Setters
// ==========================================================================

void	Client::setBuffer(std::string const & str)
{
	this->_buffer = str;
}

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

void	Client::setMode(std::string const & mode)
{
	this->_mode = mode;
}

void	Client::setIsPasswordValid(bool const & isPasswordValid)
{
	this->_isPasswordValid = isPasswordValid;
}

void	Client::setIsRegistered(bool const & isRegistered)
{
	this->_isRegistered = isRegistered;
}

void	Client::setIsOper(bool const & isOper)
{
	this->_isOper = isOper;
}

// Member functions
// ==========================================================================

void	Client::addToBuffer(std::string const & str)
{
	this->_buffer += str;
}

bool	Client::extractMessage(std::string & dest)
{
	size_t separatorPos = this->_buffer.find("\r\n");
	if (separatorPos == std::string::npos)
		return (false);

	std::string message = this->_buffer.substr(0, separatorPos);
	this->_buffer = this->_buffer.substr(separatorPos + 2, this->_buffer.size());
	dest = message;
	return (true);
}

std::string	Client::getHostmask(void) const
{
	return (this->_nickname + "!" + this->_username + "@" + this->_hostname);
}

void	Client::reply(std::string const & msg) const
{
	Log::output(this->_fd, msg);
	send(this->_fd, msg.c_str(), msg.size(), 0);
}

void	Client::unsetMode(char mode)
{
	std::string::size_type pos = this->_mode.find(mode);
	if (pos != std::string::npos)
		this->_mode.erase(pos, 1);
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
