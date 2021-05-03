#pragma once

#include <array>
#include <cstdint>
#include <limits>
#include <tuple>
#include <type_traits>

namespace Cafe::Core::Misc
{
	/// @brief  与 std::type_identity 大致等价，若 std::type_identity 可用则不需使用本类
	template <typename T>
	struct Identity
	{
		using Type = T;
		using type = Type;
	};

	/// @brief	当 std::remove_cvref 不可用时用于替代，C++20 之后不需使用
	template <typename T>
	using RemoveCvRef = std::remove_cv_t<std::remove_reference_t<T>>;

	/// @brief  判断类型是否为指定的模板的实例
	/// @remark 仅适用于只接受类型参数的类型模板
	template <typename T, template <typename...> typename Template>
	struct IsInstantiationOfTrait : std::false_type
	{
	};

	template <typename... Args, template <typename...> typename Template>
	struct IsInstantiationOfTrait<Template<Args...>, Template> : std::true_type
	{
	};

	template <typename T, template <typename...> typename Template>
	constexpr bool IsInstantiationOf = IsInstantiationOfTrait<T, Template>::value;

	template <typename From, template <typename...> typename ToTemplate>
	struct ApplyToTrait;

	template <typename... Args, template <typename...> typename FromTemplate,
	          template <typename...> typename ToTemplate>
	struct ApplyToTrait<FromTemplate<Args...>, ToTemplate> : Identity<ToTemplate<Args...>>
	{
	};

	template <typename From, template <typename...> typename ToTemplate>
	using ApplyTo = typename ApplyToTrait<From, ToTemplate>::Type;

	template <template <typename...> class Template, typename... T>
	struct BindFrontTrait
	{
		template <typename... U>
		using Result = Template<T..., U...>;
	};

	template <template <typename...> class Template, typename... T>
	struct BindBackTrait
	{
		template <typename... U>
		using Result = Template<U..., T...>;
	};

	template <typename T>
	using ExtractType = typename T::type;

	namespace Detail
	{
		template <typename T, typename Fallback, typename = void>
		struct TypeOrFallbackImpl : Identity<Fallback>
		{
		};

		template <typename T, typename Fallback>
		struct TypeOrFallbackImpl<T, Fallback, std::void_t<typename T::type>> : T
		{
		};
	} // namespace Detail

	template <typename T, typename Fallback = void>
	struct TypeOrFallbackTrait : Detail::TypeOrFallbackImpl<T, Fallback>
	{
	};

	template <typename T, typename Fallback = void>
	using TypeOrFallback = ExtractType<TypeOrFallbackTrait<T, Fallback>>;

	namespace Detail
	{
		struct EmptyStruct
		{
		};
	} // namespace Detail

	template <bool Cond, typename TrueBase, typename FalseBase = Detail::EmptyStruct>
	struct DeriveIf : TrueBase
	{
		using TrueBase::TrueBase;
	};

	template <typename TrueBase, typename FalseBase>
	struct DeriveIf<false, TrueBase, FalseBase> : FalseBase
	{
		using FalseBase::FalseBase;
	};

	/// @brief  判断类型在此 trait 实例化之时是否完整
	/// @remark 即使一个不完整类型在此 trait 实例化之后提供了完整定义，之后仍会判断为
	/// 		false，若此情况发生，不同翻译单元中结果有可能不同
	template <typename T, typename = void>
	struct IsCompleteTrait : std::false_type
	{
	};

	template <typename T>
	struct IsCompleteTrait<T, std::void_t<decltype(sizeof(T))>> : std::true_type
	{
	};

	template <typename T>
	constexpr bool IsComplete = IsCompleteTrait<T>::value;

	template <typename T>
	struct RemoveCvOverRefTrait : Identity<std::remove_cv_t<T>>
	{
	};

	template <typename T>
	struct RemoveCvOverRefTrait<T&> : Identity<std::remove_cv_t<T>&>
	{
	};

	template <typename T>
	struct RemoveCvOverRefTrait<T&&> : Identity<std::remove_cv_t<T>&&>
	{
	};

	template <typename T>
	using RemoveCvOverRef = typename RemoveCvOverRefTrait<T>::Type;

