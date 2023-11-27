
# ngircd logs

```sh
sudo journalctl -u ngircd -f
```

## Start server

```sh
./ircserv 1234 password
```

## Connect

```sh
nc -C localhost 1234
nc -C localhost 6667
```

## Register

```sh
PASS password
NICK davfront
USER dapereir 0 * :David Pereira
```

```sh
PASS password
NICK jo
USER johndoe 0 * :John Doe
```

```sh
PASS password
NICK bill
USER billy 0 * :Billy the kid
```

## PRIVMSG

```sh
PRIVMSG jo :Hi jo, this is bill
```

## JOIN

```sh
# Command to join channels #foo and #bar
JOIN #foo,#bar

# Leave all currently joined channels
JOIN 0
```

## Send file with irssi

Getter create and configure a download folder:
```sh
mkdir <path/to/dl_folder>
chmod 777 <path/to/dl_folder>

# irssi
/set dcc_download_path <path/to/dl_folder>
```

Sender does:
```sh
# irssi
/dcc send <getterNickname> <path/to/file>
```

Getter does:
```sh
# irssi
/dcc get <senderNickname>
```