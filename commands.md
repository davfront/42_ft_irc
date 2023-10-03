# Commands

## Connection Registration

- [PASS](https://datatracker.ietf.org/doc/html/rfc1459#section-4.1.1)
- [NICK](https://datatracker.ietf.org/doc/html/rfc1459#section-4.1.2)
- [USER](https://datatracker.ietf.org/doc/html/rfc1459#section-4.1.3)
- [~~SERVER~~](https://datatracker.ietf.org/doc/html/rfc1459#section-4.1.4) - server connection not required
- [OPER](https://datatracker.ietf.org/doc/html/rfc1459#section-4.1.5)
- [QUIT](https://datatracker.ietf.org/doc/html/rfc1459#section-4.1.6)
- [~~SQUIT~~](https://datatracker.ietf.org/doc/html/rfc1459#section-4.1.7) - server connection not required

## Channel operations

- [JOIN](https://datatracker.ietf.org/doc/html/rfc1459#section-4.2.1)
- [PART](https://datatracker.ietf.org/doc/html/rfc1459#section-4.2.2)
- [MODE](https://datatracker.ietf.org/doc/html/rfc1459#section-4.2.3)

	#### [Channel modes](https://datatracker.ietf.org/doc/html/rfc1459#section-4.2.3.1)
	- o - give/take channel operator privileges
	- ~~p - private channel flag~~ - not required
	- ~~s - secret channel flag~~ - not required
	- i - invite-only channel flag
	- t - topic settable by channel operator only flag
	- ~~n - no messages to channel from clients on the outside~~ - not required
	- ~~m - moderated channel~~ - not required
	- l - set the user limit to channel
	- ~~b - set a ban mask to keep users out~~ - not required
	- ~~v - give/take the ability to speak on a moderated channel~~ - not required
	- k - set a channel key (password)

	#### [User modes](https://datatracker.ietf.org/doc/html/rfc1459#section-4.2.3.2)
	- i - marks a user as invisible;
	- s - marks a user for receipt of server notices;
	- w - user receives wallops;
	- o - operator flag.


- [TOPIC](https://datatracker.ietf.org/doc/html/rfc1459#section-4.2.4)
- [~~NAMES~~](https://datatracker.ietf.org/doc/html/rfc1459#section-4.2.5) - not required
- [~~LIST~~](https://datatracker.ietf.org/doc/html/rfc1459#section-4.2.6) - not required
- [INVITE](https://datatracker.ietf.org/doc/html/rfc1459#section-4.2.7)
- [KICK](https://datatracker.ietf.org/doc/html/rfc1459#section-4.2.8)

## Server queries and commands

- [VERSION](https://datatracker.ietf.org/doc/html/rfc1459#section-4.3.1)
- [STATS](https://datatracker.ietf.org/doc/html/rfc1459#section-4.3.2)
- [LINKS](https://datatracker.ietf.org/doc/html/rfc1459#section-4.3.3)
- [TIME](https://datatracker.ietf.org/doc/html/rfc1459#section-4.3.4)
- [CONNECT](https://datatracker.ietf.org/doc/html/rfc1459#section-4.3.5)
- [TRACE](https://datatracker.ietf.org/doc/html/rfc1459#section-4.3.6)
- [ADMIN](https://datatracker.ietf.org/doc/html/rfc1459#section-4.3.7)
- [INFO](https://datatracker.ietf.org/doc/html/rfc1459#section-4.3.8)

## Sending messages

- [PRIVMSG](https://datatracker.ietf.org/doc/html/rfc1459#section-4.4.1)
- [NOTICE](https://datatracker.ietf.org/doc/html/rfc1459#section-4.4.2)

## User based queries

- [WHO](https://datatracker.ietf.org/doc/html/rfc1459#section-4.5.1)
- [WHOIS](https://datatracker.ietf.org/doc/html/rfc1459#section-4.5.2)
- [WHOWAS](https://datatracker.ietf.org/doc/html/rfc1459#section-4.5.3)

## Miscellaneous messages

- [KILL](https://datatracker.ietf.org/doc/html/rfc1459#section-4.6.1)
- [PING](https://datatracker.ietf.org/doc/html/rfc1459#section-4.6.2)
- [PONG](https://datatracker.ietf.org/doc/html/rfc1459#section-4.6.3)
- [ERROR](https://datatracker.ietf.org/doc/html/rfc1459#section-4.6.4)
