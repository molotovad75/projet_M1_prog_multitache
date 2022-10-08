#include "normes_echanges.h"

char ** listener(serveur server, client customer);
void sender(char * text_message, client sender, client * receiver, serveur server);
int server_connection(serveur server);


