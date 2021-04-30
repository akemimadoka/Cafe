#pragma once

#include "TypeTraits.h"
#include "UtilityMacros.h"

namespace Cafe::Core::Misc
{
	struct AlwaysInvoke
	{
		template <typename T>
		static constexpr bool ShouldInvoke(T const&) noexcept
		{
			return true;
		}
	};

	struct InvokeOnError
	{
		template <typename T>
		static bool ShouldInvoke(T const&) noexcept
		{
			return std::uncaught_exceptions();
		}
	};

	template <typename Callable, typename InvokeCondition = AlwaysInvoke>
	class Scope
	{
	public:
		template <typename... Args>
		explicit Scope(Args&&... args) noexcept(std::is_nothrow_constructible_v<Callable, Args&&...>)
		    : m_Callable(std::forward<Args>(args)...)
		{
		}

		~Scope() noexcept(std::is_nothrow_invocable_v<Callable>)
		{
			if (InvokeCondition::ShouldInvoke(m_Callable))
			{
				m_Callable();
			}
		}

	private:
#if __has_cpp_attribute(no_unique_address) >= 201803L
		[[no_unique_address]]
#endif
		Callable m_Callable;
	};

	namespace Detail
	{
		template <typename InvokeCondition>
		struct ScopeMakerType : Core::Misc::Identity<InvokeCondition>
		{
			constexpr ScopeMakerType() noexcept = default;
		};

		template <typename InvokeCondition>
		constexpr ScopeMakerType<InvokeCondition> ScopeMaker{};

		template <typename Callable, typename InvokeCondition>
		constexpr Scope<Core::Misc::RemoveCvRef<Callable>, InvokeCondition>
		operator*(ScopeMakerType<InvokeCondition>, Callable&& callable) noexcept(
		    std::is_nothrow_constructible_v<Scope<Core::Misc::RemoveCvRef<Callable>, InvokeCondition>,
		                                    Callable&&>)
		{
			return Scope<Core::Misc::RemoveCvRef<Callable>, InvokeCondition>{ std::forward<Callable>(
				  callable) };
		}
	} // namespace Detail
} // namespace Cafe::Core::Misc

#define CAFE_SCOPE_EXIT_ID(id) const auto id = ::Cafe::Core::Misc::Detail::ScopeMaker<::Cafe::Core::Misc::AlwaysInvoke> * [&]
#define CAFE_SCOPE_FAIL_ID(id) const auto id = ::Cafe::Core::Misc::Detail::ScopeMaker<::Cafe::Core::Misc::InvokeOnError> * [&]

#ifdef __COUNTER__
#define CAFE_SCOPE_MAGIC_ID CAFE_CONCAT(cafeScopeMagicId, __COUNTER__)
#else
#define CAFE_SCOPE_MAGIC_ID CAFE_CONCAT(cafeScopeMagicId, __LINE__)
#endif

#define CAFE_SCOPE_EXIT CAFE_SCOPE_EXIT_ID(CAFE_SCOPE_MAGIC_ID)
#define CAFE_SCOPE_FAIL CAFE_SCOPE_FAIL_ID(CAFE_SCOPE_MAGIC_ID)
