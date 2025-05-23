//***********************************************
// File: ctest.h
//
// Author: Bryce Schultz
//
// Purpose: This file contains the CTest 
// framework for testing C/C++ code. It provides 
// macros for assertions, assessments, and 
// exception handling. It also provides a simple 
// way to run tests and print the results. The 
// framework is designed to be easy to use and 
// understand.
//***********************************************

#pragma once

// includes
#include <stdio.h>
#include <fenv.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define CTEST_VERSION "v1.0"

// status codes
#define PASS 1
#define FAIL 0

// exceptions
#define DIVIDE_BY_ZERO_EXCEPTION FE_DIVBYZERO
#define OVERFLOW_EXCEPTION FE_OVERFLOW
#define UNDERFLOW_EXCEPTION FE_UNDERFLOW
#define INEXACT_EXCEPTION FE_INEXACT
#define INVALID_EXCEPTION FE_INVALID

#define UNUSED(x) (void)(x)

// test type
typedef int Test;

// if we are using the ctest framework
// define these variables
#ifdef CTEST
FILE* test_out = NULL;
int TEST_PASS = 1;
int ALL_TESTS_PASS = 1;
int ALL_GROUPS_PASS = 1;
char manual_yn = '\0';
clock_t test_start_time;
clock_t test_end_time;
#endif

// colors
#define errSetColor(r, g, b) fprintf(stderr, "\033[38;2;%d;%d;%dm", r, g, b)
#define errReserColor() fprintf(stderr, "\033[0m")
#define setColor(r, g, b) if (!test_out) { errSetColor(212, 55, 92); fprintf(stderr, "Set test_out in main: test_out = stderr;\n"); errReserColor(); exit(1); } if (test_out == stderr || test_out == stdout) fprintf(test_out, "\033[38;2;%d;%d;%dm", r, g, b)
#define resetColor() if (test_out == stderr || test_out == stdout) fprintf(test_out, "\033[0m")

// timers
#define start_timer test_start_time = clock()
#define end_timer test_end_time = clock()
#define delta_time ((double)(test_end_time - test_start_time) / CLOCKS_PER_SEC)
#define print_timer fprintf(test_out, "    time: %f\n", delta_time)

// formatting
#define pass(...) setColor(0, 189, 142); fprintf(test_out, __VA_ARGS__); resetColor()
#define fail(...) setColor(212, 55, 92); fprintf(test_out, __VA_ARGS__); resetColor()
#define group(...) setColor(227, 202, 111); fprintf(test_out, __VA_ARGS__); resetColor()
#define end(...) setColor(0, 120, 90); fprintf(test_out, __VA_ARGS__); resetColor()
#define info(...) setColor(200, 200, 200); fprintf(test_out, __VA_ARGS__); resetColor()
#define intro(...) setColor(52, 152, 219); fprintf(test_out, __VA_ARGS__); resetColor()

// printing
#define printEqual(a, b) fprintf(test_out, "    %d == %d\n", a, b)

// user level print
#define tprint(...) fprintf(test_out, "    "); fflush(test_out); info(__VA_ARGS__)

// assertions
#define assertEqual(a, b) if (a == b) { return PASS; } else { fail("    fail %s:%d\n     reason: %s != %s\n",__FILE__, __LINE__, #a, #b); return FAIL; }
#define assertNotEqual(a, b) if (a != b) { return PASS; } else { fail("    fail %s:%d\n     reason: %s == %s\n",__FILE__, __LINE__, #a, #b); return FAIL; }
#define assertGreaterThan(a, b) if (a > b) { return PASS; } else { fail("    fail %s:%d\n     reason: %s <= %s\n",__FILE__, __LINE__, #a, #b); return FAIL; }
#define assertLessThan(a, b) if (a < b) { return PASS; } else { fail("    fail %s:%d\n     reason: %s >= %s\n",__FILE__, __LINE__, #a, #b); return FAIL; }
#define assertGreaterThanOrEqual(a, b) if (a >= b) { return PASS; } else { fail("    fail %s:%d\n     reason: %s < %s\n",__FILE__, __LINE__, #a, #b); return FAIL; }
#define assertLessThanOrEqual(a, b) if (a <= b) { return PASS; } else { fail("    fail %s:%d\n     reason: %s > %s\n",__FILE__, __LINE__, #a, #b); return FAIL; }
#define assertNull(a) if (a == NULL) { return PASS; } else { fail("    fail %s:%d\n     reason: %s != NULL\n", __FILE__, __LINE__, #a); return FAIL; }
#define assertNotNull(a) if (a != NULL) { return PASS; } else { fail("    fail %s:%d\n     reason: %s == NULL\n", __FILE__, __LINE__, #a); return FAIL; }
#define assertStringEqual(a, b) if (strcmp(a, b) == 0) { return PASS; } else { fail("    fail %s:%d\n     reason: %s != %s\n", __FILE__, __LINE__, #a, #b); return FAIL; }
#define assertStringNotEqual(a, b) if (strcmp(a, b) != 0) { return PASS; } else { fail("    fail %s:%d\n     reason: %s == %s\n", __FILE__, __LINE__, #a, #b); return FAIL; }
#define assertTrue(expr) if (expr) { return PASS; } else { fail("    fail %s:%d\n     reason: (%s) != true\n", __FILE__, __LINE__, #expr); return FAIL; }
#define assertFalse(expr) if (!expr) { return PASS; } else { fail("    fail %s:%d\n     reason: (%s) != false\n", __FILE__, __LINE__, #expr); return FAIL; }
#define assertManual() info("pass? y/n: "); while ((manual_yn = getchar()) == '\n') {} if (manual_yn == 'y') { info("\033[A\r"); return PASS; } else { info("\033[A\r"); return FAIL; }
#define assertPassedAllAssessments(_) if (TEST_PASS) { pass("    all assessments passed.\n"); return PASS; } else { fail("    Some assessments failed\n"); TEST_PASS = 1; return FAIL; } 
#define assertFail fail("    Forced fail %s:%d\n", __FILE__, __LINE__); return FAIL;
#define assertPass pass("    Forced pass\n"); return PASS;

