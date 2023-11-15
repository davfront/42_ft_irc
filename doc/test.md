
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
# Command to join channel #foobar
JOIN #foo,#bar

# Command to join channel &foo using key "fubar"
JOIN &foo fubar

# Command to join channel #foo using key "fubar"
# and &bar using no key
JOIN #foo,&bar fubar

# Command to join channel #foo using  key "fubar",
# and channel #bar using key "foobar"
JOIN #foo,#bar fubar,foobar     

# Command to join channels #foo and #bar
JOIN #foo,#bar

# Leave all currently joined channels
JOIN 0
```