
#include <SDL.h>
#include "Application.h"
#include <memory>

int main(int argc, char** argv)
{
	std::unique_ptr<Engine> app(new GL::Application());
	return app->Execute(argc, argv);
}