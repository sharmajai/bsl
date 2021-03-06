// bslmf_isarray.t.cpp                                                -*-C++-*-

#include <bslmf_isarray.h>

#include <bsls_bsltestutil.h>
#include <bsls_platform.h>            // for testing only

#include <cstdlib>
#include <cstdio>

using namespace BloombergLP;
using namespace std;

//=============================================================================
//                                TEST PLAN
//-----------------------------------------------------------------------------
//                                Overview
//                                --------
// The component under test defines two meta-functions, 'bsl::is_array' and
// 'bslmf::IsArray', that determine whether a template parameter type is an
// array type.  Thus, we need to ensure that the values returned by these
// meta-functions are correct for each possible category of types.  Since the
// two meta-functions are functionally equivalent, we will use the same set of
// types for both.
//
//-----------------------------------------------------------------------------
// [ 2] BloombergLP::bslmf::IsPointer
// [ 1] bsl::is_pointer
//
// ----------------------------------------------------------------------------
// [ 3] USAGE EXAMPLE

//=============================================================================
//                       STANDARD BDE ASSERT TEST MACRO
//-----------------------------------------------------------------------------
// NOTE: THIS IS A LOW-LEVEL COMPONENT AND MAY NOT USE ANY C++ LIBRARY
// FUNCTIONS, INCLUDING IOSTREAMS.
static int testStatus = 0;

void aSsErT(bool b, const char *s, int i)
{
    if (b) {
        printf("Error " __FILE__ "(%d): %s    (failed)\n", i, s);
        if (testStatus >= 0 && testStatus <= 100) ++testStatus;
    }
}

# define ASSERT(X) { aSsErT(!(X), #X, __LINE__); }

//=============================================================================
//                       STANDARD BDE TEST DRIVER MACROS
//-----------------------------------------------------------------------------
#define LOOP_ASSERT  BSLS_BSLTESTUTIL_LOOP_ASSERT
#define LOOP2_ASSERT BSLS_BSLTESTUTIL_LOOP2_ASSERT
#define LOOP3_ASSERT BSLS_BSLTESTUTIL_LOOP3_ASSERT
#define LOOP4_ASSERT BSLS_BSLTESTUTIL_LOOP4_ASSERT
#define LOOP5_ASSERT BSLS_BSLTESTUTIL_LOOP5_ASSERT
#define LOOP6_ASSERT BSLS_BSLTESTUTIL_LOOP6_ASSERT

#define Q   BSLS_BSLTESTUTIL_Q   // Quote identifier literally.
#define P   BSLS_BSLTESTUTIL_P   // Print identifier and value.
#define P_  BSLS_BSLTESTUTIL_P_  // P(X) without '\n'.
#define T_  BSLS_BSLTESTUTIL_T_  // Print a tab (w/o newline).
#define L_  BSLS_BSLTESTUTIL_L_  // current Line number

//=============================================================================
//                  GLOBAL TYPEDEFS/CONSTANTS FOR TESTING
//-----------------------------------------------------------------------------

enum Enum {};

struct Struct {
    int a[4];
};

union Union {
    int  i;
    char a[sizeof(int)];
};

