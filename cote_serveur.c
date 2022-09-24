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
serveur server;
sem_t semaphore;// Le semaphore sert à synchroniser des threads au sein d'un même processus ou bien entre plusieurs processus.
message * pile_message=server.current_list_messages; //Notre fameux dispacher qui va stocker tous les messages en permanance tant que ce message ce sera pas arrivé à destination.

server.IP_adress=local_IP_adress; //Association de l'adresse IP locale à notre serveur
unsigned int instanciation_taille=0; //Indicateur nous permettant de savoir si l'espace mémoire de la pile de message est réalisé : 0 = non instancier et 1= instancier
//int 

//Fonctions du côté serveur



//C'est la pile d'exécution des threads du serveur
void push_in_dispatcher(message m){ //On enfile le message dans une pile ! Création éventuelle d'un thread, selon la date de validité du thread et par défaut sa date d'ajout.
	accept_connexion(m.sender_);//On accepte la connexion si cela n'est pas encore faite.
	if(instanciation_taille==0){
		pile_message=malloc(sizeof(message));	
		instanciation_taille=1;//Marqueur indiquant que c'est fait
	}
	
	for(int i=0;i<sizeof(pile_message);i++){
		if(pile_message[i]==NULL){
			pile_message[i]=m;
		
		}
	}

}

void accept_connexion(client customer,serveur server){ //Accepter les connexion entrantes


}

void wait_connection(client customer, serveur server){ //Mise en attente des connexions.


}


void client_listening(char * message_entering, client customer){//Collecte tous les messages venus du client vers ce serveur
 
	
}

char ** client_sender(client customer, serveur server){//Renvoi tous les messages stockés temporairement dans le serveur au client

	
}


