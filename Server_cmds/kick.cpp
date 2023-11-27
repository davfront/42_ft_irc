/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaxime- <mmaxime-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 16:48:05 by mmaxime-          #+#    #+#             */
/*   Updated: 2023/11/25 17:19:45 by mmaxime-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	Server::_kick(Client & sender, std::vector<std::string> const & params)
{
	if (params.size() < 2) {
		throw Server::ErrException(ERR_NEEDMOREPARAMS(sender.getNickname(), "KICK"));
	}

	Channel * channel = this->_channels.get(params[0]);
	Client * target = this->_clients.get(params[1]);

	if (!channel) {
		throw Server::ErrException(ERR_NOSUCHCHANNEL(sender.getNickname(), params[0]));
	}

	if (channel->isJoined(&sender) == false) {
		throw Server::ErrException(ERR_NOTONCHANNEL(sender.getNickname(), params[0]));
	}

	if (channel->hasOperatorRights(&sender) == false) {
		throw Server::ErrException(ERR_CHANOPRIVSNEEDED(sender.getNickname(), params[0]));
	}

	if (!target) {
		throw Server::ErrException(ERR_NOSUCHNICK(sender.getNickname(), params[1]));
	}

	if (channel->isJoined(target) == false) {
		throw Server::ErrException(ERR_USERNOTINCHANNEL(sender.getNickname(), target->getNickname(), params[0]));
	}

	std::string reason = params.size() > 2 ? params[2] : sender.getNickname();
	channel->reply(RPL_KICK(sender.getHostmask(), channel->getName(), target->getNickname(), reason));
	channel->removeClientLink(target);
}