# resolve6ip
Simple utility to resolve a hostname to either an IPv6 or IPv4 address

I'm a huge fan of the simplicity and directness of a utility provided by MySQL called "resolveip". However,
resolveip only works for IPv4 addresses, which isn't ideal in a modern environment.  Thus, a quick bit of
hacking later, here's resolve6ip, which first tries to find an IPv6 address if it can, and then falls back
to IPv4 otherwise.  Usage couldn't be simpler: no flags, no fancy tricks, just <code>resolve6ip somehost.com</code> and you'll
get back either the IPv6 or the IPv4 address, as appropriate.

Open-source/free-as-in-speech/free-as-in-beer.  Let me know if you need it under different licensing terms.  Enjoy!
