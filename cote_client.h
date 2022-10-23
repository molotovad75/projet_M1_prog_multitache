//Pour copier sur nano : Il faut selectionner (souris et ou clavier ou Crtl + 6) et pour copier la sélection :  Alt +Shift + 6

char * listener(serveur server, client customer);
void sender(char * text_message, client sender, client * receiver, serveur server);
int server_connection(serveur server);

void initialisation_id_customers(client * list_customer_official);
void add_customer(client customer,client * list_customer_official);
char * customers_list(client * list_customer_official);
