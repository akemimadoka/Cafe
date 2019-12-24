#include "TypeTraits.h"

namespace Cafe::Core::Misc
{
	namespace Detail
	{
		template <typename T>
		struct TypeIdImpl
		{
			static constexpr const void* GetId() noexcept
			{
				static const int s_Dummy;
				return &s_Dummy;
			}
		};
	} // namespace Detail

	class AnyView
	{
	public:
		template <typename T>
		constexpr AnyView(T&& object)
		    : m_TypeId{ Detail::TypeIdImpl<std::remove_reference_t<T>>::GetId() }, m_ObjectView{
			      static_cast<void*>(const_cast<RemoveCvRef<T>*>(std::addressof(object)))
		      }
		{
		}

		template <typename T>
		constexpr bool Is() const noexcept
		{
			return m_TypeId == Detail::TypeIdImpl<T>::GetId();
		}

		template <typename T>
		T* Get() const noexcept
		{
			if (Is<T>())
			{
				return static_cast<T*>(m_ObjectView);
			}

			return nullptr;
		}

	private:
		const void* m_TypeId;
		void* m_ObjectView;
	};
} // namespace Cafe::Core::Misc
