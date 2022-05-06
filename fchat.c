#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
char buffer[4096];
char outboxbuffer[4096];
char recipientbuffer[4096];
char messagebuffer[4096];
int main() {
        char *me = getenv("USER");
        snprintf(buffer, 4096, "/bigtemp/cso1/%s.chat", me);

        FILE *inbox = fopen(buffer, "r");
        size_t got = fread(buffer, sizeof(char), 4096, inbox);
        if(got==0) {
                puts("You have no new messages");
        }
        else {
                puts("Your messages:");
                printf("%s\n", buffer);
        }
        
        snprintf(buffer, 4096, "/bigtemp/cso1/%s.chat", me);
        truncate(buffer, 0);
        fclose(inbox);
        puts("Who would you like to message?");
        gets(recipientbuffer);
        char *recipient = recipientbuffer;

        outboxbuffer[0] = '\0';

        strcat(outboxbuffer, "/bigtemp/cso1/");
        strcat(outboxbuffer, recipient);
        strcat(outboxbuffer, ".chat");
        FILE *outbox = fopen(outboxbuffer, "a");
        puts("What do you want to say?");
        gets(messagebuffer);
        char *message =  messagebuffer;
        fprintf(outbox, "%s:%s\n", me, message);
        return 0;
}