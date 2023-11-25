/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaxime- <mmaxime-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 15:40:03 by mmaxime-          #+#    #+#             */
/*   Updated: 2023/11/25 15:57:34 by mmaxime-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	Server::_quit(Client & sender, std::vector<std::string> const & params)
{
	std::string	reason = (params.size() > 0) ? "Quit: " + params[0] : sender.getNickname();

	ChannelList::iterator it = this->_channels.begin();
	while (it != this->_channels.end()) {
		Channel*  channel = it->second;
		it++;
		if (channel->isJoined(&sender)) {
			channel->removeClientLink(&sender);
			if (channel->getMemberCount() == 0) {
				this->_channels.remove(channel->getName());
			}
			else {
				channel->reply(RPL_QUIT(sender.getHostmask(), reason));
			}
		}
	}

	sender.reply(RPL_ERROR("Closing connection"));
	this->_deleteClient(sender.getFd());
}