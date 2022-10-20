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

//Liste de clients

client * list_customer_official=NULL; //Pour sauvegarder les mêmes lorsqu'on relance l'application


void initialisation_id_customers(){//On initialise à -1 tous les champs: La première fonction a être exécuté dans le main.
	list_customer_official=malloc(sizeof(client)*10);//On initialise la taille d'une liste de client.
	for(int i=0;i<sizeof(list_customer_official)/sizeof(client);i++){
		list_customer_official[i].id_customer=-1;	
	}
}


client * add_customer(client customer){ //Ajouter un nouveau client dans notre espace de stockage. Il faut l'utiliser après si et seulement si la fonction initialisation_id_customers() est lancée.
	for(int i=0;i<sizeof(list_customer_official)/sizeof(client);i++){
		if(list_customer_official[i].id_customer==-1){
			list_customer_official[i].id_customer=customer.id_customer;
			list_customer_official[i].pseudo=customer.pseudo;
		}
	}
	return list_customer_official;
}



char * customers_list(){ //Consulter la liste de tous les clients de notre application. Il faut l'utiliser après si et seulement si la fonction initialisation_id_customers() est lancée.
	char * description=NULL;
	//char * texte_actuel=NULL;//Texte qui doit être modifier
	
	for(int i=0;i<sizeof(list_customer_official)/sizeof(client);i++){
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



void run_application(){
	//création des threads
	printf("Bienvenue sur l'application client-serveur officiel !\n\nQue voulez vous faire ?\n\n1 - Inscrire un nouveau client\n2 - Se connecter au serveur\n3 - Voir les autres clients\n4 - Quittez l'application !\n");
	int initialisation_faite=0;
	int reponse=0;
	unsigned int identifiant_client=0;
	//while(1){
	reponse=0;
	scanf("%d",&reponse);	
	
	if(initialisation_faite==0){
		initialisation_id_customers();//initialisation des champs d'ID à -1.
		initialisation_faite=1;
	}
	client customer;
	switch(reponse){
		case 1:
			
			printf("Veuillez entrer le nouveau pseudo de ce client\n");
			
			customer.pseudo=malloc(sizeof(char)*10);	
			
			scanf("%s",customer.pseudo); //customer.pseudo est un pointeur
			customer.id_customer=identifiant_client;
		
			identifiant_client++;	
			printf("%s est enregistré en tant que nouveau client et à le numéro d'identifiant unique %d !\n",customer.pseudo, customer.id_customer);
			//On ajoute le nouveau client.
			add_customer(customer);
			free(customer.pseudo);
			
		case 2:
			
		case 3: //Voir les autre clients.
			printf("%s",customers_list());
			
		case 4: //Quitter l'application
			//system("kill -l %ld",getpid()); //Tuer le processus en cours d'éxécution (Ne fonctionne pas sur tous les systemes d'exploitation). Fonctionne uniquement sur Linux.
			exit(0);//On quitte programme en laissant un succès		
		default:
			exit(0);//On quitte programme en laissant un succès
	}
	
	char * recommencer=malloc(sizeof(char));
	printf("Voulez-vous recommencez ? [Oui - O - Yes - Y] - [Non - N - No]\n");
	scanf("%s",recommencer);
	if(strcmp(recommencer,"Oui")==0 || strcmp(recommencer,"O")==0 || strcmp(recommencer,"Yes")==0 || strcmp(recommencer,"Y")==0){
		run_application();
	}else if(strcmp(recommencer,"Non")==0 || strcmp(recommencer,"No")==0 || strcmp(recommencer,"N")==0){
		exit(0);
	}
	free(recommencer);
	
	//free(list_customer_official);
	
	//}

}

int main(){
	run_application();
	return 0;
}
