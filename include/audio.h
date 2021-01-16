#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

class audio {

public:

    void set_filePath(string path);

    void preExtract();

    void extract();

    int get_bitDepth();

    int get_tailleData();

    int get_tailleFichier();

    int get_freqEch();

    std::vector<int> get_binaryData();

    void createWave();

    void fillWave();

    void fillWave_testSinus(float duration, float period);

    void finalWave();

private:

    string filePath = "./MonMessageMorse.wav"; //Emplacement fichier audio pour lecture/création (par défaut répertoire courant pour création)
    uint16_t bitDepth = 16; //Nombre de bits par échantillons
    uint32_t tailleFichier = 0; //Taille du fichier .wav
    uint32_t tailleData = 0; //Taille des données binaires audio pour .wav
    uint32_t freqEch = 11025;//Fréquence d'échantillonnage
    int nbSample; //Nombre d'échantillon
    std::vector<int> binaryData;
    
};