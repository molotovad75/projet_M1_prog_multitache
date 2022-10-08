//Ici on met toutes les fonction du source cote_serveur.c
#include "normes_echanges.h"

void push_in_dispatcher(message m, message * pile_message);
void pop_in_dispatcher(message m, message * pile_message);
void client_listener(message message_entering,serveur server);
void client_sender(message message_to_send, serveur server);
