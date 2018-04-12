#include "states\TestState.h"
using namespace std;

int main(int argc, char *argv[])
{
	Application *app = new Application();
	SetState<TestState>(app);
	while (app->Run());
	delete app;
	return 0;
}