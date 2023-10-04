/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 15:52:34 by dapereir          #+#    #+#             */
/*   Updated: 2023/10/05 09:58:20 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# ifndef DEBUG
#  define DEBUG (0)
# endif

# include <iostream>
# include "text_formatting.hpp"

class Server
{

	public:

		// Constructors & destructor
		Server(int port, std::string password);
		Server(Server const & src);
		~Server(void);
		
        // Assignment operator
		Server &	operator=(Server const & rhs);

		// Getters
		int const &			getPort(void) const;
		std::string const &	getPassword(void) const; // todo: check if security issue
		

	private:

		// Prevent default constructor call
		Server(void) {}

		// Member attributes
		int				_port;
		std::string		_password;

};

// Output stream
std::ostream &	operator<<(std::ostream & o, Server const & x);

#endif