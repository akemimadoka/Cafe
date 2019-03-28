#pragma once

#include <array>
#include <tuple>
#include <type_traits>

namespace Cafe::Core::Misc
{
	namespace Detail
	{
		template <typename Tuple, typename Callable, std::size_t... I>
		constexpr auto ForEachImpl(Tuple&& tuple, Callable&& callable,
		                           std::index_sequence<I...>) noexcept(noexcept(std::tuple{
		    std::forward<Callable>(callable)(std::get<I>(std::forward<Tuple>(tuple)))... }))
		{
			return std::tuple{ std::forward<Callable>(callable)(
				  std::get<I>(std::forward<Tuple>(tuple)))... };
		}
	} // namespace Detail

	template <typename Tuple, typename Callable>
	constexpr auto ForEach(Tuple&& tuple, Callable&& callable) noexcept(noexcept(Detail::ForEachImpl(
	    std::forward<Tuple>(tuple), std::forward<Callable>(callable),
	    std::make_index_sequence<std::tuple_size_v<std::remove_reference_t<Tuple>>>{})))
	{
		return Detail::ForEachImpl(
		    std::forward<Tuple>(tuple), std::forward<Callable>(callable),
		    std::make_index_sequence<std::tuple_size_v<std::remove_reference_t<Tuple>>>{});
	}

	template <typename T>
	using RemoveCvRef = std::remove_cv_t<std::remove_reference_t<T>>;

	template <typename T, typename... Args>
	constexpr T Construct(Args&&... args) noexcept(std::is_nothrow_constructible_v<T, Args&&...>)
	{
		return T(std::forward<Args>(args)...);
	}

	template <typename T, typename Mapper, typename... Args>
	constexpr T MapConstruct(Mapper&& mapper, Args&&... args) noexcept(
	    (... && noexcept(std::forward<Mapper>(mapper)(std::forward<Args>(args)))))
	{
		return T(std::forward<Mapper>(mapper)(std::forward<Args>(args))...);
	}

	template <typename T>
	struct ConvertMapperType
	{
		constexpr ConvertMapperType() noexcept = default;

		template <typename U>
		constexpr T operator()(U&& arg) noexcept(std::is_nothrow_constructible_v<T, U&&>)
		{
			return T(std::forward<U>(arg));
		}
	};

	template <typename T>
	constexpr ConvertMapperType<T> ConvertMapper{};

	template <typename T, typename TConv, typename... Args>
	constexpr T ConvertConstruct(Args&&... args) noexcept(
	    noexcept(MapConstruct<T>(ConvertMapper<TConv>, std::forward<Args>(args)...)))
	{
		return MapConstruct<T>(ConvertMapper<TConv>, std::forward<Args>(args)...);
	}

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

	/// @brief  用于对一组非 void 的表达式进行无顺序保证计算，也可以用于检查合法性
	struct UnseqEvaluatorType
	{
		constexpr UnseqEvaluatorType() noexcept = default;

		template <typename... T>
		constexpr void operator()(T&&...) noexcept
		{
		}
	};

	constexpr UnseqEvaluatorType UnseqEvaluator{};
} // namespace Cafe::Core::Misc
