/// @file	Optional.h
///	@remark 未完工，仅为思考方向用
#pragma once

#include "TypeTraits.h"
#include "Utility.h"
#include <cassert>
#include <cstddef>

namespace Cafe::Core::Misc
{
	template <typename T>
	struct NormalChecker
	{
		constexpr NormalChecker() noexcept : m_HasValue{ false }
		{
		}

		constexpr void Emplace(T*) noexcept
		{
			m_HasValue = true;
		}

		constexpr void Destroy(T*) noexcept
		{
			m_HasValue = false;
		}

		constexpr bool Check(T*) const noexcept
		{
			return m_HasValue;
		}

	private:
		bool m_HasValue;
	};

	template <typename T, T Value>
	struct SpecifiedInvalidValueChecker
	{
		template <typename T>
		struct Checker
		{
			constexpr void Emplace(T* storage) noexcept
			{
				assert(*storage != Value);
			}

			constexpr void Destroy(T* storage) noexcept
			{
				new (static_cast<void*>(storage)) T(Value);
			}

			constexpr bool Check(T* storage) const noexcept
			{
				return *storage == Value;
			}
		};
	};

	template <typename T>
	struct NullValueChecker
	{
		constexpr void Emplace(T* storage) noexcept
		{
			assert(*storage != T{});
		}

		constexpr void Destroy(T* storage) noexcept
		{
			new (static_cast<void*>(storage)) T{};
		}

		constexpr bool Check(T* storage) const noexcept
		{
			return *storage == T{};
		}
	};

	namespace Detail
	{
		struct InitContainerCheckerTagType
		{
			constexpr InitContainerCheckerTagType() noexcept = default;
		};
	} // namespace Detail

	constexpr Detail::InitContainerCheckerTagType InitContainerCheckerTag{};

	template <typename T, typename ContainerChecker = NormalChecker<T>>
	class Optional
	{
	public:
		constexpr Optional() noexcept = default;

		template <typename... Args>
		constexpr Optional(std::in_place_t, Args&&... args)
		    : m_Storage{ std::forward<Args>(args)... }
		{
			m_Checker.Emplace(std::addressof(m_Storage));
		}

		template <typename... Args>
		constexpr Optional(Detail::InitContainerCheckerTagType, Args&&... args)
		    : m_Checker{ std::forward<Args>(args)... }
		{
		}

	private:
		template <typename... Args1, std::size_t... I1, typename... Args2, std::size_t... I2>
		constexpr Optional(std::piecewise_construct_t, std::tuple<Args1...>& contentArgs,
		                   std::index_sequence<I1...>, std::tuple<Args2...>& checkerArgs,
		                   std::index_sequence<I2...>)
		    : m_Storage{ std::get<I1>(contentArgs)... }, m_Checker{ std::get<I2>(checkerArgs)... }
		{
			m_Checker.Emplace(std::addressof(m_Storage));
		}

	public:
		template <typename... Args1, typename... Args2>
		constexpr Optional(std::piecewise_construct_t, std::tuple<Args1...> contentArgs,
		                   std::tuple<Args2...> checkerArgs)
		    : Optional(std::piecewise_construct, contentArgs,
		               std::make_index_sequence<sizeof...(Args1)>{}, checkerArgs,
		               std::make_index_sequence<sizeof...(Args2)>{})
		{
		}

		constexpr ~Optional()
		{
			if (HasValue())
			{
				m_Checker.Destroy(std::addressof(m_Storage));
			}
		}

		constexpr bool HasValue() const noexcept
		{
			return m_Checker.Check();
		}

		constexpr T* Value() noexcept
		{
			if (HasValue())
			{
				return std::addressof(m_Storage);
			}
			return nullptr;
		}

		constexpr const T* Value() const noexcept
		{
			if (HasValue())
			{
				return std::addressof(m_Storage);
			}
			return nullptr;
		}

		constexpr explicit operator bool() const noexcept
		{
			return HasValue();
		}

		constexpr T& operator*()
		{
			const auto value = Value();
			if (value)
			{
				return *value;
			}
			throw std::runtime_error("No value");
		}

		constexpr T& operator*() const
		{
			const auto value = Value();
			if (value)
			{
				return *value;
			}
			throw std::runtime_error("No value");
		}

	private:
#if __has_cpp_attribute(no_unique_address)
		[[no_unique_address]]
#endif
		union
		{
			Detail::EmptyStruct m_Dummy;
			T m_Storage;
		} m_Payload;
#if __has_cpp_attribute(no_unique_address)
		[[no_unique_address]]
#endif
		ContainerChecker m_Checker;
	};

	template <typename T, typename ContainerChecker>
	class Optional<T&, ContainerChecker>
	{
	public:
		constexpr Optional() noexcept = default;

		constexpr Optional(T& value) noexcept : m_Value{ value }
		{
		}

		constexpr bool HasValue() const noexcept
		{
			return m_Value.HasValue();
		}

		constexpr T* Value() const noexcept
		{
			return m_Value.Value();
		}

		constexpr explicit operator bool() const noexcept
		{
			return HasValue();
		}

		constexpr T& operator*() const
		{
			const auto value = Value();
			if (value)
			{
				return *value;
			}
			throw std::runtime_error("No value");
		}

	private:
		Optional<T*, NullValueChecker> m_Value;
	};
} // namespace Cafe::Core::Misc
