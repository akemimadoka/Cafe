#pragma once

#include <array>
#include <cstdint>
#include <limits>
#include <tuple>
#include <type_traits>

namespace Cafe::Core::Misc
{
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
	struct ApplyToTrait<FromTemplate<Args...>, ToTemplate>
	{
		using Type = ToTemplate<Args...>;
	};

	template <typename From, template <typename...> typename ToTemplate>
	using ApplyTo = typename ApplyToTrait<From, ToTemplate>::Type;

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
	/// @remark 即使一个不完整类型在此 trait 实例化之后提供了完整定义，之后仍会判断为 false
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

	/// @brief  与 std::type_identity 大致等价，若 std::type_identity 可用则不需使用本类
	template <typename T>
	struct Identity
	{
		using Type = T;
	};

	template <typename T>
	struct RemoveCvOverRefTrait
	{
		using Type = std::remove_cv_t<T>;
	};

	template <typename T>
	struct RemoveCvOverRefTrait<T&>
	{
		using Type = std::remove_cv_t<T>&;
	};

	template <typename T>
	struct RemoveCvOverRefTrait<T&&>
	{
		using Type = std::remove_cv_t<T>&&;
	};

	template <typename T>
	using RemoveCvOverRef = typename RemoveCvOverRefTrait<T>::Type;

	template <std::uintmax_t Value>
	struct UnsignedMinTypeToHoldTrait
	{
	private:
		static constexpr auto TestFunc()
		{
			if constexpr (Value <= std::numeric_limits<std::uint8_t>::max())
			{
				return Identity<std::uint8_t>{};
			}
			else if constexpr (Value <= std::numeric_limits<std::uint16_t>::max())
			{
				return Identity<std::uint16_t>{};
			}
			else if constexpr (Value <= std::numeric_limits<std::uint32_t>::max())
			{
				return Identity<std::uint32_t>{};
			}
			else if constexpr (Value <= std::numeric_limits<std::uint64_t>::max())
			{
				return Identity<std::uint64_t>{};
			}
			else
			{
				return Detail::EmptyStruct{};
			}
		}

	public:
		using Type = typename std::invoke_result_t<decltype(&TestFunc)>::Type;
	};

	template <std::uintmax_t Value>
	using UnsignedMinTypeToHold = typename UnsignedMinTypeToHoldTrait<Value>::Type;

	template <std::intmax_t Value>
	struct SignedMinTypeToHoldTrait
	{
	private:
		static constexpr auto TestFunc()
		{
			if constexpr (std::numeric_limits<std::int8_t>::min() <= Value &&
			              Value <= std::numeric_limits<std::int8_t>::max())
			{
				return Identity<std::int8_t>{};
			}
			else if constexpr (std::numeric_limits<std::int16_t>::min() <= Value &&
			                   Value <= std::numeric_limits<std::int16_t>::max())
			{
				return Identity<std::int16_t>{};
			}
			else if constexpr (std::numeric_limits<std::int32_t>::min() <= Value &&
			                   Value <= std::numeric_limits<std::int32_t>::max())
			{
				return Identity<std::int32_t>{};
			}
			else if constexpr (std::numeric_limits<std::int64_t>::min() <= Value &&
			                   Value <= std::numeric_limits<std::int64_t>::max())
			{
				return Identity<std::int64_t>{};
			}
			else
			{
				return Detail::EmptyStruct{};
			}
		}

	public:
		using Type = typename std::invoke_result_t<decltype(&TestFunc)>::Type;
	};

	template <std::intmax_t Value>
	using SignedMinTypeToHold = typename SignedMinTypeToHoldTrait<Value>::Type;
} // namespace Cafe::Core::Misc
