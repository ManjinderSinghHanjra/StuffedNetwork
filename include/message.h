#ifndef MESSAGE_H
#define MESSAGE_H
#include <stdio.h>

void SysMessage(const char *msg);
void UserMessage(const char *msg, const char *details);
void Message(const char *msg, FILE *stream);

#endif // MESSAGE_H
