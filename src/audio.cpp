#include "../include/audio.h"



void audio::define_filePath(string path){
    filePath = path;
}

int audio::get_nbBit(){
    return nbBit;
}

int audio::get_tailleData(){
    return tailleData;
}

int* audio::preExtract(){

    ifstream fichier(filePath, ios::in);  //Ouverture fichier en mode lecture
 
    if(fichier.is_open())  //Si ouverture réussie
    {   
        bool valid = true; //Variable de vérification de la validité du fichier
        char buffer[10]; //Pointeur pour la lecture

        //  1. Vérification RIFF

        fichier.read(buffer, 4); //Lecture constante d'entête du fichier
        string cste = buffer; //Conversion en string
        cste.resize(4);

        if (cste != "RIFF"){
            valid = false;
        }

        //  2. Passage taille fichier

        fichier.read(buffer, 4);
        
        //  3. Vérification format

        fichier.read(buffer, 4);
        string format = buffer;
        format.resize(4);

        if (format != "WAVE"){
            valid = false;
        }

        //  4. Passage informations non exploitées

        fichier.read(buffer, 10);

        //  5. Vérification de l'unicité du canal

        fichier.read(buffer, 2);
        string nbCanauxStr = buffer; //Conversion de char* à string
        nbCanauxStr.resize(1);
        int nbCanaux = stoi(nbCanauxStr); //Conversion de string à int

        if (nbCanaux != 1){
            valid = false;
        }

        //  6. Passage informations non exploitées

        fichier.read(buffer, 10);

        //  7. Extraction nombre de bits par échantillon

        fichier.read(buffer, 2);
        string nbBitStr = buffer; //Conversion de char* à string
        nbBitStr.resize(1);
        int nbBitEx = stoi(nbBitStr); //Conversion de string à int

        //  8. Passage informations non exploitées

        fichier.read(buffer, 4);

        //  9. Extraction taille des données (en octets)

        fichier.read(buffer, 4);
        int tailleDataEx = stoi(buffer);

        //  10. Attribution et vérification

        if (valid){ //Récupération des données obtenues
            nbBit = nbBitEx;
            tailleData = tailleDataEx;
        }
        else{
            cerr << "Format de fichier non pris en charge !" << endl;
        }
    }
    else {
        cerr << "Impossible d'ouvrir le fichier !" << endl;
    }

    fichier.close();
}



void audio::extract(){
    
    }