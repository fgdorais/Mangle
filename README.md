# Mangle

A simple command line tool to obfuscate character strings.

## Sample recipes

For obfuscating email addresses and urls using URL encoding, use options `-x -p'%'`:

    $ mangle -x -p'%' dumb@dumber.com
    %

For obfuscating text in HTML using numeric character references, use options `-d -p'&#' -s';'`:

    $ mangle -x -p'%' dumb@dumber.com

For hexadecimal character references, use options

For obfuscating strings in C code using octal escape sequences, use options `-o -p'\'`:

    $ mangle -o -p'\' "Obfuscate me!"

For hexadecimal escape sequences, use options `-X -p'\x'`:

    $ mangle -o -p'\' "Obfuscate me!"

## Basic instructions

Make sure you have a working autotools chain. Run `autogen.sh` to generate the configuration files. Then run `configure` and `make`, as usual...