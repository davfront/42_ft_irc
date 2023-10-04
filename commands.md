# Commands

## Connection Registration

- [**PASS**](https://datatracker.ietf.org/doc/html/rfc2812#section-3.1.1) - mandatory
- [**NICK**](https://datatracker.ietf.org/doc/html/rfc2812#section-3.1.2) - mandatory
- [**USER**](https://datatracker.ietf.org/doc/html/rfc2812#section-3.1.3) - mandatory
- [OPER](https://datatracker.ietf.org/doc/html/rfc2812#section-3.1.4)
- [MODE](https://datatracker.ietf.org/doc/html/rfc2812#section-3.1.5)
- [~~SERVICE~~](https://datatracker.ietf.org/doc/html/rfc2812#section-3.1.6) - bot bonus
- [QUIT](https://datatracker.ietf.org/doc/html/rfc2812#section-3.1.7)
- [~~SQUIT~~](https://datatracker.ietf.org/doc/html/rfc2812#section-3.1.8) - server connection not required

## Channel operations

- [**JOIN**](https://datatracker.ietf.org/doc/html/rfc2812#section-3.2.1) - mandatory
- [**PART**](https://datatracker.ietf.org/doc/html/rfc2812#section-3.2.2) - mandatory
- [**MODE**](https://datatracker.ietf.org/doc/html/rfc2812#section-3.2.3) - mandatory
	#### Channel modes (required in subject) :
	- i: Set/remove Invite-only channel
	- t: Set/remove the restrictions of the TOPIC command to channel operators
	- k: Set/remove the channel key (password)
	- o: Give/take channel operator privilege
	- l: Set/remove the user limit to channel


- [**TOPIC**](https://datatracker.ietf.org/doc/html/rfc2812#section-3.2.4) - mandatory
- [NAMES](https://datatracker.ietf.org/doc/html/rfc2812#section-3.2.5)
- [LIST](https://datatracker.ietf.org/doc/html/rfc2812#section-3.2.6)
- [**INVITE**](https://datatracker.ietf.org/doc/html/rfc2812#section-3.2.7) - mandatory
- [**KICK**](https://datatracker.ietf.org/doc/html/rfc2812#section-3.2.8) - mandatory

## Sending messages

- [**PRIVMSG**](https://datatracker.ietf.org/doc/html/rfc2812#section-3.3.1) - mandatory
- [NOTICE](https://datatracker.ietf.org/doc/html/rfc2812#section-3.3.2)

## Server queries and commands

- [MOTD](https://datatracker.ietf.org/doc/html/rfc2812#section-3.4.1)
- [LUSERS](https://datatracker.ietf.org/doc/html/rfc2812#section-3.4.2)
- [VERSION](https://datatracker.ietf.org/doc/html/rfc2812#section-3.4.3)
- [STATS](https://datatracker.ietf.org/doc/html/rfc2812#section-3.4.4)
- [LINKS](https://datatracker.ietf.org/doc/html/rfc2812#section-3.4.5)
- [TIME](https://datatracker.ietf.org/doc/html/rfc2812#section-3.4.6)
- [CONNECT](https://datatracker.ietf.org/doc/html/rfc2812#section-3.4.7)
- [TRACE](https://datatracker.ietf.org/doc/html/rfc2812#section-3.4.8)
- [ADMIN](https://datatracker.ietf.org/doc/html/rfc2812#section-3.4.9)
- [INFO](https://datatracker.ietf.org/doc/html/rfc2812#section-3.4.10)

## Service Query and Commands

- [SERVLIST](https://datatracker.ietf.org/doc/html/rfc2812#section-3.5.1)
- [SQUERY](https://datatracker.ietf.org/doc/html/rfc2812#section-3.5.2)

## User based queries

- [WHO](https://datatracker.ietf.org/doc/html/rfc2812#section-3.6.1)
- [WHOIS](https://datatracker.ietf.org/doc/html/rfc2812#section-3.6.2)
- [WHOWAS](https://datatracker.ietf.org/doc/html/rfc2812#section-3.6.3)

## Miscellaneous messages

- [KILL](https://datatracker.ietf.org/doc/html/rfc2812#section-3.7.1)
- [PING](https://datatracker.ietf.org/doc/html/rfc2812#section-3.7.2)
- [PONG](https://datatracker.ietf.org/doc/html/rfc2812#section-3.7.3)
- [ERROR](https://datatracker.ietf.org/doc/html/rfc2812#section-3.7.4)
