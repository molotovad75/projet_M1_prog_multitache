#include "cote_client.c"
#include "cote_serveur.c"

/*extern date date;*/
/*extern client customer;*/
/*extern message m;*/
/*extern serveur server;*/


//Fonctions coté serveur

void push_in_dispatcher(message m, message * pile_message);
void pop_in_dispatcher(message m, message * pile_message);
void client_listener(message message_entering,serveur server);
void client_sender(message message_to_send, serveur server);


//Fonctions coté client


char ** listener(serveur server, client customer);
void sender(char * text_message, client sender, client * receiver, serveur server);
int server_connection(serveur server);

void initialisation_id_customers();
client * add_customer(client customer);
char * customers_list();




