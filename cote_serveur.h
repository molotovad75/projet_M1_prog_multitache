//Pour copier sur nano : Il faut selectionner (souris et ou clavier ou Crtl + 6) et pour copier la sélection :  Alt +Shift + 6
void push_in_dispatcher(message m, message * pile_message);
void pop_in_dispatcher(message m, message * pile_message);
void client_listener(message message_entering,serveur server);
void client_sender(message message_to_send, serveur server);
