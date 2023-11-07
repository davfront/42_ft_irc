
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
