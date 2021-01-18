#include "../include/audio.h"

audio::audio() {
    dashDuration = 3*dotDuration;
    interWordDuration = 7*intraLetterDuration;
    interLetterDuration = 3*intraLetterDuration;
}



void audio::set_filePath(string path){
    filePath = path;
}



void audio::set_binaryData(std::vector<uint16_t> data) {
    binaryData = data;
}



void audio::set_nbSample(int nb) {
    nbSample = nb;
}



int audio::get_bitDepth(){
    return bitDepth;
}



int audio::get_tailleData(){
    return tailleData;
}



int audio::get_tailleFichier(){
    return tailleFichier;
}



std::vector<uint16_t> audio::get_binaryData(){
    return binaryData;
}



std::vector<bool> audio::get_logicData(){
    return logicData;
}


int audio::get_freqEch(){
    return freqEch;
}


float audio::get_dotDuration(){
    return dotDuration;
}



float audio::get_intraLetterDuration(){
    return intraLetterDuration;
}



void audio::preExtract(){

    ifstream fichier(filePath, ios::binary);  //Ouverture fichier en mode lecture
 
    if(fichier.is_open())  //Si ouverture réussie
    {   
        bool valid = true; //Variable de vérification de la validité du fichier

        //  1. Vérification RIFF

        char RIFF[4];
        fichier.read(RIFF, sizeof(RIFF)); //Lecture constante d'entête du fichier
        std::string RIFF_str = RIFF;
        RIFF_str.resize(4);

        if (RIFF_str.compare("RIFF") != 0){
            valid = false;
        }

        //  2. Extraction taille fichier

        uint32_t tailleFichier_ex;
        fichier.read(reinterpret_cast<char*>(&tailleFichier_ex), sizeof(tailleFichier_ex));
        tailleFichier_ex += 8; //Ajout taille des deux premières infos d'entête
        
        //  3. Vérification format

        char format[4];
        fichier.read(format, sizeof(format));
        std::string format_str = format;
        format_str.resize(4);

        if (format_str.compare("WAVE") != 0){
            valid = false;
        }

        //  4. Passage informations non exploitées

        fichier.ignore(10);

        //  5. Vérification de l'unicité du canal

        uint16_t nbCanaux;
        fichier.read(reinterpret_cast<char*>(&nbCanaux), sizeof(nbCanaux));

        if (nbCanaux != 1){
            valid = false;
        }

        //  6. Extraction fréquence d'échantillonnage

        uint32_t freqEch_ex;
        fichier.read(reinterpret_cast<char*>(&freqEch_ex), sizeof(freqEch_ex));

        //  7. Passage informations non exploitées

        fichier.ignore(6);

        //  8. Extraction nombre de bits par échantillon

        uint16_t bitDepth_ex;
        fichier.read(reinterpret_cast<char*>(&bitDepth_ex), sizeof(bitDepth_ex));

        //  9. Vérification entrée dans le boc de données

        char data[4];
        fichier.read(data, sizeof(data));
        std::string data_str = data;
        data_str.resize(4);

        if (data_str.compare("data") != 0) {
            valid = false;
        }

        //  10. Extraction taille des données

        uint32_t tailleData_ex;
        fichier.read(reinterpret_cast<char*>(&tailleData_ex), sizeof(tailleData_ex));  

        //  11. Attribution et vérification

        fichier.close();

        if (valid){ //Récupération des données obtenues
            bitDepth = bitDepth_ex;
            tailleData = tailleData_ex;
            tailleFichier = tailleFichier_ex;
            nbSample = tailleData / bitDepth;
            freqEch = freqEch_ex;
        }
        else{
            cerr << "Format de fichier non pris en charge !" << endl;
        }
    }
    else {
        cerr << "Impossible d'ouvrir le fichier pour lecture !" << endl;
    }
}



