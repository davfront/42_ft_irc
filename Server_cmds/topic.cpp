/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:16:19 by mmaxime-          #+#    #+#             */
/*   Updated: 2023/11/14 14:17:46 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	Server::_topic(Client & sender, std::vector<std::string> const & params)
{
	(void)sender;
	(void)params;
	Log::debug("TOPIC command called");
}
