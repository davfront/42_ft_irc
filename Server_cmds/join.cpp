/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 10:54:00 by mmaxime-          #+#    #+#             */
/*   Updated: 2023/11/15 10:51:01 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	Server::_joinSingleChannel(Client & sender, std::string const & channelName, std::string const & key)
{
	try {
		Log::debug("Joining single channel " + channelName + " (key: " + key + ")");

		// check if channel name is valid
		if (channelName.size() < 1 || channelName.size() > 50 || (channelName[0] != '&' && channelName[0] != '#')) {
			throw Server::ErrException(ERR_NOSUCHCHANNEL(sender.getNickname(), channelName));
		}

		// find channel or create it
		Channel* channel = this->_channels.get(channelName);
		if (!channel) {
			channel = new Channel(channelName);
			this->_channels.add(channel);
			channel->addClientLink(&sender, Channel::FOUNDER);
		} else {
			// check if user is already in channel
			if (channel->isJoined(&sender)) {
				return ;
			}
			// todo: check if channel is invite-only		(mode i)
			// todo: check if channel's limit is reached	(mode l)
			// todo: check if channel is key-locked			(mode k)
			
			// add user to channel
			channel->addClientLink(&sender, Channel::MEMBER);
		}

		// reply
		this->_reply(sender.getFd(), RPL_JOIN(sender.getNickname(), channelName));
		std::vector<std::string> params;
		params.push_back(channelName);
		this->_topic(sender, params);
		this->_names(sender, params);

	} catch(Server::ErrException & e) {
		Server::_reply(sender.getFd(), e.what());
	} catch(std::exception & e) {
		throw e;
	}
}

void	Server::_join(Client & sender, std::vector<std::string> const & params)
{
	// if no channel parameter
	if (params.size() < 1) {
		throw Server::ErrException(ERR_NEEDMOREPARAMS(sender.getNickname(), "JOIN"));
	}
	
	// if channel parameter is "0"
	if (params[0] == "0") {
		// todo: leave all channels
		return ;
	}

	// parse channel names and keys
	std::vector<std::string> channelNames = split(params[0], ",");
	if (channelNames.empty()) {
		throw Server::ErrException(ERR_NEEDMOREPARAMS(sender.getNickname(), "JOIN"));
	}
	// remove duplicates
	std::vector<std::string> keys;
	if (params.size() >= 1) {
		channelNames = split(params[0], ",");
	}
	
	// for each channel
	for (size_t i = 0; i < channelNames.size(); i++) {
		Server::_joinSingleChannel(sender, channelNames[i], (i < keys.size() ? keys[i] : ""));
	}
}