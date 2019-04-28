#include <optional>

namespace Cafe::Core::Misc
{
	struct EmptySetTagType
	{
		constexpr EmptySetTagType() noexcept = default;
	};

	constexpr EmptySetTagType EmptySetTag{};

	template <typename T>
	class NumericInterval
	{
	public:
		struct Bound
		{
			T Value;
			bool Closed;
		};

		// 表示空集
		constexpr NumericInterval(EmptySetTagType) noexcept : m_IsEmptySet{ true }
		{
		}

		// 表示实数集
		constexpr NumericInterval(std::nullopt_t = std::nullopt, std::nullopt_t = std::nullopt) noexcept
		    : m_IsEmptySet{ false }
		{
		}

		// 表示无右界区间
		constexpr NumericInterval(Bound leftBound, std::nullopt_t) noexcept
		    : m_IsEmptySet{ false }, m_LeftBound{ leftBound }
		{
		}

		// 表示无左界区间
		constexpr NumericInterval(std::nullopt_t, Bound rightBound) noexcept
		    : m_IsEmptySet{ false }, m_RightBound{ rightBound }
		{
		}

		// 根据实际值表示特定的区间
		constexpr NumericInterval(Bound leftBound, Bound rightBound) noexcept : m_IsEmptySet{ true }
		{
			if (leftBound.Value < rightBound.Value ||
			    (leftBound.Value == rightBound.Value && leftBound.Closed && rightBound.Closed))
			{
				m_IsEmptySet = false;
				m_LeftBound.emplace(leftBound);
				m_RightBound.emplace(rightBound);
			}
		}

		constexpr bool InBounds(T value) const noexcept
		{
			if (m_IsEmptySet)
			{
				return false;
			}

			if (m_LeftBound.has_value())
			{
				const auto leftBound = m_LeftBound.value();
				if (leftBound.Closed)
				{
					if (value < leftBound.Value)
					{
						return false;
					}
				}
				else if (value <= leftBound.Value)
				{
					return false;
				}
			}

			if (m_RightBound.has_value())
			{
				const auto rightBound = m_RightBound.value();
				if (rightBound.Closed)
				{
					if (value > rightBound.Value)
					{
						return false;
					}
				}
				else if (value >= rightBound.Value)
				{
					return false;
				}
			}

			return true;
		}

		constexpr bool IsEmptySet() const noexcept
		{
			return m_IsEmptySet;
		}

		constexpr std::optional<Bound> const& GetLeftBound() const noexcept
		{
			return m_LeftBound;
		}

		constexpr std::optional<Bound> const& GetRightBound() const noexcept
		{
			return m_RightBound;
		}

	private:
		bool m_IsEmptySet;
		std::optional<Bound> m_LeftBound;
		std::optional<Bound> m_RightBound;
	};
} // namespace Cafe::Core::Misc
