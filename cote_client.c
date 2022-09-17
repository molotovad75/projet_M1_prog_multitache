#include <stdio.h>
#include <stdlib.h>
#include <threads.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <pthread.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>


#include "normes_echanges.h"
#include "cote_serveur.h"

//Fonctions de la partie cliente

char ** listener(client customer,serveur server){ //Lister tous les messages d'un client en provenance du serveur 
	server.IP_adress=local_IP_adress;
	//server_connection(server->IP_adress);
	customer.descriptor_customer=server_connection(server->IP_adress); // Descripteur de la socket ce qui va permettre d'identifier 
	for(int i=0;i<sizeof(server.)/sizeof(char*);i++){
				
	}
	
	client_sender(customer);
}

/*Dans les paramètres de cette fonction 
on peut avoir un client sur lequel on envoi le message 
comme n clients. 
Pour n clients il va falloir boucler sur cette fonction.*/
void sender(char * message,client customer,serveur server){ //Envoi un message à un autre client via le serveur 
	//server_connection(local_IP_adress); /*local_IP_adress sort de notre fichier d'en tête "normes_echanges.h"*/
	server.current_list_message->text=message; //On instancie le contenu du message avec le paramètre message qui est un pointeur de char.  
	server.current_list_message->pseudo_customer_sender=customer.pseudo; // On instancie l'émetteur du message à partir du paramètre customer de type client
	
	
	
	
	
	//Mise en place de la date à laquelle le message est envoyé.
	time_t now; //time_t pour time timer
	struct tm *local_date=localtime(&now); //Une structure pour instancier le temps actuel
	server.current_list_message->send_date.day=local_date->tm_mday;
	server.current_list_message->send_date.month=local_date->tm_mon;
	server.current_list_message->send_date.year=local_date->tm_year;
	
	
	//Action client
	customer.send_messages->text=message; //customer.send_messages->text = customer.(*send_messages).text <!-- EQUIVALENCE -->
	customer.send_messages->pseudo_customer_sender=customer.pseudo; //On instancie le nom du client 
	
	
}


//Une fonction pour se connecter à notre serveur.
int server_connection(char * adress_ip_server){ //Utilisation d'une socket
	//Rappel : Une socket renvoie un entier qui permet de se connecter à un serveur à long terme en créant tout d'abord un canal de communication puis en utilisant une autre fonction. L'entier en question s'appelle un descripteur de socket.
	
	struct sockaddr_in addr_server; //sockaddr_in c'est un type de donnné permettant d'instancier une adresse IP dans la ligne de mire du socket.
	addr_server.sin_addr.s_addr=inet_addr(*adress_ip_server);
	addr_server.sin_family=AF_INET; //Ceci est pour indiquer le type d'adresse IP. AF_INET est instancié pour indiqué que nous utilisons une adresse IPv4.
	addr_server.sin_port=htons(30000); //Il faut découvrir ce que signifie réélement la fonction htons.
	
	int server_socket_describer=socket(AF_INET,SOCK_STREAM,0); 
	/*
	La fonction socket(AF_INET,SOCK_STREAM,0) crée un canal de communication entre notre machine et notre serveur.
	Les paramètres dans l'ordre : 
	famille, type, protocole.
	On a mis 0 en dernier paramètre, c'est le système qui va choisir le protocole selon la famille et le type que l'on a utilisé.
	Cette variable de type entier s'appelle un descripteur de socket.
	
	*/
	
	int bind_socket=bind(server_socket_describer,(const struct sockaddr *) &addr_server,sizeof(addr_server)); //Permet à notre socket de se connecter à l'adresse IP de notre serveur !
	if(server_socket_describer<0){
		perror("Connection failed !\n");//La connexion a échoué !
	}
	
	return bind_socket; //On peut décider de retourner le descripteur de socket 

}


//Fonctions de la partie serveur



