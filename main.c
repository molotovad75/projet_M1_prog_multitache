#include <stdio.h>
#include <stdlib.h>
#include <threads.h>
#include <sys/types.h> 
#include <unistd.h> 

#include "fonctions.h"


unsigned int identifiant_client=0;

int main(){
	//création des threads
	printf("Bienvenue sur l'application client-serveur officiel !\n\nQue voulez vous faire ?\n\n1 - Inscrire un nouveau client\n2 - Se connecter au serveur\n3 - Voir les autres clients\n4 - Quittez l'application !");
	int initialisation_faite=0;
	int reponse=0;
	while(1){
		reponse=0;
		scanf("%d",&reponse);
		client customer;
		
		
		if(initialisation_faite==0){
			initialisation_id_customers();//initialisation des champs d'ID à -1.
			initialisation_faite=1;
		}
		
		switch(reponse){
			case 1:
				
				printf("Veuillez entrer le nouveau pseudo de ce client\n");
				customer.pseudo=malloc(sizeof(char)*10);	
				
				scanf("%s",customer.pseudo); //customer.pseudo est un pointeur
				customer.id_customer=identifiant_client;
				identifiant_client++;	
				printf("%s est enregistré en tant que nouveau client et à le numéro unique %d !\n",customer.pseudo,customer.id_customer);
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
		
		return 0;
	}
	
}
