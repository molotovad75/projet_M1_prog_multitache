#include <stdio.h>
#include <stdlib.h>
#include <threads.h>
#include <string.h>
#include <sys/socket.h>  //Fonction bind() et socket()
#include <sys/types.h> //Fonction bind()
#include <pthread.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include <semaphore.h>

#include <stdarg.h>

#ifndef __NORMES_ECHANGES_H__
#define __NORMES_ECHANGES_H__ 
#include "normes_echanges.h"
#endif

/*#include "normes_echanges.h"*/

//Variables génrales du fichier source

unsigned int indice_current_message=0; //Fonction sender(char * text_message, client sender, client * receiver, serveur server)
int indice_bloc_message=0;
const char * local_IP_adress="127.0.0.1"; //localhost

//Liste de clients
client * list_customer_official; //Pour sauvegarder les mêmes lorsqu'on relance l'application


//Fonctions de la partie cliente

char * listener(serveur server, client customer){ //Lister tous les messages à destination d'un seul client en provenance du serveur 
	unsigned int nb_messages=0;
	int * stockage_indice_message=NULL; //On veut stocker
	stockage_indice_message=malloc(sizeof(int));//Allocation de mémoire dynamique. Fonction malloc()
	int indice_de_indice=0;//Variable pour se déplacer à l'intérieur de notre pointeur d'entiers.
	
	//On vérifie les messages qui iront bien à destination du bon client.
	for(int i=0;i<sizeof(server.current_list_messages);i++){
		for(int e=0;e<sizeof(server.current_list_messages[i].receiver_);e++){
			if(server.current_list_messages[i].receiver_[e].id_customer==customer.id_customer){ //Si c'est le bon client alors ... (Vérification de son id_customer)
				//indice_bloc_message=i; //Stockage de son indice i dans le nouvel indice "indice_client" 
				stockage_indice_message[indice_de_indice]=i;//Remplissage de notre tableau d'indices par les indices des bons messages stockés dans le dispacher.
				//Associer le client au bon message.
				
				nb_messages++;//Incrémentation du nombre de messages
				indice_de_indice++; // Incrémentation de notre variable servant à gravir les cases mémoires du tableau/pointeur.
			}//Fin if
		}//Fin for
	}//Fin for
	char * message_clients=NULL; //Tableau de pointeurs que nous allons renvoyer de par cette fonction.
	message_clients=malloc(sizeof(char)*10);//La taille pour un message
	
		
	for(int e=0;e<indice_de_indice;e++){
		//Ceci est pour un client
		strcat(message_clients , server.current_list_messages[stockage_indice_message[e]].text);// Affectation du corps du message stocké dans le dispacher au tableau de ponteurs qui va être retourné. 
		strcat(message_clients , "\n");
	}
		
	free(message_clients);
	free(stockage_indice_message); //On libère la mémoire
	//free(message_clients);
	return message_clients; //On retourne un tableau de pointeur sur des char.
}

/*Dans les paramètres de cette fonction 
on peut avoir un client sur lequel on envoi le message 
comme n clients.
Pour n clients cibles il va falloir boucler sur cette fonction.*/


//A tester
void sender(char * text_message, client sender, client * receiver, serveur server){ //Envoi un message à un autre client via le serveur : Dans le paramètre receiver on attend un tableau de clients allant recevoir le message.
	
	//Il faut que current_list_messages soit initialiser dans le main ou dans le coté serveur.
	
	server.current_list_messages[indice_current_message].text=text_message; //On instancie le contenu du message avec le paramètre message qui est un pointeur de char.  
	server.current_list_messages[indice_current_message].sender_.pseudo=sender.pseudo; // On instancie l'émetteur du message à partir du paramètre customer de type client
	
	//m.text=text_message;
	
	int taille_receiver_=0;
	//Condition if peut être à changer
	if(sizeof(server.current_list_messages[indice_current_message].receiver_)>=sizeof(receiver)){
		taille_receiver_=sizeof(receiver);
	}else{
		taille_receiver_=sizeof(server.current_list_messages[indice_current_message].receiver_);
	}
	
	
	//Ici on déroule toute la liste des clients receveurs
	int e=0;
	for(int i=0;i<taille_receiver_;i++){ //Avant c'était sizeof(receiver)
		server.current_list_messages[indice_current_message].receiver_[e].pseudo=receiver[i].pseudo; // On instancie le destinataire du message à partir du paramètre receiver étant un pointeur sur le type client
		server.current_list_messages[indice_current_message].receiver_[e].id_customer=receiver[i].id_customer;
		e++;
	}
	
	
	//Dans le main il va falloir initialiser une liste de clients
	
	//Mise en place de la date à laquelle le message est envoyé.
	time_t now; //time_t une variable de type temporel
	struct tm *local_date=localtime(&now); //Une structure pour instancier le temps actuel
	 
	//Mise en place des deux types de dates. 
	/***************************************************************************************************/
	/* Dates du jour sur lequel notre contenue entre dans le dispatcher */
	server.current_list_messages[indice_current_message].send_date.day=local_date->tm_mday; // local_date->tm_mday c'est comme si c'était 
	server.current_list_messages[indice_current_message].send_date.month=local_date->tm_mon;
	server.current_list_messages[indice_current_message].send_date.year=local_date->tm_year;
	
	/* Dates de péremption de tout le paquet que l-on veut envoyer à notre destinataire.*/
	server.current_list_messages[indice_current_message].validity_date.day=local_date->tm_mday+1;//On laisse un délai de 24h avant la fin de validité du message.
	server.current_list_messages[indice_current_message].validity_date.month=local_date->tm_mon;
	server.current_list_messages[indice_current_message].validity_date.year=local_date->tm_year;
	/***************************************************************************************************/	
	
	//Le sémaphore doit être utilisé dans la partie serveur.
	//push_in_dispatcher(server.current_list_messages[indice_current_message],server.current_list_messages); 
	//server.current_list_messages[indice_current_message] est le message à envoyer
	//server.current_list_messages est la pile de message.
	//Le message est inséré par la suite dans le dispatcher. Donc dans une pile ou le multithreading et les sémaphores seront appliqués !
	
	indice_current_message++; //Incrémentation de l'indice. 
}

