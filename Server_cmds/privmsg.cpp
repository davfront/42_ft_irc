/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 10:54:00 by mmaxime-          #+#    #+#             */
/*   Updated: 2023/11/24 15:18:28 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	Server::_privmsg(Client & sender, std::vector<std::string> const & params)
{
	if (params.size() < 1) {
		throw Server::ErrException(ERR_NORECIPIENT(sender.getNickname(), "PRIVMSG"));
	}
	if (params.size() < 2) {
		throw Server::ErrException(ERR_NOTEXTTOSEND(sender.getNickname()));
	}

	// parse target names
	std::vector<std::string> targetNames = split(params[0], ",");
	if (targetNames.empty()) {
		throw Server::ErrException(ERR_NORECIPIENT(sender.getNickname(), "PRIVMSG"));
	}

	// for each target
	for (size_t i = 0; i < targetNames.size(); i++) {
		if (toLowerCase(targetNames[i]) == toLowerCase(BOT_NICK)) {
			// bot
			Log::debug(std::string("") + "Bot (" + BOT_NICK + ") recieves: " + params[1]);
			usleep(10e5);
			Log::debug(std::string("") + "Bot (" + BOT_NICK + ") replies: " + BOT_MSG);
			sender.reply(RPL_PRIVMSG(BOT_NICK, sender.getNickname(), BOT_MSG));
		} else if (!targetNames[i].empty() && (targetNames[i][0] == '#' || targetNames[i][0] == '&')) {
			// channel
			Channel* channel = this->_channels.get(targetNames[i]);
			if (!channel) {
				throw Server::ErrException(ERR_NOSUCHNICK(sender.getNickname(), targetNames[i]));
			}
			channel->reply(RPL_PRIVMSG(sender.getHostmask(), channel->getName(), params[1]), &sender);
		} else {
			// client
			Client* client = this->_clients.get(targetNames[i]);
			if (!client) {
				throw Server::ErrException(ERR_NOSUCHNICK(sender.getNickname(), targetNames[i]));
			}
			client->reply(RPL_PRIVMSG(sender.getHostmask(), client->getNickname(), params[1]));
		}
	}
}
