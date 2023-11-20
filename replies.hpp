/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replies.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 12:50:02 by dapereir          #+#    #+#             */
/*   Updated: 2023/11/16 17:32:36 by mmaxime-         ###   ########.fr       */
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
# define RPL_PING(msg)										(std::string(":") + RPL_SERVERNAME + " PONG " + RPL_SERVERNAME + " :" + msg + "\r\n")
# define RPL_JOIN(hostmask, channel)						(std::string(":") + hostmask + " JOIN " + channel + "\r\n")
# define RPL_PRIVMSG(hostmask, target, msg)					(std::string(":") + hostmask + " PRIVMSG " + target + " :" + msg + "\r\n")
# define RPL_OPER(nick)										(std::string(":") + RPL_SERVERNAME + " MODE " + nick + " :+o" + "\r\n")

// Numeric replies
// ==========================================================================

// Format
# define RPL(nick, code, msg)								(std::string(":") + RPL_SERVERNAME + " " + code + " " + nick + " " + msg + "\r\n")

// Success
# define RPL_WELCOME(nick, user, host)						RPL(nick, "001", ":Welcome to the Internet Relay Network, " + nick + "!" + user + "@" + host)
# define RPL_YOURHOST(nick, serv, ver)						RPL(nick, "002", ":Your host is " + serv + ", running version " + ver)
# define RPL_CREATED(nick, date)							RPL(nick, "003", ":This server was created " + date)
# define RPL_MYINFO(nick, serv, ver, userMod, chanMod)		RPL(nick, "004", serv + " " + ver + " " + userMod + " " + chanMod)

# define RPL_LISTSTART(nick)								RPL(nick, "321", "Channel :Users Name")
# define RPL_LIST(nick, channel, size, topic)		        RPL(nick, "322", channel + " " + size + " :" + topic)
# define RPL_LISTEND(nick)									RPL(nick, "323", ":End of /LIST")

# define RPL_TOPIC(nick, channel, topic)					RPL(nick, "332", channel + " :" + topic)
# define RPL_NAMREPLY(nick, channel, chanNicks)				RPL(nick, "353", "= " + channel + " :" + chanNicks)
# define RPL_ENDOFNAMES(nick, channel)						RPL(nick, "366", channel + " :End of /NAMES list")
# define RPL_UMODEIS(nick, mode)							RPL(nick, "221", mode)

# define RPL_MOTDSTART(nick, serv)							RPL(nick, "375", ":- " + serv + " Message of the day")
# define RPL_MOTD(nick, motd)								RPL(nick, "372", ":" + motd)
# define RPL_ENDOFMOTD(nick)								RPL(nick, "376", ":End of /MOTD command")

# define RPL_YOUREOPER(nick)								RPL(nick, "381", ":You are now an IRC operator")

// Error
# define ERR_NOSUCHNICK(nick, target)						RPL(nick, "401", target + " :No such nick/channel")
# define ERR_NOSUCHSERVER(nick, target)						RPL(nick, "402", target + " :No such server")
# define ERR_NOSUCHCHANNEL(nick, target)					RPL(nick, "403", target + " :No such channel")
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

# define ERR_NOOPERHOST(nick)								RPL(nick, "491", ":No O-lines for your host")

# define ERR_USERSDONTMATCH(nick)							RPL(nick, "502", ":Cant change mode for other users")

#endif
