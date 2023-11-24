/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 10:54:00 by mmaxime-          #+#    #+#             */
/*   Updated: 2023/11/24 12:18:46 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	Server::_nick(Client & sender, std::vector<std::string> const & params)
{
	if (!sender.getIsPasswordValid()) {
		return ;
	}
	
	if (params.empty() || params[0].empty()) {
		throw Server::ErrException(ERR_NEEDMOREPARAMS(sender.getNickname(), "NICK"));
	}

	// check nickname validity
	if (params[0].empty() || params[0].size() > 9) {
		throw Server::ErrException(ERR_ERRONEUSNICKNAME(sender.getNickname(), params[0]));
	}
	std::string specialChars = "[]\\`_^{|}";
	if (!isalpha(params[0][0]) && specialChars.find(params[0][0]) == std::string::npos) {
		throw Server::ErrException(ERR_ERRONEUSNICKNAME(sender.getNickname(), params[0]));
	}
	for (size_t i = 1; i < params[0].size(); ++i) {
		if (!isalnum(params[0][i]) && specialChars.find(params[0][i]) == std::string::npos && params[0][i] != '-') {
			throw Server::ErrException(ERR_ERRONEUSNICKNAME(sender.getNickname(), params[0]));
		}
	}
	
	// check nickname availability
	Client* otherClient = this->_clients.get(params[0]);
	if (otherClient && otherClient == &sender) {
		return ;
	}
	if (otherClient && otherClient != &sender) {
		throw Server::ErrException(ERR_NICKNAMEINUSE(sender.getNickname(), params[0]));
	}

	// update nickname and reply
	if (sender.getIsRegistered()) {
		std:: string oldHostmask = sender.getHostmask();
		sender.setNickname(params[0]);
		sender.reply(RPL_NICK(oldHostmask, params[0]));
	} else {
		sender.setNickname(params[0]);
	}
}
