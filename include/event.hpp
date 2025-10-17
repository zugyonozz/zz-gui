#pragma once

#include "unit.hpp"

namespace zz {

	class Event {
	protected :
		EventType type_ = EventType::None ;
		HWND handle_ = nullptr ;

		Event(HWND handle, EventType type) noexcept : handle_(handle), type_(type) {}

	public :
		Event() noexcept = default ;
		Event(const Event&) noexcept = default ;
		Event(Event&&) noexcept = default ;
		Event& operator=(const Event&) noexcept = default ;
		Event& operator=(Event&&) noexcept = default ;
		virtual ~Event() noexcept = default ;

		EventType GetType() const noexcept { return type_ ; }
		HWND GetHandle() const noexcept { return handle_ ; }
		const Window* GetContext() const noexcept ;

		bool IsWindowEvent() const noexcept { return type_ == EventType::Window ; }
		bool IsKeyEvent() const noexcept { return type_ == EventType::Key ; }
		bool IsMouseEvent() const noexcept { return type_ == EventType::Mouse ; }
	} ;

	class WindowEvent : public Event, public Size<uint16_t> {
	private :
		WindowState state_ = WindowState::None ;

		template <Arithmetic type>
		WindowEvent(HWND handle, WindowState state, const Size<type> size) noexcept : Size(size), state_(state), Event(handle, EventType::Window) {}

	public :
		WindowEvent() noexcept = default ;
		WindowEvent(const WindowEvent&) noexcept = default ;
		WindowEvent& operator=(const WindowEvent&) noexcept = default ;
		WindowEvent(WindowEvent&&) noexcept = default ;
		WindowEvent& operator=(WindowEvent&&) noexcept = default ;

		WindowState GetState() const noexcept { return state_ ; }
		Size<uint16_t> GetValue() const noexcept { return this->GetSize() ; }
	} ;

	class MouseEvent : public Event, public  Size<uint16_t> {
	protected :
		MouseState type_ = MouseState::None ;
		MouseButton button_ = MouseButton::None ;

	public :
		virtual ~MouseEvent() noexcept = default ;
	} ;

	class MouseDelta : public MouseEvent {
	private :
		float value_ = 0.0f ;

		template <Arithmetic type>
		MouseDelta(type value) noexcept : value_(value) {}

	public :
		MouseDelta() noexcept = default ;
		MouseDelta(const MouseDelta&) noexcept = default ;
		MouseDelta& operator=(const MouseDelta&) noexcept = default ;
		MouseDelta(MouseDelta&&) noexcept = default ;
		MouseDelta& operator=(MouseDelta&&) noexcept = default ;

		float GetValue() const noexcept { return value_ ; }
	} ;

	class MousePos : public MouseEvent, public Point<float> {
	private :
		template <Arithmetic type>
		MousePos(const Point<type>& value) noexcept : Point(value) {}

	public :
		MousePos() noexcept = default ;
		MousePos(const MousePos&) noexcept = default ;
		MousePos& operator=(const MousePos&) noexcept = default ;
		MousePos(MousePos&&) noexcept = default ;
		MousePos& operator=(MousePos&&) noexcept = default ;
		
		Point<float> GetValue() const noexcept { return this->GetPoint() ; }
	} ;

	class KeyEvent {
	private :
		KeyState type_ = KeyState::None ;
		KeyCode value_ = KeyCode::None ;

		KeyEvent(KeyState type, KeyCode value) noexcept : type_(type), value_(value) {}
	
	public :
		KeyEvent() noexcept = default ;
		KeyEvent(const KeyEvent&) noexcept = default ;
		KeyEvent& operator=(const KeyEvent&) noexcept = default ;
		KeyEvent(KeyEvent&&) noexcept = default ;
		KeyEvent& operator=(KeyEvent&&) noexcept = default ;

		KeyState GetEvent() const noexcept { return type_ ; }
		KeyCode GetValue() const noexcept { return value_ ; }
	} ;

	template <typename> struct is_event_type : std::false_type {} ;
	template <> struct is_event_type<WindowEvent> : std::true_type {} ;
	template <> struct is_event_type<MouseEvent> : std::true_type {} ;
	template <> struct is_event_type<KeyEvent> : std::true_type {} ;
	
	template <typename T>
	concept EventType_t = is_event_type<T>::value ;
}