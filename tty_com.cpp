/* 
 * Auteurs: Jean-Samuel Lauzon    
 * Date: Fevrier 2022
 * Projet S2ei
*/

/*------------------------------ Librairies ---------------------------------*/
#include <iostream>
#include <string>
#include <thread>
using namespace std;

/*-------------------------- Librairies externes ----------------------------*/
#include "serial/SerialPort.hpp"
#include "json.hpp"
#include "controller.h"
using json = nlohmann::json;

/*------------------------------ Constantes ---------------------------------*/
#define MSG_MAX_SIZE 1024   // Longueur maximale d'un message


/*------------------------- Prototypes de fonctions -------------------------*/
bool SendToSerial(SerialPort *arduino, json j_msg);
bool RcvFromSerial(SerialPort *arduino, string &msg);


/*---------------------------- Variables globales ---------------------------*/
SerialPort * arduino; //doit etre un objet global!

/*----------------------------- Fonction "Main" -----------------------------*/


void TTY(controller* ptr_ctrl, string COM, int BAUD) {
    string raw_msg;

    arduino = new SerialPort(COM.c_str(), BAUD);
    
    if(!arduino->isConnected()) {
        cout << "Impossible de se connecter au port "<< COM <<". Fermeture du thread!" <<endl;
        while(1)
        {
            this_thread::sleep_for(20000000000000000ms);
        }
    }
    
    // Structure de donnees JSON pour envoie et reception
    
    int d_u,d_d,d_l,d_r,t_l,t_r,b_j,acc;

    json j_msg_send, j_msg_rcv;

    // Boucle infinie pour la communication bidirectionnelle Arduino-PC
    while(1) {
        
        j_msg_send["bg"] = ptr_ctrl->bargraph;      // Création du message à envoyer
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

            acc = j_msg_rcv["acc"];

            ptr_ctrl->angle_jstick = j_msg_rcv["a_j"];

            ptr_ctrl->dpad_up = d_u;
            ptr_ctrl->dpad_down = d_d;
            ptr_ctrl->dpad_left = d_l;
            ptr_ctrl->dpad_right = d_r;
            ptr_ctrl->trig_left = t_l;
            ptr_ctrl->trig_right = t_r;
            ptr_ctrl->button_jstick = b_j;
            ptr_ctrl->acc = acc;

            //cout << "Message de l'Arduino: d_u d_d d_l d_r t_l t_r b_j " << dpad_up << dpad_down << dpad_left << dpad_right << trig_left << trig_right << button_jstick << endl;
        }
        

        // Bloquer le fil pour environ 1 sec
        //Sleep(50); // 50ms
    }
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
    string check = "";
    if(!msg.empty())
        check = msg.substr(msg.length() - 1);
    while(check !="\n") {
        if(!msg.empty())
            check = msg.substr(msg.length() - 1);

        buffer_size = arduino->readSerialPort(char_buffer, MSG_MAX_SIZE);
        str_buffer.assign(char_buffer, buffer_size);
        msg.append(str_buffer);
    }

    msg.pop_back(); //remove '/n' from string
    return true;
}
