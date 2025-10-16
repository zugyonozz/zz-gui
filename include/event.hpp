#pragma once

#include "eventdata.hpp"

namespace zz {

	class Event {
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
				return Event{msg.hwnd, {WindowEvent::Resize, {LOWORD(msg.lParam), HIWORD(msg.lParam)}}} ;
			case WM_CLOSE :
				return Event{msg.hwnd, {WindowEvent::Close, {LOWORD(msg.lParam), HIWORD(msg.lParam)}}} ;
			case WM_LBUTTONDOWN :
				return Event{msg.hwnd, {MouseEvent::Down, MouseButton::Left, {GET_X_LPARAM(msg.lParam), GET_Y_LPARAM(msg.lParam)}}} ;
			case WM_RBUTTONDOWN :
				return Event{msg.hwnd, {MouseEvent::Down, MouseButton::Right, {GET_X_LPARAM(msg.lParam), GET_Y_LPARAM(msg.lParam)}}} ;
			case WM_MBUTTONDOWN :
				return Event{msg.hwnd, {MouseEvent::Down, MouseButton::Middle, {GET_X_LPARAM(msg.lParam), GET_Y_LPARAM(msg.lParam)}}} ;
			case WM_LBUTTONUP :
				return Event{msg.hwnd, {MouseEvent::Up, MouseButton::Left, {GET_X_LPARAM(msg.lParam), GET_Y_LPARAM(msg.lParam)}}} ;
			case WM_RBUTTONUP :
				return Event{msg.hwnd, {MouseEvent::Up, MouseButton::Right, {GET_X_LPARAM(msg.lParam), GET_Y_LPARAM(msg.lParam)}}} ;
			case WM_MBUTTONUP :
				return Event{msg.hwnd, {MouseEvent::Up, MouseButton::Middle, {GET_X_LPARAM(msg.lParam), GET_Y_LPARAM(msg.lParam)}}} ;
			case WM_MOUSEHWHEEL :
				return Event{msg.hwnd, {GET_WHEEL_DELTA_WPARAM(msg.wParam)}} ;
			case WM_MOUSEMOVE : 
				return Event{msg.hwnd, {MouseEvent::Move, MouseButton::None, {GET_X_LPARAM(msg.lParam), GET_Y_LPARAM(msg.lParam)}}} ;
			case WM_LBUTTONDBLCLK : 
				return Event{msg.hwnd, {MouseEvent::DoubleClick, MouseButton::Left, {GET_X_LPARAM(msg.lParam), GET_Y_LPARAM(msg.lParam)}}} ;
			case WM_RBUTTONDBLCLK : 
				return Event{msg.hwnd, {MouseEvent::DoubleClick, MouseButton::Right, {GET_X_LPARAM(msg.lParam), GET_Y_LPARAM(msg.lParam)}}} ;
			case WM_MBUTTONDBLCLK : 
				return Event{msg.hwnd, {MouseEvent::DoubleClick, MouseButton::Middle, {GET_X_LPARAM(msg.lParam), GET_Y_LPARAM(msg.lParam)}}} ;
			case WM_MOUSEHOVER :
				return Event{msg.hwnd, {MouseEvent::Hover, MouseButton::None, {GET_X_LPARAM(msg.lParam), GET_Y_LPARAM(msg.lParam)}}} ;
			case WM_KEYDOWN :
				return Event{msg.hwnd, {KeyEvent::Down, static_cast<KeyCode>(msg.wParam)}} ;
			case WM_KEYUP :
				return Event{msg.hwnd, {KeyEvent::Up, static_cast<KeyCode>(msg.wParam)}} ;
			}

			return Event{} ;
	}

	public :
		Event() noexcept = default ;
		Event(const Event&) noexcept = default ;
		Event(Event&&) noexcept = default ;
		Event& operator=(const Event&) noexcept = default ;
		Event& operator=(Event&&) noexcept = default ;
	} ;

}