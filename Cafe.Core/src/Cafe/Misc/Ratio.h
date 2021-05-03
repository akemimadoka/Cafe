#pragma once
#include <Cafe/Misc/TypeTraits.h>
#include <cassert>
#include <numeric>

namespace Cafe::Core::Misc
{
	/// @brief  提供运行时的比例支持，编译期的已有 std::ratio 故不重复提供，T 应为整数类型
	/// @remark 检查分母不为 0 是用户的责任，本类仅提供一个 assert 进行检查
	template <typename T>
	class Ratio
	{
		static_assert(std::is_integral_v<T>, "T should be an integral type.");

	public:
		constexpr Ratio(T value) noexcept : m_Num{ value }, m_Denom{ T(1) }
		{
		}

		constexpr Ratio(T num, T denom) noexcept : m_Num{ num }, m_Denom{ denom }
		{
			assert(denom != T{} && "denom should not be zero.");
		}

		[[nodiscard]] constexpr T GetNum() const noexcept
		{
			return m_Num;
		}

		constexpr Ratio& SetNum(T value) noexcept
		{
			m_Num = value;
			return *this;
		}

		[[nodiscard]] constexpr T GetDenom() const noexcept
		{
			return m_Denom;
		}

		constexpr Ratio& SetDenom(T value) noexcept
		{
			m_Denom = value;
			return *this;
		}

		[[nodiscard]] constexpr Ratio Reduce() const noexcept
		{
			if (m_Num == T{})
			{
				return { T{}, T{ 1 } };
			}

			const auto gcd = std::gcd(m_Num, m_Denom);
			assert(gcd != T{} && "should never happen.");
			return { m_Num / gcd, m_Denom / gcd };
		}

		/// @remark 检查 num 是否为 0 是用户的责任
		[[nodiscard]] constexpr Ratio Reciprocal() const noexcept
		{
			assert(m_Num != T{} && "num is zero.");
			return { m_Denom, m_Num };
		}

		template <typename U>
		[[nodiscard]] constexpr U CastTo() const
		    noexcept(std::is_nothrow_constructible_v<U, T const&>&& noexcept(std::declval<U>() /
		                                                                     std::declval<U>()))
		{
			return U(U(m_Num) / U(m_Denom));
		}

		[[nodiscard]] constexpr bool IsZero() const noexcept
		{
			return m_Num == T{};
		}

	private:
		T m_Num, m_Denom;
	};

	template <typename T>
	[[nodiscard]] constexpr Ratio<T> operator+(Ratio<T> const& lhs) noexcept
	{
		return lhs;
	}

	// 若 T 是无符号数，可能无意义，但在二元 operator- 实现中使用，故不移除
	template <typename T>
	[[nodiscard]] constexpr Ratio<T> operator-(Ratio<T> const& lhs) noexcept
	{
		return { -lhs.GetNum(), lhs.GetDenom() };
	}

	template <typename T, typename U>
	[[nodiscard]] constexpr auto operator+(Ratio<T> const& lhs, Ratio<U> const& rhs) noexcept
	{
		return Ratio<std::common_type_t<T, U>>{ lhs.GetNum() * rhs.GetDenom() +
			                                        rhs.GetNum() * lhs.GetDenom(),
			                                    lhs.GetDenom() * rhs.GetDenom() }
		    .Reduce();
	}

	template <typename T, typename U>
	[[nodiscard]] constexpr auto operator-(Ratio<T> const& lhs, Ratio<U> const& rhs) noexcept
	{
		return lhs + (-rhs);
	}

	template <typename T, typename U>
	[[nodiscard]] constexpr auto operator*(Ratio<T> const& lhs, Ratio<U> const& rhs) noexcept
	{
		return Ratio<std::common_type_t<T, U>>{ lhs.GetNum() * rhs.GetNum(),
			                                    lhs.GetDenom() * rhs.GetDenom() }
		    .Reduce();
	}

