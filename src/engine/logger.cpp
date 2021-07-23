#define STB_IMAGE_IMPLEMENTATION

#include "./logger.h"

using namespace std;

void consoleLog(string text)
{
	printf("%s \n", text.c_str());
}

void consoleLog(int text)
{
	consoleLog(to_string(text));
}

void consoleLog(double text)
{
	consoleLog(to_string(text));
}

void consoleLog(float text)
{
	consoleLog(to_string(text));
}