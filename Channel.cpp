/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 14:58:27 by dapereir          #+#    #+#             */
/*   Updated: 2023/11/20 12:26:15 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"


// Constructors & destructor
// ==========================================================================

Channel::Channel(std::string name, std::string topic, bool isInviteOnly):
	_name(name),
	_topic(topic),
	_isInviteOnly(isInviteOnly)
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

bool const &	Channel::getIsInviteOnly(void) const
{
	return (this->_isInviteOnly);
}


// Setters
// ==========================================================================

void	Channel::setTopic(std::string const & topic)
{
	this->_topic = topic;
}

void	Channel::setIsInviteOnly(bool const & isInviteOnly)
{
	this->_isInviteOnly = isInviteOnly;
}

void	Channel::setClientStatus(Client* client, Channel::t_status status)
{
	if (!this->isClientLinked(client)) {
		return ;
	}
	this->_clientLinks[client] = status;
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

// Output stream
// ==========================================================================

std::ostream &	operator<<(std::ostream & o, Channel const & x)
{
	o << "{";
	o << "name: \"" << x.getName() << "\"";
	o << ", ";
	o << "topic: \"" << x.getTopic() << "\"";
	o << ", ";
	o << "isInviteOnly: " << (x.getIsInviteOnly() ? "true": "false");
	o << "}";
	return (o);
}
