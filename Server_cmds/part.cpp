/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 15:56:15 by dapereir          #+#    #+#             */
/*   Updated: 2023/11/24 09:31:11 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	Server::_partSingleChannel(Client & sender, std::string const & channelName, std::string const & reason)
{
	try {
		Log::debug("Parting single channel " + channelName + " (reason: " + reason + ")");
	
		// find channel
		Channel* channel = this->_channels.get(channelName);
		if (!channel) {
			throw Server::ErrException(ERR_NOSUCHCHANNEL(sender.getNickname(), channelName));
		}

		// check if user is in channel
		if (!channel->isJoined(&sender)) {
			throw Server::ErrException(ERR_NOTONCHANNEL(sender.getNickname(), channel->getName()));
		}

		// remove user from channel
		channel->removeClientLink(&sender);

		// reply to user
		sender.reply(RPL_PART(sender.getHostmask(), channel->getName(), reason));

		// if empty, delete channel 
		if (channel->getMemberCount() == 0) {
			this->_channels.remove(channel->getName());
		}
		// reply to all channel members
		else {
			channel->reply(RPL_PART(sender.getHostmask(), channel->getName(), reason));
		}
	} catch (std::exception & e) {
		sender.reply(e.what());
	}
}

void	Server::_part(Client & sender, std::vector<std::string> const & params)
{
	// if no channel parameter
	if (params.size() < 1) {
		throw Server::ErrException(ERR_NEEDMOREPARAMS(sender.getNickname(), "PART"));
	}

	// parse channel names
	std::vector<std::string> channelNames = split(params[0], ",");
	if (channelNames.empty()) {
		throw Server::ErrException(ERR_NEEDMOREPARAMS(sender.getNickname(), "PART"));
	}

	// parse reason
	std::string reason = (params.size() > 1 ? params[1] : "");
	
	// for each channel
	for (size_t i = 0; i < channelNames.size(); i++) {
		Server::_partSingleChannel(sender, channelNames[i], reason);
	}
}
