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

//Variables du côté serveur
//sem_t semaphore;// Le semaphore sert à synchroniser des threads au sein d'un même processus ou bien entre plusieurs processus.


//server.IP_adress=local_IP_adress; //Association de l'adresse IP locale à notre serveur
//unsigned int instanciation_taille=0; //Indicateur nous permettant de savoir si l'espace mémoire de la pile de message est réalisé : 0 = non instancier et 1= instancier

//N'oublions pas que dans le type de structure message, il y a le type client stocké à l'intérieur!

//Dans les deux fonction suivantes, le pointeur de message devra être égal au dispacher présent dans la structure d'un serveur.
void push_in_dispatcher(message m, message * pile_message){ //On enfile le message dans une pile ! Création éventuelle d'un thread, selon la date de validité du thread et par défaut sa date d'ajout.
	//Notre fameux dispacher qui va stocker tous les messages en permanance tant que ce message ce sera pas arrivé à destination. message * pile_message
	for(int i=0;i<sizeof(pile_message);i++){
		if(!pile_message[i]){
			pile_message[i]=m;
		
		}
	}
}

void pop_in_dispatcher(message m, message * pile_message){ //On retire le message de la pile et on met les valeurs de chaque indice du tableau à jour.
	for(int i=0;i<sizeof(pile_message);i++){
		if(/*Texte du message*/ strcmp(pile_message[i].text,m.text)==0 && /*On passe au client destinataire du message*/ strcmp(pile_message[i].sender_.pseudo,m.sender_.pseudo)==0 && pile_message[i].sender_.id_customer==m.sender_.id_customer && /*On passe à la date d'envoi*/ /*Jour*/pile_message[i].send_date.day==m.send_date.day && /*mois*/ pile_message[i].send_date.month==m.send_date.month && /*année*/ pile_message[i].send_date.year==m.send_date.year /*On passe à la date de validité*/ ){//
			for(int e=i;e<sizeof(pile_message)-1;e++){
				pile_message[e]=pile_message[e+1]; //Technique d'écrasement.
			}		
		}
	}
}


//Utilisation de 2 fonctions développées côté client sender() et listener().
void client_listener(message message_entering,serveur server){//Collecte tous les messages venus du client vers ce serveur
	for(int i=0; i<sizeof(message_entering.receiver_);i++){
		
		sender(message_entering.text, message_entering.sender, message_entering.receiver_[i], server);
	}
	push_in_dispatcher(message_entering,server.current_list_messages);//On ajoute le message dans le serveur.
	
}

void client_sender(message message_to_send, serveur server){//Renvoi tous les messages stockés temporairement dans le serveur au client
	for(int i=0;i<sizeof(message_to_send.receiver_);i++){ //Bouclons sur la liste de clients sélectionnés.
		listener(server, message_to_send.receiver_[i]); //On rappelle que receiver_[i] c'est l'indice pour un client. Cela représente un client.
	}
	pop_in_dispatcher(message_to_send,server.current_list_messages);//On retire le message de notre pile de message sur serveur.
} 

/*
void accept_connexion(client customer,serveur server){ //Accepter les connexion entrantes


}
*/

/*void wait_connection(client customer, serveur server){ //Mise en attente des connexions, si le serveur est surchargé de iencli.


}
*/

