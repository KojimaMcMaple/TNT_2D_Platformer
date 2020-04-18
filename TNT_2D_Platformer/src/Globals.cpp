#include "Globals.h"

int Globals::sFps = 60;
int Globals::sDelayTime = 1000.0f / sFps;
int Globals::sViewWidth = 320;
int Globals::sViewHeight = 180;
int Globals::sWindowWidth = 1024;
int Globals::sWindowHeight = 768;
int Globals::sGuiScale = Globals::sWindowHeight / Globals::sViewHeight;
float Globals::sGravity = 2.0f;
//float Globals::sGravity = 0.0f;
float Globals::sJumpForce = 14.5f;