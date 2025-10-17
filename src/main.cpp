#include "window.hpp"
using namespace zz ;


int main() {
	Application::RegisterWindowClass() ;

	Window window("Window demo", Size{600, 400}, WindowStyle::OverlappedWindow) ;
	try {
		window.SetShowMode(WindowShowMode::Show) ;
	} catch (const Ex::window& e) {
		std::cerr << e.what() ;
	}

	Event e ;
	while (Application::IsRunning()) {
		try {
			while (PollEvent(e)) {
				if (e.GetType() == EventType::Window) {
					auto e_ = e.GetWindowEventData() ;
					if (e_->GetEvent() == WindowEvent::Close) {
						window.Close() ;
						Application::QuitProgram() ;
						break ;
					}
				}
			}
			Point<int> pos {1} ;
			pos /= Point{0} ;
			Sleep(16) ;
		} catch (const Ex::error_logic e) {
			std::cerr << e.what() << '\n' ;
		} catch (...) {
			std::cerr << "unhandle error\n" ;
		}
	}
}