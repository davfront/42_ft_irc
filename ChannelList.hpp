/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelList.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 15:52:34 by dapereir          #+#    #+#             */
/*   Updated: 2023/10/27 11:23:40 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNELLIST_HPP
# define CHANNELLIST_HPP

# include <iostream>
# include <map>
# include <string>

# include "utils.hpp"

# include "Channel.hpp"
# include "Log.hpp"

class ChannelList
{
		
	private:

		// Prevent copy
		ChannelList(ChannelList const &) {}
		ChannelList &	operator=(ChannelList const &) { return (*this); }

		// Member attributes
		bool								_deleteOnRemove;
		std::map<std::string, Channel*>		_channels;

	public:

		// Constructors & destructor
		ChannelList(void);
		~ChannelList(void);

		// Getters
		bool const &								getDeleteOnRemove(void) const;
		std::map<std::string, Channel*> const &		getChannels(void) const;

		// Setters
		void		setDeleteOnRemove(bool const & deleteOnRemove);

		// Member functions
		bool		empty(void) const;
		size_t		size(void) const;
		void		add(Channel* channel);
		void		remove(std::string const & name);
		Channel*	get(std::string const & name) const;
};

// Output stream
std::ostream &	operator<<(std::ostream & o, ChannelList const & x);

#endif