	template <template <typename> class Predicate, typename... T>
	struct FindFirstTrait;

	template <template <typename> class Predicate, typename TFirst, typename... TRest>
	struct FindFirstTrait<Predicate, TFirst, TRest...>
	    : std::conditional_t<Predicate<TFirst>::value, Identity<TFirst>,
	                         FindFirstTrait<Predicate, TRest...>>
	{
	};

	template <template <typename> class Predicate>
	struct FindFirstTrait<Predicate>
	{
	};

	template <template <typename> class Predicate, typename... T>
	using FindFirst = typename FindFirstTrait<Predicate, T...>::type;

	template <template <typename> class Predicate, typename Fallback, typename... T>
	using FindFirstOr = TypeOrFallback<FindFirstTrait<Predicate, T...>, Fallback>;

	template <template <typename> class Predicate, typename Tuple>
	struct FindFirstFromTupleTrait;

	template <template <typename> class Predicate, template <typename...> class Tuple,
	          typename... T>
	struct FindFirstFromTupleTrait<Predicate, Tuple<T...>> : FindFirstTrait<Predicate, T...>
	{
	};

	template <template <typename> class Predicate, typename Tuple>
	using FindFirstFromTuple = FindFirstFromTupleTrait<Predicate, Tuple>;

	template <template <typename> class Predicate, typename Fallback, typename Tuple>
	using FindFirstFromTupleOr =
	    TypeOrFallback<FindFirstFromTupleTrait<Predicate, Tuple>, Fallback>;

	namespace Detail
	{
		template <std::uintmax_t Value>
		struct UnsignedMinTypeToHoldPredicateBuilder
		{
			template <typename T>
			struct Predicate : std::bool_constant<Value <= std::numeric_limits<T>::max()>
			{
			};
		};

		template <std::intmax_t Value>
		struct SignedMinTypeToHoldPredicateBuilder
		{
			template <typename T>
			struct Predicate : std::bool_constant<std::numeric_limits<T>::min() <= Value &&
			                                      Value <= std::numeric_limits<T>::max()>
			{
			};
		};
	} // namespace Detail

	template <std::uintmax_t Value>
	struct UnsignedMinFixedWidthTypeToHoldTrait
	    : FindFirstTrait<Detail::UnsignedMinTypeToHoldPredicateBuilder<Value>::template Predicate,
	                     std::uint8_t, std::uint16_t, std::uint32_t, std::uint64_t, std::uintmax_t>
	{
	};

	template <std::uintmax_t Value>
	using UnsignedMinFixedWidthTypeToHold =
	    typename UnsignedMinFixedWidthTypeToHoldTrait<Value>::Type;

	template <std::uintmax_t Value>
	struct UnsignedMinTypeToHoldTrait
	    : FindFirstTrait<Detail::UnsignedMinTypeToHoldPredicateBuilder<Value>::template Predicate,
	                     unsigned char, unsigned short, unsigned int, unsigned long,
	                     unsigned long long, std::uintmax_t>
	{
	};

	template <std::uintmax_t Value>
	using UnsignedMinTypeToHold = typename UnsignedMinTypeToHoldTrait<Value>::Type;

	template <std::intmax_t Value>
	struct SignedMinFixedWidthTypeToHoldTrait
	    : FindFirstTrait<Detail::SignedMinTypeToHoldPredicateBuilder<Value>::template Predicate,
	                     std::int8_t, std::int16_t, std::int32_t, std::int64_t, std::intmax_t>
	{
	};

	template <std::intmax_t Value>
	using SignedMinFixedWidthTypeToHold = typename SignedMinFixedWidthTypeToHoldTrait<Value>::Type;

	template <std::intmax_t Value>
	struct SignedMinTypeToHoldTrait
	    : FindFirstTrait<Detail::UnsignedMinTypeToHoldPredicateBuilder<Value>::template Predicate,
	                     char, short, int, long, long long, std::intmax_t>
	{
	};

	template <std::intmax_t Value>
	using SignedMinTypeToHold = typename SignedMinTypeToHoldTrait<Value>::Type;
} // namespace Cafe::Core::Misc
