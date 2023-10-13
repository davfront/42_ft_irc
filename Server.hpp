/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 15:52:34 by dapereir          #+#    #+#             */
/*   Updated: 2023/10/13 12:08:21 by marvin           ###   ########.fr       */
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
# include <string>
# include <sys/socket.h>
# include <sys/types.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <unistd.h>
# include <poll.h>
# include <vector>
# include <fcntl.h>
# include <stdio.h>
# include <netdb.h>

# include "text_formatting.hpp"

# include "ClientList.hpp"
# include "Channel.hpp"
# include "Command.hpp"

class Server
{
		
	private:

		// Prevent default constructor and copy
		Server(void) {}
		Server(Server const &) {}
		Server &	operator=(Server const &) { return (*this); }

		// Member attributes
		int									_port;
		std::string							_password;
		int									_server_socket;
		ClientList							_clients;
		std::map<std::string, Channel*>		_channels;

		// Non-member functions
		static int const &				_checkPort(int const & port);
		static std::string const &		_checkPassword(std::string const & password);
		static int						_stringToPort(std::string const & token);

	public:

		// Constructors & destructor
		Server(int port, std::string password);
		Server(std::string portToken, std::string password);
		~Server(void);

		// Getters
		int const &									getPort(void) const;
		std::string const &							getPassword(void) const;
		ClientList const &							getClients(void) const;
		std::map<std::string, Channel*> const &		getChannels(void) const;

		// Member functions
		int			init();
		void		addClient(Client* client);
		void		removeClient(int fd);
		Client*		getClient(int const & fd) const;
	
		void		addChannel(Channel* channel);
		void		deleteChannel(std::string name);
		Channel*	getChannel(std::string const & name) const;
		void		printChannels(void) const;

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