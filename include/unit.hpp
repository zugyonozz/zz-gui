#pragma once

#include "operator.hpp"

namespace zz {

	template <Arithmetic type>
	class Point {
	public :
		type x = {} ;
		type y = {} ;

		constexpr Point() noexcept = default ;
		constexpr Point(const Point&) noexcept = default ;
		constexpr Point(Point&&) noexcept = default ;
		constexpr Point& operator=(const Point&) noexcept = default ;
		constexpr Point& operator=(Point&&) noexcept = default ;

		constexpr Point(type x, type y) noexcept : x(x), y(y) {}

		constexpr Point(type value) noexcept : x(value), y(value) {}

		template <Arithmetic Other>
		constexpr explicit Point(const Point<Other>& o) noexcept : x(static_cast<type>(o.x)), y(static_cast<type>(o.y)) {}

		template <Arithmetic Other>
		constexpr Point(Other value) noexcept : x(static_cast<type>(value)), y(static_cast<type>(value)) {}

		bool operator==(const Point& o) const noexcept { return x == o.x && y == o.y ; }
		bool operator!=(const Point& o) const noexcept { return !(*this == o) ; }

		template <Arithmetic Other>
		constexpr operator Point<Other>() const noexcept {
			if constexpr (XNOR{}.operator()<Integral<type>, Integral<Other>>()) {
				return Point<Other>{static_cast<Other>(x), static_cast<Other>(y)} ;
			} else {
				return Point<Other>{x, y} ;
			}
		}

		template <Arithmetic Other>
		constexpr operator Size<Other>() const noexcept {
			if constexpr (XNOR{}.operator()<Integral<type>, Integral<Other>>()) {
				return Size<Other>{static_cast<Other>(x), static_cast<Other>(y)} ;
			} else {
				return Size<Other>{x, y} ;
			}
		}

		#ifdef UNIT_DEBUG
			std::string debug() const noexcept {
				return '[' + stringfication(x, y) + ']' ;
			}
		#endif

	protected :
		const Point& GetPoint() const noexcept { return *this ; }
		Point& GetPoint() noexcept { return *this ; }
	} ;

	template <Arithmetic type1, Arithmetic type2>
	constexpr auto operator+(const Point<type1>& a, const Point<type2>& b) noexcept {
		using type = std::common_type_t<type1, type2> ;
		return Point<type> {Add{}(a.x, b.x), Add{}(a.y, b.y)} ;
	}

	template <Arithmetic type1, Arithmetic type2>
	constexpr auto operator-(const Point<type1>& a, const Point<type2>& b) noexcept {
		using type = std::common_type_t<type1, type2> ;
		return Point<type> {Sub{}(a.x, b.x), Sub{}(a.y, b.y)} ;
	}

	template <Arithmetic type1, Arithmetic type2>
	constexpr auto operator*(const Point<type1>& a, const Point<type2>& b) noexcept {
		using type = std::common_type_t<type1, type2> ;
		return Point<type> {Mul{}(a.x, b.x), Mul{}(a.y, b.y)} ;
	}

	template <Arithmetic type1, Arithmetic type2>
	constexpr auto operator/(const Point<type1>& a, const Point<type2>& b) {
		using type = std::common_type_t<type1, type2> ;
		return Point<type> {Div{}(a.x, b.x), Div{}(a.y, b.y)} ;
	}

	template <Arithmetic type1, Arithmetic type2>
	constexpr auto operator+(const Point<type1>& a, type2 b) noexcept {
		using type = std::common_type_t<type1, type2> ;
		return Point<type> {Add{}(a.x, b), Add{}(a.y, b)} ;
	}

	template <Arithmetic type1, Arithmetic type2>
	constexpr auto operator-(const Point<type1>& a, type2 b) noexcept {
		using type = std::common_type_t<type1, type2> ;
		return Point<type> {Sub{}(a.x, b), Sub{}(a.y, b)} ;
	}

	template <Arithmetic type1, Arithmetic type2>
	constexpr auto operator*(const Point<type1>& a, type2 b) noexcept {
		using type = std::common_type_t<type1, type2> ;
		return Point<type> {Mul{}(a.x, b), Mul{}(a.y, b)} ;
	}

	template <Arithmetic type1, Arithmetic type2>
	constexpr auto operator/(const Point<type1>& a, type2 b) {
		using type = std::common_type_t<type1, type2> ;
		return Point<type> {Div{}(a.x, b), Div{}(a.y, b)} ;
	}

