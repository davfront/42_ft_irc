/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelList.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 15:52:34 by dapereir          #+#    #+#             */
/*   Updated: 2023/11/14 17:21:07 by dapereir         ###   ########.fr       */
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

	public:
	
		// Custom comparator for std::map
		struct 	cmp {
			bool operator()(std::string const & s1, std::string const & s2) const {
				return (isEqualIgnoreCase(s1, s2));
			}
		};

		typedef std::map<std::string, Channel*, cmp>::iterator			iterator;
		typedef std::map<std::string, Channel*, cmp>::const_iterator	const_iterator;

		// Constructors & destructor
		ChannelList(void);
		~ChannelList(void);

		// Getters
		bool const &									getDeleteOnRemove(void) const;
		std::map<std::string, Channel*, cmp> const &	getChannels(void) const;

		// Setters
		void		setDeleteOnRemove(bool const & deleteOnRemove);

		// Member functions
		bool			empty(void) const;
		size_t			size(void) const;
		iterator		begin(void);
		const_iterator	begin(void) const;
		iterator		end(void);
		const_iterator	end(void) const;
	
		void			add(Channel* channel);
		void			remove(std::string const & name);
		Channel*		get(std::string const & name) const;
		
		
	private:

		// Prevent copy
		ChannelList(ChannelList const &) {}
		ChannelList &	operator=(ChannelList const &) { return (*this); }

		// Member attributes
		bool									_deleteOnRemove;
		std::map<std::string, Channel*, cmp>	_channels;

};

// Output stream
std::ostream &	operator<<(std::ostream & o, ChannelList const & x);

#endif
