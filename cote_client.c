#include <stdio.h>
#include <stdlib.h>
#include <threads.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <pthread.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "normes_echanges.h"

//Fonctions de la partie cliente

char * listener(serveur * message_serveur){
	connexion_serveur(serveur server);
	for(int i=0;i<sizeof(message_serveur);i++){
		
	}

}

/*Dans les paramètres de cette fonction 
on peut avoir un client sur lequel on envoi le message 
comme n clients. 
Pour n clients il va falloir boucler sur cette fonction.*/
message send(message mess,client customer){ 

	//server_connection(local_IP_adress); /*local_IP_adress sort de notre fichier d'en tête "normes_echanges.h"*/
	
	 
	return mess;
}


//Une fonction pour se connecter à notre serveur.
void server_connection(char * adress_ip_server){ //Il faudra utiliser une socket
	//Rappel : Une socket est un entier qui permet de se connecter à un serveur. L'entier en question s'appelle un descripteur de socket.
	struct sockaddr_in addr_server; //sockaddr_in c'est un type de donnné permettant d'instancier une adresse IP dans la ligne de mire du socket.
	addr_server.sin_addr.s_addr=inet_addr(*adress_ip_server);
	addr_server.sin_family=AF_INET
	addr_server.sin_port=htons(30000) //Il faut découvrir ce que signifie réélement la fonction htons.
	
	int server_socket=socket(AF_INET,SOCK_STREAM,0); 
	/*Les paramètres dans l'ordre : 
	famille, type, protocole.
	On a mis 0 en dernier paramètre, c'est le système qui va choisir le protocole selon la famille et le type que l'on a utilisé.
	Cette variable de type entier s'appelle un descripteur de socket.*/
	
	int bind_socket=bind(server_socket,(const struct sockaddr *) &addr_server,sizeof(addr_server)); //Permet à notre socket de se connecter à l'adresse IP de notre serveur !
	

}


//Fonctions de la partie serveur



