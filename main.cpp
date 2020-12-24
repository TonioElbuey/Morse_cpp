#include <iostream>
#include "include/audio.h"
#include "include/test.h"
using namespace std;

int main() {

    test T;
    bool valid = T.audio_preExtract();
    cout << valid << endl;
}