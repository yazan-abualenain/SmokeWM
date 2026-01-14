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

auto setupOutputs(LCompositor* &compositor) {
    std::vector<LOutput*> outputList;
    for (const auto& output : compositor->outputs()) {
        std::cout << "Output: " << output << std::endl;
        compositor->addOutput(output);
        output->initializeGL();
        outputList.push_back(output);
    }
    return outputList;
}
void LOutput::initializeGL()
{
    painter()->setClearColor(1.f, 1.f, 1.f, 1.f);
}