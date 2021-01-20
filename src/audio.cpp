#include "../include/audio.h"

audio::audio() {
    dashDuration = 3*dotDuration;
    interWordDuration = 7*intraLetterDuration;
    interLetterDuration = 3*intraLetterDuration;
}



audio::~audio() {
    if (wavR.is_open()) {
        wavR.close();
    }
    if (wavC.is_open()) {
        wavC.close();
    }
}



void audio::set_filePath(string path){
    filePath = path;
}



void audio::set_binaryData(std::vector<int16_t> data) {
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



std::vector<int16_t> audio::get_binaryData(){
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



float audio::get_dashDuration(){
    return dashDuration;
}



void audio::preExtract(){

    wavR.open(filePath, ios::binary);  //Ouverture fichier en mode lecture
 
    if(wavR.is_open())  //Si ouverture réussie
    {   
        bool valid = true; //Variable de vérification de la validité du fichier

        //  1. Vérification RIFF

        char RIFF[4];
        wavR.read(RIFF, sizeof(RIFF)); //Lecture constante d'entête du fichier
        std::string RIFF_str = RIFF;
        RIFF_str.resize(4);

        if (RIFF_str.compare("RIFF") != 0){
            valid = false;
        }

        //  2. Extraction taille fichier

        uint32_t tailleFichier_ex;
        wavR.read(reinterpret_cast<char*>(&tailleFichier_ex), sizeof(tailleFichier_ex));
        tailleFichier_ex += 8; //Ajout taille des deux premières infos d'entête
        
        //  3. Vérification format

        char format[4];
        wavR.read(format, sizeof(format));
        std::string format_str = format;
        format_str.resize(4);

        if (format_str.compare("WAVE") != 0){
            valid = false;
        }

        //  4. Passage informations non exploitées

        wavR.ignore(10);

        //  5. Vérification de l'unicité du canal

        uint16_t nbCanaux;
        wavR.read(reinterpret_cast<char*>(&nbCanaux), sizeof(nbCanaux));

        if (nbCanaux != 1){
            valid = false;
        }

        //  6. Extraction fréquence d'échantillonnage

        uint32_t freqEch_ex;
        wavR.read(reinterpret_cast<char*>(&freqEch_ex), sizeof(freqEch_ex));

        //  7. Passage informations non exploitées

        wavR.ignore(6);

        //  8. Extraction nombre de bits par échantillon

        uint16_t bitDepth_ex;
        wavR.read(reinterpret_cast<char*>(&bitDepth_ex), sizeof(bitDepth_ex));

        //  9. Vérification entrée dans le boc de données

        char data[4];
        wavR.read(data, sizeof(data));
        std::string data_str = data;
        data_str.resize(4);

        if (data_str.compare("data") != 0) {
            valid = false;
        }

        //  10. Extraction taille des données

        uint32_t tailleData_ex;
        wavR.read(reinterpret_cast<char*>(&tailleData_ex), sizeof(tailleData_ex));  


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

    if (wavR.is_open()) {

        //  1. Passage de l'entête

        wavR.ignore(44);

        //  2. Préparation à l'extraction de données

        int bytDepth = bitDepth / 8; //Nombre d'octet à lire pour chaque échantillon

        //  3. EXtraction données entières

        nbSample = 0;
        while(wavR) {

            int sample;
            wavR.read(reinterpret_cast<char*>(&sample), bytDepth);
            binaryData.push_back(sample);
            nbSample++;
        }
    }
    else{
        cerr << "Impossible d'ouvrir le fichier pour lecture ! Pre-extraction oubliée ?" << endl;
    }
}



void audio::createWave() {

    wavC.open(filePath, std::ofstream::out | std::ofstream::binary);

    if (wavC.is_open())
    {
        //  1. Entête de déclaration au format WAVE

        //      1.1 Ecriture "RIFF"

        char RIFF[4] = {'R', 'I', 'F', 'F'};
        wavC.write(RIFF, sizeof(RIFF));

        //      1.2 Ecriture de la taille

        //tailleFichier est déjà initialisé à 0, il sera rempli plus tard...
        wavC.write(reinterpret_cast<char*>(&tailleFichier), sizeof(tailleFichier));

        //      1.3 Ecriture du format

        char format[4] = {'W', 'A', 'V', 'E'};
        wavC.write(format, sizeof(format));

        //  2. Entête décrivant le format audio

        //      2.1 Ecriture de l'identifiant

        char id[4] = {'f', 'm', 't', ' '};
        wavC.write(id, sizeof(id));

        //      2.2 Ecriture de la taille du bloc de description

        uint32_t tailleBloc = 16;
        wavC.write(reinterpret_cast<char*>(&tailleBloc), sizeof(tailleBloc));

        //      2.3 Ecriture du format de stockage

        uint16_t formatStock = 1;
        wavC.write(reinterpret_cast<char*>(&formatStock), sizeof(formatStock));

        //      2.4 Ecriture du nb de canaux

        uint16_t nbCanaux = 1;
        wavC.write(reinterpret_cast<char*>(&nbCanaux), sizeof(nbCanaux));

        //      2.5 Ecriture de la fréquence d'échantillonnage

        //freqEch est déjà initialisé à 11 025 Hz
        wavC.write(reinterpret_cast<char*>(&freqEch), sizeof(freqEch));

        //      2.6 Ecriture du nb d'octets à lire par seconde

        uint16_t bytePerBloc = bitDepth / 2; //Initialisation en amont pour le calcul qui suit

        uint32_t bytePerSec = freqEch*bytePerBloc;
        wavC.write(reinterpret_cast<char*>(&bytePerSec), sizeof(bytePerSec));

        //      2.7 Ecriture du nb d'octets par bloc d'échantillonnage

        //Initilisation en amont
        wavC.write(reinterpret_cast<char*>(&bytePerBloc), sizeof(bytePerBloc));

        //      2.8 Ecriture du nb de bits par échantillon

        //bitDepth est déjà initialisé à 16 bits
        wavC.write(reinterpret_cast<char*>(&bitDepth), sizeof(bitDepth));

        //  3. Entête de description du bloc de données

        //      3.1 Ecriture constante de données

        char data[4] = {'d','a','t','a'};
        wavC.write(data, sizeof(data));

        //      3.2 Ecriture nb d'octets de données

        //tailleData est déjà initialisé à 0, il sera rempli plus tard...
        wavC.write(reinterpret_cast<char*>(&tailleData), sizeof(tailleData));
    }
    else {
        std::cerr << "Problème de création de fichier !" << std::endl;
    }
}



void audio::fillWave() {

    if (wavC.is_open()) {
        
        for (int i=0; i<nbSample; i++) {

            uint16_t byte = binaryData[i]; // Extraction donnée (ATTTENTION ne fonctionne qu'avec 16 bits pour bitDepth !) 
            wavC.write(reinterpret_cast<char*>(&byte), sizeof(byte));
        }
    }
    else {
        std::cerr << "Problème d'ouverture de fichier pour écriture ! (Création effectuée ?)" << std::endl;
    }
}

void audio::fillWave_testSinus(float secDuration, float freq) {

    if (wavC.is_open()) {

        /* Tous les temps indiqués sont en ms */

        float time = 0;
        float periodEch = 1000 / ((float) freqEch); //  Passage en ms
        float period = 1000 / freq;
        nbSample = 1000*secDuration / periodEch; // ATTENTION Conversion en ms
        int16_t amplitude = pow(2,8*sizeof(int16_t)-2); //  Calcul amplitude

        for (int i=0; i<nbSample; i++) {

            int16_t signal = ((float) amplitude)*sin(2*3.14*time/period); //  Création signal (ATTENTION ne fonctionne qu'avec 16 bits pour bitDepth)
            binaryData.push_back(signal);
            time += periodEch;

            wavC.write(reinterpret_cast<char*>(&signal), sizeof(signal)); //  Ajout dans le fichier
        }
    }
    else {
        std::cerr << "Problème d'ouverture de fichier pour écriture ! (Création effectuée ?)" << std::endl;
    }
}



void audio::finalWave() {

    /* Le but de cette méthode est de compléter les données manquantes lors de l'écriture de l'entête */

    tailleData = bitDepth*binaryData.size(); //  Actualisation du nb de données
    tailleFichier = tailleData + 44; //  Actualisation taille fichier avec entête

    if (wavC.is_open()) {
        
        //  1. Ajout taille du fichier
        
        wavC.seekp(4); //  Replacement au bon endroit
        uint32_t tailleFichier_ex = tailleFichier - 8; //  Application de la norme
        wavC.write(reinterpret_cast<char*>(&tailleFichier_ex), sizeof(tailleFichier_ex));

        //  2. Ajout taille des données

        wavC.seekp(40); //  Replacement au bon endroit
        wavC.write(reinterpret_cast<char*>(&tailleData), sizeof(tailleData));
    }
    else {
        std::cerr << "Problème d'ouverture de fichier pour écriture ! (Création effectuée ?)" << std::endl;
    }
}



void audio::lissage() {

    /* Lissage du signal pour éviter l'interprétation de "0" issus du sinus et non d'un silence morse */

    std::vector<int16_t> binaryDataFinal = binaryData;

    for (int i=1; i<nbSample-1; i++) {

        int somme = binaryData[i-1] + binaryData[i] + binaryData[i+1]; //  Moyenne sur 3 éléments
        binaryDataFinal[i] = (somme / 3);
    }

    binaryData = binaryDataFinal;
}



void audio::detecLogicData() {

    /* Création d'une liste des données en booléen pour la détection de la durée d'un dot */

    for (int i=0; i<nbSample; i++) {

        logicData.push_back(0 < abs(binaryData[i]));
    }
}



void audio::detecDurations() {

    int nbTrueMax = 0;  //  Nb maximum de niveaux haut successifs (dashDuration)
    int nbFalseMin = nbSample; //  Nb minimum de niveau bas successfis (intraLetterDuration)

    int i=0;
    while (i < (nbSample - nbTrueMax)) { //  Recherche pour nbTrueMax
    
        int j=i;
        while( (j<nbSample) and logicData[j]) {
            j++;
        }
        if ( (j-i) > nbTrueMax ) {
            nbTrueMax = j-i;
        }
        i=j+1;
    }

    /* On peut optimiser le programme avec une seule boucle while mais ici la clareté est privilégiée */

    i=0;
    while ( not(logicData[i]) ) { //   Passage du silence initial ne correspondant pas à un caractère
        i++;
    }

    while (i < nbSample) {  //  Recherche pour nbFalseMin

        int j=i;
        while( (j<nbSample) and not(logicData[j])) {
            j++;
        }
        if ( (0 < (j-i)) and ((j-i) < nbFalseMin) ) {
            nbFalseMin = j-i;
        }
        i=j+1;
    }

    dashDuration = 1000*((float) nbTrueMax)/((float) freqEch);
    dotDuration = dashDuration / 3;

    intraLetterDuration = 1000*((float) nbFalseMin)/((float) freqEch);
    interLetterDuration = 3*intraLetterDuration;
    interWordDuration = 7*intraLetterDuration;
}



std::string audio::analyseLogicData() {

    int i = 0; //   Variable pour balayage du message
    int j = 0; //   Variable pour détection caractère
    float duration = 0;
    std::string msg = "";

    while ( not(logicData[i]) ) { //   Passage du silence initial ne correspondant pas à un caractère
        i++;
    }

    bool buffer = logicData[i]; //  Extraction premier terme

    while (i<nbSample) {

        j=i; //  Variable de détection d'un caractère ou espace en morse
        while ( (j<nbSample) and (logicData[j]==buffer) ) { //  Détection
            j++;
        }
        duration = 1000*((float) (j-i))/((float) freqEch); //   Calcul durée en ms

        /* La détection va du plus long pour un niveau logique au plus court */

        if ( buffer and (duration > tolerance*dashDuration) ) { //  Détection tiret
            msg += "-";
        }
        else if ( buffer and (duration > tolerance*dotDuration) ) { //  Détection point
            msg += ".";
        }
        else if ( not(buffer) and (duration > tolerance*interWordDuration) ) { //  Détection espace inter-mots
            msg += "   ";
        }
        else if ( not(buffer) and (duration > tolerance*interLetterDuration) ) { // Détection espace inter-lettre
            msg += " "; 
        }
        else if ( not(buffer) and (duration > tolerance*intraLetterDuration) ) { // Détection espace intra-lettre
            msg += "";
        }
        else {
            std::cerr << "Problème durant l'interprétation temporelle du signal !" << std::endl;
        }

        i=j+1; //   Passage au caractère suivant
        buffer = logicData[i];
    }

    return msg;
}



void audio::createLogicData(std::string msg) {

    /* Calcul du nb d'échantillon par caractère */

    uint dashPulse = dashDuration*freqEch/1000;
    uint dotPulse = dotDuration*freqEch/1000;
    uint intraLetterPulse = intraLetterDuration*freqEch/1000;
    uint interLetterPulse = interLetterDuration*freqEch/1000;
    uint interWordPulse = interWordDuration*freqEch/1000;

    for (int k=0; k<intraLetterPulse; k++) { //   Silence initial
                logicData.push_back(false);
        }
    int len = msg.size();

    int i = 0; //   Variable de parcours
    int j = 0; //   Itérateur pour extraction caractère morse complet

    while (i<len) { //   Décodage caractère morse par caractère morse
        
        if ( msg[i] == '.' ) {
            for (int k=0; k<dotPulse; k++) {
                logicData.push_back(true);
            }
            i++;
        }
        else if ( msg[i] == '-' ) {
            for (int k=0; k<dashPulse; k++) {
                logicData.push_back(true);
            }
            i++;
        }
        else if ( (i<len-1) and (msg[i] == ' ') and (msg[i+1] == ' ') ) {
            for (int k=0; k<interWordPulse; k++) {
                logicData.push_back(false);
            }
            i = i+2;
        }
        else if ( msg[i] == ' ' ) {
            for (int k=0; k<interLetterPulse; k++) {
                logicData.push_back(false);
            }
            i++;
        }
        else {
            std::cerr << "Problème d'interprétation d'un caractère morse !" << std::endl;
        }

        for (int k=0; k<intraLetterPulse; k++) { //   Séparation intra-Lettres
                logicData.push_back(false);
        }
    }

    nbSample = logicData.size();
}



void audio::createBinary() {

    float time = 0; //  Variable temporelle pour le sinus
    float periodEch = 1/((float) freqEch); // Période en ms

    int16_t amplitude = pow(2,8*sizeof(int16_t)-2); //  Calcul amplitude
    
    for (int i=0; i<nbSample; i++) {

        if (logicData[i]) { //  Si émission
            int16_t signal = ((float) amplitude)*sin(2*3.14*time*freqSin); //  Création signal (ATTENTION ne fonctionne qu'avec 16 bits pour bitDepth)
            binaryData.push_back(signal);
        }
        else { //   Si silence
            binaryData.push_back(0);
        }
        time += periodEch;
    }
}