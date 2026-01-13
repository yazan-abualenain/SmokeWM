#include <iostream>
#include <LCompositor.h>



using namespace Louvre;




int main() {
    std::cout << "Starting SmokeWM..." << std::endl;

    LCompositor* compositor = new LCompositor();

    if (!compositor->start()) {
        std::cerr << "Failed to start." << std::endl;
        delete compositor;
        return 1;
    }



    while (compositor->state()==2) {
        std::string line;
        std::getline(std::cin, line);
        if (line == "exit") {
            break;
        }
    }



    compositor->finish();
    
    std::cout << "Compositor finished cleanly." << std::endl;
    delete compositor;

    _Exit(0);
}
