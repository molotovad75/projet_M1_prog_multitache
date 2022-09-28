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
#include <semaphore.h>

#include "normes_echanges.h"
#include "cote_client.h"

//Variables du côté serveur
//serveur server;
sem_t semaphore;// Le semaphore sert à synchroniser des threads au sein d'un même processus ou bien entre plusieurs processus.
//message * pile_message=server.current_list_messages; //Notre fameux dispacher qui va stocker tous les messages en permanance tant que ce message ce sera pas arrivé à destination.

server.IP_adress=local_IP_adress; //Association de l'adresse IP locale à notre serveur
//unsigned int instanciation_taille=0; //Indicateur nous permettant de savoir si l'espace mémoire de la pile de message est réalisé : 0 = non instancier et 1= instancier


//Fonctions du côté serveur



//C'est la pile d'exécution des threads du serveur

//Dans les deux fonction suivantes, le pointeur de message devra être égal au dispacher présent dans la structure d'un serveur.
void push_in_dispatcher(message m, message * pile_message){ //On enfile le message dans une pile ! Création éventuelle d'un thread, selon la date de validité du thread et par défaut sa date d'ajout.
	
	for(int i=0;i<sizeof(pile_message);i++){
		if(pile_message[i]==NULL){
			pile_message[i]=m;
		
		}
	}
}

void pop_in_dispatcher(message m, message * pile_message){ //On retire le message de la pile et on met les champs du tableau à jour.
	for(int i=0;i<sizeof(pile_message);i++){
		if(pile_message[i]==m){
			for(int e=i;e<sizeof(pile_message)-1;e++){
				pile_message[e]=pile_message[e+1];		
			}		
		}
	}
}

//N'oublions pas que dans le type de structure message, il y a le type client !
void client_listener(message message_entering,serveur server){//Collecte tous les messages venus du client vers ce serveur
	for(){
	
	}
	push_in_dispatcher(message_entering,server.current_list_messages);
	
}

void client_sender(message message_to_send, serveur server){//Renvoi tous les messages stockés temporairement dans le serveur au client
	for(int i=0;i<sizeof(message_to_send.receiver_);i++){
		listener(server, message_to_send.receiver_[i]); //On rappelle que receiver_[i] c'est l'indice pour un client. Cela représente un client.
		
	}
	pop_in_dispatcher(message_to_send,server.current_list_messages);
} 


void accept_connexion(client customer,serveur server){ //Accepter les connexion entrantes


}

void wait_connection(client customer, serveur server){ //Mise en attente des connexions.


}



