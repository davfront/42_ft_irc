# ft_irc

## Resources

IRC clients:
- [Irssi](https://irssi.org/) - Simple CLI client
- [WeeChat](https://weechat.org/) - Extensible CLI client
- [Kiwi IRC](https://kiwiirc.com/) - Web client

IRC Protocols:
- [RFC 1459](https://datatracker.ietf.org/doc/html/rfc1459)
- [RFC 2812](https://datatracker.ietf.org/doc/html/rfc2812)

Miscellaneous:
- [ℳíиí₸ΞḶ ⱤØṨΞ](https://loving-slicer-4bc.notion.site/FT_IRC_-8ba17be867ac4c7cb2ad5e3ae5d91ce8) - Doc and tutorial
- [IRCv3](https://ircv3.net/)
- [Evaluation sheet](https://rphlr.github.io/42-Evals/Rank05/ft_irc/)

## Structure

### Server Class

Server class represents the IRC server itself.

#### Attributes:
- name
- address (IP or hostname)
- Port number
- List of connected clients
- List of available channels

#### Methods:

- Start: Initialize the server and begin listening for incoming connections.
- AcceptClient: Accept and handle incoming client connections.
- BroadcastMessage: Send a message to all connected clients.
- ManageChannels: Create, delete, and manage IRC channels.
- HandleCommands: Parse and process IRC commands received from clients.


### User Class

User class represents a connected user client.

#### Attributes:
- Client socket
- Nickname
- User modes (e.g., operator status)
- List of joined channels

#### Methods:
- Connect: Establish a connection to the server.
- Authenticate: Authenticate the client (e.g., with a password).
- JoinChannel: Join an IRC channel.
- SendMessage: Send a message to a channel or another user.
- LeaveChannel: Leave an IRC channel.
- Disconnect: Close the client's connection to the server.


### Operator Class (inherits from User):

Operator class represents IRC operators with elevated privileges.

Inherits from Client and adds additional operator-specific attributes and methods.

#### Channel operator commands:
- To be defined...

#### Channel operator commands:
- KICK - Eject a client from the channel
- INVITE - Invite a client to a channel
- TOPIC - Change or view the channel topic
- MODE - Change the channel’s mode:
  - i: Set/remove Invite-only channel
  - t: Set/remove the restrictions of the TOPIC command to channel
operators
  - k: Set/remove the channel key (password)
  - o: Give/take channel operator privilege
5
ft_irc Internet Relay Chat
  - l: Set/remove the user limit to channel

### Channel Class

Channel class represents an IRC channel (chat room).

#### Attributes:
- Channel name
- List of clients/users in the channel
- Channel modes (e.g., invite-only, moderated)

#### Methods:
- AddClient: Add a client to the channel.
- RemoveClient: Remove a client from the channel.
- SendChannelMessage: Send a message to all clients in the channel.
- SetChannelModes: Set or modify channel-specific modes.

### Message Class

Message class can be used to encapsulate and parse IRC messages. You can create instances of this class to represent messages sent between clients and the server.

### CommandParser Class

CommandParser class can be used to parse incoming IRC commands and route them to the appropriate handlers (e.g., join, part, privmsg).
