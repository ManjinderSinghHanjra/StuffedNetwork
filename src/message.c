#include <string.h>
#include "message.h"

void SysMessage(const char *msg)
{
    perror(msg);
}

void UserMessage(const char *msg, const char *details)
{
    fputs(msg, stdout);
    fputs("\n", stdout);
    fputs(details, stdout);
}

void Message(const char *msg, FILE *stream)
{
    fputs(msg, stream);
}
