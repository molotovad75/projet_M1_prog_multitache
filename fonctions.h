#ifndef __NORMES_ECHANGES_H__
#define __NORMES_ECHANGES_H__ 
	#include "normes_echanges.h"
#endif

//Fonctions coté client
#ifndef __FONCTIONS_CLIENTES__ 
#define __FONCTIONS_CLIENTES__
	char ** listener(serveur server, client customer);
	void sender(char * text_message, client sender, client * receiver, serveur server);
	int server_connection(serveur server);

	void initialisation_id_customers();
	client * add_customer(client customer);
	char * customers_list();
	
#endif

//Fonctions coté serveur
#ifndef __FONCTIONS_SERVEUR__ 
#define __FONCTIONS_SERVEUR__
	void push_in_dispatcher(message m, message * pile_message);
	void pop_in_dispatcher(message m, message * pile_message);
	void client_listener(message message_entering,serveur server);
	void client_sender(message message_to_send, serveur server);

#endif

