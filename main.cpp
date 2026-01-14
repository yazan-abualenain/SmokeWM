#include <iostream>
#include <LCompositor.h>
#include <LSeat.h>
#include <LKeyboard.h>
#include <LOutput.h>


#include <linux/input-event-codes.h> 
#include <cstdlib>
#include <string>
#include <array>

#include "main.h"

#define KP( x ) keyboard->isKeyCodePressed( x )

using namespace Louvre;




int main() {
    std::cout << "Starting SmokeWM..." << std::endl;

    LCompositor* compositor = new LCompositor();


    
    if (!compositor->start()) {
        std::cerr << "Failed to start." << std::endl;
        delete compositor;
        return 1;
    }
    std::cout << "Compositor started successfully." << std::endl;
    LSeat* seat = compositor->seat();
    LKeyboard* keyboard = seat->keyboard();
    
    auto outputList=setupOutputs(compositor);


    while (compositor->state()==2) {
        compositor->processLoop(-1);
        if(KP( KEY_ESC )) {
            std::cout << "ESC pressed, exiting..." << std::endl;
            break;
        }

        for (const auto& output : outputList) {
            output->paintGL();
        }
        for (const auto& client : compositor->clients()) {
            std::cout << "Client: " << client << std::endl;
        }
    }

    compositor->finish();
    
    std::cout << "Compositor finished cleanly." << std::endl;
    delete compositor;

    _Exit(0);
}

