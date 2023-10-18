/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replies.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 12:50:02 by dapereir          #+#    #+#             */
/*   Updated: 2023/10/17 12:55:28 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REPLIES_HPP
# define REPLIES_HPP

# ifndef RPL_SERVERNAME
#  define RPL_SERVERNAME ("localhost")
# endif

# define RPL(nick, code, msg)								(std::string(":") + RPL_SERVERNAME + " " + code + " " + nick + " " + msg + "\r\n")

# define ERR_UNKNOWNCOMMAND(nick, cmd)						RPL(nick, "421", cmd + " :Unknown command")

#endif
