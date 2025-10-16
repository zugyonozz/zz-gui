#pragma once

#include "unit.hpp"

namespace zz {

	class Event ;
	
	class WindowEventData {
		friend class Event ;

	private :
		WindowEvent type_ = WindowEvent::None ;
		Size<uint32_t> size_ = {} ;

	public :
		WindowEventData() noexcept = default ;
		WindowEventData(const WindowEventData&) noexcept = default ;
		WindowEventData& operator=(const WindowEventData&) noexcept = default ;
		WindowEventData(WindowEventData&&) noexcept = default ;
		WindowEventData& operator=(WindowEventData&&) noexcept = default ;
		WindowEventData(WindowEvent type) noexcept : type_(type) {}
		WindowEventData(WindowEvent type, const Size<uint16_t> size) noexcept : type_(type), size_(size) {}

		WindowEvent GetEvent() const noexcept { return type_ ; }
		Size<int> GetSize() const noexcept { return size_ ; }
	} ;

	class MouseEventData {
		friend class Event ;

	private :
		MouseEvent type_ = MouseEvent::None ;
		MouseButton button_ = MouseButton::None ;
		std::variant<Point<uint16_t>, uint16_t> data_ {} ;

	public :
		MouseEventData() noexcept = default ;
		MouseEventData(const MouseEventData&) noexcept = default ;
		MouseEventData& operator=(const MouseEventData&) noexcept = default ;
		MouseEventData(MouseEventData&&) noexcept = default ;
		MouseEventData& operator=(MouseEventData&&) noexcept = default ;
		MouseEventData(float value) noexcept : type_(MouseEvent::Wheel), data_(value) {} 

		MouseEventData(MouseEvent type, MouseButton button, const Point<uint16_t>& position) {
			if (type == MouseEvent::Wheel) {
				throw Ex::mouse_event_data("MouseEventData", "Mismatch event data with value") ;
			} else {
				type_ = type ;
				button_ = button ;
				data_ = position ;
			}
		}

		MouseEvent GetEvent() const noexcept { return type_ ; }
		MouseButton GetButton() const noexcept { return button_ ; }
		float GetValue() const noexcept { return type_ == MouseEvent::Wheel ? std::get<uint16_t>(data_) : 0.0f ; }
		Point<uint16_t> GetPosition() const noexcept { return type_ != MouseEvent::Wheel ? std::get<Point<uint16_t>>(data_) : Point<uint16_t>{0, 0} ; }
	} ;

	class KeyEventData {
		friend class Event ;

	private :
		KeyEvent type_ = KeyEvent::None ;
		KeyCode value_ = KeyCode::None ;
	
	public :
		KeyEventData() noexcept = default ;
		KeyEventData(const KeyEventData&) noexcept = default ;
		KeyEventData& operator=(const KeyEventData&) noexcept = default ;
		KeyEventData(KeyEventData&&) noexcept = default ;
		KeyEventData& operator=(KeyEventData&&) noexcept = default ;
		KeyEventData(KeyEvent type, KeyCode value) noexcept : type_(type), value_(value) {}

		KeyEvent GetEvent() const noexcept { return type_ ; }
		KeyCode GetValue() const noexcept { return value_ ; }
	} ;
}