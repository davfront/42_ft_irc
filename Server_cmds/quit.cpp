/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaxime- <mmaxime-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 15:40:03 by mmaxime-          #+#    #+#             */
/*   Updated: 2023/11/10 15:44:15 by mmaxime-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	Server::_quit(Client & sender, std::vector<std::string> const & params)
{
	(void)params;
	this->_reply(sender.getFd(), RPL_ERROR("Closing connection"));
	this->_deleteClient(sender.getFd());
}