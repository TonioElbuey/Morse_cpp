#pragma once
#include <iostream>
#include <string>   
#include <map>

class msg {

public:

    msg();

    void set_msg_morse(std::string code);

    void set_msg_fr(std::string phrase);

    void frToMorse();

    void morseToFr();

    std::string get_msg_morse();

    std::string get_msg_fr();

private:

    std::string msg_morse = "";
    std::string msg_fr = "";
    std::map<char, std::string> tabFrToMorse;
    std::map<std::string, char> tabMorseToFr;   
};