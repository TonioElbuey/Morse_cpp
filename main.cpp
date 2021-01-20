#include <iostream>
#include "include/audio.h"
#include "include/test.h"
#include "include/interface.h"
using namespace std;

int main() {

    interface dialog;
    audio wavFile;
    msg message;

    dialog.init(); //   Choix du traitement et récupération entrées
    bool sens = dialog.get_sens();

    if (sens) { //  Encodage

        message.set_msg_fr( dialog.get_texte() );
        message.frToMorse();
        wavFile.createWave();
        wavFile.createLogicData( message.get_msg_morse() );
        wavFile.createBinary();
        wavFile.fillWave();
        wavFile.finalWave();
    }
    else { //   Décodage
        wavFile.set_filePath( dialog.get_filePathMr() );
        wavFile.preExtract();
        wavFile.extract();
        wavFile.lissage();
        wavFile.detecLogicData();
        wavFile.detecDurations();
        wavFile.analyseLogicData();
        message.set_msg_morse( wavFile.analyseLogicData() );
        message.morseToFr();

        std::cout << std::endl;
        std::cout << "Message décodé : ";
        std::cout << message.get_msg_fr() << std::endl;
    }
}