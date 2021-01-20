#include "../include/interface.h"

void interface::init() {

    std::cout << std::endl;
    std::cout << "#------------# Encodeur / Transcodeur Morse #------------#" << std::endl << std::endl;
    std::cout << "Sens de conversion (0:décodage ou 1:encodage) ? ";
    std::cin >> sens;
    std::cout << std::endl;

    if (sens) { //Si français vers morse
        std::cout << "#---# Encodage (français vers morse)" << std::endl;;
        frInput();
    }
    else { //Si morse vers français
        std::cout << "#---# Decodage (morse vers français)" << std::endl;
        morseInput();
    }
}



void interface::frInput() {

    std::cout << std::endl;
    std::cout << "Saisie clavier ou lecture fichier texte (0 ou 1) ? ";
    std::cin >> lectureFr;
    std::cout << std::endl;

    if ( not(lectureFr) ) { // Si saisie clavier
        std::cin.ignore();
        std::cout << "Text à encoder (sur une seule ligne) :" << std::endl;
        getline(cin, texte);
    }
    else {
        std::string fileName;
        std::cin.ignore();
        std::cout << "Nom fichier dans dossier fichiers_textes :" << std::endl;
        getline(cin, fileName);
        filePathFr += fileName;

        std::fstream txtFile;
        txtFile.open(filePathFr, ios::binary);

        if (txtFile.is_open()) {
            getline(txtFile, texte);
            txtFile.close();
        }
        else {
            std::cerr << "Problème fichier non trouvé !" << std::endl;
        }        
    }
}



std::string interface::get_texte() {
    return texte;
}



std::string interface::get_filePathFr() {
    return filePathFr;
}



std::string interface::get_filePathMr() {
    return filePathMr;
}



void interface::morseInput() {

    std::cout << std::endl;
    std::string fileName;
    std::cin.ignore();
    std::cout << "Nom fichier dans dossier wave_exemples :" << std::endl;
    getline(cin, fileName);
    filePathMr += fileName;
}



bool interface::get_sens() {
    return sens;
}