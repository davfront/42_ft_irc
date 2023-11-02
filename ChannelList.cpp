/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelList.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 15:52:31 by dapereir          #+#    #+#             */
/*   Updated: 2023/10/27 11:47:02 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ChannelList.hpp"


// Constructors & destructor
// ==========================================================================

ChannelList::ChannelList(void): _deleteOnRemove(false)
{
	Log::debug("ChannelList created");
	return ;
}

ChannelList::~ChannelList(void)
{
	if (this->_deleteOnRemove) {
		std::map<std::string, Channel*, ChannelList::cmp>::const_iterator it;
		for (it = this->_channels.begin(); it != this->_channels.end(); ++it) {
			delete it->second;
		}
	}
	
	Log::debug("ChannelList (" + stringify(this->getChannels().size()) + " channel(s)) destroyed");
	return ;
}


// Getters
// ==========================================================================


bool const &	ChannelList::getDeleteOnRemove(void) const
{
	return (this->_deleteOnRemove);
}

std::map<std::string, Channel*, ChannelList::cmp> const &	ChannelList::getChannels(void) const
{
	return (this->_channels);
}


// Setters
// ==========================================================================


void	ChannelList::setDeleteOnRemove(bool const & deleteOnRemove)
{
	this->_deleteOnRemove = deleteOnRemove;
}


// Member functions (public)
// ==========================================================================

bool	ChannelList::empty(void) const
{
	return (this->_channels.empty());
}

size_t	ChannelList::size(void) const
{
	return (this->_channels.size());
}

void	ChannelList::add(Channel* channel)
{
	if (!channel) {
		return ;
	}

	std::map<std::string, Channel*, ChannelList::cmp>::iterator it;
	it = this->_channels.find(channel->getName());
	if (it == this->_channels.end()) {
		this->_channels[channel->getName()] = channel;
	}
}

void	ChannelList::remove(std::string const & name)
{
	std::map<std::string, Channel*, ChannelList::cmp>::iterator it = this->_channels.find(name);
	if (it == this->_channels.end()) {
		return ;
	}
	if (this->_deleteOnRemove) {
		delete it->second;
	}
	this->_channels.erase(it);
}

Channel*	ChannelList::get(std::string const & name) const
{
	std::map<std::string, Channel*, ChannelList::cmp>::const_iterator	it;
	it = this->_channels.find(name);

	if (it == this->_channels.end()) {
		return (NULL);
	}
	return (it->second);
}


// Output stream
// ==========================================================================

std::ostream &	operator<<(std::ostream & o, ChannelList const & x)
{
	o << x.getChannels().size() << " channel(s)"<< std::endl;
	if (x.getChannels().empty()) {
		return (o);
	}
	
	std::map<std::string, Channel*, ChannelList::cmp>::const_iterator it;
	for (it = x.getChannels().begin(); it != x.getChannels().end(); ++it) {
		o << "Channel " << it->first << ": ";
		if (it->second) {
			o << *(it->second);
		} else {
			o << "NULL";
		}
		o << std::endl;
	}

	return (o);
}
