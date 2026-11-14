#include <iostream>

// Define color codes as constants
const std::string RESET   = "\033[0m";
const std::string RED     = "\033[31m";
const std::string GREEN   = "\033[32m";
const std::string YELLOW  = "\033[33m";
const std::string BLUE    = "\033[34m";
const std::string BOLDRED = "\033[1m\033[31m";

std::string TerminalColor(int colorvalue) {
    if (colorvalue == 0) {
        return RESET;
    }
    
    if (colorvalue == 1) {
        return RED;
    }

    if (colorvalue == 2) {
        return YELLOW;
    }
}