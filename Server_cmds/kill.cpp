/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaxime- <mmaxime-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 11:41:39 by mmaxime-          #+#    #+#             */
/*   Updated: 2023/11/27 19:42:40 by mmaxime-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	Server::_kill(Client & sender, std::vector<std::string> const & params)
{
	Log::info("Killing (" + params[0] + " " + params[1] + ")");

	if (params.size() < 2) {
		throw Server::ErrException(ERR_NEEDMOREPARAMS(sender.getNickname(), "KILL"));
	}

	if (sender.getMode().find('o') == std::string::npos) {
		throw Server::ErrException(ERR_NOPRIVILEGES(sender.getNickname()));
	}

	Client* target = this->_clients.get(params[0]);
	
	if (!target) {
		throw Server::ErrException(ERR_NOSUCHNICK(sender.getNickname(), params[0]));
	}
	target->reply(RPL_ERROR("Killed by" + sender.getNickname() + ": " + params[1]));
	
	ChannelList::iterator it = this->_channels.begin();
	while (it != this->_channels.end()) {
		Channel*  channel = it->second;
		it++;
		if (channel->isJoined(target)) {
			channel->removeClientLink(target);
			if (channel->getMemberCount() == 0) {
				this->_channels.remove(channel->getName());
			}
			else {
				channel->reply(RPL_KILL(target->getHostmask(), sender.getNickname(), params[1]));
			}
		}
	}
	this->_deleteClient(target->getFd());
}