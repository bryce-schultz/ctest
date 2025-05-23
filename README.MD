# ctest

A basic C test library for writing and running unit tests in C projects.

## Features

- Simple API for defining and running tests
- Minimal dependencies
- Clear output for test results

## Usage
1. Add ctest.h to your project
2. Write some tests

### The Bare Minimum
```c
#define CTEST // <-- needed for the implementation

#include <stdio.h>
#include "ctest.h"

Test add_two_numbers() 
{
    int expected = 42;
    int actual = 40 + 2;
    assertEqual(expected, actual);
}

int main()
{
    test_out = stderr;
    TEST(add_two_numbers);
}
```

3. Build and run your test executable.

### Sample Output

```
    running test: add_two_numbers
    add_two_numbers passed.
```

## Test Groups

Test groups allow sets of tests to be run together sharing a group passing status

### Groups
```c
#define CTEST

#include <stdio.h>

#include "ctest.h"

Test add_two_numbers()
{
    int a = 1;
    int b = 2;
    int expected = 3;

    int result = a + b;

    assertEqual(result, expected);
}

Test subtract_two_numbers()
{
    int a = 1;
    int b = 2;
    int expected = -1;

    int result = a - b;

    assertEqual(result, expected);
}

int main()
{
    test_out = stderr;
    START;
    TEST_GROUP(math_lib);
    TEST(add_two_numbers);
    TEST(subtract_two_numbers);
    END_GROUP;
    END;
}
```
### Output
```
-----------------------------------------
          CTest Framework v1.0
-----------------------------------------
-----------------------------------------
math_lib
-----------------------------------------
    running test: add_two_numbers
    add_two_numbers passed.

    running test: subtract_two_numbers
    subtract_two_numbers passed.

    All tests in the group passed.
-----------------------------------------

-----------------------------------------
            All tests passed.
-----------------------------------------
```