#pragma once

#include "TypeTraits.h"
#include <climits>
#include <cstddef>

namespace Cafe::Core::Misc
{
	using BitCountType = UnsignedMinTypeToHold<sizeof(std::uintmax_t) * CHAR_BIT>;

	template <BitCountType Pos, BitCountType Count,
	          typename FieldTypeParam = UnsignedMinTypeToHold<(std::uintmax_t(1) << Count) - 1>>
	struct BitField
	{
		using FieldType = FieldTypeParam;
		static constexpr FieldType FieldMaskWithoutShift =
		    static_cast<FieldType>((std::uintmax_t(1) << Count) - 1);
		static constexpr std::uintmax_t FieldMask =
		    static_cast<std::uintmax_t>(FieldMaskWithoutShift) << Pos;

		template <typename SourceType>
		static constexpr FieldType Decode(SourceType source)
		{
			return static_cast<FieldType>((source & FieldMask) >> Pos);
		}

		static constexpr bool CheckInRange(FieldType field)
		{
			return (field & ~FieldMaskWithoutShift) == FieldType();
		}

		template <typename SourceType>
		static constexpr SourceType Encode(FieldType field)
		{
			return static_cast<SourceType>(field) << Pos;
		}

		template <typename SourceType>
		static constexpr SourceType ClearAll(SourceType source)
		{
			return source & ~static_cast<SourceType>(FieldMask);
		}

		template <typename SourceType>
		static constexpr SourceType Compose(SourceType source, FieldType field)
		{
			return source | Encode<SourceType>(field);
		}

		template <typename SourceType>
		static constexpr SourceType Clear(SourceType source, FieldType field)
		{
			return source & ~Encode<SourceType>(field);
		}

		template <typename SourceType>
		static constexpr SourceType Update(SourceType source, FieldType field)
		{
			return ClearAll(source) | Encode<SourceType>(field);
		}
	};
} // namespace Cafe::Core::Misc
