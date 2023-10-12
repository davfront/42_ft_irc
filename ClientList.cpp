/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientList.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 15:52:31 by dapereir          #+#    #+#             */
/*   Updated: 2023/10/12 11:51:26 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClientList.hpp"


// Constructors & destructor
// ==========================================================================

ClientList::ClientList(void): _deleteOnRemove(false)
{
	if (DEBUG)
		std::cout << Txt::FAINT << "ClientList created." << Txt::RESET << std::endl;
	return ;
}

ClientList::~ClientList(void)
{
	if (this->_deleteOnRemove) {
		std::map<int, Client*>::const_iterator	it, begin, end;
		begin = this->_clients.begin();
		end = this->_clients.end();
		
		for (it = begin; it != end; it++) {
			delete it->second;
		}
	}
	
	if (DEBUG)
		std::cout << Txt::FAINT << "ClientList (" << this->getClients().size() << " client(s)) destroyed." << Txt::RESET << std::endl;
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

void	ClientList::add(Client* client)
{
	if (!client) {
		return ;
	}

	std::map<int, Client*>::iterator it = this->_clients.find(client->getFd());
	if (it == this->_clients.end()) {
		this->_clients[client->getFd()] = client;
	}
}

void	ClientList::remove(int fd)
{
	std::map<int, Client*>::iterator it = this->_clients.find(fd);
	if (it == this->_clients.end()) {
		return ;
	}
	if (this->_deleteOnRemove) {
		delete it->second;
	}
	this->_clients.erase(it);
}

Client*	ClientList::get(int const & fd) const
{
	std::map<int, Client*>::const_iterator	it, end;
	it = this->_clients.find(fd);
	end = this->_clients.end();

	if (it == end) {
		return (NULL);
	}
	return (it->second);
}

Client*	ClientList::get(std::string const & nickname) const
{
	std::map<int, Client*>::const_iterator	it, begin, end;
	begin = this->_clients.begin();
	end = this->_clients.end();

	for (it = begin; it != end; it++) {
		if (it->second && it->second->getNickname() == nickname) {
			return (it->second);
		}
	}
	return (NULL);
}


// Output stream
// ==========================================================================

std::ostream &	operator<<(std::ostream & o, ClientList const & x)
{
	o << x.getClients().size() << " client(s)"<< std::endl;
	if (x.getClients().empty()) {
		return (o);
	}
	
	std::map<int, Client*>::const_iterator	it, begin, end;
	begin = x.getClients().begin();
	end = x.getClients().end();
	
	for (it = begin; it != end; it++) {
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
