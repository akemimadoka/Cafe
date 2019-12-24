#pragma once

#include "Utility.h"
#include "UtilityMacros.h"
#include <cassert>
#include <tuple>

namespace Cafe::Core::Misc
{
	template <typename Prototype>
	struct FunctionTraits;

	template <typename ReturnTypeArg, typename... Args>
	struct FunctionTraits<ReturnTypeArg(Args...)>
	{
		using ReturnType = ReturnTypeArg;
		using ArgsTuple = std::tuple<Args...>;
	};

	template <typename ReturnTypeArg, typename... Args>
	struct FunctionTraits<ReturnTypeArg(Args...) const> : FunctionTraits<ReturnTypeArg(Args...)>
	{
		using IsConstQualified = std::true_type;
	};

	template <typename ReturnTypeArg, typename... Args>
	struct FunctionTraits<ReturnTypeArg(Args...) volatile> : FunctionTraits<ReturnTypeArg(Args...)>
	{
		using IsVolatileQualified = std::true_type;
	};

	template <typename ReturnTypeArg, typename... Args>
	struct FunctionTraits<ReturnTypeArg(Args...) const volatile>
	    : FunctionTraits<ReturnTypeArg(Args...)>
	{
		using IsConstQualified = std::true_type;
		using IsVolatileQualified = std::true_type;
	};

	template <typename ReturnTypeArg, typename... Args>
	struct FunctionTraits<ReturnTypeArg(Args...) noexcept> : FunctionTraits<ReturnTypeArg(Args...)>
	{
		using IsNoexcept = std::true_type;
	};

	template <typename ReturnTypeArg, typename... Args>
	struct FunctionTraits<ReturnTypeArg(Args...) const noexcept>
	    : FunctionTraits<ReturnTypeArg(Args...) const>
	{
		using IsNoexcept = std::true_type;
	};

	template <typename ReturnTypeArg, typename... Args>
	struct FunctionTraits<ReturnTypeArg(Args...) volatile noexcept>
	    : FunctionTraits<ReturnTypeArg(Args...) volatile>
	{
		using IsNoexcept = std::true_type;
	};

	template <typename ReturnTypeArg, typename... Args>
	struct FunctionTraits<ReturnTypeArg(Args...) const volatile noexcept>
	    : FunctionTraits<ReturnTypeArg(Args...) const volatile>
	{
		using IsNoexcept = std::true_type;
	};

	template <typename ReturnTypeArg, typename... Args>
	struct FunctionTraits<ReturnTypeArg(Args...)&> : FunctionTraits<ReturnTypeArg(Args...)>
	{
		using IsLValueReferenceQualified = std::true_type;
	};

	template <typename ReturnTypeArg, typename... Args>
	struct FunctionTraits<ReturnTypeArg(Args...) const&>
	    : FunctionTraits<ReturnTypeArg(Args...) const>
	{
		using IsLValueReferenceQualified = std::true_type;
	};

	template <typename ReturnTypeArg, typename... Args>
	struct FunctionTraits<ReturnTypeArg(Args...) volatile&>
	    : FunctionTraits<ReturnTypeArg(Args...) volatile>
	{
		using IsLValueReferenceQualified = std::true_type;
	};

	template <typename ReturnTypeArg, typename... Args>
	struct FunctionTraits<ReturnTypeArg(Args...) const volatile&>
	    : FunctionTraits<ReturnTypeArg(Args...) const volatile>
	{
		using IsLValueReferenceQualified = std::true_type;
	};

	template <typename ReturnTypeArg, typename... Args>
	struct FunctionTraits<ReturnTypeArg(Args...) & noexcept>
	    : FunctionTraits<ReturnTypeArg(Args...) noexcept>
	{
		using IsLValueReferenceQualified = std::true_type;
	};

	template <typename ReturnTypeArg, typename... Args>
	struct FunctionTraits<ReturnTypeArg(Args...) const& noexcept>
	    : FunctionTraits<ReturnTypeArg(Args...) const noexcept>
	{
		using IsLValueReferenceQualified = std::true_type;
	};

	template <typename ReturnTypeArg, typename... Args>
	struct FunctionTraits<ReturnTypeArg(Args...) volatile& noexcept>
	    : FunctionTraits<ReturnTypeArg(Args...) volatile noexcept>
	{
		using IsLValueReferenceQualified = std::true_type;
	};

	template <typename ReturnTypeArg, typename... Args>
	struct FunctionTraits<ReturnTypeArg(Args...) const volatile& noexcept>
	    : FunctionTraits<ReturnTypeArg(Args...) const volatile noexcept>
	{
		using IsLValueReferenceQualified = std::true_type;
	};

