/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerCommands.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 10:54:00 by mmaxime-          #+#    #+#             */
/*   Updated: 2023/11/07 13:14:32 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"


// Command list
// ==========================================================================

void	Server::_initCmds(void)
{
	this->_cmds["PASS"] = &Server::_pass;
	this->_cmds["NICK"] = &Server::_nick;
	this->_cmds["USER"] = &Server::_user;
	this->_cmds["PRIVMSG"] = &Server::_privmsg;
}


// Commands
// ==========================================================================

void	Server::_pass(Client & client, std::vector<std::string> const & params)
{
	if (params.empty() || params[0].empty()) {
		throw Server::ErrException(ERR_NEEDMOREPARAMS(client.getNickname(), "PASS"));
	}

	if (client.getIsRegistered()) {
		throw Server::ErrException(ERR_ALREADYREGISTERED(client.getNickname()));
	}
	
	client.setIsPasswordValid(params[0] == this->_password);
	if (!client.getIsPasswordValid()) {
		throw Server::ErrException(ERR_PASSWDMISMATCH(client.getNickname()));
	}
}

void	Server::_nick(Client & client, std::vector<std::string> const & params)
{
	if (!client.getIsPasswordValid()) {
		return ;
	}
	
	if (params.empty() || params[0].empty()) {
		throw Server::ErrException(ERR_NEEDMOREPARAMS(client.getNickname(), "NICK"));
	}

	// check nickname validity
	if (params[0].empty() || params[0].size() > 9) {
		throw Server::ErrException(ERR_ERRONEUSNICKNAME(client.getNickname(), params[0]));
	}
	std::string specialChars = "[]\\`_^{|}";
	if (!isalpha(params[0][0]) && specialChars.find(params[0][0]) == std::string::npos) {
		throw Server::ErrException(ERR_ERRONEUSNICKNAME(client.getNickname(), params[0]));
	}
	for (size_t i = 1; i < params[0].size(); ++i) {
		if (!isalnum(params[0][i]) && specialChars.find(params[0][i]) == std::string::npos && params[0][i] != '-') {
			throw Server::ErrException(ERR_ERRONEUSNICKNAME(client.getNickname(), params[0]));
		}
	}
	
	// check nickname availability
	Client* otherClient = this->_clients.get(params[0]);
	if (otherClient && otherClient != &client) {
		throw Server::ErrException(ERR_NICKNAMEINUSE(client.getNickname(), params[0]));
	}

	// update nickname
	client.setNickname(params[0]);
}

void	Server::_user(Client & client, std::vector<std::string> const & params)
{
	if (!client.getIsPasswordValid()) {
		return ;
	}
	
	if (params.size() < 4 || params[0].empty() || params[3].empty()) {
		throw Server::ErrException(ERR_NEEDMOREPARAMS(client.getNickname(), "USER"));
	}

	// todo: check params validity

	client.setUsername("~" + params[0]);
	client.setRealname(params[3]);
}

std::string	Server::_motdMsg(Client & client)
{
	std::string motd;

	motd += RPL_MOTDSTART(client.getNickname(), HOST);
	motd += RPL_MOTD(client.getNickname(), "- ****************************************************************");
	motd += RPL_MOTD(client.getNickname(),  "- * ####    ######     ####    #####   #######  ######   ##   ## *");
	motd += RPL_MOTD(client.getNickname(),  "- *  ##      ##  ##   ##  ##  ##   ##   ##   #   ##  ##  ##   ## *");
	motd += RPL_MOTD(client.getNickname(),  "- *  ##      ##  ##  ##       #         ## #     ##  ##   ## ##  *");
	motd += RPL_MOTD(client.getNickname(),  "- *  ##      #####   ##        #####    ####     #####    ## ##  *");
	motd += RPL_MOTD(client.getNickname(),  "- *  ##      ## ##   ##            ##   ## #     ## ##     ###   *");
	motd += RPL_MOTD(client.getNickname(),  "- *  ##      ##  ##   ##  ##  ##   ##   ##   #   ##  ##    ###   *");
	motd += RPL_MOTD(client.getNickname(),  "- * ####    #### ##    ####    #####   #######  #### ##     #    *");
	motd += RPL_MOTD(client.getNickname(),  "- ****************************************************************");
	motd += RPL_MOTD(client.getNickname(),  "- *         This is a private irc server. Please contact         *");
	motd += RPL_MOTD(client.getNickname(),  "- *         the admin of the server for any question or          *");
	motd += RPL_MOTD(client.getNickname(),  "- *         issue.                                               *");
	motd += RPL_MOTD(client.getNickname(),  "- ****************************************************************");
	motd += RPL_ENDOFMOTD(client.getNickname());
	
	return (motd);
}

void	Server::_privmsg(Client & client, std::vector<std::string> const & params)
{
	if (params.size() < 1) {
		throw Server::ErrException(ERR_NORECIPIENT(client.getNickname(), "PRIVMSG"));
	}
	if (params.size() < 2) {
		throw Server::ErrException(ERR_NOTEXTTOSEND(client.getNickname()));
	}

	Client* targetClient = this->_clients.get(params[0]);
	if (!targetClient) {
		throw Server::ErrException(ERR_NOSUCHNICK(client.getNickname(), params[0]));
	}
	this->_reply(targetClient->getFd(), RPL_PRIVMSG(client.getNickname(), targetClient->getNickname(), params[1]));
}