	template <typename T, typename U>
	[[nodiscard]] constexpr auto operator/(Ratio<T> const& lhs, Ratio<U> const& rhs) noexcept
	{
		return lhs * rhs.Reciprocal();
	}

	template <typename T, typename U, std::enable_if_t<!IsInstantiationOf<U, Ratio>, int> = 0>
	[[nodiscard]] constexpr auto operator+(Ratio<T> const& lhs, U rhs) noexcept
	{
		return lhs + Ratio<U>{ rhs, U{ 1 } };
	}

	template <typename T, typename U, std::enable_if_t<!IsInstantiationOf<U, Ratio>, int> = 0>
	[[nodiscard]] constexpr auto operator-(Ratio<T> const& lhs, U rhs) noexcept
	{
		return lhs - Ratio<U>{ rhs, U{ 1 } };
	}

	template <typename T, typename U, std::enable_if_t<!IsInstantiationOf<U, Ratio>, int> = 0>
	[[nodiscard]] constexpr auto operator*(Ratio<T> const& lhs, U rhs) noexcept
	{
		return lhs * Ratio<U>{ rhs, U{ 1 } };
	}

	template <typename T, typename U, std::enable_if_t<!IsInstantiationOf<U, Ratio>, int> = 0>
	[[nodiscard]] constexpr auto operator/(Ratio<T> const& lhs, U rhs) noexcept
	{
		return lhs / Ratio<U>{ rhs, U{ 1 } };
	}

	template <typename T, typename U>
	constexpr Ratio<T>& operator+=(Ratio<T>& lhs, U&& rhs) noexcept
	{
		return (lhs = (lhs + std::forward<U>(rhs)));
	}

	template <typename T, typename U>
	constexpr Ratio<T>& operator-=(Ratio<T>& lhs, U&& rhs) noexcept
	{
		return (lhs = (lhs - std::forward<U>(rhs)));
	}

	template <typename T, typename U>
	constexpr Ratio<T>& operator*=(Ratio<T>& lhs, U&& rhs) noexcept
	{
		return (lhs = (lhs * std::forward<U>(rhs)));
	}

	template <typename T, typename U>
	constexpr Ratio<T>& operator/=(Ratio<T>& lhs, U&& rhs) noexcept
	{
		return (lhs = (lhs / std::forward<U>(rhs)));
	}

	template <typename T, typename U>
	[[nodiscard]] constexpr bool operator==(Ratio<T> const& lhs, Ratio<U> const& rhs) noexcept
	{
		const auto reducedLhs = lhs.Reduce();
		const auto reducedRhs = rhs.Reduce();
		return reducedLhs.GetNum() == reducedRhs.GetNum() &&
		       reducedLhs.GetDenom() == reducedRhs.GetDenom();
	}

	template <typename T, typename U>
	[[nodiscard]] constexpr bool operator!=(Ratio<T> const& lhs, Ratio<U> const& rhs) noexcept
	{
		return !(lhs == rhs);
	}

	template <typename T, typename U>
	[[nodiscard]] constexpr bool operator<(Ratio<T> const& lhs, Ratio<U> const& rhs) noexcept
	{
		const auto gcd = std::gcd(lhs.GetDenom(), rhs.GetDenom());
		return lhs.GetNum() * gcd < rhs.GetNum() * gcd;
	}

	template <typename T, typename U>
	[[nodiscard]] constexpr bool operator<=(Ratio<T> const& lhs, Ratio<U> const& rhs) noexcept
	{
		return lhs == rhs || lhs < rhs;
	}

	template <typename T, typename U>
	[[nodiscard]] constexpr bool operator>(Ratio<T> const& lhs, Ratio<U> const& rhs) noexcept
	{
		return !(lhs <= rhs);
	}

	template <typename T, typename U>
	[[nodiscard]] constexpr bool operator>=(Ratio<T> const& lhs, Ratio<U> const& rhs) noexcept
	{
		return !(lhs < rhs);
	}

} // namespace Cafe::Core::Misc
