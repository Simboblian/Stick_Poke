#include <Windows.h>
#include "Engine.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	Engine* engine = new Engine();

	AllocConsole();
	freopen("CONOUT$", "w", stdout);

	try
	{
		engine->Go();
	}
	catch(char* e)
	{
		MessageBoxA(NULL, e, "Exception Occurred", MB_OK | MB_ICONERROR);
	}

	return 0;
}