	template <typename ReturnTypeArg, typename... Args>
	struct FunctionTraits<ReturnTypeArg(Args...) &&> : FunctionTraits<ReturnTypeArg(Args...)>
	{
		using IsRValueReferenceQualified = std::true_type;
	};

	template <typename ReturnTypeArg, typename... Args>
	struct FunctionTraits<ReturnTypeArg(Args...) const&&>
	    : FunctionTraits<ReturnTypeArg(Args...) const>
	{
		using IsRValueReferenceQualified = std::true_type;
	};

	template <typename ReturnTypeArg, typename... Args>
	struct FunctionTraits<ReturnTypeArg(Args...) volatile&&>
	    : FunctionTraits<ReturnTypeArg(Args...) volatile>
	{
		using IsRValueReferenceQualified = std::true_type;
	};

	template <typename ReturnTypeArg, typename... Args>
	struct FunctionTraits<ReturnTypeArg(Args...) const volatile&&>
	    : FunctionTraits<ReturnTypeArg(Args...) const volatile>
	{
		using IsRValueReferenceQualified = std::true_type;
	};

	template <typename ReturnTypeArg, typename... Args>
	struct FunctionTraits<ReturnTypeArg(Args...) && noexcept>
	    : FunctionTraits<ReturnTypeArg(Args...) noexcept>
	{
		using IsRValueReferenceQualified = std::true_type;
	};

	template <typename ReturnTypeArg, typename... Args>
	struct FunctionTraits<ReturnTypeArg(Args...) const&& noexcept>
	    : FunctionTraits<ReturnTypeArg(Args...) const noexcept>
	{
		using IsRValueReferenceQualified = std::true_type;
	};

	template <typename ReturnTypeArg, typename... Args>
	struct FunctionTraits<ReturnTypeArg(Args...) volatile&& noexcept>
	    : FunctionTraits<ReturnTypeArg(Args...) volatile noexcept>
	{
		using IsRValueReferenceQualified = std::true_type;
	};

	template <typename ReturnTypeArg, typename... Args>
	struct FunctionTraits<ReturnTypeArg(Args...) const volatile&& noexcept>
	    : FunctionTraits<ReturnTypeArg(Args...) const volatile noexcept>
	{
		using IsRValueReferenceQualified = std::true_type;
	};

	template <typename Prototype, typename = void>
	struct IsFunctionConstQualified : std::false_type
	{
	};

	template <typename Prototype>
	struct IsFunctionConstQualified<Prototype,
	                                std::void_t<typename FunctionTraits<Prototype>::IsConstQualified>>
	    : std::true_type
	{
	};

	template <typename Prototype, typename = void>
	struct IsFunctionVolatileQualified : std::false_type
	{
	};

	template <typename Prototype>
	struct IsFunctionVolatileQualified<
	    Prototype, std::void_t<typename FunctionTraits<Prototype>::IsVolatileQualified>>
	    : std::true_type
	{
	};

	template <typename Prototype, typename = void>
	struct IsFunctionNoexcept : std::false_type
	{
	};

	template <typename Prototype>
	struct IsFunctionNoexcept<Prototype, std::void_t<typename FunctionTraits<Prototype>::IsNoexcept>>
	    : std::true_type
	{
	};

	template <typename Prototype, typename = void>
	struct IsFunctionLValueReferenceQualified : std::false_type
	{
	};

	template <typename Prototype>
	struct IsFunctionLValueReferenceQualified<
	    Prototype, std::void_t<typename FunctionTraits<Prototype>::IsLValueReferenceQualified>>
	    : std::true_type
	{
	};

	template <typename Prototype, typename = void>
	struct IsFunctionRValueReferenceQualified : std::false_type
	{
	};

	template <typename Prototype>
	struct IsFunctionRValueReferenceQualified<
	    Prototype, std::void_t<typename FunctionTraits<Prototype>::IsRValueReferenceQualified>>
	    : std::true_type
	{
	};

	enum class FunctionTraitsEnum
	{
		ConstQualified = 0x01,
		VolatileQualified = 0x02,
		Noexcept = 0x04,
		LValueReferenceQualified = 0x08,
		RValueReferenceQualified = 0x10
	};

	CAFE_MAKE_ENUM_BITMASK_TYPE(FunctionTraitsEnum);

