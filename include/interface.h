#pragma once
#include "msg.h"
#include "audio.h"
#include <iostream>
#include <string>

class interface {

public:

    void init();

    void frProc();

public:

    bool sens = 0;
    bool lectureFr = 0;
    std::string texte;
};