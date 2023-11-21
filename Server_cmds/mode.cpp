/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:16:19 by mmaxime-          #+#    #+#             */
/*   Updated: 2023/11/21 15:05:16 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	Server::_modeClient(Client & sender, std::vector<std::string> const & params)
{
	// todo
	(void)sender;
	(void)params;
}

void	Server::_updateChannelMode( \
	Client & sender, Channel & channel, char modeChar, bool enable, \
	std::vector<std::string>::const_iterator & nextParamIt, \
	std::vector<std::string>::const_iterator const & end, \
	std::vector<std::string> & replyTokens)
{
	// mode 'i'
	if (modeChar == 'i') {
		if (enable && !channel.hasMode('i')) {
			channel.setMode('i');
			replyTokens[0] += "+i";
			return ;
		}
		if (!enable && channel.hasMode('i')) {
			channel.unsetMode('i');
			replyTokens[0] += "-i";
			return ;
		}
		return ;
	}

	// mode 't'
	if (modeChar == 't') {
		if (enable && !channel.hasMode('t')) {
			channel.setMode('t');
			replyTokens[0] += "+t";
			return ;
		}
		if (!enable && channel.hasMode('t')) {
			channel.unsetMode('t');
			replyTokens[0] += "-t";
			return ;
		}
		return ;
	}

	// mode 'k'
	if (modeChar == 'k') {
		if (enable) {
			if (nextParamIt == end) {
				throw Server::SyntaxErrorException();
			}
			channel.setMode('k');
			channel.setKey(*nextParamIt);
			replyTokens[0] += "+k";
			replyTokens.push_back(*nextParamIt);
			nextParamIt++;
			return ;
		}
		if (!enable && channel.hasMode('k')) {
			channel.unsetMode('k');
			channel.setKey("");
			replyTokens[0] += "-k";
			replyTokens.push_back("*");
			return ;
		}
		return ;
	}

	// mode 'l'
	if (modeChar == 'l') {
		if (enable) {
			if (nextParamIt == end) {
				throw Server::SyntaxErrorException();
			}
			if (!isValidInt(*nextParamIt)) {
				return ;
			}
			int limit = atoi(nextParamIt->c_str());
			nextParamIt++;
			if (limit < 2 || limit > MAX_CLIENTS) {
				return ;
			}
			channel.setMode('l');
			channel.setLimit(limit);
			replyTokens[0] += "+l";
			replyTokens.push_back(stringify(limit));
			return ;
		}
		if (!enable && channel.hasMode('l')) {
			channel.unsetMode('l');
			channel.setLimit(-1);
			replyTokens[0] += "-l";
			return ;
		}
		return ;
	}
	
	// mode 'o'
	if (modeChar == 'o') {
		if (nextParamIt == end) {
			throw Server::SyntaxErrorException();
		}
		Client* client = this->_clients.get(*nextParamIt);
		if (!client) {
			this->_reply(sender.getFd(), ERR_NOSUCHNICK(sender.getNickname(), *nextParamIt));
			return ;
		}
		if (!channel.isJoined(client)) {
			this->_reply(sender.getFd(), ERR_USERNOTINCHANNEL(sender.getNickname(), *nextParamIt, channel.getName()));
			return ;
		}
		if (channel.hasOperatorRights(client) == enable) {
			return ;
		}
		channel.setClientStatus(client, enable ? Channel::OPERATOR : Channel::MEMBER);
		replyTokens[0] += std::string(enable ? "+" : "-") + "o";
		replyTokens.push_back(*nextParamIt);
		nextParamIt++;
		return ;
	}
	
	// unknow mode
	this->_reply(sender.getFd(), ERR_UNKNOWNMODE(sender.getNickname(), stringify(modeChar), channel.getName()));
}

void	Server::_modeChannel(Client & sender, std::vector<std::string> const & params)
{
	if (params.empty()) {
		return ;
	}

	// check if channel exists
	Channel* channel = this->_channels.get(params[0]);
	if (!channel) {
		throw Server::ErrException(ERR_NOSUCHCHANNEL(sender.getNickname(), params[0]));
	}
	
	// if no mode is given
	if (params.size() == 1) {
		this->_reply(sender.getFd(), RPL_CHANNELMODEIS(sender.getNickname(), channel->getName(), channel->getModes()));
		// todo: RPL_CHANNELMODEIS add values if the user has rights
		this->_reply(sender.getFd(), RPL_CREATIONTIME(sender.getNickname(), channel->getName(), stringify(channel->getCreationTime())));
		return ;
	}

	// check if sender is operator of the channel
	if (!channel->hasOperatorRights(&sender)) {
		throw Server::ErrException(ERR_CHANOPRIVSNEEDED(sender.getNickname(), channel->getName()));
	}

	// apply mode changes
	std::vector<std::string> replyTokens;
	replyTokens.push_back("");
	std::vector<std::string>::const_iterator nextParamIt = params.begin() + 1;
	try {
		while (nextParamIt != params.end()) {
			std::string modeString = *nextParamIt;
			nextParamIt++;
			bool enable = true;
			for (size_t i = 0; i < modeString.size(); i++) {
				if (modeString[i] == '+' || modeString[i] == '-') {
					enable = (modeString[i] == '+');
				} else {
					_updateChannelMode(sender, *channel, modeString[i], enable, nextParamIt, params.end(), replyTokens);
				}
			}
		}
	} catch(Server::SyntaxErrorException &) {}

	// Create reply message
	if (replyTokens[0].empty()) {
		return ;
	}
	std::string replyMsg;
	char actionKey = '\0';
	for (size_t i = 0; i < replyTokens[0].size(); ++i) {
		if (replyTokens[0][i] != actionKey) {
			replyMsg += stringify(replyTokens[0][i]);
		}
		if (replyTokens[0][i] == '+' || replyTokens[0][i] == '-') {
			actionKey = replyTokens[0][i];
		}
	}
	for (size_t i = 1; i < replyTokens.size(); ++i) {
		replyMsg += " " + replyTokens[i];
	}
	
	// Send reply to all channel members
	std::map<Client*, Channel::t_status>::const_iterator it;
	for (it = channel->getClientLinks().begin(); it != channel->getClientLinks().end(); ++it) {
		if (it->first) {
			Client* client = it->first;
			Channel::t_status clientStatus = it->second;
			if (clientStatus >= Channel::MEMBER) {
				this->_reply(client->getFd(), RPL_MODE(client->getHostmask(), channel->getName(), replyMsg));
			}
		}
	}
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

	
	