//A tester
//Une fonction pour se connecter à notre serveur. On utilisera cette fonction au tt début.
int server_connection(serveur server){ //Utilisation d'une socket
	//Rappel : Une socket renvoie un entier qui permet de se connecter à un serveur à long terme en créant tout d'abord un canal de communication puis en utilisant une autre fonction. L'entier en question s'appelle un descripteur de socket.
	
	//struct sockaddr_in addr_server; //sockaddr_in c'est un type de donnné permettant d'instancier une adresse IP dans la ligne de mire du socket.
	//addr_server.sin_addr.s_addr=inet_addr(*local_IP_adress);
	
	server.addr_server.sin_addr.s_addr=inet_addr(local_IP_adress); //Cette fonction sert à convertir une chaine de caractère (chaine de caractères de l'Adresse IP) en adresse compréhensible par le serveur.
	
	server.addr_server.sin_family=AF_INET; //Ceci est pour indiquer le type d'adresse IP. AF_INET est instancié pour indiqué que nous utilisons une adresse IPv4.
	server.addr_server.sin_port=htons(30000); // La fonction htons c'est pour le numéro de port'.
	
	int server_socket_describer=socket(AF_INET,SOCK_STREAM,0); 
	/*
	La fonction socket(AF_INET,SOCK_STREAM,0) crée un canal de communication entre notre machine et notre serveur.
	Les paramètres dans l'ordre : 
	famille, type, protocole.
	On a mis 0 en dernier paramètre, c'est le système qui va choisir le protocole selon la famille et le type que l'on a utilisé.
	Cette fonction est affecté à une variable de type entier qui s'appelle un descripteur de socket.
	
	*/
	
	int bind_socket=bind(server_socket_describer,(const struct sockaddr *) &server.addr_server,sizeof(server.addr_server)); //Permet à notre socket de se connecter à l'adresse IP de notre serveur ! Il peut donner aussi un nom à notre socket.
	if(server_socket_describer<0){
		perror("Connection failed !\n");//La connexion a échoué !
	}else{
		printf("Successful connection !\n");
	}
	
	return bind_socket; //On peut décider de retourner le nom de socket 

}

void initialisation_id_customers(){//On initialise à -1 tous les champs
	for(int i=0;i<sizeof(list_customer_official);i++){
		list_customer_official[i].id_customer=-1;	
	}
}

client * add_customer(client customer){ //Ajouter un nouveau client dans notre espace de stockage.
	for(int i=0;i<sizeof(list_customer_official);i++){
		if(list_customer_official[i].id_customer==-1){
			list_customer_official[i].id_customer=customer.id_customer;
		}
	}
	return list_customer_official;
}

char * customers_list(){
	char * description=NULL;
	//char * texte_actuel=NULL;//Texte qui doit être modifier
	
	for(int i=0;i<sizeof(list_customer_official);i++){
		description="Pseudo client numéro ";
		sprintf(description,"%d",i+1); //sprintf() fait la même chose que itoa()
		//itoa(i+1,description,10);
		strcat(description, " :");
		strcat(description, " ");
		strcat(description, list_customer_official[i].pseudo);	
		strcat(description, " ");
		strcat(description, "ID client : ");
		sprintf(description,"%d",i+1); //sprintf fait la même chose que itoa()
		//itoa(i+1,description,10); //itoa() c'est la fonction pour convertir un entier en une chaine de caractères 
		strcat(description, "\n");
	}
	
	return description;
}


//Il faut intégrer la partie sur SDL. Comment intégrer la bibliothèque SDL sur les fichier sources en C/C++
