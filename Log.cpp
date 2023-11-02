/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Log.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 10:01:16 by dapereir          #+#    #+#             */
/*   Updated: 2023/10/24 22:06:48 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Log.hpp"

// Non-member functions

std::string		Log::_timestamp(void)
{
	char	buf[9];
	time_t	t = time(NULL);
	tm*		tm = localtime(&t);
	
	strftime(buf, 9, "%H:%M:%S", tm);
	return (buf);
}

void	Log::_write(std::ostream & o, std::string const & style, std::string const & head, std::string const & msg)
{
	o << style;
	o << _timestamp() << "  ";
	if (!head.empty()) {
		o << std::left << std::setw(8) << head;
	}
	o << msg;
	o << Txt::RESET << std::endl;
}

// Member functions

void	Log::debug(std::string const & msg)
{
	if (LOG_LVL > LOG_LVL_DEBUG) {
		return ;
	}
	Log::_write(std::cout, Txt::FAINT, "DEBUG", msg);
}

void	Log::info(std::string const & msg)
{
	if (LOG_LVL > LOG_LVL_INFO) {
		return ;
	}
	Log::_write(std::cout, Txt::RESET, "", msg);
}

void	Log::error(std::string const & msg)
{
	if (LOG_LVL > LOG_LVL_ERROR) {
		return ;
	}
	Log::_write(std::cerr, Txt::RED, "ERROR", msg);
}

void	Log::input(int const & fd, std::string const & msg)
{
	if (LOG_LVL > LOG_LVL_IO) {
		return ;
	}
	Log::_write(std::cout, Txt::BLUE, "MSG_" + stringify(fd), msg);
}

void	Log::output(int const & fd, std::string const & msg)
{
	if (LOG_LVL > LOG_LVL_IO) {
		return ;
	}
	std::vector<std::string> lines = split(msg, "\r\n");
	for (size_t i = 0; i < lines.size(); ++i) {

		//	RPL or ERR
		std::string token;
		std::istringstream iss(lines[i]);
		iss >> token;
		iss >> token;
		std::string color = Txt::GREEN;
		std::string headPrefix = "RPL_";
		if (token[0] == '4' || token[0] == '5') {
			color = Txt::RED;
			headPrefix = "ERR_";
		}
		Log::_write(std::cout, color, headPrefix + stringify(fd), lines[i]);
	}
}
