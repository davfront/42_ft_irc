/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 23:30:41 by dapereir          #+#    #+#             */
/*   Updated: 2023/10/27 10:27:12 by dapereir         ###   ########.fr       */
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
		start = end + sep.size();
		end = s.find(sep, start);
	}

	token = s.substr(start, end - start);
	if (!token.empty() || keepEmpty) {
		tokens.push_back(s.substr(start, end));
	}

	return (tokens);
}

bool	isEqualIgnoreCase(std::string const & s1, std::string const & s2) {
	if (s1.size() != s2.size()) {
		return (false);
	}
	for (size_t i = 0; i < s1.size(); i++) {
		if (tolower(s1[i]) != tolower(s2[i])) {
			return (false);
		}
	}
	return (true);
}
