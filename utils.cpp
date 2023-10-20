/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 23:30:41 by dapereir          #+#    #+#             */
/*   Updated: 2023/10/20 23:56:42 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"

std::string formatTime(time_t t)
{
	char		buf[128];
	struct tm	*tm;

	tm = localtime(&t);
	strftime(buf, sizeof(buf), "%a %b %d %Y at %H:%M:%S (%Z)", tm);
	return (std::string(buf));
}

std::vector<std::string>	split(std::string const & s, std::string const & sep, bool keepEmpty) {
	std::vector<std::string> tokens;
	size_t start = 0;
	size_t end = s.find(sep);
	std::string token;

	while (end != std::string::npos) {
		token = s.substr(start, end - start);
		if (!token.empty() || keepEmpty) {
			tokens.push_back(token);
		}
		start = end + sep.length();
		end = s.find(sep, start);
	}

	token = s.substr(start, end - start);
	if (!token.empty() || keepEmpty) {
		tokens.push_back(s.substr(start, end));
	}

	return (tokens);
}
