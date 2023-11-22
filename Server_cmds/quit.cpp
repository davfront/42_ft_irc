/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 15:40:03 by mmaxime-          #+#    #+#             */
/*   Updated: 2023/11/16 14:48:16 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	Server::_quit(Client & sender, std::vector<std::string> const & params)
{
	(void)params;
	this->_reply(sender.getFd(), RPL_ERROR("Closing connection"));
	this->_deleteClient(sender.getFd());
}