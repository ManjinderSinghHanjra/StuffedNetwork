#ifndef MESSAGE_H
#define MESSAGE_H

void SysMessage(const char *msg);
void UserMessage(const char *msg, const char details);
void Message(void *msg, FILE *stream);

#endif // MESSAGE_H
