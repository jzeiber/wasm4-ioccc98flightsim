#pragma once

#include "input.h"

/*
Adapted to WASM-4 from deobfuscated version
https://github.com/Hadlock/c_banks_flightsim
*/

#define dt 1./60.   // delta time in sec every frame - WASM-4 targets 60 fps

void bankssetup(int8_t location);
void banksupdate(Input *input);
