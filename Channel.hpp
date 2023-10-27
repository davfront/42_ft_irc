/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 14:58:31 by dapereir          #+#    #+#             */
/*   Updated: 2023/10/27 11:26:48 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <iostream>

# include "Log.hpp"

class Channel
{
		
	private:

		// Prevent default constructor and copy
		Channel(void) {}
		Channel(Channel const &) {}
		Channel &	operator=(Channel const &) { return (*this); }

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
