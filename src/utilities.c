#include "utilities.h"

void HandleTCPClient(int sd_client)
{

}

void PrintSocketAddress(const struct sockaddr *address, FILE *stream)
{
    if(address==NULL || stream==NULL)
        return;

    void *numericAddress;
    char buffer[INET6_ADDRSTRLEN];
    in_port_t port;

    switch(address->sa_family)
    {
        case AF_INET:
            numericAddress = &((struct sockaddr_in *) address)->sin_addr;
            port           = ntohs(((struct sockaddr_in *) address)->sin_port);
            break;
        case AF_INET6:
            numericAddress = &((struct sockaddr_in *) address)->sin_addr;
            port           = ntohs(((struct sockaddr_in *) address)->sin_port);
            break;
        default:
            fputs("[unknown type]", stream);
            return;
    }

    if(inet_ntop(address->sa_family, numericAddress, buffer, sizeof(buffer)) == NULL)
        fputs("[invalid address]", stream);
    else
    {
        fputs(stream, "%s", buffer);
        if(port != 0)
            fprintf(stream, "%-u", port);
    }
}

struct addrinfo* GetAddressInfo(const char *address, const char *port, size_t protocol, size_t flags)
{
    struct addrinfo criteria;
    memset(criteria, 0, sizeof(criteria));
    criteria.ai_family   = AF_UNSPEC;
    criteria.ai_socktype = SOCK_STREAM;
    criteria.ai_flags    = flags;
    criteria.ai_protocol = protocol;
    struct addrinfo addrList;
    int retVal = (getaddrinfo(address, port, criteria, addrList);
    if(retVal != 0)
    {
        SysMessage("[error] getaddrinfo(): ");
        exit(-1);
    }
    return addrList;
}

GetNameInfo(const struct sockaddr* address, int flag=NI_NUMERICHOST)
{
    char nodeName[NI_MAXHOST];
    char service[NI_MAXSERV];
    int retVal = getnameinfo(address, sizeof(address), nodeName, sizeof(nodeName), service, sizeof(service), flag);
    if(retVal != 0)
    {
        SysMessage("[error] getnameinfo(): ");
    }
}

WhoAmI()
{
    char buffer[NI_MAXHOST];
    size_t length = NI_MAXHOST;
    gethostname(buffer, length);
    Message("Own address: \n", stdout);
    Message(buffer, stdout);
}
