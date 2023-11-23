/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:16:19 by mmaxime-          #+#    #+#             */
/*   Updated: 2023/11/22 15:36:08 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	Server::_list(Client & sender, std::vector<std::string> const & params)
{
	(void)params;

	// start
	sender.reply(RPL_LISTSTART(sender.getNickname()));

	// for each channel
	ChannelList::const_iterator it;
	for (it = this->_channels.begin(); it != this->_channels.end(); ++it) {
		Channel* channel = it->second;
		if (!channel) {
			continue ;
		}
		sender.reply(RPL_LIST(\
			sender.getNickname(), \
			channel->getName(), \
			stringify(channel->getMembersCount()), \
			channel->getTopic()\
		));
	}

	// end
	sender.reply(RPL_LISTEND(sender.getNickname()));
}
