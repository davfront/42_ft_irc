/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 14:58:27 by dapereir          #+#    #+#             */
/*   Updated: 2023/10/06 21:02:10 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"


// Constructors & destructor
// ==========================================================================

Client::Client(void): _fd(-1)
{
	return ;
}

Client::Client(int fd, std::string nickname, std::string username, std::string realname, bool isOper):
	_fd(fd),
	_nickname(nickname),
	_username(username),
	_realname(realname),
	_isOper(isOper)
{
	if (DEBUG)
		std::cout << Txt::FAINT << "Client " << *this << " created." << Txt::RESET << std::endl;
	return ;
}

Client::Client(Client const & src):
	_fd(src.getFd()),
	_nickname(src.getNickname()),
	_username(src.getUsername()),
	_realname(src.getRealname()),
	_isOper(src.getIsOper())
{
	if (DEBUG)
		std::cout << Txt::FAINT << "Client " << *this << " created (copy)." << Txt::RESET << std::endl;
	return ;
}

Client::~Client(void)
{
	if (DEBUG)
		std::cout << Txt::FAINT << "Client " << *this << " destroyed." << Txt::RESET << std::endl;
	return ;
}


// Assignment operator
// ==========================================================================

Client &	Client::operator=(Client const & rhs)
{
	if (this != &rhs) {
		this->_nickname = rhs.getNickname();
		this->_username = rhs.getUsername();
		this->_realname = rhs.getRealname();
		this->_isOper = rhs.getIsOper();
	}
	return (*this);
}


// Getters
// ==========================================================================

int const &	Client::getFd(void) const
{
	return (this->_fd);
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


// Setters
// ==========================================================================

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


// Output stream
// ==========================================================================

std::ostream &	operator<<(std::ostream & o, Client const & x)
{
	o << "{";
	o << "fd: " << x.getFd();
	o << ", ";
	o << "nick: \"" << x.getNickname() << "\"";
	o << ", ";
	o << "user: \"" << x.getUsername() << "\"";
	o << ", ";
	o << "isOper: " << (x.getIsOper() ? "true": "false");
	o << "}";
	return (o);
}