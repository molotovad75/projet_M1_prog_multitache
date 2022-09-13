
//Destinataire privé.	
//Groupe de destinataires. Un destinataire peut être un ou plusieurs groupes c'est la raison pour laquelle on utilise un double pointeur.

//Qu'est-ce qu'un destinataire publique ?

/*Un destinataire public est tt simplement 
la liste de tous les clients 
enregistrés sur l'application
Du coup si nous voulons envoyé un message à un destinataire public
il suffit de sélectionner  */


const char * local_IP_adress="127.0.0.1"

typedef struct{
	unsigned int day;// jour
	unsigned int month; //mois
	unsigned int year; // année
}date;


typedef struct{
	char * text; //c'est le corps du message.
	char * pseudo_customer_sender; //Pseudo de l'envoyeur du message. On part du principe qu'il peut y avoir au maximum une personne dans l'envoi d'un message.
	char * pseudo_customer_receiver;//Pour un destinataire. 
	date send_date; //date d'envoie du message. 
	date validity_date; //date de validité du message
}message;



typedef struct{
	char * pseudo;
	message * received_messages; //Liste des messages recus
	message * send_messages; // Listes des messages envoyés
}client;


typedef struct{
	char * name;
	char * ip_adress;
	//struct
	client * connected_customers;
}serveur;
