#include "core/SDLApplication.h"
#include <SDL.h>
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // Check Memory Leaks
#endif

	cout << argv[0];
	//cin.get();

	try {
		srand(time(0));
		SDLApplication::init();
		SDLApplication::instance()->run();
	} catch (const std::string& e) { // catch exceptions thrown as strings
		std::cerr << e << std::endl;
	} catch (const char* e) { // catch exceptions thrown as char*
		std::cerr << e << std::endl;
	} catch (const std::exception& e) { // catch exceptions thrown as a sub-type of std::exception
		std::cerr << e.what();
	} catch (...) {
		std::cerr << "Caught and exception of unknown type ...";
	}

	return 0;
}