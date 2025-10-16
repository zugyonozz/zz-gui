#include "window.hpp"
using namespace zz ;


int main() {
	Application::RegisterWindowClass() ;

	Window window("Window demo", Size{600, 400}) ;
	try {
		window.SetShowMode(WindowShowMode::Show) ;
	} catch (const Ex::window& e) {
		std::cerr << e.what() ;
	}

	while (Application::IsRunning()) {
		
	}
}