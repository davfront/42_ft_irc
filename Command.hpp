/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 14:58:31 by dapereir          #+#    #+#             */
/*   Updated: 2023/11/27 14:44:43 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef COMMAND_HPP
# define COMMAND_HPP

# include <iostream>
# include <stdexcept>
# include <string>
# include <vector>

# include "utils.hpp"

# include "Log.hpp"

class Command
{
		
	private:

		// Prevent default constructor and copy
		Command(void) {}

		// Member attributes
		std::string					_prefix;
		std::string					_command;
		std::vector<std::string>	_parameters;

		// Non-member functions
		static std::string		_extractMessageToken(std::string & msg);

	public:

		// Constructors & destructor
		Command(std::string msg);
		Command(Command const & src);
		~Command(void);
		
		// Operators
		Command &	operator=(Command const & rhs);

		// Getters
		std::string const &					getPrefix(void) const;
		std::string const &					getCommand(void) const;
		std::vector<std::string> const &	getParameters(void) const;

		// Exceptions
		class TooLargeMessageException: public std::exception {
			public: virtual const char* what() const throw() {
				return "Too large message (510 characters max)";
			}
		};
		class InvalidMessageException: public std::exception {
			public: virtual const char* what() const throw() {
				return "Invalid message";
			}
		};
		class EmptyMessageException: public std::exception {
			public: virtual const char* what() const throw() {
				return "Empty message";
			}
		};


};

// Output stream
std::ostream &	operator<<(std::ostream & o, Command const & x);

#endif
