#include <protocols/ScreenCopy/GScreenCopyManager.h>
#include <linux/input-event-codes.h> 

#include <iostream>
#include <cstdlib>
#include <string>
#include <array>

#include <LCompositor.h>
#include <LSeat.h>
#include <LKeyboard.h>
#include <LScene.h>
#include <LLauncher.h>
#include <LTimer.h>
#include <LGlobal.h>
#include <LClient.h>


#include "compositor.h"
#include "Output.h"
#include "utils/Systemd.h"
#include "utils/Assets.h"
#include "Scene/Scene.h"
#include "Scene/LayerView.h"




#define KP( x ) keyboard->isKeyCodePressed( x )



using namespace Louvre;


void setupENV(){
    setenv("LOUVRE_DEBUG", "1", 0);
    setenv("SRM_DEBUG", "1", 0);
    setenv("MOZ_ENABLE_WAYLAND", "1", 1);
    setenv("GDK_BACKEND", "wayland", 1);
    setenv("LOUVRE_WAYLAND_DISPLAY", "wayland-2", 0);
}

int main() {

    setupENV();
    LLauncher::startDaemon();

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
    LScene* scene = new LScene();

    
    scene->enableAutoRepaint(true);


    LLauncher::launch("foot");
    LLauncher::launch("swww-daemon");
    
    while (compositor->state()==2) {
        compositor->processLoop(-1);
        if(KP( KEY_ESC )) {
                std::cout << "ESC pressed, exiting..." << std::endl;
                break;
            }
        if(KP( KEY_KPENTER )){
            LLauncher::launch("foot");
        }
        }
    
    compositor->finish();
    
    std::cout << "Compositor finished cleanly." << std::endl;

    delete compositor;
    _Exit(0);
}