void audio::extract(){

    ifstream wav(filePath, ios::binary);  //Ouverture fichier en mode lecture

    if (wav.is_open()){

        //  1. Passage de l'entête

        wav.ignore(44);

        //  2. Préparation à l'extraction de données

        int bytDepth = bitDepth / 8; //Nombre d'octet à lire pour chaque échantillon

        //  3. EXtraction données entières

        nbSample = 0;
        while(wav){

            int sample;
            wav.read(reinterpret_cast<char*>(&sample), bytDepth);
            binaryData.push_back(sample);
            nbSample++;
        }

        wav.close();
    }
    else{
        cerr << "Impossible d'ouvrir le fichier pour lecture !" << endl;
    }
}



void audio::createWave() {

    std::ofstream wav;
    wav.open(filePath, std::ofstream::out | std::ofstream::binary);

    if (wav.is_open())
    {
        //  1. Entête de déclaration au format WAVE

        //      1.1 Ecriture "RIFF"

        char RIFF[4] = {'R', 'I', 'F', 'F'};
        wav.write(RIFF, sizeof(RIFF));

        //      1.2 Ecriture de la taille

        //tailleFichier est déjà initialisé à 0, il sera rempli plus tard...
        wav.write(reinterpret_cast<char*>(&tailleFichier), sizeof(tailleFichier));

        //      1.3 Ecriture du format

        char format[4] = {'W', 'A', 'V', 'E'};
        wav.write(format, sizeof(format));

        //  2. Entête décrivant le format audio

        //      2.1 Ecriture de l'identifiant

        char id[4] = {'f', 'm', 't', ' '};
        wav.write(id, sizeof(id));

        //      2.2 Ecriture de la taille du bloc de description

        uint32_t tailleBloc = 16;
        wav.write(reinterpret_cast<char*>(&tailleBloc), sizeof(tailleBloc));

        //      2.3 Ecriture du format de stockage

        uint16_t formatStock = 1;
        wav.write(reinterpret_cast<char*>(&formatStock), sizeof(formatStock));

        //      2.4 Ecriture du nb de canaux

        uint16_t nbCanaux = 1;
        wav.write(reinterpret_cast<char*>(&nbCanaux), sizeof(nbCanaux));

        //      2.5 Ecriture de la fréquence d'échantillonnage

        //freqEch est déjà initialisé à 11 025 Hz
        wav.write(reinterpret_cast<char*>(&freqEch), sizeof(freqEch));

        //      2.6 Ecriture du nb d'octets à lire par seconde

        uint16_t bytePerBloc = bitDepth / 2; //Initialisation en amont pour le calcul qui suit

        uint32_t bytePerSec = freqEch*bytePerBloc;
        wav.write(reinterpret_cast<char*>(&bytePerSec), sizeof(bytePerSec));

        //      2.7 Ecriture du nb d'octets par bloc d'échantillonnage

        //Initilisation en amont
        wav.write(reinterpret_cast<char*>(&bytePerBloc), sizeof(bytePerBloc));

        //      2.8 Ecriture du nb de bits par échantillon

        //bitDepth est déjà initialisé à 16 bits
        wav.write(reinterpret_cast<char*>(&bitDepth), sizeof(bitDepth));

        //  3. Entête de description du bloc de données

        //      3.1 Ecriture constante de données

        char data[4] = {'d','a','t','a'};
        wav.write(data, sizeof(data));

        //      3.2 Ecriture nb d'octets de données

        //tailleData est déjà initialisé à 0, il sera rempli plus tard...
        wav.write(reinterpret_cast<char*>(&tailleData), sizeof(tailleData));
        
        wav.close();
    }
    else {
        std::cerr << "Problème de création de fichier !" << std::endl;
    }
}



void audio::fillWave() {

    std::ofstream wav;
    wav.open(filePath, std::ofstream::app | std::ofstream::binary);

    if (wav.is_open()) {

        int len = binaryData.size();
        
        for (int i=0; i<len; i++) {

            uint16_t byte = binaryData[i]; // Extraction donnée (ATTTENTION ne fonctionne qu'avec 16 bits pour bitDepth !) 
            wav.write(reinterpret_cast<char*>(&byte), sizeof(byte));
        }

        wav.close();
    }
    else {
        std::cerr << "Problème d'ouverture de fichier pour écriture !" << std::endl;
    }
}

