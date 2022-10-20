char * listener(serveur server, client customer);
void sender(char * text_message, client sender, client * receiver, serveur server);
int server_connection(serveur server);

void initialisation_id_customers(client * list_customer_official);
client * add_customer(client customer,client * list_customer_official);
char * customers_list(client * list_customer_official);
