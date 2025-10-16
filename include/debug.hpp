#pragma once

#include <iostream>
#include "types.hpp"

namespace Ex {
	class application : public std::exception {
	protected :
		std::string msg_ {} ;

	public :
		explicit application(const std::string& msg) noexcept : msg_(msg) {}
		const char* what() const noexcept override { return msg_.c_str() ; }
	} ;

	class mouse_event_data : public application {
	public :
		explicit mouse_event_data(const std::string& msg) noexcept : application("MouseEventData - " + msg) {}
		explicit mouse_event_data(const std::string& label, const std::string& msg) noexcept : application("MouseEventData:: - " + label + " - " + msg) {}
		const char* what() const noexcept override { return msg_.c_str() ; }
	} ;

	class window : public application {
	public :
		explicit window(const std::string& msg) noexcept : application("Window - " + msg) {}
		explicit window(const std::string& label, const std::string& msg) noexcept : application("Window::" + label + " - "+ msg) {}
		const char* what() const noexcept override { return msg_.c_str() ; }
	} ;

	class error_logic : public application {
	public :
		explicit error_logic(const std::string& msg) noexcept : application("error logic - " + msg) {}
		const char* what() const noexcept override { return msg_.c_str() ; }
	} ;
}

namespace zz {

	template <Arithmetic Arg, Arithmetic... Args>
	std::string stringfication(const Arg& first, const Args&... rest) noexcept {
		std::string result = std::to_string(first);
		((result += ", " + std::to_string(rest)), ...);
		return result;
	}

}