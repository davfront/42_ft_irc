/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientList.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 15:52:31 by dapereir          #+#    #+#             */
/*   Updated: 2023/11/28 19:51:38 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClientList.hpp"


// Constructors & destructor
// ==========================================================================

ClientList::ClientList(void): _deleteOnRemove(false)
{
	Log::debug("ClientList created");
	return ;
}

ClientList::ClientList(ClientList const & src):
	_deleteOnRemove(false),
	_clients(src.getClients())
{
	Log::debug("ClientList created by copy");
	return ;
}

ClientList::~ClientList(void)
{
	this->removeAll();
	Log::debug("ClientList (" + stringify(this->getClients().size()) + " client(s)) destroyed");
	return ;
}


// Getters
// ==========================================================================


bool const &	ClientList::getDeleteOnRemove(void) const
{
	return (this->_deleteOnRemove);
}

std::map<int, Client*> const &	ClientList::getClients(void) const
{
	return (this->_clients);
}


// Setters
// ==========================================================================


void	ClientList::setDeleteOnRemove(bool const & deleteOnRemove)
{
	this->_deleteOnRemove = deleteOnRemove;
}


// Member functions (public)
// ==========================================================================

bool	ClientList::empty(void) const
{
	return (this->_clients.empty());
}

size_t	ClientList::size(void) const
{
	return (this->_clients.size());
}

ClientList::iterator	ClientList::begin(void)
{
	return (this->_clients.begin());
}

ClientList::const_iterator	ClientList::begin(void) const
{
	return (this->_clients.begin());
}

ClientList::iterator	ClientList::end(void)
{
	return (this->_clients.end());
}

ClientList::const_iterator	ClientList::end(void) const
{
	return (this->_clients.end());
}

void	ClientList::add(Client* client)
{
	if (!client) {
		return ;
	}

	ClientList::iterator it = this->_clients.find(client->getFd());
	if (it == this->_clients.end()) {
		this->_clients[client->getFd()] = client;
	}
}

void	ClientList::remove(int fd)
{
	ClientList::iterator it = this->_clients.find(fd);
	if (it == this->_clients.end()) {
		return ;
	}
	if (this->_deleteOnRemove) {
		deleteSafe(it->second);
	}
	this->_clients.erase(it);
}

Client*	ClientList::get(int const & fd) const
{
	ClientList::const_iterator	it;
	it = this->_clients.find(fd);

	if (it == this->_clients.end()) {
		return (NULL);
	}
	return (it->second);
}

Client*	ClientList::get(std::string const & nickname) const
{
	ClientList::const_iterator it;
	for (it = this->begin(); it != this->end(); ++it) {
		if (it->second && toLowerCase(it->second->getNickname()) == toLowerCase(nickname)) {
			return (it->second);
		}
	}
	return (NULL);
}

void	ClientList::removeAll(void)
{
	if (this->_deleteOnRemove) {
		ClientList::iterator it;
		for (it = this->begin(); it != this->end(); ++it) {
			deleteSafe(it->second);
		}
	}
	this->_clients.clear();
}

void	ClientList::reply(std::string const & msg) const
{
	ClientList::const_iterator it;
	for (it = this->begin(); it != this->end(); ++it) {
		if (it->second) {
			it->second->reply(msg);
		}
	}
}

// Output stream
// ==========================================================================

std::ostream &	operator<<(std::ostream & o, ClientList const & x)
{
	o << x.size() << " client(s)"<< std::endl;
	if (x.empty()) {
		return (o);
	}
	
	ClientList::const_iterator it;
	for (it = x.begin(); it != x.end(); ++it) {
		o << "Client " << it->first << ": ";
		if (it->second) {
			o << *(it->second);
		} else {
			o << "NULL";
		}
		o << std::endl;
	}

	return (o);
}
