/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 11:41:39 by mmaxime-          #+#    #+#             */
/*   Updated: 2023/11/29 09:57:52 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	Server::_kill(Client & sender, std::vector<std::string> const & params)
{
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

	// Send KILL message to target
	target->reply(RPL_KILL(sender.getHostmask(), target->getNickname(), params[1]));

	// Send QUIT message to all channel peers
	std::string	reason = "Killed by " + sender.getNickname() + ": " + params[1];
	this->_getChannelPeers(*target).reply(RPL_QUIT(target->getHostmask(), reason));

	// Send ERROR message to target
	target->reply(RPL_ERROR("Closing connection: " + reason));
	
	// Send buffer to target, and close connection
	this->_reply(target->getFd(), target->getBufferOut());
	throw Server::ConnectionException("Got KILL command");
}