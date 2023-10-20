/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 15:52:34 by dapereir          #+#    #+#             */
/*   Updated: 2023/10/21 01:35:25 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# define HOST			("ircserv.net")
# define VERSION		("1.0.0")
# define USERMODES		("o")
# define CHANNELMODES	("iklot")

# define RPL_SERVERNAME	HOST

# include <iostream>
# include <cstdlib>
# include <cstring>
# include <ctime>
# include <map>
# include <stdexcept>
# include <string>
# include <vector>

# include <sys/socket.h>
# include <sys/types.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <unistd.h>
# include <poll.h>
# include <fcntl.h>
# include <stdio.h>
# include <netdb.h>

# include "replies.hpp"
# include "text_formatting.hpp"
# include "utils.hpp"

# include "ClientList.hpp"
# include "Channel.hpp"
# include "Command.hpp"
# include "Log.hpp"

class Server
{

	private:

		// Type definitions
		typedef void (Server::*cmdFn)(Client & client, std::vector<std::string> const & params);

		// Prevent default constructor and copy
		Server(void) {}
		Server(Server const &) {}
		Server &	operator=(Server const &) { return (*this); }

		// Member attributes
		int									_port;
		std::string							_password;
		int									_serverSocket;
		std::vector<pollfd>					_pollfds;
		ClientList							_clients;
		std::map<std::string, Channel*>		_channels;
		std::map<std::string, cmdFn>		_cmds;
		std::time_t							_startTime;

		// Member functions
		void	_addPollfd(int fd);
		void	_removePollfd(int fd);

		void	_handleNewConnection(void);
		void	_deleteClient(int fd);
		void	_handleClientInput(int fd);
		
		void	_initCmds(void);
		void	_executeCommand(Command const & cmd, Client & client);
		void	_checkRegistration(Client & client);
		void	_reply(int fd, std::string const & msg) const;
	
		// Commands
		void	_pass(Client & client, std::vector<std::string> const & params);
		void	_nick(Client & client, std::vector<std::string> const & params);
		void	_user(Client & client, std::vector<std::string> const & params);

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
		void		start(void);

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
		class ErrException: public std::exception {
			private:
				std::string	_msg;
			public:
				ErrException(std::string msg): _msg(msg) {}
				ErrException(ErrException const & src): _msg(src._msg) {}
				virtual ~ErrException(void) throw() {}
				virtual const char* what() const throw() {
					return (this->_msg.c_str());
				}
		};
};

// Output stream
std::ostream &	operator<<(std::ostream & o, Server const & x);

#endif
