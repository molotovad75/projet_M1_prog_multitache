#include <stdio.h>
#include <stdlib.h>
#include <threads.h>
#include <sys/types.h> 
#include <unistd.h> 
#include <string.h>


#ifndef __NORMES_ECHANGES_H__
#define __NORMES_ECHANGES_H__ 
#include "normes_echanges.h"
#endif

#ifndef __COTE_CLIENT_H__
#define __COTE_CLIENT_H__ 
#include "cote_client.h"	
#endif

#ifndef __COTE_SERVEUR_H__
#define __COTE_SERVEUR_H__ 
#include "cote_serveur.h"	
#endif

client * list_customer_official=NULL; //Liste de clients. Pour sauvegarder les mêmes lorsqu'on relance l'application
unsigned int identifiant_client=0;//Identification officielle lors de l'inscription d'un client.
int initialisation_faite=0; //variable servant de décision au remplissage d'une liste vide de client ayant pour identifiant le nombre -1.

void run_application(){
	//création des threads
	printf("Bienvenue sur l'application client-serveur officiel !\n\nQue voulez vous faire ?\n\n1 - Inscrire un nouveau client\n2 - Se connecter au serveur\n3 - Voir les autres clients\n4 - Quittez l'application !\n");
	
	int reponse=0;
	reponse=0;
	scanf("%d",&reponse);	
	list_customer_official=malloc(sizeof(client));
	
	if(initialisation_faite==0){
		initialisation_id_customers(list_customer_official);//initialisation des champs d'ID à -1.
		initialisation_faite=1;
	}
	client customer;
	switch(reponse){
		case 1:
			
			printf("Veuillez entrer le nouveau pseudo de ce client\n");
			
			customer.pseudo=malloc(sizeof(char));	
			
			scanf("%s",customer.pseudo); //customer.pseudo est un pointeur
			customer.id_customer=identifiant_client;
		
			identifiant_client++;	
			printf("%s est enregistré en tant que nouveau client et à le numéro d'identifiant unique %d !\n",customer.pseudo, customer.id_customer);
			//On ajoute le nouveau client.
			add_customer(customer,list_customer_official);
			free(customer.pseudo);
			break;
			
		case 2:
			printf("Bonjour !\n");
			break;
		case 3: //Voir les autre clients.
			printf("%s\n",customers_list(list_customer_official));
			break;
		case 4: //Quitter l'application
			//system("kill -l %ld",getpid()); //Tuer le processus en cours d'éxécution (Ne fonctionne pas sur tous les systemes d'exploitation). Fonctionne uniquement sur Linux.
			free(list_customer_official);	
			exit(0);//On quitte programme en laissant un succès	
			break;	
		default: //Quitter l'application
			free(list_customer_official);
			exit(0);//On quitte programme en laissant un succès
			break;
	}
	
	char * recommencer=malloc(sizeof(char));
	printf("Voulez-vous recommencez ? [Oui/O/o/Yes/Y/y/oui/yes] - [Non/N/No/n/non/no/n]\n");
	scanf("%s",recommencer);
	if(strcmp(recommencer,"Oui")==0 || strcmp(recommencer,"O")==0 || strcmp(recommencer,"o")==0 || strcmp(recommencer,"oui")==0 || strcmp(recommencer,"Yes")==0 || strcmp(recommencer,"Y")==0 || strcmp(recommencer,"y")==0 || strcmp(recommencer,"yes")==0){
		run_application();
	}else if(strcmp(recommencer,"Non")==0  || strcmp(recommencer,"N")==0  || strcmp(recommencer,"No")==0 || strcmp(recommencer,"n")==0 || strcmp(recommencer,"non")==0 || strcmp(recommencer,"no")==0 || strcmp(recommencer,"n")==0){
		free(list_customer_official);
		exit(0);
	}
	free(recommencer);
}


int main(void){
	run_application();
	return 0;
}
