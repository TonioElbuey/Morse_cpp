#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class audio {

public:

    void define_filePath(string path);

    int* preExtract();

    void extract();

    int get_nbBit();

    int get_tailleData();

private:

    string filePath = "."; //Emplacement fichier audio pour lecture/création (par défaut répertoire courant)
    int nbBit = 8; //Nombre de bits par échantillons
    int tailleData; //Taille des données binaires audio pour .wav
    
};