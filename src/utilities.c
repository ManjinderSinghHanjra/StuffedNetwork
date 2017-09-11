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
