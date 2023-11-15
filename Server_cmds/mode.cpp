/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:16:19 by mmaxime-          #+#    #+#             */
/*   Updated: 2023/11/15 15:09:38 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	Server::_modeClient(Client & sender, std::vector<std::string> const & params)
{
	// todo
	(void)sender;
	(void)params;
}

void	Server::_modeChannel(Client & sender, std::vector<std::string> const & params)
{
	// todo
	(void)sender;
	(void)params;
}

void	Server::_mode(Client & sender, std::vector<std::string> const & params)
{
	if (params.size() < 1) {
		throw Server::ErrException(ERR_NEEDMOREPARAMS(sender.getNickname(), "MODE"));
	}

	if (!params[0].empty() && (params[0][0] == '#' || params[0][0] == '&')) {
		Server::_modeChannel(sender, params);
	} else {
		Server::_modeClient(sender, params);
	}
}

	
	