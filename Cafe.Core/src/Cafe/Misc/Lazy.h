#pragma once

#include <optional>
#include <type_traits>

namespace Cafe::Core::Misc
{
	template <typename Producer>
	class Lazy
	{
	public:
		using ValueType = std::invoke_result_t<Producer>;

		template <typename... Args>
		constexpr explicit Lazy(Args&&... args) noexcept(
		    std::is_nothrow_constructible_v<Producer, Args&&...>)
		    : m_Producer(std::forward<Args>(args)...)
		{
		}

		constexpr ValueType& GetValue() noexcept(std::is_nothrow_invocable_v<Producer>)
		{
			if (m_Value.has_value())
			{
				return m_Value.value();
			}

			return m_Value.emplace(m_Producer());
		}

		constexpr bool HasValue() const noexcept
		{
			return m_Value.has_value();
		}

		constexpr ValueType& operator*() noexcept(std::is_nothrow_invocable_v<Producer>)
		{
			return GetValue();
		}

		constexpr explicit operator bool() const noexcept
		{
			return HasValue();
		}

	private:
		Producer m_Producer;
		std::optional<ValueType> m_Value;
	};

	template <typename Producer>
	explicit Lazy(Producer&&) -> Lazy<std::remove_cvref_t<Producer>>;
} // namespace Cafe::Core::Misc
