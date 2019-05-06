#pragma once

#include "TypeTraits.h"
#include <cassert>

namespace Cafe::Core::Misc::Math
{
	/// @brief  计算乘幂
	/// @remark 仅适用于 exp 是正整数的情况
	template <typename TBase, typename TExp>
	constexpr std::enable_if_t<std::is_integral_v<TExp>, TBase> Pow(TBase base, TExp exp) noexcept
	{
		if (exp == TExp{})
		{
			return TBase{ 1 };
		}

		assert(exp > 0);

		TBase result{ 1 };
		while (exp--)
		{
			result *= base;
		}

		return result;
	}
} // namespace Cafe::Core::Misc::Math
