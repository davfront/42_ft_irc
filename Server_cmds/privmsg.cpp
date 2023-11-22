/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 10:54:00 by mmaxime-          #+#    #+#             */
/*   Updated: 2023/11/22 15:29:46 by dapereir         ###   ########.fr       */
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

	Client* targetClient = this->_clients.get(params[0]);
	if (!targetClient) {
		throw Server::ErrException(ERR_NOSUCHNICK(sender.getNickname(), params[0]));
	}
	targetClient->reply(RPL_PRIVMSG(sender.getNickname(), targetClient->getNickname(), params[1]));
}
