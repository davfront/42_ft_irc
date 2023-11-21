/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 14:58:27 by dapereir          #+#    #+#             */
/*   Updated: 2023/11/21 12:58:25 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"


// Constructors & destructor
// ==========================================================================

Channel::Channel(std::string name):
	_name(name),
	_limit(-1)
	
{
	Log::debug("Channel " + stringify(this->_name) + " created");
	return ;
}

Channel::~Channel(void)
{
	Log::debug("Channel " + stringify(this->_name) + " destroyed");
	return ;
}


// Getters
// ==========================================================================

std::string const &	Channel::getName(void) const
{
	return (this->_name);
}

std::string const &	Channel::getTopic(void) const
{
	return (this->_topic);
}

std::string const &	Channel::getKey(void) const
{
	return (this->_key);
}

int const &	Channel::getLimit(void) const
{
	return (this->_limit);
}

std::map<Client*, Channel::t_status> const &	Channel::getClientLinks(void) const
{
	return (this->_clientLinks);
}


// Setters
// ==========================================================================

void	Channel::setTopic(std::string const & topic)
{
	this->_topic = topic;
}

void	Channel::setKey(std::string const & key)
{
	this->_key = key;
}

void	Channel::setLimit(int const & limit)
{
	this->_limit = limit;
}


// Member functions
// ==========================================================================

void	Channel::addClientLink(Client* client, Channel::t_status status)
{
	Channel::t_status currentStatus = this->getClientStatus(client);
	if (currentStatus != Channel::UNKNOWN) {
		this->_clientLinks.insert(std::make_pair(client, status));
	} else {
		this->_clientLinks[client] = status;
	}
}

void	Channel::removeClientLink(Client* client)
{
	if (!this->isClientLinked(client)) {
		return ;
	}
	this->_clientLinks.erase(client);
}

Channel::t_status	Channel::getClientStatus(Client* client) const
{
	if (!client) {
		return (Channel::UNKNOWN);
	}
	std::map<Client*, Channel::t_status>::const_iterator it = this->_clientLinks.find(client);
	if (it == this->_clientLinks.end()) {
		return (Channel::UNKNOWN);
	}
	return (it->second);
}

void	Channel::setClientStatus(Client* client, Channel::t_status status)
{
	if (!this->isClientLinked(client)) {
		return ;
	}
	this->_clientLinks[client] = status;
}

bool	Channel::isClientLinked(Client* client) const
{
	return (this->getClientStatus(client) != Channel::UNKNOWN);
}

bool	Channel::isInvitee(Client* client) const
{
	return (this->getClientStatus(client) == Channel::INVITEE);
}

bool	Channel::isJoined(Client* client) const
{
	Channel::t_status status = this->getClientStatus(client);
	return (status == Channel::MEMBER || status == Channel::OPERATOR || status == Channel::FOUNDER);
}

bool	Channel::hasOperatorRights(Client* client) const
{
	Channel::t_status status = this->getClientStatus(client);
	return (status == Channel::OPERATOR || status == Channel::FOUNDER);
}

bool	Channel::isFounder(Client* client) const
{
	Channel::t_status status = this->getClientStatus(client);
	return (status == Channel::FOUNDER);
}

size_t	Channel::getMembersCount(void) const
{
	size_t count = 0;
	std::map<Client*, Channel::t_status>::const_iterator it;
	for (it = this->_clientLinks.begin(); it != this->_clientLinks.end(); ++it) {
		if (it->second == Channel::MEMBER || it->second == Channel::OPERATOR || it->second == Channel::FOUNDER) {
			count++;
		}
	}
	return (count);
}

bool	Channel::hasMode(char modeKey) const
{
	return (this->_modes.find(modeKey) != this->_modes.end());
}

void	Channel::setMode(char modeKey)
{
	this->_modes.insert(modeKey);
}

void	Channel::unsetMode(char modeKey)
{
	this->_modes.erase(modeKey);
}

std::string	Channel::getModes(void) const
{
	std::string modes = "+";
	std::set<char>::const_iterator it;
	for (it = this->_modes.begin(); it != this->_modes.end(); ++it) {
		modes += *it;
	}
	return (modes);
}


// Output stream
// ==========================================================================

std::ostream &	operator<<(std::ostream & o, Channel const & x)
{
	o << "{";
	o << "name: \"" << x.getName() << "\"";
	o << ", ";
	o << "topic: \"" << x.getTopic() << "\"";
	o << ", ";
	o << "modes: " << (x.getModes());
	o << "}";
	return (o);
}
