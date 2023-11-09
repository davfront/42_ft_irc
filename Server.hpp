/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaxime- <mmaxime-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 15:52:34 by dapereir          #+#    #+#             */
/*   Updated: 2023/11/09 15:33:30 by mmaxime-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# define HOST					("ircserv.net")
# define VERSION				("1.0.0")
# define USERMODES				("o")
# define CHANNELMODES			("iklot")

# define RPL_SERVERNAME			HOST

# define POLL_INTERVAL			(1000)
# define REGISTRATION_TIMEOUT	(20)
# define MAX_CLIENTS			(10)

# include <algorithm>
# include <csignal>
# include <cstdlib>
# include <cstring>
# include <ctime>
# include <iostream>
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
# include "ChannelList.hpp"
# include "Command.hpp"
# include "Log.hpp"

class Server
{

	private:

		// Type definitions
		typedef void (Server::*cmdFn)(Client & sender, std::vector<std::string> const & params);

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
		ChannelList							_channels;
		std::map<std::string, cmdFn>		_cmds;
		std::time_t							_startTime;

		// Member functions
		void	_addPollfd(int fd);
		void	_removePollfd(int fd);

		void	_handleNewConnection(void);
		void	_deleteClient(int fd);
		void	_handleClientInput(Client & client);

		void	_initCmds(void);
		void	_executeCommand(Command const & cmd, Client & client);
		void	_checkRegistration(Client & client);
		bool	_isRegistrationTimedOut(Client & client) const;
		void	_reply(int fd, std::string const & msg) const;
		
		// Commands
		void	_pass(Client & sender, std::vector<std::string> const & params);
		void	_nick(Client & sender, std::vector<std::string> const & params);
		void	_user(Client & sender, std::vector<std::string> const & params);
		void	_motd(Client & sender, std::vector<std::string> const & params);
		void	_ping(Client & sender, std::vector<std::string> const & params);
		void	_pong(Client & sender, std::vector<std::string> const & params);
		void	_privmsg(Client & sender, std::vector<std::string> const & params);

		// Non-member functions
		static int const &				_checkPort(int const & port);
		static std::string const &		_checkPassword(std::string const & password);
		static int						_stringToPort(std::string const & token);
		static std::string				_motdMsg(Client & client);

	public:

		// Constructors & destructor
		Server(int port, std::string password);
		Server(std::string portToken, std::string password);
		~Server(void);

		// Getters
		int const &				getPort(void) const;
		std::string const &		getPassword(void) const;
		ClientList const &		getClients(void) const;
		ChannelList const &		getChannels(void) const;

		// Member functions
		void		start(void);
		void		stop(bool isSuccess);

		// Non member attributes
		static volatile int		receivedSignal;

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
		class MaxClientsReachedException: public std::runtime_error {
			public: MaxClientsReachedException(void): std::runtime_error("Limit of clients (" + stringify(MAX_CLIENTS) + ") reached") {}
		};
		class ErrException: public std::runtime_error {
			public: ErrException(std::string msg): std::runtime_error(msg) {}
		};
		class ConnectionException: public std::runtime_error {
			public: ConnectionException(std::string msg): std::runtime_error(msg) {}
		};
		class ServerException: public std::runtime_error {
			public: ServerException(std::string msg): std::runtime_error(msg) {}
		};	
};

// Output stream
std::ostream &	operator<<(std::ostream & o, Server const & x);

#endif
