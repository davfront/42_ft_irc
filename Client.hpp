/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 14:58:31 by dapereir          #+#    #+#             */
/*   Updated: 2023/10/06 20:57:51 by dapereir         ###   ########.fr       */
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

		// Prevent default constructor call
		Client(void);

		// Member attributes
		int const					_fd;
		std::string					_nickname;
		std::string					_username;
		std::string					_realname;
		bool						_isOper;

	public:

		// Constructors & destructor
		Client(int fd, std::string nickname, std::string username, std::string realname, bool isOper = false);
		Client(Client const & src);
		~Client(void);
	
		// Assignment operator
		Client &	operator=(Client const & rhs);

		// Getters
		int const &				getFd(void) const;
		std::string const &		getNickname(void) const;
		std::string const &		getUsername(void) const;
		std::string const &		getRealname(void) const;
		bool const &			getIsOper(void) const;

		// Setters
		void	setNickname(std::string const & nickname);
		void	setUsername(std::string const & username);
		void	setRealname(std::string const & realname);
		void	setIsOper(bool const & isOper);
};

// Output stream
std::ostream &	operator<<(std::ostream & o, Client const & x);

#endif
