#pragma once
#include "msg.h"
#include "audio.h"
#include <iostream>
#include <string>

class interface {

public:

    void init();

    void frInput();

    void morseInput();

    std::string get_texte();

    std::string get_filePathFr();

    std::string get_filePathMr();

    bool get_sens();

private:

    bool sens = 0;
    bool lectureFr = 0;
    std::string texte;
    std::string fileName;
    std::string filePathFr = "../fichiers_textes/";
    std::string filePathMr = "../wave_exemples/";
};