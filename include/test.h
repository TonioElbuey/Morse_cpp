#pragma once
#include "../include/msg.h"

class test { //   Calsse pour vérifier chacune des méthodes de chaque classe

public:

    bool frToMorse();

    bool morseToFr();

    bool preExtract();

    void extract();

    bool createWave();

    void fillWave_testSinus();

    bool lissage();

    void detecLogicData();

    bool detecDurations();
};