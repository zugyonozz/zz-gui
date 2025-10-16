#pragma once

#include "eventdata.hpp"

namespace zz {

	inline bool PollEvent(Event& e) noexcept ;

	class Event {
		friend inline bool PollEvent(Event& e) noexcept ;
		using EventData = std::variant<WindowEventData, MouseEventData, KeyEventData> ;

	private :
		EventType type_ = EventType::None ;
		HWND handle_ = nullptr ;
		EventData data_ {} ;

		Event(HWND handle, const WindowEventData& data) noexcept : type_(EventType::Window), handle_(handle), data_(data) {}
		Event(HWND handle, const MouseEventData& data) noexcept : type_(EventType::Mouse), handle_(handle), data_(data) {}
		Event(HWND handle, const KeyEventData& data) noexcept : type_(EventType::Key), handle_(handle), data_(data) {}

		static Event CreateEventFromMSG(const MSG& msg) noexcept {
		switch (msg.message) {
			case WM_SIZE :
				return Event{msg.hwnd, WindowEventData{WindowEvent::Resize, Size{LOWORD(msg.lParam), HIWORD(msg.lParam)}}} ;
			case WM_CLOSE :
				return Event{msg.hwnd, WindowEventData{WindowEvent::Close, Size{LOWORD(msg.lParam), HIWORD(msg.lParam)}}} ;
			case WM_LBUTTONDOWN :
				return Event{msg.hwnd, MouseEventData{MouseEvent::Down, MouseButton::Left, Point{GET_X_LPARAM(msg.lParam), GET_Y_LPARAM(msg.lParam)}}} ;
			case WM_RBUTTONDOWN :
				return Event{msg.hwnd, MouseEventData{MouseEvent::Down, MouseButton::Right, Point{GET_X_LPARAM(msg.lParam), GET_Y_LPARAM(msg.lParam)}}} ;
			case WM_MBUTTONDOWN :
				return Event{msg.hwnd, MouseEventData{MouseEvent::Down, MouseButton::Middle, Point{GET_X_LPARAM(msg.lParam), GET_Y_LPARAM(msg.lParam)}}} ;
			case WM_LBUTTONUP :
				return Event{msg.hwnd, MouseEventData{MouseEvent::Up, MouseButton::Left, Point{GET_X_LPARAM(msg.lParam), GET_Y_LPARAM(msg.lParam)}}} ;
			case WM_RBUTTONUP :
				return Event{msg.hwnd, MouseEventData{MouseEvent::Up, MouseButton::Right, Point{GET_X_LPARAM(msg.lParam), GET_Y_LPARAM(msg.lParam)}}} ;
			case WM_MBUTTONUP :
				return Event{msg.hwnd, MouseEventData{MouseEvent::Up, MouseButton::Middle, Point{GET_X_LPARAM(msg.lParam), GET_Y_LPARAM(msg.lParam)}}} ;
			case WM_MOUSEHWHEEL :
				return Event{msg.hwnd, MouseEventData{static_cast<float>(GET_WHEEL_DELTA_WPARAM(msg.wParam))}} ;
			case WM_MOUSEMOVE : 
				return Event{msg.hwnd, MouseEventData{MouseEvent::Move, MouseButton::None, Point{GET_X_LPARAM(msg.lParam), GET_Y_LPARAM(msg.lParam)}}} ;
			case WM_LBUTTONDBLCLK : 
				return Event{msg.hwnd, MouseEventData{MouseEvent::DoubleClick, MouseButton::Left, Point{GET_X_LPARAM(msg.lParam), GET_Y_LPARAM(msg.lParam)}}} ;
			case WM_RBUTTONDBLCLK : 
				return Event{msg.hwnd, MouseEventData{MouseEvent::DoubleClick, MouseButton::Right, Point{GET_X_LPARAM(msg.lParam), GET_Y_LPARAM(msg.lParam)}}} ;
			case WM_MBUTTONDBLCLK : 
				return Event{msg.hwnd, MouseEventData{MouseEvent::DoubleClick, MouseButton::Middle, Point{GET_X_LPARAM(msg.lParam), GET_Y_LPARAM(msg.lParam)}}} ;
			case WM_MOUSEHOVER :
				return Event{msg.hwnd, MouseEventData{MouseEvent::Hover, MouseButton::None, Point{GET_X_LPARAM(msg.lParam), GET_Y_LPARAM(msg.lParam)}}} ;
			case WM_KEYDOWN :
				return Event{msg.hwnd, KeyEventData{KeyEvent::Down, static_cast<KeyCode>(msg.wParam)}} ;
			case WM_KEYUP :
				return Event{msg.hwnd, KeyEventData{KeyEvent::Up, static_cast<KeyCode>(msg.wParam)}} ;
			}

			return Event{} ;
		}

	public :
		Event() noexcept = default ;
		Event(const Event&) noexcept = default ;
		Event(Event&&) noexcept = default ;
		Event& operator=(const Event&) noexcept = default ;
		Event& operator=(Event&&) noexcept = default ;

		EventType GetType() const noexcept { return type_ ; }
		HWND GetHandle() const noexcept { return handle_ ; }

		template<typename T>
		const T* GetData() const noexcept {
			return std::get_if<T>(&data_) ;
		}

		const WindowEventData* GetWindowEventData() const noexcept {
			return std::get_if<WindowEventData>(&data_) ;
		}

		const MouseEventData* GetMouseEventData() const noexcept {
			return std::get_if<MouseEventData>(&data_) ;
		}

		const KeyEventData* GetKeyEventData() const noexcept {
			return std::get_if<KeyEventData>(&data_) ;
		}

		bool IsWindowEvent() const noexcept { return type_ == EventType::Window ; }
		bool IsKeyEvent() const noexcept { return type_ == EventType::Key ; }
		bool IsMouseEvent() const noexcept { return type_ == EventType::Mouse ; }
	} ;
}