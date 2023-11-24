/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   names.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:16:19 by mmaxime-          #+#    #+#             */
/*   Updated: 2023/11/24 09:53:23 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	Server::_names(Client & sender, std::vector<std::string> const & params)
{
	if (params.size() < 1) {
		ChannelList::const_iterator it;
		for (it = this->_channels.begin(); it != this->_channels.end(); ++it) {
			Channel* channel = it->second;
			std::vector<std::string> nameLists = channel->getMemberNameLists();
			for (size_t i = 0; i < nameLists.size(); ++i) {
				sender.reply(RPL_NAMREPLY(sender.getNickname(), channel->getName(), nameLists[i]));
			}
			sender.reply(RPL_ENDOFNAMES(sender.getNickname(), channel->getName()));
		}
		return ;
	}

	// parse channel names
	std::vector<std::string> channelNames = split(params[0], ",");
	for (size_t i = 0; i < channelNames.size(); i++) {
		// find channel
		Channel* channel = this->_channels.get(channelNames[i]);

		// if channel doesn't exist, reply with RPL_ENDOFNAMES
		if (!channel) {
			sender.reply(RPL_ENDOFNAMES(sender.getNickname(), channelNames[i]));
		}
		// else reply with RPL_NAMREPLY and RPL_ENDOFNAMES
		else {
			std::vector<std::string> nameLists = channel->getMemberNameLists();
			for (size_t i = 0; i < nameLists.size(); ++i) {
				sender.reply(RPL_NAMREPLY(sender.getNickname(), channel->getName(), nameLists[i]));
			}
			sender.reply(RPL_ENDOFNAMES(sender.getNickname(), channel->getName()));
		}
	}
}
