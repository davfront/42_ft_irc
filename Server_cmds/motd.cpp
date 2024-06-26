/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   motd.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 10:54:00 by mmaxime-          #+#    #+#             */
/*   Updated: 2023/11/22 15:36:59 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	Server::_motd(Client & sender, std::vector<std::string> const & params)
{
	if (!params.empty() && params[0] != HOST) {
		throw Server::ErrException(ERR_NOSUCHSERVER(sender.getNickname(), params[0]));
	}
	sender.reply(this->_motdMsg(sender));
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
