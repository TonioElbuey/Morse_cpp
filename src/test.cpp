#include "../include/msg.h"
#include "../include/test.h"
#include "../include/audio.h"



bool test::frToMorse() {

    msg sos;
    sos.set_msg_fr("sos sos");
    sos.frToMorse();
    std::string code = sos.get_msg_morse();
    bool valid = false;

    if (code.compare("... --- ...   ... --- ...") == 0) {
        valid = true;
    }
    std::cout << code << std::endl; 
    return valid;
}



bool test::morseToFr() {

    msg sos;
    sos.set_msg_morse("... --- ...   ... --- ...");
    sos.morseToFr();
    std::string phrase = sos.get_msg_fr();
    bool valid = false;

    if (phrase == "sos sos") {
        valid = true;
    }
    std::cout << sos.get_msg_fr() << std::endl; 
    return valid;
}



bool test::preExtract() {

    audio exemple;
    exemple.set_filePath("../wave_exemples/sos.wav");
    exemple.preExtract();

    bool valid = true;
    if (exemple.get_tailleFichier() != 108044) {
        valid = false;
    }
    if (exemple.get_bitDepth() != 16) {
        valid = false;
    }

    return valid;
}



void test::extract() {

    audio exemple;
    exemple.set_filePath("../wave_exemples/sos.wav");
    exemple.preExtract();
    exemple.extract();

    std::vector<int16_t> data;
    data = exemple.get_binaryData();
    int length = data.size();

    for (int i=0; i<length; i++) {
        std::cout << data[i] << std::endl;
    }
}



bool test::createWave() {

    audio exemple;
    exemple.set_filePath("../wave_exemples/test_creation_entete.wav");
    exemple.createWave();

    exemple.preExtract();

    std::cout << "tailleFichier : " << exemple.get_tailleFichier() << std::endl;
    std::cout << "tailleData : " << exemple.get_tailleData() << std::endl;
    std::cout << "bitDepth : " << exemple.get_bitDepth() << std::endl;
    std::cout << "freqEch : " << exemple.get_freqEch() << std::endl;

    bool valid = true;
    if (exemple.get_tailleFichier() != 8) { // Prise en compte de la norme
        valid = false;
    }
    if (exemple.get_tailleData() != 0) {
        valid = false;
    }
    if (exemple.get_bitDepth() != 16) {
        valid = false;
    }
    if ( exemple.get_freqEch() != 11025) {
        valid = false;
    }

    return valid;
}



void test::fillWave_testSinus() {

    audio exemple;
    exemple.set_filePath("../wave_exemples/test_sinusPur.wav");
    exemple.createWave();

    float freq = 440; //  En Hz
    float secDuration = 10; // En s

    exemple.fillWave_testSinus(secDuration, freq);
    std::vector<int16_t> data;
    data = exemple.get_binaryData();
    int length = data.size();

    for (int i=0; i<length; i++) {
        std::cout << data[i] << std::endl;
    }

    exemple.finalWave();
}



bool test::lissage() {

    audio exemple;
    std::vector<int16_t> test = {1,2,6,4,5};
    exemple.set_binaryData(test);
    exemple.set_nbSample(5);
    exemple.lissage();
    bool valid = true;

    if (exemple.get_binaryData() != (std::vector<int16_t>) {1,3,4,5,5}) {
        valid = false;
    }
    return valid;
}



void test::detecLogicData() {

    audio exemple;
    std::vector<int16_t> test = {1,2,0,0,5};
    exemple.set_binaryData(test);
    exemple.set_nbSample(5);
    exemple.detecLogicData();
    std::vector<bool> detec = exemple.get_logicData();

    for (int i=0; i<5; i++) {
        std::cout << detec[i] << std::endl;
    }
}



bool test::detecDurations() {

    audio exemple;
    std::vector<int16_t> test = {1,2,0,0,5};
    exemple.set_binaryData(test);
    exemple.set_nbSample(5);
    exemple.detecLogicData();
    exemple.detecDurations();

    int dashPulse = exemple.get_dashDuration()*exemple.get_freqEch()/1000;
    int intraLetterPulse = exemple.get_intraLetterDuration()*exemple.get_freqEch()/1000;

    bool valid = true;
    if (dashPulse != 2){
        valid = false;
    }
    if (intraLetterPulse != 2){
        valid = false;
    }
    return valid;
}



void test::analyseLogicData() {

    audio exemple;
    exemple.set_filePath("../wave_exemples/sos.wav");
    exemple.preExtract();
    exemple.extract();
    exemple.lissage();
    exemple.detecLogicData();
    exemple.detecDurations();
    std::cout << exemple.analyseLogicData() << std::endl;
}