	template <typename Prototype>
	struct GetFunctionTraitsEnum
	    : std::integral_constant<FunctionTraitsEnum,
	                             ComposeFlags(IsFunctionConstQualified<Prototype>::value
	                                              ? FunctionTraitsEnum::ConstQualified
	                                              : FunctionTraitsEnum{},
	                                          IsFunctionVolatileQualified<Prototype>::value
	                                              ? FunctionTraitsEnum::VolatileQualified
	                                              : FunctionTraitsEnum{},
	                                          IsFunctionNoexcept<Prototype>::value
	                                              ? FunctionTraitsEnum::Noexcept
	                                              : FunctionTraitsEnum{},
	                                          IsFunctionLValueReferenceQualified<Prototype>::value
	                                              ? FunctionTraitsEnum::LValueReferenceQualified
	                                              : FunctionTraitsEnum{},
	                                          IsFunctionRValueReferenceQualified<Prototype>::value
	                                              ? FunctionTraitsEnum::RValueReferenceQualified
	                                              : FunctionTraitsEnum{})>
	{
	};

	namespace Detail
	{
		template <bool IsConstQualified, bool IsVolatileQualified, bool Noexcept,
		          bool IsLValueReferenceQualified, bool IsRValueReferenceQualified, typename ResultType,
		          typename... Args>
		struct MakeFunctionTypeImpl;

		template <typename ResultType, typename... Args>
		struct MakeFunctionTypeImpl<false, false, false, false, false, ResultType, Args...>
		{
			using Result = ResultType(Args...);
		};

		template <typename ResultType, typename... Args>
		struct MakeFunctionTypeImpl<true, false, false, false, false, ResultType, Args...>
		{
			using Result = ResultType(Args...) const;
		};

		template <typename ResultType, typename... Args>
		struct MakeFunctionTypeImpl<false, true, false, false, false, ResultType, Args...>
		{
			using Result = ResultType(Args...) volatile;
		};

		template <typename ResultType, typename... Args>
		struct MakeFunctionTypeImpl<true, true, false, false, false, ResultType, Args...>
		{
			using Result = ResultType(Args...) const volatile;
		};

		template <typename ResultType, typename... Args>
		struct MakeFunctionTypeImpl<false, false, true, false, false, ResultType, Args...>
		{
			using Result = ResultType(Args...) noexcept;
		};

		template <typename ResultType, typename... Args>
		struct MakeFunctionTypeImpl<true, false, true, false, false, ResultType, Args...>
		{
			using Result = ResultType(Args...) const noexcept;
		};

		template <typename ResultType, typename... Args>
		struct MakeFunctionTypeImpl<false, true, true, false, false, ResultType, Args...>
		{
			using Result = ResultType(Args...) volatile noexcept;
		};

		template <typename ResultType, typename... Args>
		struct MakeFunctionTypeImpl<true, true, true, false, false, ResultType, Args...>
		{
			using Result = ResultType(Args...) const volatile noexcept;
		};

		template <typename ResultType, typename... Args>
		struct MakeFunctionTypeImpl<false, false, false, true, false, ResultType, Args...>
		{
			using Result = ResultType(Args...) &;
		};

		template <typename ResultType, typename... Args>
		struct MakeFunctionTypeImpl<true, false, false, true, false, ResultType, Args...>
		{
			using Result = ResultType(Args...) const&;
		};

		template <typename ResultType, typename... Args>
		struct MakeFunctionTypeImpl<false, true, false, true, false, ResultType, Args...>
		{
			using Result = ResultType(Args...) volatile&;
		};

		template <typename ResultType, typename... Args>
		struct MakeFunctionTypeImpl<true, true, false, true, false, ResultType, Args...>
		{
			using Result = ResultType(Args...) const volatile&;
		};

		template <typename ResultType, typename... Args>
		struct MakeFunctionTypeImpl<false, false, true, true, false, ResultType, Args...>
		{
			using Result = ResultType(Args...) & noexcept;
		};

		template <typename ResultType, typename... Args>
		struct MakeFunctionTypeImpl<true, false, true, true, false, ResultType, Args...>
		{
			using Result = ResultType(Args...) const& noexcept;
		};

		template <typename ResultType, typename... Args>
		struct MakeFunctionTypeImpl<false, true, true, true, false, ResultType, Args...>
		{
			using Result = ResultType(Args...) volatile& noexcept;
		};

		template <typename ResultType, typename... Args>
		struct MakeFunctionTypeImpl<true, true, true, true, false, ResultType, Args...>
		{
			using Result = ResultType(Args...) const volatile& noexcept;
		};

		template <typename ResultType, typename... Args>
		struct MakeFunctionTypeImpl<false, false, false, false, true, ResultType, Args...>
		{
			using Result = ResultType(Args...) &&;
		};

		template <typename ResultType, typename... Args>
		struct MakeFunctionTypeImpl<true, false, false, false, true, ResultType, Args...>
		{
			using Result = ResultType(Args...) const&&;
		};

