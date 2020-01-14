#include "Engine.h"

// Main function.
int main(int argc, char* args[]) // Main MUST have these parameters for SDL.
{
	//Engine engine_obj;
	//return engine_obj.Run();

	return Engine::Instance().Run();
}