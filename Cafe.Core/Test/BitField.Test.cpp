#include <Cafe/Misc/BitField.h>
#include <catch2/catch.hpp>

using namespace Cafe;
using namespace Core;
using namespace Misc;

TEST_CASE("Cafe.Core.Misc.BitField", "[Core][Misc][BitField]")
{
	SECTION("BitField")
	{
		using Field1 = BitField<2, 4>;
		// 0b0001000100100010001100110100010001010101011001100111011110001000
		constexpr std::uint64_t source = 0x1122334455667788;

		constexpr auto field1Value = Field1::Decode(source);
		REQUIRE(field1Value == 0b0010);

		constexpr auto allClearedValue = Field1::ClearAll(source);
		REQUIRE(allClearedValue == 0b0001000100100010001100110100010001010101011001100111011110000000);

		constexpr auto field1UpdateValue = 0b0100;
		constexpr auto updatedValue = Field1::Update(allClearedValue, field1UpdateValue);
		REQUIRE(updatedValue == 0b0001000100100010001100110100010001010101011001100111011110010000);

        constexpr auto field1ComposeValue = 0b1000;
        constexpr auto composedValue = Field1::Compose(updatedValue, field1ComposeValue);
        REQUIRE(composedValue == 0b0001000100100010001100110100010001010101011001100111011110110000);

        constexpr auto clearedValue = Field1::Clear(composedValue, field1UpdateValue);
        REQUIRE(clearedValue == 0b0001000100100010001100110100010001010101011001100111011110100000);
	}
}
