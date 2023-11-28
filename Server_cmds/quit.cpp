/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 15:40:03 by mmaxime-          #+#    #+#             */
/*   Updated: 2023/11/28 11:49:24 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	Server::_quit(Client & sender, std::vector<std::string> const & params)
{
	std::string	reason = (params.size() > 0) ? "Quit: " + params[0] : sender.getNickname();

	Log::info("Quitting (" + reason + ")");

	// Send QUIT message to all channel peers
	this->_getChannelPeers(sender).reply(RPL_QUIT(sender.getHostmask(), reason));

	// Remove client from all channels
	ChannelList::iterator it = this->_channels.begin();
	while (it != this->_channels.end()) {
		Channel*  channel = it->second;
		it++;
		if (channel->isJoined(&sender)) {
			channel->removeClientLink(&sender);
			if (channel->getMemberCount() == 0) {
				this->_channels.remove(channel->getName());
			}
		}
	}

	// Send ERROR message to client
	sender.reply(RPL_ERROR("Closing connection"));

	// Delete client
	Log::info("User \"" + sender.getHostmask() + "\" unregistered (socket " + stringify(sender.getFd()) + "): Got QUIT command.");
	this->_deleteClient(sender.getFd());
}
