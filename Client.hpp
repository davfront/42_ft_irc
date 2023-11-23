/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaxime- <mmaxime-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 14:58:31 by dapereir          #+#    #+#             */
/*   Updated: 2023/11/23 17:31:05 by mmaxime-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <ctime>
# include <iostream>
# include <string>
# include <sys/socket.h>

# include "utils.hpp"

# include "Log.hpp"

class Client
{
		
	private:

		// Prevent default constructor and copy
		Client(void): _fd(-1), _connectTime(time(NULL)) {}
		Client(Client const &): _fd(-1), _connectTime(time(NULL)) {}
		Client &	operator=(Client const &) { return (*this); }

		// Member attributes
		int const					_fd;
		time_t const				_connectTime;
		std::string					_buffer;
		std::string					_hostname;
		std::string					_nickname;
		std::string					_username;
		std::string					_realname;
		std::string					_mode;
		bool						_isPasswordValid;
		bool						_isRegistered;
		bool						_isOper;

	public:

		// Constructors & destructor
		Client(int fd, std::string hostname);
		~Client(void);

		// Getters
		int const &				getFd(void) const;
		time_t const &			getConnectTime(void) const;
		std::string const &		getBuffer(void) const;
		std::string const &		getHostname(void) const;
		std::string const &		getNickname(void) const;
		std::string const &		getUsername(void) const;
		std::string const &		getRealname(void) const;
		std::string const &		getMode(void) const;
		bool const &			getIsPasswordValid(void) const;
		bool const &			getIsRegistered(void) const;
		bool const &			getIsOper(void) const;

		// Setters
		void					setBuffer(std::string const & str);
		void					setHostname(std::string const & hostname);
		void					setNickname(std::string const & nickname);
		void					setUsername(std::string const & username);
		void					setRealname(std::string const & realname);
		void					setMode(std::string const & mode);
		void					setIsPasswordValid(bool const & isPasswordValid);
		void					setIsRegistered(bool const & isRegistered);
		void					setIsOper(bool const & isOper);

		// Member functions
		void					addToBuffer(std::string const & str);
		bool					extractMessage(std::string & dest);
		std::string				getHostmask(void) const;
		void					reply(std::string const & msg) const;
		void					unsetMode(char modeChar);
};

// Output stream
std::ostream &	operator<<(std::ostream & o, Client const & x);

#endif