	template <Arithmetic type1, Arithmetic type2>
	constexpr auto operator+(type1 a, const Point<type2>& b) noexcept {
		using type = std::common_type_t<type1, type2> ;
		return Point<type> {Add{}(a, b.x), Add{}(a, b.y)} ;
	}

	template <Arithmetic type1, Arithmetic type2>
	constexpr auto operator-(type1 a, const Point<type2>& b) noexcept {
		using type = std::common_type_t<type1, type2> ;
		return Point<type> {Sub{}(a, b.x), Sub{}(a, b.y)} ;
	}

	template <Arithmetic type1, Arithmetic type2>
	constexpr auto operator*(type1 a, const Point<type2>& b) noexcept {
		using type = std::common_type_t<type1, type2> ;
		return Point<type> {Mul{}(a, b.x), Mul{}(a, b.y)} ;
	}

	template <Arithmetic type1, Arithmetic type2>
	constexpr auto operator/(type1 a, const Point<type2>& b) {
		using type = std::common_type_t<type1, type2> ;
		return Point<type> {Div{}(a, b.x), Div{}(a, b.y)} ;
	}

	template <Arithmetic type1, Arithmetic type2>
	constexpr auto operator+=(Point<type1>& a, const Point<type2>& b) noexcept {
		a = a + b ;
		return a ;
	}

	template <Arithmetic type1, Arithmetic type2>
	constexpr auto operator-=(Point<type1>& a, const Point<type2>& b) noexcept {
		a = a - b ;
		return a ;
	}

	template <Arithmetic type1, Arithmetic type2>
	constexpr auto operator*=(Point<type1>& a, const Point<type2>& b) noexcept {
		a = a * b ;
		return a ;
	}

	template <Arithmetic type1, Arithmetic type2>
	constexpr auto operator/=(Point<type1>& a, const Point<type2>& b) {
		a = a / b ;
		return a ;
	}

	template <Arithmetic type1, Arithmetic type2>
	constexpr auto operator+=(Point<type1>& a, type2 b) noexcept {
		a = a + b ;
		return a ;
	}

	template <Arithmetic type1, Arithmetic type2>
	constexpr auto operator-=(Point<type1>& a, type2 b) noexcept {
		a = a - b ;
		return a ;
	}

	template <Arithmetic type1, Arithmetic type2>
	constexpr auto operator*=(Point<type1>& a, type2 b) noexcept {
		a = a * b ;
		return a ;
	}

	template <Arithmetic type1, Arithmetic type2>
	constexpr auto operator/=(Point<type1>& a, type2 b) {
		a = a / b ;
		return a ;
	}

	template <Arithmetic type1, Arithmetic type2>
	Point(type1, type2) -> Point<std::common_type_t<type1, type2>> ;

	template <Arithmetic type>
	Point(type) -> Point<type> ;

	template <Arithmetic type>
	class Size {
	public :
		MakeSizeType<type> w {} ;
		MakeSizeType<type> h {} ;

		constexpr Size() noexcept = default ;
		constexpr Size(const Size&) noexcept = default ;
		constexpr Size(Size&&) noexcept = default ;
		constexpr Size& operator=(const Size&) noexcept = default ;
		constexpr Size& operator=(Size&&) noexcept = default ;

		constexpr Size(type w, type h) noexcept : w(w), h(h) {}

		constexpr Size(type value) noexcept : w(value), h(value) {}

		template <Arithmetic Other>
		constexpr explicit Size(const Size<Other>& o) noexcept : w(static_cast<type>(o.w)), h(static_cast<type>(o.h)) {}

		template <Arithmetic Other>
		constexpr Size(Other value) noexcept : w(static_cast<type>(value)), h(static_cast<type>(value)) {}

		bool operator==(const Size& o) const noexcept { return w == o.w && h == o.h ; }
		bool operator!=(const Size& o) const noexcept { return !(*this == o) ; }

		template <Arithmetic Other>
		constexpr operator Size<Other>() const noexcept {
			if constexpr (XNOR{}.operator()<Integral<type>, Integral<Other>>()) {
				return Size<Other>{static_cast<Other>(w), static_cast<Other>(h)} ;
			} else {
				return Size<Other>{w, h} ;
			}
		}

