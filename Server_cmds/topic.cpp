/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:16:19 by mmaxime-          #+#    #+#             */
/*   Updated: 2023/11/22 13:51:10 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	Server::_topic(Client & sender, std::vector<std::string> const & params)
{
	if (params.size() < 1) {
		throw Server::ErrException(ERR_NEEDMOREPARAMS(sender.getNickname(), "TOPIC"));
	}

	// check if the channel exists
	Channel* channel = this->_channels.get(params[0]);
	if (!channel) {
		throw Server::ErrException(ERR_NOSUCHCHANNEL(sender.getNickname(), params[0]));
	}

	// check if the sender is on the channel
	if (!channel->isJoined(&sender)) {
		throw Server::ErrException(ERR_NOTONCHANNEL(sender.getNickname(), channel->getName()));
	}

	// if no topic is given, return the current topic
	if (params.size() < 2) {
		if (channel->getTopic().empty()) {
			this->_reply(sender.getFd(), RPL_NOTOPIC(sender.getNickname(), channel->getName()));
		} else {
			this->_reply(sender.getFd(), RPL_TOPIC(sender.getNickname(), channel->getName(), channel->getTopic()));
			this->_reply(sender.getFd(), RPL_TOPICWHOTIME(sender.getNickname(), channel->getName(), channel->getTopicSetter(), stringify(channel->getTopicTime())));
		}
		return ;
	}

	// check if the sender has the rights to change the topic
	if (channel->hasMode('t') && !channel->hasOperatorRights(&sender)) {
		throw Server::ErrException(ERR_CHANOPRIVSNEEDED(sender.getNickname(), channel->getName()));
	}

	// set the new topic
	channel->setTopic(params[1]);
	channel->setTopicTime(time(NULL));
	channel->setTopicSetter(sender.getNickname());

	// send the new topic to all channel members
	std::vector<std::string> replyParams;
	replyParams.push_back(channel->getName());
	std::map<Client*, Channel::t_status>::const_iterator it;
	for (it = channel->getClientLinks().begin(); it != channel->getClientLinks().end(); ++it) {
		if (it->first && (it->second == Channel::MEMBER || it->second == Channel::OPERATOR|| it->second == Channel::FOUNDER)) {
			Client* client = it->first;
			if (channel->getTopic().empty()) {
				this->_reply(client->getFd(), RPL_NOTOPIC(sender.getNickname(), channel->getName()));
			} else {
				this->_reply(client->getFd(), RPL_TOPIC(sender.getNickname(), channel->getName(), channel->getTopic()));
				this->_reply(client->getFd(), RPL_TOPICWHOTIME(sender.getNickname(), channel->getName(), channel->getTopicSetter(), stringify(channel->getTopicTime())));
			}
		}
	}
}
