/* 
 * Auteurs: Jean-Samuel Lauzon    
 * Date: Fevrier 2022
 * Projet S2ei
*/

/*------------------------------ Librairies ---------------------------------*/
#include <iostream>
#include <string>
using namespace std;

/*-------------------------- Librairies externes ----------------------------*/
#include "include/serial/SerialPort.hpp"
#include "include/json.hpp"
using json = nlohmann::json;

/*------------------------------ Constantes ---------------------------------*/
#define BAUD 74880           // Frequence de transmission serielle
#define MSG_MAX_SIZE 1024   // Longueur maximale d'un message


/*------------------------- Prototypes de fonctions -------------------------*/
bool SendToSerial(SerialPort *arduino, json j_msg);
bool RcvFromSerial(SerialPort *arduino, string &msg);


/*---------------------------- Variables globales ---------------------------*/
SerialPort * arduino; //doit etre un objet global!

/*----------------------------- Fonction "Main" -----------------------------*/
int main() {
    string raw_msg;

    // Initialisation du port de communication
    string com;
    cout << "Entrer le port de communication du Arduino: ";
    cin >> com;
    arduino = new SerialPort(com.c_str(), BAUD);
    
    if(!arduino->isConnected()) {
        cerr << "Impossible de se connecter au port "<< string(com) <<". Fermeture du programme!" <<endl;
        exit(1);
    }
    
    // Structure de donnees JSON pour envoie et reception
    int bargraph = 7;

    bool dpad_up = false;
    bool dpad_down = false;
    bool dpad_left = false;
    bool dpad_right = false;

    bool trig_left = false;
    bool trig_right = false;

    bool button_jstick = false;
    double angle_jstick = 0;

    bool acc_ST = false;
    int acc_x = 0; //La valeur max ne sera pas 1024 étant donné que l'accéléromètre est alimenté par du 3.3V
    int acc_y = 0;
    int acc_z = 0;
    
    int d_u,d_d,d_l,d_r,t_l,t_r,b_j;

    double angle = 0;

    json j_msg_send, j_msg_rcv;

    // Boucle infinie pour la communication bidirectionnelle Arduino-PC
    while(1) {
        
        j_msg_send["bg"] = bargraph;      // Création du message à envoyer
        if(!SendToSerial(arduino, j_msg_send)) {    //Envoie au Arduino
            cerr << "Erreur lors de l'envoie du message. " << endl;
        }
        // Reception message Arduino
        j_msg_rcv.clear(); // effacer le message precedent
        if(!RcvFromSerial(arduino, raw_msg)) {
            cerr << "Erreur lors de la reception du message. " << endl;
        }
        
        // Impression du message de l'Arduino, si valide
        if(raw_msg.size()>0) {
             j_msg_rcv = json::parse(raw_msg);       // Transfert du message en json
            d_u = j_msg_rcv["d_u"];
            d_d = j_msg_rcv["d_d"];
            d_l = j_msg_rcv["d_l"];
            d_r = j_msg_rcv["d_r"];

            t_l = j_msg_rcv["t_l"];
            t_r = j_msg_rcv["t_r"];

            b_j = j_msg_rcv["b_j"];
            angle_jstick = j_msg_rcv["a_j"];

            //acc_ST = j_msg_rcv["a_S"];
            acc_x = j_msg_rcv["a_x"];
            acc_y = j_msg_rcv["a_y"];
            acc_z = j_msg_rcv["a_z"];
            
            dpad_up = d_u;
            dpad_down = d_d;
            dpad_left = d_l;
            dpad_right = d_r;
            trig_left = t_l;
            trig_right = t_r;
            button_jstick = b_j;

            //cout << "Message de l'Arduino: d_u d_d d_l d_r t_l t_r b_j " << dpad_up << dpad_down << dpad_left << dpad_right << trig_left << trig_right << button_jstick << endl;
        }
        

        // Bloquer le fil pour environ 1 sec
        //Sleep(50); // 50ms
    }
    return 0;
}


/*---------------------------Definition de fonctions ------------------------
Fonction d'envoi
Entrée : Port de communication, tampon de réception du message
Sortie : Code d'erreur, 1 = erreur, 0 = ok
Traitement : Réception du message
-----------------------------------------------------------------------------*/
bool SendToSerial(SerialPort *arduino, json j_msg) {
    // Return 0 if error
    string msg = j_msg.dump();
    bool ret = arduino->writeSerialPort(msg.c_str(), msg.length());
    return ret;
}


/*---------------------------Definition de fonctions ------------------------
Fonction de réception
Entrée : Port de communication, message à envoyer
Sortie : Code d'erreur, 1 = erreur, 0 = ok
Traitement : Envoie du message
-----------------------------------------------------------------------------*/
bool RcvFromSerial(SerialPort *arduino, string &msg) {
    // Return 0 if error
    // Message output in msg
    string str_buffer;
    char char_buffer[MSG_MAX_SIZE];
    int buffer_size;

    msg.clear(); // clear string
    // Read serialport until '\n' character (Blocking)
    while(msg.back()!='\n') {
        if(msg.size()>MSG_MAX_SIZE) {
            return false;
        }

        buffer_size = arduino->readSerialPort(char_buffer, MSG_MAX_SIZE);
        str_buffer.assign(char_buffer, buffer_size);
        msg.append(str_buffer);
    }

    msg.pop_back(); //remove '/n' from string
    return true;
}
