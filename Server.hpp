/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 15:52:34 by dapereir          #+#    #+#             */
/*   Updated: 2023/10/06 20:58:18 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# ifndef DEBUG
#  define DEBUG (0)
# endif

# include <iostream>
# include <cstdlib>
# include <map>
# include <stdexcept>

# include "text_formatting.hpp"

# include "Client.hpp"

class Server
{
		
	private:

		// Prevent default constructor call
		Server(void) {}

		// Member attributes
		int						_port;
		std::string				_password;
		std::map<int, Client*>	_clients;

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
		int const &						getPort(void) const;
		std::string const &				getPassword(void) const;
		std::map<int, Client*> const &	getClients(void) const;

		// Member functions
		void		addClient(Client* client);
		void		deleteClient(int fd);
		Client*		getClient(int const & fd) const;
		Client*		getClientByNick(std::string const & nickname) const;
		void		printClients(void) const;

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
