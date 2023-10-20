/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Log.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 09:39:09 by dapereir          #+#    #+#             */
/*   Updated: 2023/10/24 14:44:31 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOG_LVL_HPP
# define LOG_LVL_HPP

# include <ctime>
# include <iomanip>
# include <iostream>
# include <string>

# include "text_formatting.hpp"
# include "utils.hpp"

# ifndef LOG_LVL
#  define LOG_LVL (LOG_LVL_INFO)
# endif

enum e_level {
	LOG_LVL_DEBUG,
	LOG_LVL_IO,
	LOG_LVL_INFO,
	LOG_LVL_ERROR
};

class Log {
	
	public:

		// Non-member functions
		static void	debug(std::string const & msg);
		static void	info(std::string const & msg);
		static void	error(std::string const & msg);
		static void	input(int const & fd, std::string const & msg);
		static void	output(int const & fd, std::string const & msg);

	private:

		// Prevent constructor and copy
		Log(void) {}
		Log(Log const &) {}
		Log &	operator=(Log const &) { return (*this); }

		// Non-member functions
		static std::string	_timestamp(void);
		static void			_write(std::ostream & o, std::string const & style, std::string const & head, std::string const & msg);

};

#endif
