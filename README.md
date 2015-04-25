# Mangle

A simple command line tool to obfuscate character strings.

## Sample recipes

For obfuscating email addresses and urls using URL encoding, use options `-x -l'%'`:

    $ mangle -x -l'%' dumb@dumber.com
    %64%75%6d%62%40%64%75%6d%62%65%72%2e%63%6f%6d

For obfuscating text in HTML using numeric character references, use options `-d -l'&#' -r';'`:

    $ mangle -x -l'&#' -r';' dumb@dumber.com
    &#100;&#117;&#109;&#98;&#64;&#100;&#117;&#109;&#98;&#101;&#114;&#46;&#99;&#111;&#109;

For hexadecimal character references, use options `-X -l'&#x' -r';'`:

    $ mangle -x -l'&#x' -r';' dumb@dumber.com
    &#x64;&#x75;&#x6D;&#x62;&#x40;&#x64;&#x75;&#x6D;&#x62;&#x65;&#x72;&#x2E;&#x63;&#x6F;&#x6D;
    
For obfuscating strings in C code using octal escape sequences, use options `-zo -w3 -l'\' -L'"' -R'"'`:

    $ mangle -zo -w3 -l'\' -L'"' -R'"' "obfuscated"
    "\157\142\146\165\163\143\141\164\145\144"
    
For hexadecimal escape sequences, use options `-zX -w2 -l'\' -L'"' -R'"'`:

    $ mangle -zX -w2 -l'\' -L'"' -R'"' "obfuscated"
    "\x6f\x62\x66\x75\x73\x63\x61\x74\x65\x64"

For inserting zeros before letters in a string, use options `-z -w2`:

    $ mangle -z -w2 "abc..."
    0a0b0c0.0.0.

## Basic instructions

Make sure you have a working autotools chain. Run `autogen.sh` to generate the configuration files. Then run `configure` and `make`, as usual...