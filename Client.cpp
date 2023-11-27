/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 14:58:27 by dapereir          #+#    #+#             */
/*   Updated: 2023/11/27 15:09:29 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"


// Constructors & destructor
// ==========================================================================

Client::Client(int fd, std::string hostname):
	_fd(fd),
	_connectTime(time(NULL)),
	_bufferIn(""),
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

std::string const &	Client::getBufferIn(void) const
{
	return (this->_bufferIn);
}

std::string const &	Client::getBufferOut(void) const
{
	return (this->_bufferOut);
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

void	Client::setBufferIn(std::string const & str)
{
	this->_bufferIn = str;
}

void	Client::setBufferOut(std::string const & str)
{
	this->_bufferOut = str;
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

void	Client::addToBufferIn(std::string const & str)
{
	this->_bufferIn += str;
}

bool	Client::extractMessage(std::string & dest)
{
	size_t lfPos = this->_bufferIn.find("\n");
	if (lfPos == std::string::npos)
		return (false);

	bool isCRLF = (lfPos > 0 && this->_bufferIn[lfPos - 1] == '\r');
	size_t endlinePos = isCRLF ? lfPos - 1 : lfPos;
	size_t endlineLen = isCRLF ? 2 : 1;

	std::string message = this->_bufferIn.substr(0, endlinePos);
	this->_bufferIn = this->_bufferIn.substr(endlinePos + endlineLen, this->_bufferIn.size());
	dest = message;
	return (true);
}

std::string	Client::getHostmask(void) const
{
	return (this->_nickname + "!" + this->_username + "@" + this->_hostname);
}

void	Client::reply(std::string const & msg)
{
	Log::output(this->_fd, msg);
	this->_bufferOut += msg;
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
