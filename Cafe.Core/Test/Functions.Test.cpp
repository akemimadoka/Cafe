#include <Cafe/Misc/Functions.h>
#include <catch2/catch.hpp>

using namespace Cafe;
using namespace Core;
using namespace Misc;

namespace
{
	using TestFuncPtr = int (*)(const void*, int, int);
	int Test(TestFuncPtr func, const void* opaque, int a, int b)
	{
		return func(opaque, a, b);
	}
} // namespace

TEST_CASE("Cafe.Core.Misc.Functions", "[Core][Misc][Functions]")
{
	SECTION("FunctionPtrBindingBuilder")
	{
		const auto functor = [salt = 10](int a, int b) { return salt + a + b; };
		const auto funcPtr =
		    FunctionPtrBindingBuilder<TestFuncPtr,
		                              0>::ResultFunction<OpaquePtrToFunctorPtr<decltype(functor)>>;
		const auto result = Test(funcPtr, &functor, 1, 2);
		REQUIRE(result == 13);
	}
}
