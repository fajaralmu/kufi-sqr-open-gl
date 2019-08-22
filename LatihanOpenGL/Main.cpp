#include "Application.h"

using namespace App;
int main() {
	
	Application * app;
	app =new Application();
	if(app->initApp())	app->run();
}