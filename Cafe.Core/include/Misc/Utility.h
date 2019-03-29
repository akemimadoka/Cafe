#include "TypeTraits.h"

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

	template <typename T, typename... Args>
	constexpr T Construct(Args&&... args) noexcept(std::is_nothrow_constructible_v<T, Args&&...>)
	{
		return T(std::forward<Args>(args)...);
	}

	template <typename T, typename Mapper, typename... Args>
	constexpr T MapConstruct(Mapper&& mapper, Args&&... args) noexcept(
	    noexcept(Construct<T>(std::forward<Mapper>(mapper)(std::forward<Args>(args))...)))
	{
		return Construct<T>(std::forward<Mapper>(mapper)(std::forward<Args>(args))...);
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
