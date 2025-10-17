#pragma once

#include "application.hpp"

namespace utility {
	bool CheckFlag(zz::WindowFlag src, zz::WindowFlag flag) noexcept {
		return static_cast<bool>(src & flag) ;
	}

	void ActivateFlag(zz::WindowFlag& src, zz::WindowFlag flag) noexcept {
		src |= flag ;
	} ;

	void DeactivateFlag(zz::WindowFlag& src, zz::WindowFlag flag) noexcept {
		src &= ~flag ;
	}
}

namespace zz {

	class Window : public Application {
	private :
		HWND handle_ {} ;
		WindowFlag state_ = WindowFlag::None ;

		template <Arithmetic type1, Arithmetic type2>
		void create_window(const char* title, const Point<type2>& pos, const Size<type1>& size, WindowStyle style) {
			handle_ = CreateWindowEx(
				0,
				g_class_name_.c_str(),
				title,
				static_cast<uint32_t>(style),
				pos.x,
				pos.y,
				size.w,
				size.h,
				nullptr,
				nullptr,
				g_hinstance_,
				nullptr
			) ;

			if (!handle_) {
				throw Ex::window("create_window", "Failed to create window!") ;
			} else {
				utility::ActivateFlag(state_, WindowFlag::Registered) ;
			}
		}

	public :
		Window() noexcept = default ;
		Window(const Window&) = delete ;
		Window& operator=(const Window&) = delete ;

		Window(const char* title, uint16_t w, uint16_t h, WindowStyle style = WindowStyle::Basic) {
			try {
				create_window(title, Point{CW_USEDEFAULT}, Size{w, h}, style) ;
			} catch (const Ex::window& e) {
				std::cerr << e.what() << '\n' ;
			} catch (...) {
				std::cerr << "Window::Window - Unhandled error!\n" ;
			}
		}

		template <Arithmetic type>
		Window(const char* title, const Size<type>& size, WindowStyle style = WindowStyle::Basic) {
			try {
				create_window(title, Point{CW_USEDEFAULT}, size, style) ;
			} catch (const Ex::window& e) {
				std::cerr << e.what() << '\n' ;
			} catch (...) {
				std::cerr << "Window::Window - Unhandled error!\n" ;
			}
		}

		Window(const char* title, uint16_t x, uint16_t y, uint16_t w, uint16_t h, WindowStyle style = WindowStyle::Basic) {
			try {
				create_window(title, Point{x, y}, Size{w, h}, style) ;
			} catch (const Ex::window& e) {
				std::cerr << e.what() << '\n' ;
			} catch (...) {
				std::cerr << "Window::Window - Unhandled error!\n" ;
			}
		}

		template <Arithmetic type>
		Window(const char* title, const Point<type>& pos, const Size<type>& size, WindowStyle style = WindowStyle::Basic) {
			try {
				create_window(title, pos, size, style) ;
			} catch (const Ex::window& e) {
				std::cerr << e.what() << '\n' ;
			} catch (...) {
				std::cerr << "Window::Window - Unhandled error!\n" ;
			}
		}

		template <Arithmetic type>
		Window(const char* title, const Rect<type>& rect, WindowStyle style = WindowStyle::Basic) {
			try {
				create_window(title, rect.GetPoint(), rect.GetSize(), style) ;
			} catch (const Ex::window& e) {
				std::cerr << e.what() << '\n' ;
			} catch (...) {
				std::cerr << "Window::Window - Unhandled error!\n" ;
			}
		}

		template <Arithmetic type>
		Window(Window&& o) noexcept {
			handle_ = std::exchange(o.handle_, nullptr) ;
			state_ = std::exchange(o.state_, WindowFlag::None) ;
			if (handle_) {
				UnregisterWindow(handle_) ;
				RegisterWindow(handle_, this) ;
			}
		}

		~Window() noexcept {}

		Window& operator=(Window&& o) noexcept {
			if (this != &o) {
				handle_ = std::exchange(o.handle_, nullptr) ;
				state_ = std::exchange(o.state_, WindowFlag::None) ;
				if (handle_) {
					UnregisterWindow(handle_) ;
					RegisterWindow(handle_, this) ;
				}
			}

			return *this ;
		}

		void SetShowMode(WindowShowMode mode) const {
			if (handle_) {
				ShowWindow(handle_, static_cast<uint8_t>(mode)) ;
				if (mode == WindowShowMode::Show && !UpdateWindow(handle_)) {
					throw Ex::window("Show", "Failed to update window.") ;
				}
			}
		}

		void Close() noexcept {
			if (utility::CheckFlag(state_, WindowFlag::Registered)) {
				UnregisterWindow(handle_) ;
				utility::DeactivateFlag(state_, WindowFlag::Registered) ;
				DestroyWindow(handle_) ;
				// sepertinya cukup bikin registered saja tidak perlu close, karena di dalam proses pembuatan window itu sendiri udah satu alur proses dengan register window
				// ntah lah aku pikir nanti
				utility::ActivateFlag(state_, WindowFlag::Closed) ; 
				utility::ActivateFlag(state_, WindowFlag::Destroyed) ; 
			}
		}

		void SetTitle(const char* NewTitle) noexcept {
			if (handle_) {
				SetWindowText(handle_, NewTitle) ;
			}
		}

		Rect<int> GetClientBound() const noexcept {
			tagRECT r ;
			GetClientRect(handle_, &r) ;
			return r ;
		}

		Rect<int> GetWindowBound() const noexcept {
			tagRECT r ;
			GetWindowRect(handle_, &r) ;
			return r ;
		}

		bool IsWindowValid() const noexcept { 
			return handle_ && !utility::CheckFlag(state_, WindowFlag::Destroyed); 
		}
	} ;

	inline LRESULT CALLBACK WindowProcedure(HWND handle, uint32_t message, uint64_t wparam, int64_t lparam) noexcept {
		switch (message) {
			case WM_SIZE :
				Application::PushEvent(Event{handle, WindowEventData{WindowEvent::Resize, Size{LOWORD(lparam), HIWORD(lparam)}}}) ;
				break ; 
			case WM_CLOSE :
				Application::PushEvent(Event{handle, WindowEventData{WindowEvent::Close, Size{LOWORD(lparam), HIWORD(lparam)}}}) ;
				return 0 ;

			case WM_DESTROY :
				if (Application::g_windows_.empty()) {
					Application::g_is_running_ = false ;
					PostQuitMessage(0) ;
				}
				return 0 ;
		}

		return DefWindowProc(handle, message, wparam, lparam) ;
	}
}