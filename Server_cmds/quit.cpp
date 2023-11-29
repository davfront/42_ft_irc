/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 15:40:03 by mmaxime-          #+#    #+#             */
/*   Updated: 2023/11/29 10:01:46 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	Server::_quit(Client & sender, std::vector<std::string> const & params)
{
	// Send QUIT message to all channel peers
	std::string	reason = (params.size() > 0) ? "Quit: " + params[0] : sender.getNickname();
	this->_getChannelPeers(sender).reply(RPL_QUIT(sender.getHostmask(), reason));

	// Send ERROR message to client
	this->_reply(sender.getFd(), RPL_ERROR("Closing connection: " + reason));
	
	// Close connection
	throw Server::ConnectionException("Got QUIT command");
}