//=============================================================================
//                              MAIN PROGRAM
//-----------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    int test = argc > 1 ? atoi(argv[1]) : 0;
    int verbose = argc > 2;
    // int veryVerbose = argc > 3;

    printf("TEST " __FILE__ " CASE %d\n", test);

    switch (test) { case 0:  // Zero is always the leading case.
      case 3: {
        // --------------------------------------------------------------------
        // USAGE EXAMPLE
        //   Simple example illustrating use of 'bslmf::IsArray'.
        //
        // Concerns:
        //
        // Plan:
        //
        // Tactics:
        //   - Add-Hoc Data Selection Method
        //   - Brute-Force implementation technique
        //
        // Testing:
        //   USAGE EXAMPLE
        // --------------------------------------------------------------------

        if (verbose) printf("\nUSAGE EXAMPLE\n"
                            "\n=============\n");

///Usage
///-----
// For example:
//..
     ASSERT(1 == bslmf::IsArray<int    [5]>::value);
     ASSERT(0 == bslmf::IsArray<int  *    >::value);
     ASSERT(0 == bslmf::IsArray<int (*)[5]>::value);
//..

      } break;
      case 2: {
        // --------------------------------------------------------------------
        // Test Plan:
        //   Instantiate 'bslmf::IsArray' with various types and verify
        //   that their 'value' member is initialized properly.
        //
        // Testing:
        //   bslmf::IsArray
        // --------------------------------------------------------------------

        if (verbose) printf("\nbslmf::IsArray\n"
                            "\n==============\n");

        ASSERT(1 == bslmf::IsArray<char          [1]>::VALUE);
        ASSERT(1 == bslmf::IsArray<char const    [1]>::VALUE);
        ASSERT(0 == bslmf::IsArray<char       (&)[1]>::VALUE);
        ASSERT(0 == bslmf::IsArray<char             >::VALUE);
        ASSERT(0 == bslmf::IsArray<char const       >::VALUE);
        ASSERT(0 == bslmf::IsArray<char        *    >::VALUE);

        ASSERT(1 == bslmf::IsArray<void       *   [2]>::VALUE);
        ASSERT(1 == bslmf::IsArray<void const *   [2]>::VALUE);
        ASSERT(0 == bslmf::IsArray<void       *(&)[2]>::VALUE);
        ASSERT(0 == bslmf::IsArray<void       *      >::VALUE);
        ASSERT(0 == bslmf::IsArray<void              >::VALUE);

        ASSERT(1 == bslmf::IsArray<int                [3]>::VALUE);
        ASSERT(1 == bslmf::IsArray<int const          [3]>::VALUE);
        ASSERT(1 == bslmf::IsArray<int volatile       [3]>::VALUE);
        ASSERT(1 == bslmf::IsArray<int const volatile [3]>::VALUE);
        ASSERT(0 == bslmf::IsArray<int                   >::VALUE);
        ASSERT(0 == bslmf::IsArray<int const             >::VALUE);
        ASSERT(0 == bslmf::IsArray<int volatile          >::VALUE);
        ASSERT(0 == bslmf::IsArray<int const volatile    >::VALUE);

        ASSERT(0 == bslmf::IsArray<int                (&)[4]>::VALUE);
        ASSERT(0 == bslmf::IsArray<int const          (&)[4]>::VALUE);
        ASSERT(0 == bslmf::IsArray<int volatile       (&)[4]>::VALUE);
        ASSERT(0 == bslmf::IsArray<int const volatile (&)[4]>::VALUE);
        ASSERT(0 == bslmf::IsArray<int                 &    >::VALUE);
        ASSERT(0 == bslmf::IsArray<int const           &    >::VALUE);
        ASSERT(0 == bslmf::IsArray<int volatile        &    >::VALUE);
        ASSERT(0 == bslmf::IsArray<int const volatile  &    >::VALUE);

        ASSERT(1 == bslmf::IsArray<int                 * [5]>::VALUE);
        ASSERT(1 == bslmf::IsArray<int const           * [5]>::VALUE);
        ASSERT(1 == bslmf::IsArray<int volatile        * [5]>::VALUE);
        ASSERT(1 == bslmf::IsArray<int const volatile  * [5]>::VALUE);
        ASSERT(0 == bslmf::IsArray<int                (*)[5]>::VALUE);
        ASSERT(0 == bslmf::IsArray<int const          (*)[5]>::VALUE);
        ASSERT(0 == bslmf::IsArray<int volatile       (*)[5]>::VALUE);
        ASSERT(0 == bslmf::IsArray<int const volatile (*)[5]>::VALUE);
        ASSERT(0 == bslmf::IsArray<int                 *    >::VALUE);
        ASSERT(0 == bslmf::IsArray<int const           *    >::VALUE);
        ASSERT(0 == bslmf::IsArray<int volatile        *    >::VALUE);
        ASSERT(0 == bslmf::IsArray<int const volatile  *    >::VALUE);

        ASSERT(1 == bslmf::IsArray<int         [6][6]>::VALUE);
        ASSERT(1 == bslmf::IsArray<int const   [6][6]>::VALUE);
        ASSERT(0 == bslmf::IsArray<int      (&)[6][6]>::VALUE);
        ASSERT(1 == bslmf::IsArray<int       * [6][6]>::VALUE);
        ASSERT(0 == bslmf::IsArray<int      (*)[6][6]>::VALUE);

        ASSERT(1 == bslmf::IsArray<int *const    [6][6]>::VALUE);
        ASSERT(0 == bslmf::IsArray<int *const (&)[6][6]>::VALUE);
        ASSERT(0 == bslmf::IsArray<int *const (*)[6][6]>::VALUE);

        ASSERT(1 == bslmf::IsArray<void *[]>::VALUE);

        ASSERT(1 == bslmf::IsArray<int                []>::VALUE);
        ASSERT(1 == bslmf::IsArray<int const          []>::VALUE);
        ASSERT(1 == bslmf::IsArray<int volatile       []>::VALUE);
        ASSERT(1 == bslmf::IsArray<int const volatile []>::VALUE);

        ASSERT(1 == bslmf::IsArray<int                 * []>::VALUE);
        ASSERT(1 == bslmf::IsArray<int const           * []>::VALUE);
        ASSERT(1 == bslmf::IsArray<int volatile        * []>::VALUE);
        ASSERT(1 == bslmf::IsArray<int const volatile  * []>::VALUE);
        ASSERT(0 == bslmf::IsArray<int                (*)[]>::VALUE);
        ASSERT(0 == bslmf::IsArray<int const          (*)[]>::VALUE);
        ASSERT(0 == bslmf::IsArray<int volatile       (*)[]>::VALUE);
        ASSERT(0 == bslmf::IsArray<int const volatile (*)[]>::VALUE);

        ASSERT(1 == bslmf::IsArray<int          [][7]>::VALUE);
        ASSERT(1 == bslmf::IsArray<int const    [][7]>::VALUE);
        ASSERT(1 == bslmf::IsArray<int        * [][7]>::VALUE);
        ASSERT(0 == bslmf::IsArray<int       (*)[][7]>::VALUE);

        ASSERT(1 == bslmf::IsArray<int *const    [][7]>::VALUE);
        ASSERT(0 == bslmf::IsArray<int *const (*)[][7]>::VALUE);

        ASSERT(1 == bslmf::IsArray<Enum          [8]>::VALUE);
        ASSERT(0 == bslmf::IsArray<Enum       (&)[8]>::VALUE);
        ASSERT(0 == bslmf::IsArray<Enum const (&)[8]>::VALUE);
        ASSERT(0 == bslmf::IsArray<Enum             >::VALUE);

        ASSERT(1 == bslmf::IsArray<Struct    [8]>::VALUE);
        ASSERT(0 == bslmf::IsArray<Struct (&)[8]>::VALUE);
        ASSERT(0 == bslmf::IsArray<Struct       >::VALUE);

        ASSERT(1 == bslmf::IsArray<Union    [8]>::VALUE);
        ASSERT(0 == bslmf::IsArray<Union (&)[8]>::VALUE);
        ASSERT(0 == bslmf::IsArray<Union       >::VALUE);

        ASSERT(0 == bslmf::IsArray<int  Struct::*    >::VALUE);
        ASSERT(0 == bslmf::IsArray<int (Struct::*)[9]>::VALUE);
      } break;
      case 1: {
        // --------------------------------------------------------------------
        // Test Plan:
        //   Instantiate 'bsl::is_array' with various types and verify
        //   that their 'value' member is initialized properly.
        //
        // Testing:
        //   bsl::is_array
        // --------------------------------------------------------------------

        if (verbose) printf("\nbsl::is_array\n"
                            "\n=============\n");

        ASSERT(1 == bsl::is_array<char          [1]>::value);
        ASSERT(1 == bsl::is_array<char const    [1]>::value);
        ASSERT(0 == bsl::is_array<char       (&)[1]>::value);
        ASSERT(0 == bsl::is_array<char             >::value);
        ASSERT(0 == bsl::is_array<char const       >::value);
        ASSERT(0 == bsl::is_array<char        *    >::value);

        ASSERT(1 == bsl::is_array<void       *   [2]>::value);
        ASSERT(1 == bsl::is_array<void const *   [2]>::value);
        ASSERT(0 == bsl::is_array<void       *(&)[2]>::value);
        ASSERT(0 == bsl::is_array<void       *      >::value);
        ASSERT(0 == bsl::is_array<void              >::value);

        ASSERT(1 == bsl::is_array<int                [3]>::value);
        ASSERT(1 == bsl::is_array<int const          [3]>::value);
        ASSERT(1 == bsl::is_array<int volatile       [3]>::value);
        ASSERT(1 == bsl::is_array<int const volatile [3]>::value);
        ASSERT(0 == bsl::is_array<int                   >::value);
        ASSERT(0 == bsl::is_array<int const             >::value);
        ASSERT(0 == bsl::is_array<int volatile          >::value);
        ASSERT(0 == bsl::is_array<int const volatile    >::value);

        ASSERT(0 == bsl::is_array<int                (&)[4]>::value);
        ASSERT(0 == bsl::is_array<int const          (&)[4]>::value);
        ASSERT(0 == bsl::is_array<int volatile       (&)[4]>::value);
        ASSERT(0 == bsl::is_array<int const volatile (&)[4]>::value);
        ASSERT(0 == bsl::is_array<int                 &    >::value);
        ASSERT(0 == bsl::is_array<int const           &    >::value);
        ASSERT(0 == bsl::is_array<int volatile        &    >::value);
        ASSERT(0 == bsl::is_array<int const volatile  &    >::value);

        ASSERT(1 == bsl::is_array<int                 * [5]>::value);
        ASSERT(1 == bsl::is_array<int const           * [5]>::value);
        ASSERT(1 == bsl::is_array<int volatile        * [5]>::value);
        ASSERT(1 == bsl::is_array<int const volatile  * [5]>::value);
        ASSERT(0 == bsl::is_array<int                (*)[5]>::value);
        ASSERT(0 == bsl::is_array<int const          (*)[5]>::value);
        ASSERT(0 == bsl::is_array<int volatile       (*)[5]>::value);
        ASSERT(0 == bsl::is_array<int const volatile (*)[5]>::value);
        ASSERT(0 == bsl::is_array<int                 *    >::value);
        ASSERT(0 == bsl::is_array<int const           *    >::value);
        ASSERT(0 == bsl::is_array<int volatile        *    >::value);
        ASSERT(0 == bsl::is_array<int const volatile  *    >::value);

        ASSERT(1 == bsl::is_array<int         [6][6]>::value);
        ASSERT(1 == bsl::is_array<int const   [6][6]>::value);
        ASSERT(0 == bsl::is_array<int      (&)[6][6]>::value);
        ASSERT(1 == bsl::is_array<int       * [6][6]>::value);
        ASSERT(0 == bsl::is_array<int      (*)[6][6]>::value);

        ASSERT(1 == bsl::is_array<int *const    [6][6]>::value);
        ASSERT(0 == bsl::is_array<int *const (&)[6][6]>::value);
        ASSERT(0 == bsl::is_array<int *const (*)[6][6]>::value);

        ASSERT(1 == bsl::is_array<void *[]>::value);

        ASSERT(1 == bsl::is_array<int                []>::value);
        ASSERT(1 == bsl::is_array<int const          []>::value);
        ASSERT(1 == bsl::is_array<int volatile       []>::value);
        ASSERT(1 == bsl::is_array<int const volatile []>::value);

        ASSERT(1 == bsl::is_array<int                 * []>::value);
        ASSERT(1 == bsl::is_array<int const           * []>::value);
        ASSERT(1 == bsl::is_array<int volatile        * []>::value);
        ASSERT(1 == bsl::is_array<int const volatile  * []>::value);
        ASSERT(0 == bsl::is_array<int                (*)[]>::value);
        ASSERT(0 == bsl::is_array<int const          (*)[]>::value);
        ASSERT(0 == bsl::is_array<int volatile       (*)[]>::value);
        ASSERT(0 == bsl::is_array<int const volatile (*)[]>::value);

        ASSERT(1 == bsl::is_array<int          [][7]>::value);
        ASSERT(1 == bsl::is_array<int const    [][7]>::value);
        ASSERT(1 == bsl::is_array<int        * [][7]>::value);
        ASSERT(0 == bsl::is_array<int       (*)[][7]>::value);

        ASSERT(1 == bsl::is_array<int *const    [][7]>::value);
        ASSERT(0 == bsl::is_array<int *const (*)[][7]>::value);

        ASSERT(1 == bsl::is_array<Enum          [8]>::value);
        ASSERT(0 == bsl::is_array<Enum       (&)[8]>::value);
        ASSERT(0 == bsl::is_array<Enum const (&)[8]>::value);
        ASSERT(0 == bsl::is_array<Enum             >::value);

        ASSERT(1 == bsl::is_array<Struct    [8]>::value);
        ASSERT(0 == bsl::is_array<Struct (&)[8]>::value);
        ASSERT(0 == bsl::is_array<Struct       >::value);

        ASSERT(1 == bsl::is_array<Union    [8]>::value);
        ASSERT(0 == bsl::is_array<Union (&)[8]>::value);
        ASSERT(0 == bsl::is_array<Union       >::value);

        ASSERT(0 == bsl::is_array<int  Struct::*    >::value);
        ASSERT(0 == bsl::is_array<int (Struct::*)[9]>::value);
      } break;
      default: {
        fprintf(stderr, "WARNING: CASE `%d' NOT FOUND.\n", test);
        testStatus = -1;
      }
    }

    if (testStatus > 0) {
        fprintf(stderr, "Error, non-zero test status = %d.\n", testStatus);
    }
    return testStatus;
}

// ----------------------------------------------------------------------------
// Copyright (C) 2012 Bloomberg L.P.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
// ----------------------------- END-OF-FILE ----------------------------------
