#include <protocols/ScreenCopy/GScreenCopyManager.h>
#include <linux/input-event-codes.h> 

#include <iostream>
#include <cstdlib>
#include <string>
#include <array>
#include <memory>


#include <LCompositor.h>
#include <LSeat.h>
#include <LKeyboard.h>
#include <LScene.h>
#include <LLauncher.h>
#include <LTimer.h>
#include <LGlobal.h>
#include <LClient.h>

#include "Scene/Scene.h"
#include "Scene/LayerView.h"

#include "utils/Systemd.h"
#include "utils/Assets.h"

using namespace Louvre;

class Assets;


class Compositor : public LCompositor{
public:
    Scene scene;
    /*
    std::unique_ptr<Assets> assets;
    std::unique_ptr<Systemd> systemd;
    */

protected:

    /* Triggered after calling start() from main.cpp */
    void initialized() override;

    /* Triggered after calling finish(), see Keyboard */
    void uninitialized() override;

    /* Object factory, used to override Louvre default classes */
    LFactoryObject *createObjectRequest(LFactoryObject::Type objectType, const void *params) override;
    void onAnticipatedObjectDestruction(LFactoryObject *object) override;

    /* If you want to add/remove protocol globals */
    bool createGlobalsRequest() override;

    /* Controls which client can bind to which global */
    bool globalsFilter(LClient *client, LGlobal *global) override;

};



