#ifndef SETUP_H
#define SETUP_H
#include <stdio.h>

int  SetupTCPClient(const char *host, const char *service, size_t flag);
int  SetupTCPServer(const char *service, size_t flag);

//int  SetupUDPClient();
//int  SetupUDPServer();

//void AcceptTCPConnection();
//void AcceptUDPConnection();

#endif // SETUP_H