		template <typename ResultType, typename... Args>
		struct MakeFunctionTypeImpl<false, true, false, false, true, ResultType, Args...>
		{
			using Result = ResultType(Args...) volatile&&;
		};

		template <typename ResultType, typename... Args>
		struct MakeFunctionTypeImpl<true, true, false, false, true, ResultType, Args...>
		{
			using Result = ResultType(Args...) const volatile&&;
		};

		template <typename ResultType, typename... Args>
		struct MakeFunctionTypeImpl<false, false, true, false, true, ResultType, Args...>
		{
			using Result = ResultType(Args...) && noexcept;
		};

		template <typename ResultType, typename... Args>
		struct MakeFunctionTypeImpl<true, false, true, false, true, ResultType, Args...>
		{
			using Result = ResultType(Args...) const&& noexcept;
		};

		template <typename ResultType, typename... Args>
		struct MakeFunctionTypeImpl<false, true, true, false, true, ResultType, Args...>
		{
			using Result = ResultType(Args...) volatile&& noexcept;
		};

		template <typename ResultType, typename... Args>
		struct MakeFunctionTypeImpl<true, true, true, false, true, ResultType, Args...>
		{
			using Result = ResultType(Args...) const volatile&& noexcept;
		};
	} // namespace Detail

	template <FunctionTraitsEnum Traits, typename ResultType, typename... Args>
	struct MakeFunctionType
	    : Detail::MakeFunctionTypeImpl<
	          HasAnyFlagsSet(Traits, FunctionTraitsEnum::ConstQualified),
	          HasAnyFlagsSet(Traits, FunctionTraitsEnum::VolatileQualified),
	          HasAnyFlagsSet(Traits, FunctionTraitsEnum::Noexcept),
	          HasAnyFlagsSet(Traits, FunctionTraitsEnum::LValueReferenceQualified),
	          HasAnyFlagsSet(Traits, FunctionTraitsEnum::RValueReferenceQualified), ResultType,
	          Args...>
	{
	};

	template <FunctionTraitsEnum Traits, typename ResultType, typename ArgsTuple>
	struct MakeFunctionTypeFromTuple;

	template <FunctionTraitsEnum Traits, typename ResultType, template <typename...> typename Tuple,
	          typename... Args>
	struct MakeFunctionTypeFromTuple<Traits, ResultType, Tuple<Args...>>
	    : MakeFunctionType<Traits, ResultType, Args...>
	{
	};

	template <typename Prototype>
	class FunctionView
	{
		using PrototypeTraits = FunctionTraits<Prototype>;
		using ForwardFunctionPrototype = typename MakeFunctionTypeFromTuple<
		    GetFunctionTraitsEnum<Prototype>, typename PrototypeTraits::ResultType,
		    decltype(std::tuple_cat(std::tuple<void*>, typename PrototypeTraits::ArgsTuple))>::Result;

	public:
		template <typename Functor>
		constexpr FunctionView(Functor&& functor) : m_OriginFunctionObjectView{}, m_ForwardFunction{}
		{
			if constexpr (std::is_function_v<std::remove_pointer_t<RemoveCvRef<Functor>>>)
			{
				m_OriginFunctionObjectView = +functor;
				m_ForwardFunction = []<typename... Args>(void* objectView, Args&&... args) noexcept(
				    IsFunctionNoexcept<Prototype>::value)
				{
					return reinterpret_cast<decltype(+functor)>(objectView)(std::forward<Args>(args)...);
				};
			}
			else
			{
				m_OriginFunctionObjectView =
				    static_cast<void*>(const_cast<RemoveCvRef<Functor>*>(std::addressof(functor)));
				m_ForwardFunction = []<typename... Args>(void* objectView, Args&&... args) noexcept(
				    IsFunctionNoexcept<Prototype>::value)
				{
					return static_cast<Functor&&>(*static_cast<std::remove_reference_t<Functor>*>(
					    objectView))(std::forward<Args>(args)...);
				};
			}
		}

		template <typename... Args>
		constexpr decltype(auto) operator()(Args&&... args) const noexcept(IsFunctionNoexcept<Prototype>::value)
		{
			return m_ForwardFunction(m_OriginFunctionObjectView, std::forward<Args>(args)...);
		}

		constexpr void* GetOriginFunctionObjectView() const noexcept
		{
			return m_OriginFunctionObjectView;
		}

		constexpr ForwardFunctionPrototype* GetForwardFunctionPointer() const noexcept
		{
			return m_ForwardFunction;
		}

	private:
		void* m_OriginFunctionObjectView;
		ForwardFunctionPrototype* m_ForwardFunction;
	};
} // namespace Cafe::Core::Misc
