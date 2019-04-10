#pragma once

#define CAFE_CONCAT_IMPL(a, b) a##b
#define CAFE_CONCAT(a, b) CAFE_CONCAT_IMPL(a, b)

#define CAFE_STRINGIFY_IMPL(a) #a
#define CAFE_STRINGIFY(a) CAFE_STRINGIFY_IMPL(a)

#define CAFE_GET_HEAD(a, ...) a
#define CAFE_GET_TAIL(a, ...) __VA_ARGS__

#define CAFE_EXPAND_OR_IMPL(replacement, ...) CAFE_GET_HEAD(__VA_ARGS__ __VA_OPT__(,) replacement)
#define CAFE_EXPAND_OR(replacement, a) CAFE_EXPAND_OR_IMPL(replacement, a)

#define CAFE_ISEMPTY(...) CAFE_EXPAND_OR(true, __VA_OPT__(false))

#define CAFE_IF_IMPL_true(a, b) a
#define CAFE_IF_IMPL_1(a, b) a
#define CAFE_IF_IMPL_false(a, b) b
#define CAFE_IF_IMPL_0(a, b) b
#define CAFE_IF(cond, a, b) CAFE_CONCAT(CAFE_IF_IMPL_, cond)(a, b)

#define CAFE_NOT(a) CAFE_IF(a, false, true)
#define CAFE_AND(a, b) CAFE_IF(a, b, a)
#define CAFE_OR(a, b) CAFE_IF(a, a, b)

#define CAFE_BOOL_LITERAL_TO_01(a) CAFE_IF(a, 1, 0)
#define CAFE_01_TO_BOOL_LITERAL(a) CAFE_IF(a, true, false)

#define CAFE_HAS_MULTIPLE_ARGUMENT(...) CAFE_IF(CAFE_ISEMPTY(__VA_ARGS__), false, CAFE_ISEMPTY(CAFE_GET_TAIL(__VA_ARGS__)))
