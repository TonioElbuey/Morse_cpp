#include "../include/interface.h"

void interface::init() {

    std::endl;
    std::cout << "#---------# Encodeur / Transcodeur Morse #---------#" << std::endl << std::endl;
    std::cout << "Sens de conversion (0 ou 1) ? ";
    std::cin >> sens;
    std::endl;

    if (sens) { //Si français vers morse
        frProc();
        std::cout << "#------# Encodage (français vers morse)"
    }
    else { //Si morse vers français
        morseProc();
        std::cout << "#------# Decodage (morse vers français)"
    }
}



void interface::frProc() {

    std::endl;
    std::cout << "Saisie clavier ou lecture fichier texte (0 ou 1) ? ";
    std::cin >> lectureFr;
    std::endl;

    if (lectureFr) { // Si saisie clavier
        std::cout << "Text à encoder (sur une seule ligne) :" << std::endl;
        getLine(cin, texte);
    }
    else {
        
    }
}