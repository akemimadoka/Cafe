#pragma once

#include <algorithm>
#include <tuple>
#include <type_traits>
#include <variant>

namespace Cafe::Core::Misc
{
	namespace Detail
	{
		template <typename Seq, typename Container, typename Callable>
		struct DispatcherListMakerImpl;
		
		template <std::size_t... I, typename Container, typename Callable>
		struct DispatcherListMakerImpl<std::index_sequence<I...>, Container, Callable>
		{
			template <std::size_t I>
			struct Dispatcher
			{
				static constexpr decltype(auto) Dispatch(Container container, Callable callable)
				{
					return std::invoke(callable, container.GetAs<I>());
				}
			};
			
			static constexpr Array DispatcherArray{ { +Dispatcher<I>::Dispatch... } };
		};
	
		template <std::size_t Size, typename Container, typename Callable>
		struct DispatcherListMaker
			: DispatcherListMakerImpl<std::make_index_sequence<Size>, Container, Callable>
		{
		};
	}

	template <typename Container, typename Visitor>
	constexpr decltype(auto) Visit(Container&& container, Visitor&& visitor)
	{
		return Detail::DispatcherListMaker<Size, Container&&, Visitor&&>::DispatcherArray
				[container.GetIndex()](std::forward<Container>(container), std::forward<Visitor>(visitor));
	}

	template <typename ContainerChecker, typename... T>
	class CommonContainer : ContainerChecker
	{
	protected:
		static constexpr std::size_t Size = sizeof...(T);
	
		using TypeTuple = std::tuple<T...>;

		template <std::size_t I>
		using NthElem = std::tuple_element_t<TypeTuple, I>;

	public:
		constexpr std::size_t GetIndex() const noexcept
		{
			return static_cast<ContainerChecker*>(this)->GetIndex();
		}

		template <std::size_t I, typename... Args>
		constexpr std::enable_if_t<std::is_constructible_v<NthElem<T>, Args&&...> Emplace(Args&&... args)
			noexcept(std::is_nothrow_constructible_v<NthElem<I>, Args&&...>)
		{
			static_cast<ContainerChecker*>(this)->BeginSwitchTo<I>();
			Destroy();
			new (static_cast<void*>(&m_Storage)) NthElem<I>(std::forward<Args>(args)...);
			static_cast<ContainerChecker*>(this)->EndSwitchTo<I>();
		}

		template <std::size_t I>
		constexpr NthElem<I>& GetAs() noexcept
		{
			return reinterpret_cast<NthElem<I>&>(m_Storage);
		}

		template <std::size_t I>
		constexpr const NthElem<I>& GetAs() const noexcept
		{
			return reinterpret_cast<const NthElem<I>&>(m_Storage);
		}

	private:
		std::aligned_storage_t<std::max({ sizeof(T)... }), std::max({ alignof(T)... })> m_Storage;

	protected:
		constexpr void Destroy() noexcept
		{
			Visit(*this, [](auto& elem)
			{
				using Type = decltype(elem);
				elem.Type::~Type();
			});
		}
	};
} // namespace Cafe::Core::Misc
