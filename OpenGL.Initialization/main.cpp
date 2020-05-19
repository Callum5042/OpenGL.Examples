#include "Application.h"
#include <memory>

int main(int argc, char** argv)
{
	std::unique_ptr<Engine> app(new GL::Application());
	app->Execute(argc, argv);
}