#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
extern int h_errno;

#define IPv6_FORMAT_LENGTH 50

int resolveip_by_family( char **argv, int af ) {
  struct hostent *rv;
  int i;
  int v6i = -1;
  int v4i = -1;
  char *ipv6formatted;

  rv = gethostbyname2( argv[1], af );

  if ( rv == NULL ) {
    //herror(argv[1]);
    return 1;
  }
  /*
   *         struct hostent {
   *             char  *h_name;            // official name of host
   *             char **h_aliases;         // alias list
   *             int    h_addrtype;        // host address type
   *             int    h_length;          // length of address
   *             char **h_addr_list;       // list of addresses
   *         }
   *         #define h_addr h_addr_list[0] // for backward compatibility
   *
   *     The members of the hostent structure are:
   *
   *     h_name The official name of the host.
   *
   *     h_aliases
   *            An array of alternative names for the host, terminated by a NULL pointer.
   *
   *     h_addrtype
   *            The type of address; always AF_INET or AF_INET6 at present.
   *
   *     h_length
   *            The length of the address in bytes.
   *
   *     h_addr_list
   *            An array of pointers to network addresses for the host (in network byte order), terminated by a NULL pointer.
   *
   *     h_addr The first address in h_addr_list for backward compatibility.
   */

  for ( i = 0; &rv[i] != NULL && rv[i].h_addr_list != NULL && i < INT_MAX - 1; i++ ) {
    if ( rv[i].h_addrtype == AF_INET6 && v6i == -1 ) {
      v6i = i;
    }
    if ( rv[i].h_addrtype == AF_INET && v4i == -1 ) {
      v4i = i;
    }
  }

  if ( v6i != -1 ) {
    ipv6formatted = malloc(sizeof(char)*IPv6_FORMAT_LENGTH);
    if ( !ipv6formatted ) {
      fprintf( stderr, "Failed to malloc for ipv6 formatted!?!?\n" );
      exit( 1 );
    }

    //printf( "Found a v6 address.\n" );
    //printf( "%s\n", rv[v6i].h_addr_list[0] );
    inet_ntop( AF_INET6, rv[v6i].h_addr_list[0], ipv6formatted, IPv6_FORMAT_LENGTH );
    if ( !ipv6formatted ) {
      // Clearly an odd IPv6 address!?
      fprintf( stderr, "You should never get here.  Please let Dan know how you did.\n" );
      return 1;
    }
    printf( "%s\n", ipv6formatted );
  }
  else if ( v4i != -1 ) {
//    printf( "Found a v4 address.\n" );
    printf( "%s\n", inet_ntoa(*(struct in_addr *)rv[v4i].h_addr_list[0]) );
  }
  else {
    printf( "No candidate addresses found!?  This should never happen; tell Dan how you managed to do this.\n" );
    exit( 1 );
  }

  exit( 0 );
}

int main( int argc, char **argv ) {
  if ( argc != 2 || strlen(argv[1]) < 1 ) {
    fprintf( stderr, "Usage: %s <hostname>\n", argv[0] );
    exit( 1 );
  }

  resolveip_by_family( argv, AF_INET6 );
  resolveip_by_family( argv, AF_INET );

  fprintf( stderr, "%s: No such host.\n", argv[1] );
  exit( 1 );
}
