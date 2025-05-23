#define CTEST

#include <stdio.h>

#include "ctest.h"
#include "basic_math.h"

Test add_two_numbers()
{
    int a = 1;
    int b = 2;
    int expected = 3;

    int result = add(a, b);

    assertEqual(result, expected);
}

Test subtract_two_numbers()
{
    int a = 1;
    int b = 2;
    int expected = -1;

    int result = subtract(a, b);

    assertEqual(result, expected);
}

Test multiply_two_numbers()
{
    int a = 2;
    int b = 3;
    int expected = 6;

    int result = multiply(a, b);

    assertEqual(result, expected);
}

Test divide_two_numbers()
{
    int a = 6;
    int b = 2;
    int expected = 3;

    int result = divide(a, b);

    assertEqual(result, expected);
}

Test divide_by_zero_throws_error()
{
    int a = 10;
    int b = 0;

    divide(a, b);

    expectException(DIVIDE_BY_ZERO_EXCEPTION);
}

int main()
{
    test_out = stderr;
    START;
    TEST_GROUP(math_lib);
    TEST(add_two_numbers);
    TEST(subtract_two_numbers);
    TEST(multiply_two_numbers);
    TEST(divide_two_numbers);
    TEST(divide_by_zero_throws_error);
    END_GROUP;
    END;
}
