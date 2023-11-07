/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 10:54:00 by mmaxime-          #+#    #+#             */
/*   Updated: 2023/11/07 13:54:30 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	Server::_pass(Client & sender, std::vector<std::string> const & params)
{
	if (params.empty() || params[0].empty()) {
		throw Server::ErrException(ERR_NEEDMOREPARAMS(sender.getNickname(), "PASS"));
	}

	if (sender.getIsRegistered()) {
		throw Server::ErrException(ERR_ALREADYREGISTERED(sender.getNickname()));
	}
	
	sender.setIsPasswordValid(params[0] == this->_password);
	if (!sender.getIsPasswordValid()) {
		throw Server::ErrException(ERR_PASSWDMISMATCH(sender.getNickname()));
	}
}
