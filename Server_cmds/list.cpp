/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:16:19 by mmaxime-          #+#    #+#             */
/*   Updated: 2023/11/14 17:07:33 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	Server::_list(Client & sender, std::vector<std::string> const & params)
{
	(void)params;

	// start
	this->_reply(sender.getFd(), RPL_LISTSTART(sender.getNickname()));

	// for each channel
	ChannelList::const_iterator it;
	for (it = this->_channels.begin(); it != this->_channels.end(); ++it) {
		Channel* channel = it->second;
		if (!channel) {
			continue ;
		}
		this->_reply(sender.getFd(), RPL_LIST(\
			sender.getNickname(), \
			channel->getName(), \
			stringify(channel->getMembersCount()), \
			channel->getTopic()\
		));
	}

	// end
	this->_reply(sender.getFd(), RPL_LISTEND(sender.getNickname()));
}
