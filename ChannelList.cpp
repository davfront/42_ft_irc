/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelList.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaxime- <mmaxime-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 15:52:31 by dapereir          #+#    #+#             */
/*   Updated: 2023/11/25 16:38:31 by mmaxime-         ###   ########.fr       */
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
		ChannelList::const_iterator it;
		for (it = this->begin(); it != this->end(); ++it) {
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

ChannelList::iterator	ChannelList::begin(void)
{
	return (this->_channels.begin());
}

ChannelList::const_iterator	ChannelList::begin(void) const
{
	return (this->_channels.begin());
}

ChannelList::iterator	ChannelList::end(void)
{
	return (this->_channels.end());
}

ChannelList::const_iterator	ChannelList::end(void) const
{
	return (this->_channels.end());
}

void	ChannelList::add(Channel* channel)
{
	if (!channel) {
		return ;
	}

	ChannelList::iterator it;
	it = this->_channels.find(channel->getName());
	if (it == this->end()) {
		this->_channels[channel->getName()] = channel;
	}
}

void	ChannelList::remove(std::string const & name)
{
	ChannelList::iterator it = this->_channels.find(name);
	if (it == this->end()) {
		return ;
	}
	if (this->_deleteOnRemove) {
		delete it->second;
	}
	this->_channels.erase(it);
}

Channel*	ChannelList::get(std::string const & name) const
{
	ChannelList::const_iterator	it;
	it = this->_channels.find(name);

	if (it == this->end()) {
		return (NULL);
	}
	return (it->second);
}

void	ChannelList::clear(void)
{
	this->_channels.clear();
}


// Output stream
// ==========================================================================

std::ostream &	operator<<(std::ostream & o, ChannelList const & x)
{
	o << x.size() << " channel(s)"<< std::endl;
	if (x.empty()) {
		return (o);
	}
	
	ChannelList::const_iterator it;
	for (it = x.begin(); it != x.end(); ++it) {
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
