/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replies.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaxime- <mmaxime-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 12:50:02 by dapereir          #+#    #+#             */
/*   Updated: 2023/11/08 15:03:43 by mmaxime-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REPLIES_HPP
# define REPLIES_HPP

# ifndef RPL_SERVERNAME
#  define RPL_SERVERNAME ("localhost")
# endif


// Non numeric replies
// ==========================================================================

# define RPL_ERROR(msg)							            (std::string("ERROR :") + msg + "\r\n")
# define RPL_PRIVMSG(hostmask, target, msg)					(std::string(":") + hostmask + " PRIVMSG " + target + " :" + msg + "\r\n")
# define RPL_PING(msg)										(std::string(":") + RPL_SERVERNAME + " PONG " + RPL_SERVERNAME + " :" + msg + "\r\n")


// Numeric replies
// ==========================================================================

// Format
# define RPL(nick, code, msg)								(std::string(":") + RPL_SERVERNAME + " " + code + " " + nick + " " + msg + "\r\n")

// Success
# define RPL_WELCOME(nick, user, host)						RPL(nick, "001", ":Welcome to the Internet Relay Network, " + nick + "!" + user + "@" + host)
# define RPL_YOURHOST(nick, serv, ver)						RPL(nick, "002", ":Your host is " + serv + ", running version " + ver)
# define RPL_CREATED(nick, date)							RPL(nick, "003", ":This server was created " + date)
# define RPL_MYINFO(nick, serv, ver, userMod, chanMod)		RPL(nick, "004", serv + " " + ver + " " + userMod + " " + chanMod)

# define RPL_MOTDSTART(nick, serv)							RPL(nick, "375", ":- " + serv + " Message of the day")
# define RPL_MOTD(nick, motd)								RPL(nick, "372", ":" + motd)
# define RPL_ENDOFMOTD(nick)								RPL(nick, "376", ":End of /MOTD command")

// Error
# define ERR_NOSUCHNICK(nick, target)						RPL(nick, "401", target + " :No such nick/channel")
# define ERR_CANNOTSENDTOCHAN(nick, target)					RPL(nick, "404", target + " :Cannot send to channel")

# define ERR_NOORIGIN(nick)									RPL(nick, "409", ":No origin specified")	

# define ERR_NORECIPIENT(nick, cmd)							RPL(nick, "411", ":No recipient given (" + cmd + ")")
# define ERR_NOTEXTTOSEND(nick)								RPL(nick, "412", ":No text to send")

# define ERR_UNKNOWNCOMMAND(nick, cmd)						RPL(nick, "421", cmd + " :Unknown command")

# define ERR_NONICKNAMEGIVEN(nick)							RPL(nick, "431", ":No nickname given")
# define ERR_ERRONEUSNICKNAME(nick, newNick)				RPL(nick, "432", newNick + " :Erroneus nickname")
# define ERR_NICKNAMEINUSE(nick, newNick)					RPL(nick, "433", newNick + " :Nickname is already in use")

# define ERR_NOTREGISTERED(nick)							RPL(nick, "451", ":You have not registered")

# define ERR_NEEDMOREPARAMS(nick, cmd)						RPL(nick, "461", cmd + " :Not enough parameters")
# define ERR_ALREADYREGISTERED(nick)						RPL(nick, "462", ":You may not reregister")
# define ERR_PASSWDMISMATCH(nick)							RPL(nick, "464", ":Password incorrect")

#endif
