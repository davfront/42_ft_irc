/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 14:58:27 by dapereir          #+#    #+#             */
/*   Updated: 2023/10/08 22:13:57 by dapereir         ###   ########.fr       */
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
	if (DEBUG)
		std::cout << Txt::FAINT << "Channel " << *this << " created." << Txt::RESET << std::endl;
	return ;
}

Channel::~Channel(void)
{
	if (DEBUG)
		std::cout << Txt::FAINT << "Channel " << *this << " destroyed." << Txt::RESET << std::endl;
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
