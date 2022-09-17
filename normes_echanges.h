
//Destinataire privé.	
//Groupe de destinataires. Un destinataire peut être un ou plusieurs groupes c'est la raison pour laquelle on utilise un double pointeur.

//Qu'est-ce qu'un destinataire publique ?

/*Un destinataire public est tt simplement 
la liste de tous les clients 
enregistrés sur l'application
Du coup si nous voulons envoyé un message à un destinataire public
il suffit de sélectionner  */


const char * local_IP_adress="127.0.0.1";

typedef struct{
	unsigned int day; //jour
	unsigned int month; //mois
	unsigned int year; // année
}date;


typedef struct{
	char * pseudo;
	const unsigned int ID_customer;
	int descriptor_customer;
}client;


typedef struct{
	char * text; //c'est le corps du message.
	client sender_; //Emetteur du message. On part du principe qu'il peut y avoir au maximum une personne dans l'envoi d'un message.
	client * receiver_;//Pour un ou plusieurs destinataire. 
	date send_date; //date d'envoie du message. 
	date validity_date; //date de validité du message
}message;


typedef struct{
	char * name;
	message * current_list_messages;//C'est le dispatcher comme sur le sujet. C'est dans cette variable de la structure serveur qu'il faut mettre en action le multithreading.
	char * IP_adress;
}serveur;
