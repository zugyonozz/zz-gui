#pragma once

#include "event.hpp"

namespace zz {

	inline bool PollEvent(Event& e) noexcept ;
	inline LRESULT CALLBACK WindowProcedure(HWND, uint32_t, uint64_t, int64_t) noexcept ;

	class EventSys {
		friend inline bool PollEvent(Event& e) noexcept ;
		friend inline LRESULT CALLBACK WindowProcedure(HWND, uint32_t, uint64_t, int64_t) noexcept ;
	private :
		static inline std::queue<std::unique_ptr<Event>> g_events_ {} ;

		static Event CreateEventFromMSG(const MSG& msg) noexcept {
			switch (msg.message) {
				case WM_LBUTTONDOWN :
					PushEvent<MouseEvent>(msg.hwnd, MouseEvent{MouseState::Down, MouseButton::Left, Point{GET_X_LPARAM(msg.lParam), GET_Y_LPARAM(msg.lParam)}}) ;
					break ;
				case WM_RBUTTONDOWN :
					return Event{msg.hwnd, MouseEvent{MouseEvent::Down, MouseButton::Right, Point{GET_X_LPARAM(msg.lParam), GET_Y_LPARAM(msg.lParam)}}} ;
				case WM_MBUTTONDOWN :
					return Event{msg.hwnd, MouseEvent{MouseEvent::Down, MouseButton::Middle, Point{GET_X_LPARAM(msg.lParam), GET_Y_LPARAM(msg.lParam)}}} ;
				case WM_LBUTTONUP :
					return Event{msg.hwnd, MouseEvent{MouseEvent::Up, MouseButton::Left, Point{GET_X_LPARAM(msg.lParam), GET_Y_LPARAM(msg.lParam)}}} ;
				case WM_RBUTTONUP :
					return Event{msg.hwnd, MouseEvent{MouseEvent::Up, MouseButton::Right, Point{GET_X_LPARAM(msg.lParam), GET_Y_LPARAM(msg.lParam)}}} ;
				case WM_MBUTTONUP :
					return Event{msg.hwnd, MouseEvent{MouseEvent::Up, MouseButton::Middle, Point{GET_X_LPARAM(msg.lParam), GET_Y_LPARAM(msg.lParam)}}} ;
				case WM_MOUSEHWHEEL :
					return Event{msg.hwnd, MouseEvent{static_cast<float>(GET_WHEEL_DELTA_WPARAM(msg.wParam))}} ;
				case WM_MOUSEMOVE : 
					return Event{msg.hwnd, MouseEvent{MouseEvent::Move, MouseButton::None, Point{GET_X_LPARAM(msg.lParam), GET_Y_LPARAM(msg.lParam)}}} ;
				case WM_LBUTTONDBLCLK : 
					return Event{msg.hwnd, MouseEvent{MouseEvent::DoubleClick, MouseButton::Left, Point{GET_X_LPARAM(msg.lParam), GET_Y_LPARAM(msg.lParam)}}} ;
				case WM_RBUTTONDBLCLK : 
					return Event{msg.hwnd, MouseEvent{MouseEvent::DoubleClick, MouseButton::Right, Point{GET_X_LPARAM(msg.lParam), GET_Y_LPARAM(msg.lParam)}}} ;
				case WM_MBUTTONDBLCLK : 
					return Event{msg.hwnd, MouseEvent{MouseEvent::DoubleClick, MouseButton::Middle, Point{GET_X_LPARAM(msg.lParam), GET_Y_LPARAM(msg.lParam)}}} ;
				case WM_MOUSEHOVER :
					return Event{msg.hwnd, MouseEvent{MouseEvent::Hover, MouseButton::None, Point{GET_X_LPARAM(msg.lParam), GET_Y_LPARAM(msg.lParam)}}} ;
				case WM_KEYDOWN :
					return Event{msg.hwnd, KeyEvent{KeyEvent::Down, static_cast<KeyCode>(msg.wParam)}} ;
				case WM_KEYUP :
					return Event{msg.hwnd, KeyEvent{KeyEvent::Up, static_cast<KeyCode>(msg.wParam)}} ;
			}

			return Event{} ;
		}

	public :
		template <EventType_t event, typename ... Args>
		static void PushEvent(Args&& ... args) noexcept {
			if (std::is_same_v<event, MouseEvent>) {
				g_events_.emplace(std::make_unique<event>(std::make_unique<MouseEvent>(std::forward<Args>(args)...))) ;
			} else {
				g_events_.emplace(std::make_unique<event>(std::forward<Args>(args)...)) ;
			}
		}

		static bool PollEvent(Event& event) noexcept {
			if (g_events_.empty()) {
				return false ;
			}

			event = *g_events_.front().release() ;
			g_events_.pop() ;
			return true ;
		}

		static bool PeekEvent(Event& event) noexcept {
			if (g_events_.empty()) {
				return false ;
			}

			event = *g_events_.front() ;
			return true ;			
		}

		static void ClearEvent() noexcept {
			while (!g_events_.empty()) {
				g_events_.pop() ;
			}
		}
	} ;

	inline bool PollEvent(Event& event) noexcept {
		if (EventSys::PollEvent(event)) {
			return true ;
		}

		MSG msg{} ;
		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
			std::make_unique<Event> event = EventSys::CreateEventFromMSG(msg) ;

			if (event.GetType() != EventType::None) {
				EventSys::PushEvent(event) ;
			}

			TranslateMessage(&msg) ;
			DispatchMessage(&msg) ;
		}

		return EventSys::PollEvent(event) ;
	}

}