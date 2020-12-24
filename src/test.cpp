#include "../include/test.h"



bool test::audio_preExtract(){

    audio exemple;
    exemple.define_filePath("../Exemple_morse.wav");
    exemple.preExtract();

    bool valid = true;
    if (exemple.get_nbBit() != 8){
        valid = false;
    }
    if (exemple.get_tailleData() != 198380){
        valid = false;
    }

    return valid;
}