//Pour copier sur nano : Il faut selectionner (souris et ou clavier ou Crtl + 6) et pour copier la sélection :  Alt +Shift + 6

#include <stdio.h>
#include <stdlib.h>
#include <threads.h>
#include <sys/types.h> 
#include <unistd.h> 
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

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

//Processus
pid_t * processus_fils;//On va créer une liste de processus fils.

void run_application(){
	//création des threads
	
	//Création d'une fenêtre graphique en SDL, la bibliothèque officielle de GUI en C/C++
/*	SDL_Window * window=NULL;*/
/*	SDL_Renderer * renderer=NULL;*/
/*	if(SDL_Init(SDL_INIT_EVERYTHING)!=0){*/
/*		SDL_Log("Erreur d'initialisation de la SDL2 > %s \n", SDL_GetError());*/
/*		exit(EXIT_FAILURE);*/
/*	}*/
/*	*/
/*	renderer=SDL_CreateRenderer(window,-1,SDL_RENDERER_SOFTWARE);*/
/*	SDL_SetRenderDrawColor(renderer,255,255,255,255);//C'est du blanc*/
/*	*/
/*	SDL_Color white={255,255,255,255};*/
/*	setWindowColor(renderer,white);//Toute la fenêtre en blanc.*/
/*	*/
/*	SDL_Surface *surface=NULL;*/
/*	Uint32 pixels[255 * 255];*/
/*	surface = SDL_CreateRGBSurfaceWithFormatFrom(pixels, 255, 255, 255, 255 * sizeof(Uint32), SDL_PIXELFORMAT_RGBA8888);*/
/*	*/
/*	window=SDL_CreateWindow("EFREI - Application client serveur",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,500,500, SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);*/
/*	*/
/*	SDL_Delay(10000);//On laisse la fenètre ouverte pendant 10 secondes.*/
/*	*/
/*	*/
/*	*/
/*	SDL_DestroyWindow(window);//On détruit la fenêtre*/
/*	free(surface);*/
/*	SDL_Quit();*/
	int running=1;
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window *window = SDL_CreateWindow("EFREI - Application client serveur", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN); //Fenêtre en général

	TTF_Font * font1=TTF_OpenFont("DejaVuSans.ttf",20); //Ici 20 est la taille de ma police
	SDL_Color couleur_text={0,0,0,0};//noir
	SDL_Color couleur_fond={255,255,255,255}; //Couleur de fond blanc
	
	SDL_Surface *surf=TTF_RenderText_Blended(font1,"Bienvenue sur l'application client-serveur officiel !\n\nQue voulez vous faire ?\n\n1 - Inscrire un nouveau client\n2 - Se connecter au serveur\n3 - Voir les autres clients\n4 - Quittez l'application !\n",couleur_fond);
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);//Corps de notre fenêtre
	SDL_Texture *text=SDL_CreateTextureFromSurface(renderer,surf);
	SDL_Rect position; //On crée une sorte de rectangle ayant pour coordonées(x,y) le point en haut à gauche du rectangle. 
	position.x=100;
	position.y=200;
	SDL_QueryTexture(text,NULL,NULL,&position.w,&position.h);//Le 2e et le 3e paramètre ne nous intérèsse pas car le format en soit on s'en moque dans cette fonction et accès aussi
	SDL_RenderCopy(renderer,text,NULL,&position);//3ème paramètre en mettant NULL on copie tt la texture. Le 4e paramètre on copie la texture à l'endroit on l'on veut mettre dans le renderer (Ses coordonées avec le sommet en haut à gauche comme point x et y)
	

	SDL_SetRenderTarget(renderer,text);
	SDL_SetRenderDrawColor(renderer, couleur_fond.r, couleur_fond.g, couleur_fond.b, couleur_fond.a);
	SDL_RenderClear(renderer);
	SDL_Delay(5000);
	SDL_RenderPresent(renderer);
	SDL_Delay(5000);
	      
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	printf("Bienvenue sur l'application client-serveur officiel !\n\nQue voulez vous faire ?\n\n1 - Inscrire un nouveau client\n2 - Se connecter au serveur\n3 - Voir les autres clients\n4 - Quittez l'application !\n");
	client customer;
	int reponse=0;
	reponse=0;
	scanf("%d",&reponse);
	//list_customer_official=malloc(sizeof(client));

	if(initialisation_faite==0){
		initialisation_id_customers(list_customer_official);//initialisation des champs d'ID à -1.
		initialisation_faite=1;
	}
	
	switch(reponse){
		case 1:

			printf("Veuillez entrer le nouveau pseudo de ce client\n");

			customer.pseudo=malloc(sizeof(char));
			scanf("%s",customer.pseudo); //customer.pseudo est un pointeur
			customer.id_customer=identifiant_client;
			identifiant_client++;
			printf("%s est enregistré en tant que nouveau client et à le numéro d'identifiant unique %d !\n",customer.pseudo, customer.id_customer);
			//On ajoute le nouveau client.
			printf("%d est la taille de list_customer_official\n",sizeof(list_customer_official));
			add_customer(customer,list_customer_official);
			free(customer.pseudo);
			break;

		case 2:
			printf("Bonjour !\n");
			break;
		case 3: //Voir les autre clients.
			//printf("%s\n",);
			customers_list(list_customer_official);
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
