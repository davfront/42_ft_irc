/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oper.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaxime- <mmaxime-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 17:28:07 by mmaxime-          #+#    #+#             */
/*   Updated: 2023/11/16 17:28:46 by mmaxime-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	Server::_oper(Client & sender, std::vector<std::string> const & params)
{
	if (params.size() < 2) {
		throw Server::ErrException(ERR_NEEDMOREPARAMS(sender.getNickname(),"OPER"));
	}
	
	else if (params[0].compare(OPER_NAME)) {
		throw Server::ErrException(ERR_NOOPERHOST(sender.getNickname()));
	}
	else if (params[1].compare(OPER_PASSWORD)) {
		throw Server::ErrException(ERR_PASSWDMISMATCH(sender.getNickname()));
	}
	else {
		sender.setIsOper(true);
		this->_reply(sender.getFd(), RPL_OPER(sender.getNickname()));
		this->_reply(sender.getFd(), RPL_YOUREOPER(sender.getNickname()));
	}
}