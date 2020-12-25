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
        char buffer[4]; //Pointeur pour la lecture

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

        fichier.ignore(10);

        //  5. Vérification de l'unicité du canal

        fichier.read(buffer, 2);
        int nbCanaux = (int) buffer[0]; //Lecture mot en format petit-boutiste

        if (nbCanaux != 1){
            valid = false;
        }

        //  6. Passage informations non exploitées

        fichier.ignore(10);

        //  7. Extraction nombre de bits par échantillon

        fichier.read(buffer, 2);
        int nbBitEx = (int) buffer[0]; //Lecture mot en format petit-boutiste

        //  8. Passage informations non exploitées

        fichier.ignore(4);

        //  9. Extraction taille des données (en octets)

        /*
        fichier.read(buffer, 4);
        unsigned char bufferAbs[4] = buffer;
        int tailleDataEx = atoi(bufferAbs);
        */        

        //  10. Attribution et vérification

        fichier.close();
        if (valid){ //Récupération des données obtenues
            nbBit = nbBitEx;
            //tailleData = tailleDataEx;
        }
        else{
            cerr << "Format de fichier non pris en charge !" << endl;
        }
    }
    else {
        cerr << "Impossible d'ouvrir le fichier !" << endl;
    }
}



void audio::extract(){

    ifstream fichier(filePath, ios::in);  //Ouverture fichier en mode lecture

    if (fichier.is_open()){

        //  1. Passage de l'entête

        fichier.ignore(44);

        //  2. Préparation à l'extraction de données

        vector<int> data(0);
        int nbOct = nbBit / 8; //Nombre d'octet à lire pour chaque échantillon

        //  3. EXtraction données entières

        while(fichier){

            char carac = fichier.get(); //Acqusistion échantillon
            int sample = atoi(&carac);
            data.push_back(sample);

            if (sample != 0){
                cout << "Bonjour !" << endl;
            }
            else{
                cout << sample << endl;
            }
        }

        fichier.close();
        //return &data;

    }
    else{
        cerr << "Impossible d'ouvrir le fichier !" << endl;
    }
}