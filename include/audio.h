#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

class audio {

public:

    audio();

    void set_filePath(string path);

    void set_binaryData(std::vector<uint16_t> data);

    void set_nbSample(int nb);

    void preExtract();

    void extract();

    int get_bitDepth();

    int get_tailleData();

    int get_tailleFichier();

    int get_freqEch();

    float get_dotDuration();

    float get_intraLetterDuration();

    std::vector<uint16_t> get_binaryData();

    std::vector<bool> get_logicData();

    void createWave();

    void fillWave();

    void fillWave_testSinus(float duration, float period);

    void finalWave();

    void lissage();

    void detecLogicData();

    void detecDurations();

private:

    /* Variables pour la gestion du fichier audio */

    string filePath = "./MonMessageMorse.wav"; //Emplacement fichier audio pour lecture/création (par défaut répertoire courant pour création)
    uint16_t bitDepth = 16; //Nombre de bits par échantillons
    uint32_t tailleFichier = 0; //Taille du fichier .wav
    uint32_t tailleData = 0; //Taille des données binaires audio pour .wav
    uint32_t freqEch = 11025;//Fréquence d'échantillonnage
    int nbSample; //Nombre d'échantillon

    /* Variables pour l'écriture/la récupération des données */

    std::vector<uint16_t> binaryData;
    std::vector<bool> logicData;

    /* Variables sur les propriétés du message */

    float dotDuration = 1;//Temps en ms
    float intraLetterDuration = 1;

    float interLetterDuration = 0;//Variables initialisées dans le constructeur ou le détecteur
    float interWordDuration = 0;
    float dashDuration = 0;

    float tolerance = 0.8;//Tolérance pour la détection
    
};