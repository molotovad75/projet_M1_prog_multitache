typedef struct{
	char * pseudo; //Destinataire privé	
	char * group_name; //Groupe de destinataires
	
	//Qu'est-ce qu'un destinataire publique ??
	bool statut; //public ou privé ?
}destinataire;



typedef struct{
	unsigned int day;// jour
	unsigned int month; //mois
	unsigned int year; // année
}date;


typedef struct{
	char * text; //c'est le corps du message.
	char * pseudo_sender; //Pseudo de l'envoyeur du message. On part du principe qu'il peut y avoir au maximum une personne dans l'envoi d'un message.
	destinataire * receiver;//C'est un pointeur car un message peut avoir plusieurs destinataires. 
	date send_date; //date d'envoie du message. 
	date validity_date; //date de validité du message
}message;




