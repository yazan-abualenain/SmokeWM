#include <iostream>
#include <LCompositor.h>
#include <LSeat.h>
#include <LKeyboard.h>
#include <LOutput.h>


#include <linux/input-event-codes.h> 
#include <cstdlib>
#include <string>
#include <array>

#define KP( x ) keyboard->isKeyCodePressed( x )

using namespace Louvre;
