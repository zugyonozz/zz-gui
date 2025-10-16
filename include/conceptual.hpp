#pragma once

#include "env.hpp"

namespace zz {
	template <typename type>
	concept Arithmetic = std::is_arithmetic_v<type> ;

	template <typename FromType, typename ToType>
	concept Convertible = std::is_convertible_v<FromType, ToType> ;

	template <typename type>
	concept Integral = std::is_integral_v<type> ;

	template <typename type>
	concept FloatingPoint = std::is_floating_point_v<type> ;

	template <typename type>
	concept EnumType = std::is_enum_v<type> ;

	template <typename>
	struct SizeType ;

	template <Integral type>
	struct SizeType<type> {
		using type_ = std::make_unsigned_t<type> ;
	} ;

	template <FloatingPoint type>
	struct SizeType<type> {
		using type_ = type ;
	} ;

	template <Arithmetic type> 
	using MakeSizeType = typename SizeType<type>::type_ ;

	template <typename type> struct is_string : std::false_type {} ;
	template <> struct is_string <char*> : std::true_type {} ;
	template <> struct is_string<const char*> : std::true_type {} ;
	template <> struct is_string<std::string> : std::true_type {} ;
	template <> struct is_string<std::string_view> : std::true_type {} ;
	template <> struct is_string<std::wstring> : std::true_type {} ;
	template <> struct is_string<std::wstring_view> : std::true_type {} ;
	template <> struct is_string<char8_t*> : std::true_type {} ;
	template <> struct is_string<const char8_t*> : std::true_type {} ;
	template <> struct is_string<std::u8string> : std::true_type {} ;
	template <> struct is_string<std::u8string_view> : std::true_type {} ;
	template <> struct is_string<char16_t*> : std::true_type {} ;
	template <> struct is_string<const char16_t*> : std::true_type {} ;
	template <> struct is_string<std::u16string> : std::true_type {} ;
	template <> struct is_string<std::u16string_view> : std::true_type {} ;
	template <> struct is_string<char32_t*> : std::true_type {} ;
	template <> struct is_string<const char32_t*> : std::true_type {} ;
	template <> struct is_string<std::u32string> : std::true_type {} ;
	template <> struct is_string<std::u32string_view> : std::true_type {} ;

	template <typename type>
	concept String = is_string<type>::value ;

	template <typename Type1, typename Type2>
	concept IsSame = std::is_convertible_v<Type1, Type2> ;
}