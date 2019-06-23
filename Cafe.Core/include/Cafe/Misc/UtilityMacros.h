#pragma once

#define CAFE_CONCAT_IMPL(a, b) a##b
#define CAFE_CONCAT(a, b) CAFE_CONCAT_IMPL(a, b)

#define CAFE_STRINGIFY_IMPL(a) #a
#define CAFE_STRINGIFY(a) CAFE_STRINGIFY_IMPL(a)

#define CAFE_ID(...) __VA_ARGS__

#define CAFE_GET_HEAD(a, ...) a
#define CAFE_GET_TAIL(a, ...) __VA_ARGS__

#define CAFE_EXPAND_OR_IMPL(replacement, ...) CAFE_GET_HEAD(__VA_ARGS__ __VA_OPT__(, ) replacement)
#define CAFE_EXPAND_OR(replacement, a) CAFE_EXPAND_OR_IMPL(replacement, a)

#define CAFE_IS_EMPTY(...) CAFE_EXPAND_OR(true, __VA_OPT__(false))

#define CAFE_IF_IMPL_true(a, b) a
#define CAFE_IF_IMPL_1(a, b) a
#define CAFE_IF_IMPL_false(a, b) b
#define CAFE_IF_IMPL_0(a, b) b
#define CAFE_IF(cond, a, b) CAFE_CONCAT(CAFE_IF_IMPL_, cond)(a, b)

#define CAFE_NOT(a) CAFE_IF(a, false, true)
#define CAFE_AND(a, b) CAFE_IF(a, b, a)
#define CAFE_OR(a, b) CAFE_IF(a, a, b)

#define CAFE_BOOL_LITERAL_TO_01(a) CAFE_IF(a, 1, 0)
#define CAFE_01_TO_BOOL_LITERAL(a) CAFE_IF(a, true, false)

#define CAFE_HAS_MULTIPLE_ARGUMENT(...)                                                            \
	CAFE_IF(CAFE_IS_EMPTY(__VA_ARGS__), false, CAFE_IS_EMPTY(CAFE_GET_TAIL(__VA_ARGS__)))

#if __has_cpp_attribute(expects)
#	define CAFE_MAKE_ENUM_BITMASK_TYPE_IMPL_CONTRACT_FUNCSIG(content) [[expects:content]]
#	define CAFE_MAKE_ENUM_BITMASK_TYPE_IMPL_CONTRACT_IN_FUNC(content)
#else
#	define CAFE_MAKE_ENUM_BITMASK_TYPE_IMPL_CONTRACT_FUNCSIG(content)
#	define CAFE_MAKE_ENUM_BITMASK_TYPE_IMPL_CONTRACT_IN_FUNC(content) assert(content)
#endif

/// @brief  定义一组操作符使得枚举类型符合 BitMask 要求
/// @remark 使用此宏需要包含头文件 <type_traits>，可包含 <cassert> 以包含部分 Contract（若已有
/// Contract 特性则不需要）
#define CAFE_MAKE_ENUM_BITMASK_TYPE(enumType)                                                      \
	static_assert(std::is_enum_v<enumType>, CAFE_STRINGIFY(enumType) " is not a enum type.");        \
                                                                                                   \
	constexpr enumType operator&(enumType a, enumType b) noexcept                                    \
	{                                                                                                \
		using UnderlyingType = std::underlying_type_t<enumType>;                                       \
		return static_cast<enumType>(static_cast<UnderlyingType>(a) & static_cast<UnderlyingType>(b)); \
	}                                                                                                \
                                                                                                   \
	constexpr enumType operator|(enumType a, enumType b) noexcept                                    \
	{                                                                                                \
		using UnderlyingType = std::underlying_type_t<enumType>;                                       \
		return static_cast<enumType>(static_cast<UnderlyingType>(a) | static_cast<UnderlyingType>(b)); \
	}                                                                                                \
                                                                                                   \
	constexpr enumType operator^(enumType a, enumType b) noexcept                                    \
	{                                                                                                \
		using UnderlyingType = std::underlying_type_t<enumType>;                                       \
		return static_cast<enumType>(static_cast<UnderlyingType>(a) ^ static_cast<UnderlyingType>(b)); \
	}                                                                                                \
                                                                                                   \
	constexpr enumType operator~(enumType a) noexcept                                                \
	{                                                                                                \
		using UnderlyingType = std::underlying_type_t<enumType>;                                       \
		return static_cast<enumType>(~static_cast<UnderlyingType>(a));                                 \
	}                                                                                                \
                                                                                                   \
	constexpr enumType& operator&=(enumType& a, enumType b) noexcept                                 \
	{                                                                                                \
		return a = (a & b);                                                                            \
	}                                                                                                \
                                                                                                   \
	constexpr enumType& operator|=(enumType& a, enumType b) noexcept                                 \
	{                                                                                                \
		return a = (a | b);                                                                            \
	}                                                                                                \
                                                                                                   \
	constexpr enumType& operator^=(enumType& a, enumType b) noexcept                                 \
	{                                                                                                \
		return a = (a ^ b);                                                                            \
	}                                                                                                \
                                                                                                   \
	constexpr bool operator==(                                                                       \
	    enumType a, int zero) noexcept CAFE_MAKE_ENUM_BITMASK_TYPE_IMPL_CONTRACT_FUNCSIG(zero == 0)  \
	{                                                                                                \
		CAFE_MAKE_ENUM_BITMASK_TYPE_IMPL_CONTRACT_IN_FUNC(zero == 0);                                  \
		return a == enumType{};                                                                        \
	}
