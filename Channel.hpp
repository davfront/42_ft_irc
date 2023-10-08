/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 14:58:31 by dapereir          #+#    #+#             */
/*   Updated: 2023/10/08 10:42:04 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# ifndef DEBUG
#  define DEBUG (0)
# endif

# include <iostream>

# include "text_formatting.hpp"

class Channel
{
		
	private:

		// Prevent default constructor and copy
		Channel(void);
		Channel(Channel const & src);
		Channel &	operator=(Channel const & rhs);

		// Member attributes
		std::string const			_name;
		std::string					_topic;
		bool						_isInviteOnly;

	public:

		// Constructors & destructor
		Channel(std::string name, std::string topic = "", bool isInviteOnly = false);
		~Channel(void);

		// Getters
		std::string const &		getName(void) const;
		std::string const &		getTopic(void) const;
		bool const &			getIsInviteOnly(void) const;

		// Setters
		void	setTopic(std::string const & topic);
		void	setIsInviteOnly(bool const & isInviteOnly);
};

// Output stream
std::ostream &	operator<<(std::ostream & o, Channel const & x);

#endif
