/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 10:54:00 by mmaxime-          #+#    #+#             */
/*   Updated: 2023/11/21 16:43:19 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	Server::_user(Client & sender, std::vector<std::string> const & params)
{
	if (!sender.getIsPasswordValid()) {
		return ;
	}
	
	if (params.size() < 4 || params[0].empty() || params[3].empty()) {
		throw Server::ErrException(ERR_NEEDMOREPARAMS(sender.getNickname(), "USER"));
	}
	
	sender.setUsername("~" + params[0]);
	sender.setRealname(params[3]);
}
