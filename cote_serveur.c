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


//C'est la pile d'exécution des threads du serveur
void push_in_dispatcher(message m){ //On enfile le message dans un pile ! Création éventuelle d'un thread, selon la date de validité du thread
	

}

void accept_connexion(){ //Accepter les connexion entrantes


}

void wait_connection(){ //Mise en attente des connexions.


}


void client_listening(char * message_entering, client customer){//Collecte tous les messages venus du client vers ce serveur
 
	
}

char ** client_sender(client customer, serveur server){//Renvoi tous les messages stockés temporairement dans le serveur au client

	
}


