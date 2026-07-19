#pragma once
#include <SDL3/SDL.h>

#include <iostream>
#include <source_location>
#include <string>
#define ERROR_LOGGING


using namespace std;



void CheckSDLError(string actionName = "", const std::source_location& loc = std::source_location::current()) {
#ifdef ERROR_LOGGING
    if (SDL_GetError() == "") { // if there is no error found
        cout << "No error found at this interval," << loc.function_name() <<
                " from [" << loc.file_name() << 
                ", ln. " << loc.line() <<
                " | " << loc.column() << "]!";
    }
    
    else { // if there is an error found
        if (actionName == "") { // if there is no action name provided
            cout << 
                "Error in " << loc.function_name() <<
                " from [" << loc.file_name() << 
                ", ln. " << loc.line() <<
                " | " << loc.column() << 
                "]: " << SDL_GetError()
            ;
        }

        else { // if there is an action name provided
            cout << 
                "Error in " << loc.function_name() <<
                ", '" << actionName << 
                "' from [" << loc.file_name() << 
                ", ln. " << loc.line() <<
                " | " << loc.column() << 
                "]: " << SDL_GetError()
            ;
        }
    }

    cout << '\n';

#endif

    SDL_ClearError();
};