#pragma once

#include "input.h"
#include "textprinter.h"
#include "outputstringstream.h"

namespace global
{
    //extern Game *game;
    extern Input *input;
    extern TextPrinter *tp;
    extern OutputStringStream *ostr;

    extern bool flying;
    extern int8_t location;

    void SetupGlobals();
}