// assessments
#define assessEqual(a, b) if (a == b) { pass("    assessment pass %s == %s\n", #a, #b); } else { fail("    assessment fail %s:%d\n     reason: %s != %s\n",__FILE__, __LINE__, #a, #b); TEST_PASS = 0; }
#define assessNotEqual(a, b) if (a != b) { pass("    assessment pass %s != %s\n", #a, #b); } else { fail("    assessment fail %s:%d\n     reason: %s == %s\n",__FILE__, __LINE__, #a, #b); TEST_PASS = 0; }
#define assessGreaterThan(a, b) if (a > b) { pass("    assessment pass %s > %s\n", #a, #b); } else { fail("    assessment fail %s:%d\n     reason: %s <= %s\n",__FILE__, __LINE__, #a, #b); TEST_PASS = 0; }
#define assessLessThan(a, b) if (a < b) { pass("    assessment pass %s < %s\n", #a, #b); } else { fail("    assessment fail %s:%d\n     reason: %s >= %s\n",__FILE__, __LINE__, #a, #b); TEST_PASS = 0; }
#define assessGreaterThanOrEqual(a, b) if (a >= b) { pass("    assessment pass %s >= %s\n", #a, #b); } else { fail("    assessment fail %s:%d\n     reason: %s < %s\n",__FILE__, __LINE__, #a, #b); TEST_PASS = 0; }
#define assessLessThanOrEqual(a, b) if (a <= b) { pass("    assessment pass %s <= %s\n", #a, #b); } else { fail("    assessment fail %s:%d\n     reason: %s > %s\n",__FILE__, __LINE__, #a, #b); TEST_PASS = 0; }
#define assessNull(a) if (a == NULL) { pass("    assessment pass %s == NULL\n", #a); } else { fail("    assessment fail %s:%d\n     reason: %s != NULL\n", __FILE__, __LINE__, #a); TEST_PASS = 0; }
#define assessNotNull(a) if (a != NULL) { pass("    assessment pass %s != NULL\n", #a); } else { fail("    assessment fail %s:%d\n     reason: %s == NULL\n", __FILE__, __LINE__, #a); TEST_PASS = 0; }
#define assessStringEqual(a, b) if (strcmp(a, b) == 0) { pass("    assessment pass %s == %s\n", #a, #b); } else { fail("    assessment fail %s:%d\n     reason: %s != %s\n", __FILE__, __LINE__, #a, #b); TEST_PASS = 0; }
#define assessStringNotEqual(a, b) if (strcmp(a, b) != 0) { pass("    assessment pass %s != %s\n", #a, #b); } else { fail("    assessment fail %s:%d\n     reason: %s == %s\n", __FILE__, __LINE__, #a, #b); TEST_PASS = 0; }
#define assessTrue(expr) if (expr) { pass("    assessment pass %s\n", #expr); } else { fail("    assessment fail %s:%d\n     reason: (%s) != true\n", __FILE__, __LINE__, #expr); TEST_PASS = 0; }
#define assessFalse(expr) if (!expr) { pass("    assessment pass %s\n", #expr); } else { fail("    assessment fail %s:%d\n     reason: (%s) != false\n", __FILE__, __LINE__, #expr); TEST_PASS = 0; }
#define assessManual() info("pass? y/n: "); while ((manual_yn = getchar()) == '\n') {} if (manual_yn == 'y') { info("\033[A\r"); pass("    assessment pass\n"); } else { info("\033[A\r"); fail("    assessment fail\n"); TEST_PASS = 0; }

// exceptions
#define expectException(e) if (fetestexcept(FE_ALL_EXCEPT) == e) { return PASS; } else { fail("     fail %s:%d\n     reason: didn't throw %s\n", __FILE__, __LINE__, #e); return FAIL; }
#define expectExceptionNotThrown(e) if (fetestexcept(FE_ALL_EXCEPT) != e) { return PASS; } else { fail("     fail %s:%d\n     reason: threw %s\n", __FILE__, __LINE__, #e); return FAIL; }

// main test run macro
#define TEST(fn) fprintf(test_out, "    running test: %s\n", #fn); if (fn()) { info("    %s ", #fn); pass("passed.\n\n"); } else { info("    %s ", #fn); fail("failed.\n\n"); ALL_TESTS_PASS = 0; ALL_GROUPS_PASS = 0; }
#define START intro("-----------------------------------------\n"); intro("          CTest Framework " CTEST_VERSION "\n"); intro("-----------------------------------------\n");
#define END if(ALL_GROUPS_PASS) { pass("-----------------------------------------\n"); pass("            All tests passed.\n"); pass("-----------------------------------------\n"); } else { fail("-----------------------------------------\n"); fail("           Some tests failed.\n"); fail("-----------------------------------------\n"); }

// groups
#define TEST_GROUP(name) ALL_TESTS_PASS = 1; group("-----------------------------------------\n%s\n-----------------------------------------\n", #name);
#define END_GROUP if (ALL_TESTS_PASS) { pass("    All tests in the group passed.\n"); } else { fail("    Some tests in the group failed.\n"); } group("-----------------------------------------\n\n");