		template <Arithmetic Other>
		constexpr operator Point<Other>() const noexcept {
			if constexpr (XNOR{}.operator()<Integral<type>, Integral<Other>>()) {
				return Point<Other>{static_cast<Other>(w), static_cast<Other>(h)} ;
			} else {
				return Point<Other>{w, h} ;
			}
		}

		#ifdef UNIT_DEBUG
			std::string debug() const noexcept {
				return '[' + stringfication(w, h) + ']' ;
			}
		#endif

	protected :
		const Size& GetSize() const noexcept { return *this ; }
		Size& GetSize() noexcept { return *this ; }
	} ;

	template <Arithmetic type1, Arithmetic type2>
	constexpr auto operator+(const Size<type1>& a, const Size<type2>& b) noexcept {
		using type = std::common_type_t<type1, type2> ;
		return Size<type> {Add{}(a.w, b.w), Add{}(a.h, b.h)} ;
	}

	template <Arithmetic type1, Arithmetic type2>
	constexpr auto operator-(const Size<type1>& a, const Size<type2>& b) noexcept {
		using type = std::common_type_t<type1, type2> ;
		return Size<type> {Sub{}(a.w, b.w), Sub{}(a.h, b.h)} ;
	}

	template <Arithmetic type1, Arithmetic type2>
	constexpr auto operator*(const Size<type1>& a, const Size<type2>& b) noexcept {
		using type = std::common_type_t<type1, type2> ;
		return Size<type> {Mul{}(a.w, b.w), Mul{}(a.h, b.h)} ;
	}

	template <Arithmetic type1, Arithmetic type2>
	constexpr auto operator/(const Size<type1>& a, const Size<type2>& b) {
		using type = std::common_type_t<type1, type2> ;
		return Size<type> {Div{}(a.w, b.w), Div{}(a.h, b.h)} ;
	}

	template <Arithmetic type1, Arithmetic type2>
	constexpr auto operator+(const Size<type1>& a, type2 b) noexcept {
		using type = std::common_type_t<type1, type2> ;
		return Size<type> {Add{}(a.w, b), Add{}(a.h, b)} ;
	}

	template <Arithmetic type1, Arithmetic type2>
	constexpr auto operator-(const Size<type1>& a, type2 b) noexcept {
		using type = std::common_type_t<type1, type2> ;
		return Size<type> {Sub{}(a.w, b), Sub{}(a.h, b)} ;
	}

	template <Arithmetic type1, Arithmetic type2>
	constexpr auto operator*(const Size<type1>& a, type2 b) noexcept {
		using type = std::common_type_t<type1, type2> ;
		return Size<type> {Mul{}(a.w, b), Mul{}(a.h, b)} ;
	}

	template <Arithmetic type1, Arithmetic type2>
	constexpr auto operator/(const Size<type1>& a, type2 b) {
		using type = std::common_type_t<type1, type2> ;
		return Size<type> {Div{}(a.w, b), Div{}(a.h, b)} ;
	}

	template <Arithmetic type1, Arithmetic type2>
	constexpr auto operator+(type1 a, const Size<type2>& b) noexcept {
		using type = std::common_type_t<type1, type2> ;
		return Size<type> {Add{}(a, b.w), Add{}(a, b.h)} ;
	}

	template <Arithmetic type1, Arithmetic type2>
	constexpr auto operator-(type1 a, const Size<type2>& b) noexcept {
		using type = std::common_type_t<type1, type2> ;
		return Size<type> {Sub{}(a, b.w), Sub{}(a, b.h)} ;
	}

	template <Arithmetic type1, Arithmetic type2>
	constexpr auto operator*(type1 a, const Size<type2>& b) noexcept {
		using type = std::common_type_t<type1, type2> ;
		return Size<type> {Mul{}(a, b.w), Mul{}(a, b.h)} ;
	}

	template <Arithmetic type1, Arithmetic type2>
	constexpr auto operator/(type1 a, const Size<type2>& b) {
		using type = std::common_type_t<type1, type2> ;
		return Size<type> {Div{}(a, b.w), Div{}(a, b.h)} ;
	}

	template <Arithmetic type1, Arithmetic type2>
	constexpr auto operator+=(Size<type1>& a, const Size<type2>& b) noexcept {
		a = a + b ;
		return a ;
	}

