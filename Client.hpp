/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 14:58:31 by dapereir          #+#    #+#             */
/*   Updated: 2023/10/15 14:39:43 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CLIENT_HPP
# define CLIENT_HPP

# ifndef DEBUG
#  define DEBUG (0)
# endif

# include <iostream>

# include "text_formatting.hpp"

class Client
{
		
	private:

		// Prevent default constructor and copy
		Client(void): _fd(-1) {}
		Client(Client const &): _fd(-1) {}
		Client &	operator=(Client const &) { return (*this); }

		// Member attributes
		int const					_fd;
		std::string					_hostname;
		std::string					_nickname;
		std::string					_username;
		std::string					_realname;
		bool						_isOper;
		std::string					_buffer;

	public:

		// Constructors & destructor
		Client(int fd, std::string hostname);
		~Client(void);

		// Getters
		int const &				getFd(void) const;
		std::string const &		getHostname(void) const;
		std::string const &		getNickname(void) const;
		std::string const &		getUsername(void) const;
		std::string const &		getRealname(void) const;
		bool const &			getIsOper(void) const;
		std::string const &		getBuffer(void) const;

		// Setters
		void	setHostname(std::string const & hostname);
		void	setNickname(std::string const & nickname);
		void	setUsername(std::string const & username);
		void	setRealname(std::string const & realname);
		void	setIsOper(bool const & isOper);
		void	setBuffer(std::string const & str);

		// Member functions
		void		addToBuffer(std::string const & str);
		std::string	extractMessage(void);
};

// Output stream
std::ostream &	operator<<(std::ostream & o, Client const & x);

#endif
