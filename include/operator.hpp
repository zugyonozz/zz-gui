#pragma once

#include "enum.hpp"

namespace zz {
	struct XNOR {
		template <bool State1, bool State2> 
		constexpr bool operator()() const noexcept {
			return (State1 == State2) ? true : false ;
		}
	} ;

	struct Add {
		template <typename Type1, typename Type2> requires (Convertible<Type1, Type2> && Convertible<Type2, Type1>)
		constexpr std::common_type_t<Type1, Type2> operator()(Type1 a, Type2 b) const noexcept {
			using type = std::common_type_t<Type1, Type2> ;
			return static_cast<type>(a) + static_cast<type>(b) ;
		}
	} ;

	struct Sub {
		template <typename Type1, typename Type2> requires (Convertible<Type1, Type2> && Convertible<Type2, Type1>)
		constexpr std::common_type_t<Type1, Type2> operator()(Type1 a, Type2 b) const noexcept {
			using type = std::common_type_t<Type1, Type2> ;
			return static_cast<type>(a) - static_cast<type>(b) ;
		}
	} ;

	struct Mul {
		template <typename Type1, typename Type2> requires (Convertible<Type1, Type2> && Convertible<Type2, Type1>)
		constexpr std::common_type_t<Type1, Type2> operator()(Type1 a, Type2 b) const noexcept {
			using type = std::common_type_t<Type1, Type2> ;
			return static_cast<type>(a) * static_cast<type>(b) ;
		}
	} ;

	struct Div {
		template <typename Type1, typename Type2> requires (Convertible<Type1, Type2> && Convertible<Type2, Type1>)
		constexpr std::common_type_t<Type1, Type2> operator()(Type1 a, Type2 b) const {
			using type = std::common_type_t<Type1, Type2> ;
			if (b == 0) {
				throw Ex::error_logic("can't divide by zero!") ;
			}
			return static_cast<type>(a) / static_cast<type>(b) ;
		}
	} ;

	template <EnumType type>
	type operator|(type a, type b) noexcept {
		using return_type = std::underlying_type_t<type> ;
		return static_cast<type>(static_cast<return_type>(a) | static_cast<return_type>(b)) ;
	}

	template <EnumType type>
	type operator&(type a, type b) noexcept {
		using return_type = std::underlying_type_t<type> ;
		return static_cast<type>(static_cast<return_type>(a) & static_cast<return_type>(b)) ;
	}

	template <EnumType type>
	type operator~(type value) noexcept {
		using return_type = std::underlying_type_t<type> ;
		return static_cast<type>(~static_cast<return_type>(value)) ;
	}

	template <EnumType type>
	type operator|=(type& a, type b) noexcept {
		a = a | b ;
		return a ;
	}

	template <EnumType type>
	type operator&=(type a, type b) noexcept {
		a = a & b ;
		return a ;
	}
}