	template <Arithmetic type1, Arithmetic type2>
	constexpr auto operator-=(Size<type1>& a, const Size<type2>& b) noexcept {
		a = a - b ;
		return a ;
	}

	template <Arithmetic type1, Arithmetic type2>
	constexpr auto operator*=(Size<type1>& a, const Size<type2>& b) noexcept {
		a = a * b ;
		return a ;
	}

	template <Arithmetic type1, Arithmetic type2>
	constexpr auto operator/=(Size<type1>& a, const Size<type2>& b) {
		a = a / b ;
		return a ;
	}

	template <Arithmetic type1, Arithmetic type2>
	constexpr auto operator+=(Size<type1>& a, type2 b) noexcept {
		a = a + b ;
		return a ;
	}

	template <Arithmetic type1, Arithmetic type2>
	constexpr auto operator-=(Size<type1>& a, type2 b) noexcept {
		a = a - b ;
		return a ;
	}

	template <Arithmetic type1, Arithmetic type2>
	constexpr auto operator*=(Size<type1>& a, type2 b) noexcept {
		a = a * b ;
		return a ;
	}

	template <Arithmetic type1, Arithmetic type2>
	constexpr auto operator/=(Size<type1>& a, type2 b) {
		a = a / b ;
		return a ;
	}

	template <Arithmetic type1, Arithmetic type2>
	Size(type1, type2) -> Size<std::common_type_t<type1, type2>> ;

	template <Arithmetic type>
	Size(type) -> Size<type> ;

	template <Arithmetic type>
	class Rect : Point<type>, Size<type> {
	public :
		constexpr Rect() noexcept = default ;
		constexpr Rect(const Rect&) noexcept = default ;
		constexpr Rect(Rect&&) noexcept = default ;
		constexpr Rect& operator=(const Rect&) noexcept = default ;
		constexpr Rect& operator=(Rect&&) noexcept = default ;

		constexpr Rect(type value) noexcept : Point<type>(value), Size<type>(value) {}
		constexpr Rect(const Point<type>& point, const Size<type>& size) noexcept : Point<type>(point), Size<type>(size) {}
		constexpr Rect(type x, type y, type w, type h) noexcept : Point<type>(x, y), Size<type>(w, h) {}
		constexpr Rect(const tagRECT& o) noexcept : Point<type>(o.left, o.top), Size<type>(o.right - o.left, o.bottom - o.top) {}
		constexpr Rect(const _RECTL& o) noexcept : Point<type>(o.left, o.top), Size<type>(o.right - o.left, o.bottom - o.top) {}

		template <Arithmetic Other>
		constexpr Rect(Other value) noexcept : Point<type>(value), Size<type>(value) {}

		template <Arithmetic Other1, Arithmetic Other2> 
		constexpr explicit Rect(const Point<Other1>& point, const Size<Other2>& size) noexcept : Point<type>(point), Size<type>(size) {}

		template <Arithmetic Other1, Arithmetic Other2, Arithmetic Other3, Arithmetic Other4>
		constexpr Rect(Other1 x, Other2 y, Other3 w, Other4 h) noexcept : Point<type>(x, y), Size<type>(w, h) {}

		template <Arithmetic Other>
		constexpr Rect(const Rect<Other>& o) noexcept : Point<type>(o.x, o.y), Size<type>(o.w, o.h) {}

		template <Arithmetic Other>
		constexpr Rect& operator=(Other value) noexcept { 
			this->GetPoint() = this->GetSize() = value ;
			return *this ;
		}

		template <Arithmetic Other>
		constexpr Rect& operator=(const Rect<Other>& o) noexcept { 
			this->GetPoint() = o.GetPoint() ;
			this->GetSize() = o.GetSize() ;
			return *this ;
		}

		constexpr bool operator==(const Rect& o) const noexcept {
			return this->GetPoint() == o.GetPoint() && this->GetSize() == o.GetSize() ;
		}

		constexpr bool operator!=(const Rect& o) const noexcept {
			return !(*this == o) ;
		}

		template <Arithmetic Other> 
		explicit constexpr operator Point<Other>() const noexcept {
			return static_cast<Point<Other>>(this->GetPoint()) ; ;
		}

		template <Arithmetic Other> 
		explicit constexpr operator Size<Other>() const noexcept {
			return static_cast<Size<Other>>(this->GetSize()) ; ;
		}

