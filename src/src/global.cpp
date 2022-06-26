
#include "global.h"
#include "font5x7.h"

namespace global
{
    //Game *game;
    Input *input;
    TextPrinter *tp;
    OutputStringStream *ostr;
    bool flying;
    int8_t location;

    void SetupGlobals()
    {
        //game=new Game();
        input=new Input();
        tp=new TextPrinter();
        ostr=new OutputStringStream();

        tp->SetCustomFont(&Font5x7::Instance());

        flying=false;
        location=0;
    }
}
