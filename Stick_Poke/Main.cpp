#include "Engine.h"

int main()
{
	Engine* engine = new Engine();

	try
	{
		engine->Go();
	}
	catch (char* e)
	{
		//oops
	}

	return 0;
}