		template <Arithmetic Other>
		constexpr operator Rect<Other>() const noexcept {
			return Rect<Other>{*this} ;
		}

		constexpr operator tagRECT() const noexcept {
			return tagRECT{this->x, this->y, this->w + this->x, this->h + this->y} ;
		}

		constexpr operator _RECTL() const noexcept {
			return _RECTL{this->x, this->y, this->w + this->x, this->h + this->y} ;
		}

		constexpr const Point<type>& GetPoint() const noexcept { Point<type>::GetPoint() ; }
		constexpr const Size<type>& GetSize() const noexcept { Size<type>::GetSize() ; }
		constexpr Point<type>& GetPoint() noexcept { Point<type>::GetPoint() ; }
		constexpr Size<type>& GetSize() noexcept { Size<type>::GetSize() ; }

		#ifdef UNIT_DEBUG
			std::string debug() const noexcept {
				return '[' + stringfication(this->x, this->y, this->w, this->h) + ']' ;
			}
		#endif
	} ;

	template <Arithmetic type1, Arithmetic type2>
	constexpr auto operator+(const Rect<type1>& a, const Rect<type2>& b) noexcept {
		using type =  std::common_type_t<type1, type2> ;
		return Rect<type>{a.GetPoint() + b.GetPoint(), a.GetSize() + b.GetSize()} ;
	}

	template <Arithmetic type1, Arithmetic type2>
	constexpr auto operator-(const Rect<type1>& a, const Rect<type2>& b) noexcept {
		using type =  std::common_type_t<type1, type2> ;
		return Rect<type>{a.GetPoint() - b.GetPoint(), a.GetSize() - b.GetSize()} ;
	}

	template <Arithmetic type1, Arithmetic type2>
	constexpr auto operator*(const Rect<type1>& a, const Rect<type2>& b) noexcept {
		using type =  std::common_type_t<type1, type2> ;
		return Rect<type>{a.GetPoint() * b.GetPoint(), a.GetSize() * b.GetSize()} ;
	}

	template <Arithmetic type1, Arithmetic type2>
	constexpr auto operator/(const Rect<type1>& a, const Rect<type2>& b) {
		using type =  std::common_type_t<type1, type2> ;
		return Rect<type>{a.GetPoint() / b.GetPoint(), a.GetSize() / b.GetSize()} ;
	}

	template <Arithmetic type1, Arithmetic type2>
	constexpr auto operator+(const Rect<type1>& a, type2 b) noexcept {
		using type = std::common_type_t<type1, type2> ;
		return Rect<type>{a.GetPoint() + b, a.GetSize() + b} ;
	}

	template <Arithmetic type1, Arithmetic type2>
	constexpr auto operator-(const Rect<type1>& a, type2 b) noexcept {
		using type = std::common_type_t<type1, type2> ;
		return Rect<type>{a.GetPoint() - b, a.GetSize() - b} ;
	}

	template <Arithmetic type1, Arithmetic type2>
	constexpr auto operator*(const Rect<type1>& a, type2 b) noexcept {
		using type = std::common_type_t<type1, type2> ;
		return Rect<type>{a.GetPoint() * b, a.GetSize() * b} ;
	}

	template <Arithmetic type1, Arithmetic type2>
	constexpr auto operator/(const Rect<type1>& a, type2 b) {
		using type = std::common_type_t<type1, type2> ;
		return Rect<type>{a.GetPoint() / b, a.GetSize() / b} ;
	}

	template <Arithmetic type1, Arithmetic type2>
	constexpr auto operator+(type1 a, const Rect<type2>& b) noexcept {
		using type = std::common_type_t<type1, type2> ;
		return Size<type> {b.GetPoint() + a, b.GetSize() + a} ;
	}

	template <Arithmetic type1, Arithmetic type2>
	constexpr auto operator-(type1 a, const Rect<type2>& b) noexcept {
		using type = std::common_type_t<type1, type2> ;
		return Size<type> {b.GetPoint() - a, b.GetSize() - a} ;
	}

	template <Arithmetic type1, Arithmetic type2>
	constexpr auto operator*(type1 a, const Rect<type2>& b) noexcept {
		using type = std::common_type_t<type1, type2> ;
		return Size<type> {b.GetPoint() * a, b.GetSize() * a} ;
	}

