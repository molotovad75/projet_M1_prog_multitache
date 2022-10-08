#include <stdio.h>
#include <stdlib.h>
#include <threads.h>
#include "cote_serveur.h"
#include "cote_client.h"
#include "normes_echanges.h"


unsigned int identifiant_client=0;

int main(){
	//création des threads
	printf("Bienvenue sur l'application client-serveur officiel !\n\nQue voulez vous faire ?\n\n1 - Inscrire un nouveau client\n2 - Se connecter au serveur\n3 - Voir les autres clients\n");	
	int reponse=0;
	scanf("%d",&reponse);
	switch(reponse){
		case 1:
			client customer;
			printf("Veuillez entrer le nouveau pseudo de ce client\n");
			customer.pseudo=malloc(sizeof(char)*10);
			scanf("%s",customer.pseudo); //customer.pseudo pointeur
			customer.id_customer=identifiant_client;
			identifiant_client++;	
			printf("%s est enregistré en tant que nouveau client et à le numéro unique %d !\n",customer.pseudo,customer.id_customer);
			free(customer.pseudo);
		//case 2:
		
		
		//case 3:
		
		
		//default:
	
	}
	
	return 0;
}
