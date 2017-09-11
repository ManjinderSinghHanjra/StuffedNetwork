#include <error.h>
#include "setup.h"
#include "constants.h"

/* TCPServerSetup will connect to any possible available interface on host that will accept the request
   and will negotiate all the protocol rules successfully
   ------------------------------------------------
   -- host, service   : typeof char*
   -- add_Criteria : typeof addrinfo
   -- add_server      : typeof addrinfo
   -- getaddrinfo()   :
   ------------------------------------------------
   -- socket()
   -- bind()
   -- listen()
   ------------------------------------------------
   -- free(add_server): Linked List : typeof addrinfo
   -- return socketDesciptor
   ------------------------------------------------
*/

int SetupTCPServer(const char *service)
{
	/* Setup the criteria for what kind(s) of addresses we want to look out for */
	struct addrinfo add_Criteria;
	memset(&addressCriteria, 0, sizeof(add_Criteria));
	add_Criteria.ai_family   = AF_UNSPEC;		// Any address family
	add_Criteria.ai_flags    = AI_PASSIVE;		// Accept on all ports/addresses
	add_Criteria.ai_socktype = SOCK_STREAM;
	add_Criteria.ai_protocol = IPPROTO_TCP;

	/* Get the addresses from all the interfaces that are available on the system */
	struct addrinfo *add_server;
	int retVal = getaddrinfo(NULL, service, &add_Criteria, &add_server);
	if(retVal != 0)
	{
		SysMessage(gai_strerror(retVal));
		return -1;
    }

    int sd_server;
    for(struct addrinfo *addr = server; addr != NULL; addr = addr->ai_next)
    {
        sd_server = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
        if(sd_server != 0)
        {
            // Can't get a socket descriptor, so continue to the next iteration
            continue;
        }
        retVal = bind(sd_server, addr->ai_addr, addr->ai_addrlen);
        if(retVal != 0)
        {
            close(sd_server);
            continue;
        }
        retVal = listen(sd_server, MAX_CONNECTIONS);
        if(retVal != 0)
        {
            close(sd_server);
            continue;
        }
        struct sockaddr_storage add_local;
        socklen_t add_size = sizeof add_local;
        retVal=getsockname(sd_server, (struct sockaddr*)&add_local, add_size)
        if( retVal != 0 )
        {
            UserMessage("<getsockname()> failed:", perror(retVal));
            close(sd_server);
        }
        // Bind has been done. We have bound the socket_descriptor to an interface with IP, can quit now
        fputs("Binding to <address, port>: ", stdout);
        PrintSocketName((struct sockaddr*)&add_local, stdout);
        fputc("\n", stdout);
        break;
    }

    return sd_server;
}


/* TCP Client Setup will connect to any possible available interface on host that will accept the request
   and will negotiate all the protocol rules successfully
   -------------------------------------
   -- host, service   : typeof char*
   -- add_Criteria : typeof addrinfo
   -- add_server      : typeof addrinfo
   -- getaddrinfo()   :
   -------------------------------------
   -- socket()
   -- bind() [optiona] +hasn't been implemented
   -- connect()
   -------------------------------------
   -- return : socketDesciptor
   -------------------------------------
*/

int SetupTCPClient(const char *host, const char *service)
{
    /* Setup the criteria for what kind(s) of addresses we want to look out for */
	struct addrinfo add_Criteria;
	memset(&addressCriteria, 0, sizeof(add_Criteria));
	add_Criteria.ai_family   = AF_UNSPEC;		// Any address family
	add_Criteria.ai_socktype = SOCK_STREAM;
	add_Criteria.ai_protocol = IPPROTO_TCP;

	/* Get the addresses from all the interfaces that are available on the system */
	struct addrinfo *add_server;
	int retVal = getaddrinfo(host, service, &add_Criteria, &add_server);
	if(retVal != 0)
	{
		SysMessage(gai_strerror(retVal));
		return -1;
    }

    int sd_server;
    for(struct addrinfo *addr = server; addr != NULL; addr = addr->ai_next)
    {
        sd_server = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
        if(sd_server != 0)
        {
            // Can't get a socket descriptor, so continue to the next iteration
            continue;
        }
        retVal = connect(sd_server, add_server->ai_addr, add_server->ai_addrlen);
        if(retVal != 0)
        {
            close(sd_server);
            SysMessage("<error> connect(): ");
            continue;
        }
        // successfully connected to the server, break the loop execution now
        break;
    }
    return sd_server;
}
