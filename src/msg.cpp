#include "../include/msg.h"
#include <iostream>

msg::msg() { //   Remplissage des tables de conversion
    tabFrToMorse['a'] = ".-";
    tabFrToMorse['b'] = "-...";
    tabFrToMorse['c'] = "-.-.";
    tabFrToMorse['d'] = "-..";
    tabFrToMorse['e'] = ".";
    tabFrToMorse['f'] = "..-.";
    tabFrToMorse['g'] = "--.";
    tabFrToMorse['h'] = "....";
    tabFrToMorse['i'] = "..";
    tabFrToMorse['j'] = ".---";
    tabFrToMorse['k'] = "-.-";
    tabFrToMorse['l'] = ".-..";
    tabFrToMorse['m'] = "--";
    tabFrToMorse['n'] = "-.";
    tabFrToMorse['o'] = "---";
    tabFrToMorse['p'] = ".--.";
    tabFrToMorse['q'] = "--.-";
    tabFrToMorse['r'] = ".-.";
    tabFrToMorse['s'] = "...";
    tabFrToMorse['t'] = "-";
    tabFrToMorse['u'] = "..-";
    tabFrToMorse['v'] = "...-";
    tabFrToMorse['w'] = ".--";
    tabFrToMorse['x'] = "-..-";
    tabFrToMorse['y'] = "-.--";
    tabFrToMorse['z'] = "--..";
    tabFrToMorse['1'] = ".----";
    tabFrToMorse['2'] = "..---";
    tabFrToMorse['3'] = "...--";
    tabFrToMorse['4'] = "....-";
    tabFrToMorse['5'] = ".....";
    tabFrToMorse['6'] = "-....";
    tabFrToMorse['7'] = "--...";
    tabFrToMorse['8'] = "---..";
    tabFrToMorse['9'] = "----.";
    tabFrToMorse['0'] = "-----";
    tabFrToMorse[' '] = " ";

    tabMorseToFr[".-"] = 'a';
    tabMorseToFr["-..."] = 'b';
    tabMorseToFr["-.-."] = 'c';
    tabMorseToFr["-.."] = 'd';
    tabMorseToFr["."] = 'e';
    tabMorseToFr["..-."] = 'f';
    tabMorseToFr["--."] = 'g';
    tabMorseToFr["...."] = 'h';
    tabMorseToFr[".."] = 'i';
    tabMorseToFr[".---"] = 'j';
    tabMorseToFr["-.-"] = 'k';
    tabMorseToFr[".-.."] = 'l';
    tabMorseToFr["--"] = 'm';
    tabMorseToFr["-."] = 'n';
    tabMorseToFr["---"] = 'o';
    tabMorseToFr[".--."] = 'p';
    tabMorseToFr["--.-"] = 'q';
    tabMorseToFr[".-."] = 'r';
    tabMorseToFr["..."] = 's';
    tabMorseToFr["-"] = 't';
    tabMorseToFr["..-"] = 'u';
    tabMorseToFr["...-"] = 'v';
    tabMorseToFr[".--"] = 'w';
    tabMorseToFr["-..-"] = 'x';
    tabMorseToFr["-.--"] = 'y';
    tabMorseToFr["--.."] = 'z';
    tabMorseToFr[".----"] = '1';
    tabMorseToFr[".----"] = '2';
    tabMorseToFr["...--"] = '3';
    tabMorseToFr["....-"] = '4';
    tabMorseToFr["....."] = '5';
    tabMorseToFr["-...."] = '6';
    tabMorseToFr["--..."] = '7';
    tabMorseToFr["---.."] = '8';
    tabMorseToFr["----."] = '9';
    tabMorseToFr["-----"] = '0';
}

void msg::set_msg_morse(std::string code) {
    msg_morse = code;
}

void msg::set_msg_fr(std::string phrase) {
    msg_fr = phrase;
}

std::string msg::get_msg_fr() {
    return msg_fr;
}

std::string msg::get_msg_morse() {
    return msg_morse;
}

void msg::frToMorse() {

    int len = msg_fr.size();
    for (int i=0; i<len; i++) { //   Codage caractère par caractère

        char carac = msg_fr[i];
        std::string equivMorse = msg::tabFrToMorse[carac]; //   Recherche de l'équivalent avec dictionnaire
        msg_morse += equivMorse;
        if (i != len-1) { //   Pas de séparation en fin de message
            msg_morse += ' '; //   Séparation inter-caractères
        }

        /*
        Si on tombe sur un espace pour le message en français (séparation inter-mots français) l'équivalent
        dictionnaire plus l'ajout sur la ligne de code juste ci-dessus va bien ajouter un double espace
        (séparation inter-mots morse).
        */
    }
}

void msg::morseToFr() {

    int len = msg_morse.size();
    int i = 0; //   Variable de parcours
    while (i<len) { //   Décodage caractère morse par caractère morse

        int j = i; //   Itérateur pour extraction caractère morse complet
        std::string carMorse;
        carMorse += msg_morse[i]; //   Ajout de la première info (. ou -)
        j++;

        while ( (j<len) and (msg_morse[j] != ' ') ) { //   Détection fin de caractère morse
            carMorse += msg_morse[j]; //   Extraction
            j++;
        }

        char equivFr = msg::tabMorseToFr[carMorse]; //   Recherche de l'équivalent avec dictionnaire (décodage)
        msg_fr += equivFr;

        //  Détection espace inter-mots morse
        if ( (j<len-2) and (msg_morse[j] == ' ') and (msg_morse[j+1] == ' ') and (msg_morse[j+2] == ' ') ) {
            msg_fr += ' ';
            j += 2; // Décalage dû à l'espace inter-mots morse
        }

        i = j+1; //   Passage au mot suivant
    }
}