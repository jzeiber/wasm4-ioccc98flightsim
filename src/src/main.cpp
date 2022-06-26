#include "wasm4.h"
#include "global.h"
#include "banks.h"
#include "palette.h"

void start()
{
    PALETTE[0]=0x000000;
    PALETTE[1]=0x5183C1;
    PALETTE[2]=0x35A54D;
    PALETTE[3]=0xffffff;

    global::SetupGlobals();
}

void chooselocation(Input *input)
{
    char locnames[4][16]={"Pittsburgh","Pyramids","River","Obstacle Course"};
    if(input->GamepadButtonPress(1,BUTTON_DOWN)==true)
    {
        if(global::location<3)
        {
            global::location++;
        }
    }
    else if(input->GamepadButtonPress(1,BUTTON_UP)==true)
    {
        if(global::location>0)
        {
            global::location--;
        }
    }
    if(input->GamepadButtonPress(1,BUTTON_1)==true)
    {
        bankssetup(global::location);
        global::flying=true;
        input->DetectChangeState(1);
    }

    global::tp->PrintCentered("Where are you flying?",SCREEN_SIZE/2,20,21,PALETTE_BLUE);
    for(int i=0; i<4; i++)
    {
        int16_t col=PALETTE_WHITE;
        if(i==global::location)
        {
            col=PALETTE_GREEN;
        }
        global::tp->Print(locnames[i],30,50+(i*16),20,col);
    }

}

void update()
{
    global::input->Update();
    
    if(global::flying==false)
    {
        chooselocation(global::input);
    }
    else
    {
        banksupdate(global::input);
    }
}
