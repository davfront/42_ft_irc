/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:16:19 by mmaxime-          #+#    #+#             */
/*   Updated: 2023/11/22 15:37:00 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	Server::_ping(Client & sender, std::vector<std::string> const & params)
{
	if (params.size() < 1) {
		throw Server::ErrException(ERR_NOORIGIN(sender.getNickname()));
	}
		
	sender.reply(RPL_PING(params[0]));
}