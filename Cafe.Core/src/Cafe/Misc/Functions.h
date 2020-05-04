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

	namespace Detail
	{
		template <typename RetType, typename FunctorMapper, std::size_t N, typename ArgsTuple,
		          typename OpaqueType = void, typename HeadTuple = std::tuple<>,
		          typename TailTuple = std::tuple<>>
		struct FunctionPtrBindingInfoImpl;

		template <typename RetType, typename FunctorMapper, std::size_t N, typename Arg,
		          typename... Args, typename... HeadType>
		struct FunctionPtrBindingInfoImpl<RetType, FunctorMapper, N, std::tuple<Arg, Args...>, void,
		                                  std::tuple<HeadType...>>
		    : FunctionPtrBindingInfoImpl<RetType, FunctorMapper, N == std::size_t(-1) ? N : N - 1,
		                                 std::tuple<Args...>, std::tuple<HeadType..., Arg>>
		{
		};

		template <typename RetType, typename FunctorMapper, typename Arg, typename... Args,
		          typename... HeadType>
		struct FunctionPtrBindingInfoImpl<RetType, FunctorMapper, 0, std::tuple<Arg, Args...>, void,
		                                  std::tuple<HeadType...>>
		    : FunctionPtrBindingInfoImpl<RetType, FunctorMapper, 0, std::tuple<>, Arg,
		                                 std::tuple<HeadType...>, std::tuple<Args...>>
		{
		};

		template <typename RetType, typename FunctorMapper, typename OpaqueType, typename... HeadType,
		          typename... TailType>
		struct FunctionPtrBindingInfoImpl<RetType, FunctorMapper, 0, std::tuple<>, OpaqueType,
		                                  std::tuple<HeadType...>, std::tuple<TailType...>>
		{
			static constexpr RetType ResultFunction(HeadType... head, OpaqueType opaque, TailType... tail)
			{
				return static_cast<RetType>(
				    FunctorMapper::Cast(opaque)(std::move(head)..., std::move(tail)...));
			}
		};

		template <std::size_t N, typename ArgsTuple>
		struct FunctionPtrBindingInfo;
	} // namespace Detail

	template <typename Functor>
	struct OpaquePtrToFunctorPtr
	{
		template <typename OpaquePtr>
		static constexpr Functor& Cast(OpaquePtr opaque)
		{
			return *static_cast<Functor*>(opaque);
		}
	};

	template <typename FuncPtrType, std::size_t OpaqueParamIndex>
	struct FunctionPtrBindingBuilder;

	template <typename RetType, typename... ArgsType, std::size_t OpaqueParamIndex>
	struct FunctionPtrBindingBuilder<RetType (*)(ArgsType...), OpaqueParamIndex>
	{
		template <typename FunctorMapper>
		static constexpr auto ResultFunction =
		    Detail::FunctionPtrBindingInfoImpl<RetType, FunctorMapper, OpaqueParamIndex,
		                                       std::tuple<ArgsType...>>::ResultFunction;
	};
} // namespace Cafe::Core::Misc
