#include <Cafe/Misc/TypeTraits.h>

using namespace Cafe;
using namespace Core;
using namespace Misc;

static_assert(std::is_same_v<FindFirst<BindFrontTrait<std::is_same, int>::template Result, bool, int, double>, int>);
static_assert(std::is_same_v<FindFirstOr<BindFrontTrait<std::is_same, float>::template Result, void, bool, int, double>, void>);