void audio::fillWave_testSinus(float duration, float freq) {

    std::ofstream wav;
    wav.open(filePath, std::ofstream::app | std::ofstream::binary);

    if (wav.is_open()) {

        /* Tous les temps indiqués sont en ms */

        float time = 0;
        float periodEch = 1000 / ((float) freqEch); //  Passage en ms
        float period = 1000 / freq;
        nbSample = duration / periodEch;
        uint16_t offset = pow(2,8*sizeof(uint16_t)-1); //  Calcul offset
        uint amplitude = pow(2,8*sizeof(uint16_t)) - 1; //  Calcul amplitude

        for (int i=0; i<nbSample; i++) {

            time += periodEch;
            uint16_t signal = ((float) amplitude)*sin(period*time); //  Création signal (ATTENTION ne fonctionne qu'avec 16 bits pour bitDepth)
            signal += offset; //  Décalage pour recentrer sur la plage de codage
            binaryData.push_back(signal);

            wav.write(reinterpret_cast<char*>(&signal), sizeof(signal)); //  Ajout dans le fichier
        }

        wav.close();
    }
    else {
        std::cerr << "Problème d'ouverture de fichier pour écriture !" << std::endl;
    }
}



void audio::finalWave() {

    /* Le but de cette méthode est de compléter les données manquantes lors de l'écriture de l'entête */

    tailleData = bitDepth*binaryData.size(); //  Actualisation du nb de données
    tailleFichier = tailleData + 44; //  Actualisation taille fichier avec entête

    std::ofstream wav;
    wav.open(filePath, std::ofstream::app | std::ofstream::binary);

    if (wav.is_open()) {
        
        //  1. Ajout taille du fichier

        wav.seekp(5, std::ios::beg); //  Replacement au bon endroit
        uint32_t tailleFichier_ex = tailleFichier - 8; //  Application de la norme
        wav.write(reinterpret_cast<char*>(&tailleFichier_ex), sizeof(tailleFichier_ex));

        //  2. Ajout taille des données

        wav.seekp(41, std::ios::beg); //  Replacement au bon endroit
        wav.write(reinterpret_cast<char*>(&tailleData), sizeof(tailleData));
        

        wav.close();
    }
    else {
        std::cerr << "Problème d'ouverture de fichier pour écriture !" << std::endl;
    }
}



void audio::lissage() {

    /* Lissage du signal pour éviter l'interprétation de "0" issus du sinus et non d'un silence morse */

    std::vector<uint16_t> binaryDataFinal = binaryData;

    for (int i=1; i<nbSample-1; i++) {

        int somme = binaryData[i-1] + binaryData[i] + binaryData[i+1]; //  Moyenne sur 3 éléments
        binaryDataFinal[i] = (somme / 3);
    }

    binaryData = binaryDataFinal;
}



void audio::detecLogicData() {

    /* Création d'une liste des données en booléen pour la détection de la durée d'un dot */

    for (int i=0; i<nbSample; i++) {

        logicData.push_back(0 < binaryData[i]);
    }
}



void audio::detecDurations() {

    int nbTrueMax = 0;  //  Nb maximum de niveaux haut successifs (dashDuration)
    int nbFalseMin = 0; //  Nb minimum de niveau bas successfis (intraLetterDuration)

    int i=0;
    while (i < (nbSample - nbTrueMax)) { //  Recherche pour nbTrueMax
    
        int j=i;
        while( (j<nbSample) and logicData[j]) {
            j++;
        }
        if ( (j-i) > nbTrueMax ) {
            nbTrueMax = j-i;
        }
        i++;
    }

    /* On peut optimiser le programme avec une seule boucle while mais ici la clareté est privilégiée */

    i=0;
    while (i < nbSample) {  //  Recherche pour nbFalseMin

        int j=i;
        while( (j<nbSample) and not(logicData[j])) {
            j++;
        }
        if ( (j-i) < nbFalseMin ) {
            nbFalseMin = j-i;
        }
        i++;
    }

    dashDuration = nbTrueMax/freqEch;
    dotDuration = dashDuration / 3;

    intraLetterDuration = nbFalseMin/freqEch;
    interLetterDuration = 3*intraLetterDuration;
    interWordDuration = 7*intraLetterDuration;
}