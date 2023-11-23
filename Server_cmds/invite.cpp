/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 10:54:00 by mmaxime-          #+#    #+#             */
/*   Updated: 2023/11/22 22:40:01 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	Server::_invite(Client & sender, std::vector<std::string> const & params)
{
	if (params.size() < 2) {
		throw Server::ErrException(ERR_NEEDMOREPARAMS(sender.getNickname(), "INVITE"));
	}
	
	// check if the client exists
	Client* client = this->_clients.get(params[0]);
	if (!client) {
		throw Server::ErrException(ERR_NOSUCHNICK(sender.getNickname(), params[0]));
	}

	// check if the channel exists
	Channel* channel = this->_channels.get(params[1]);
	if (!channel) {
		throw Server::ErrException(ERR_NOSUCHCHANNEL(sender.getNickname(), params[1]));
	}

	// check if the sender is on the channel
	if (!channel->isJoined(&sender)) {
		throw Server::ErrException(ERR_NOTONCHANNEL(sender.getNickname(), channel->getName()));
	}

	// check if the sender has the rights to invite
	if (channel->hasMode('i') && !channel->hasOperatorRights(&sender)) {
		throw Server::ErrException(ERR_CHANOPRIVSNEEDED(sender.getNickname(), channel->getName()));
	}

	// check if the client is not already on the channel
	if (channel->isJoined(client)) {
		throw Server::ErrException(ERR_USERONCHANNEL(sender.getNickname(), client->getNickname(), channel->getName()));
	}

	// invite and reply
	channel->addClientLink(client, Channel::INVITEE);
	sender.reply(RPL_INVITING(sender.getNickname(), client->getNickname(), channel->getName()));
	client->reply(RPL_INVITE(sender.getHostmask(), client->getNickname(), channel->getName()));
}