	template <Arithmetic type1, Arithmetic type2>
	constexpr auto operator/(type1 a, const Rect<type2>& b) {
		using type = std::common_type_t<type1, type2> ;
		return Size<type> {b.GetPoint() / a, b.GetSize() / a} ;
	}

	template <Arithmetic type1, Arithmetic type2>
	constexpr auto operator+=(Rect<type1>& a, const Rect<type2>& b) noexcept {
		a = a + b ;
		return a ;
	}

	template <Arithmetic type1, Arithmetic type2>
	constexpr auto operator-=(Rect<type1>& a, const Rect<type2>& b) noexcept {
		a = a - b ;
		return a ;
	}

	template <Arithmetic type1, Arithmetic type2>
	constexpr auto operator*=(Rect<type1>& a, const Rect<type2>& b) noexcept {
		a = a * b ;
		return a ;
	}

	template <Arithmetic type1, Arithmetic type2>
	constexpr auto operator/=(Rect<type1>& a, const Rect<type2>& b) {
		a = a / b ;
		return a ;
	}

	template <Arithmetic type1, Arithmetic type2>
	constexpr auto operator+=(Rect<type1>& a, type2 b) noexcept {
		a = a + b ;
		return a ;
	}

	template <Arithmetic type1, Arithmetic type2>
	constexpr auto operator-=(Rect<type1>& a, type2 b) noexcept {
		a = a - b ;
		return a ;
	}

	template <Arithmetic type1, Arithmetic type2>
	constexpr auto operator*=(Rect<type1>& a, type2 b) noexcept {
		a = a * b ;
		return a ;
	}

	template <Arithmetic type1, Arithmetic type2>
	constexpr auto operator/=(Rect<type1>& a, type2 b) {
		a = a / b ;
		return a ;
	}

	template <Arithmetic type1, Arithmetic type2, Arithmetic type3, Arithmetic type4>
	Rect(type1, type2, type3, type4) -> Rect<std::common_type_t<type1, type2, type3, type4>> ;

	template <Arithmetic type1, Arithmetic type2>
	Rect(Point<type1>, Size<type2>) -> Rect<std::common_type_t<type1, type2>> ;

	template <Arithmetic type>
	Rect(type) -> Rect<type> ;

	struct Color {
		uint8_t r = 0 ;
		uint8_t g = 0 ;
		uint8_t b = 0 ;
		uint8_t a = 0 ;

		constexpr Color() noexcept = default ;
		constexpr Color(const Color&) noexcept = default ;
		constexpr Color(Color&&) noexcept = default ;
		constexpr Color& operator=(const Color&) noexcept = default ;
		constexpr Color& operator=(Color&&) noexcept = default ;

		constexpr Color(uint8_t value) noexcept : r(value), g(value), b(value), a(value) {}
		constexpr Color(uint32_t rgba) noexcept : r(rgba & 0xFF), g((rgba >> 8) & 0xFF), b((rgba >> 16) & 0xFF), a((rgba >> 24) & 0xFF) {}
		constexpr Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) noexcept : r(r), g(g), b(b), a(a) {}

		constexpr Color& operator=(uint8_t value) noexcept{ 
			r = g = b = a = value ;
			return *this ;
		}
		constexpr Color& operator=(uint32_t rgba) noexcept{ 
			r = rgba & 0xFF ;
			g = (rgba >> 8) & 0xFF ;
			b = (rgba >> 16) & 0xFF ;
			a = (rgba >> 24) & 0xFF ;
			return *this ;
		}

		constexpr operator uint32_t() const noexcept { return (a << 24) | (b << 16) | (g << 8) | r ; }
		constexpr operator COLORREF() const noexcept { return (b << 16) | (g << 8) | r ; }

		#ifdef UNIT_DEBUG
			std::string debug() const noexcept {
				return "[" + stringfication(r, g, b, a) + "]" ;
			}
		#endif
	} ;

	inline constexpr uint32_t rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a) noexcept {
		return (a << 24) | (b << 16) | (g << 8) | r ;
	}

	inline constexpr uint32_t rgba(uint8_t r, uint8_t g, uint8_t b, double a) noexcept {
		return rgba(r, g, b, static_cast<uint8_t>(a * 255)) ;
	}

	#ifdef UNIT_DEBUG
		std::ostream& operator <<(std::ostream& os, const std::string& msg) noexcept {
			return os << msg ;
		}
	#endif
}