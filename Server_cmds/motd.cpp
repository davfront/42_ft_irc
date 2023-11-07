/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   motd.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 10:54:00 by mmaxime-          #+#    #+#             */
/*   Updated: 2023/11/07 13:49:24 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

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
