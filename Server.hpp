/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 15:52:34 by dapereir          #+#    #+#             */
/*   Updated: 2023/10/05 11:21:43 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# ifndef DEBUG
#  define DEBUG (0)
# endif

# include <iostream>
# include <cstdlib>
# include <stdexcept>

# include "text_formatting.hpp"

class Server
{
		
	private:

		// Prevent default constructor call
		Server(void) {}

		// Member attributes
		int				_port;
		std::string		_password;

		// Non-member functions
		static int const &			_checkPort(int const & port);
		static std::string const &	_checkPassword(std::string const & password);
		static int					_stringToPort(std::string const & token);

	public:

		// Constructors & destructor
		Server(int port, std::string password);
		Server(std::string portToken, std::string password);
		Server(Server const & src);
		~Server(void);
		
        // Assignment operator
		Server &	operator=(Server const & rhs);

		// Getters
		int const &			getPort(void) const;
		std::string const &	getPassword(void) const;

		// Exceptions
		class InvalidPortException: public std::exception {
			public: virtual const char* what() const throw() {
				return "Invalid port: Provide an integer in range [0, 65535]";
			}
		};
		class InvalidPasswordException: public std::exception {
			public: virtual const char* what() const throw() {
				return "Invalid password: Provide at least 8 characters";
			}
		};
};

// Output stream
std::ostream &	operator<<(std::ostream & o, Server const & x);

#endif