// bslmf_isarray.h                                                    -*-C++-*-
#ifndef INCLUDED_BSLMF_ISARRAY
#define INCLUDED_BSLMF_ISARRAY

#ifndef INCLUDED_BSLS_IDENT
#include <bsls_ident.h>
#endif
BSLS_IDENT("$Id: $")

//@PURPOSE: Provide a compile-time check for array types.
//
//@CLASSES:
//  bslmf::IsArray: meta-function for detecting array types
//
//@DESCRIPTION: This component defines two meta-functions, 'bsl::is_array' and
// 'BloombergLP::bslmf::IsArray', both of which may be used to query whether a
// type is an array type.
//
// 'bsl::is_array' meets the requirements of the 'is_array' template defined in
// the C++11 standard [meta.unary.cat], while 'bslmf::IsArray' was devised
// before 'is_array' was standardized.
//
// The two meta-functions are functionally equivalent.  The major difference
// between them is that the result for 'bsl::is_array' is indicated by the
// class member 'value', while the result for 'bslmf::IsArray' is indicated by
// the class member 'VALUE'.
//
// Note that 'bsl::is_array' should be preferred over 'bslmf::IsArray', and in
// general, should be used by new components.
//
///Usage
///-----
// In this section we show intended use of this component.
//
///Example 1: Verify Array Types
///- - - - - - - - - - - - - - - -
// Suppose that we want to assert whether a particular type is an Array type.
//
// First, we create two 'typedef's -- an array type and a non-array type:
//..
//  typedef int   MyType;
//  typedef int[] MyArrayType;
//..
// Now, we instantiate the 'bsl::is_array' template for each of the
// 'typedef's and assert the 'value' static data member of each instantiation:
//..
//  assert(false == bsl::is_array<MyType>::value);
//  assert(true == bsl::is_array<MyArrayType>::value);
//..

#ifndef INCLUDED_BSLSCM_VERSION
#include <bslscm_version.h>
#endif

#ifndef INCLUDED_BSLMF_INTEGRALCONSTANT
#include <bslmf_integralconstant.h>
#endif

#ifndef INCLUDED_CSTDDEF
#include <cstddef>       // 'std::size_t'
#define INCLUDED_CSTDDEF
#endif

#ifndef BDE_DONT_ALLOW_TRANSITIVE_INCLUDES

#ifndef INCLUDED_CSTDLIB
#include <cstdlib>  // TBD Robo transitively needs this for 'bsl::atoi', etc.
#define INCLUDED_CSTDLIB
#endif

#endif

namespace bsl {

                         // ===============
                         // struct is_array
                         // ===============

template <typename TYPE>
struct is_array : false_type {
    // This 'struct' template implements the 'is_array' meta-function defined
    // in the C++11 standard [meta.unary.cat] to determine if the (template
    // parameter) 'TYPE' is an array type.  This 'struct' derives from
    // 'bsl::true_type' if the 'TYPE' is an array type, and 'bsl::false_type'
    // otherwise.
};

                         // ====================================
                         // struct is_array<TYPE [NUM_ELEMENTS]>
                         // ====================================

template <typename TYPE, std::size_t NUM_ELEMENTS>
struct is_array<TYPE [NUM_ELEMENTS]> : true_type {
     // This specialization of 'is_array', for when the (template parameter)
     // 'TYPE' is an array of known bound type, derives from 'bsl::true_type'
};

                         // ========================
                         // struct is_array<TYPE []>
                         // ========================

template <typename TYPE>
struct is_array<TYPE []> : true_type {
     // This specialization of 'is_array', for when the (template parameter)
     // 'TYPE' is an array of unknown bound type, derives from 'bsl::true_type'
};

}

namespace BloombergLP {

namespace bslmf {

                         // ==============
                         // struct IsArray
                         // ==============

template <typename TYPE>
struct IsArray  : bsl::is_array<TYPE>::type {
    // This 'struct' template implements a meta-function to determine if the
    // (template parameter) 'TYPE' is an array type.  This 'struct' derives
    // from 'bsl::true_type' if the 'TYPE' is an array type, and
    // 'bsl::false_type' otherwise.
    //
    // Note that although this 'struct' is functionally equivalent to
    // 'bsl::is_array', the use of 'bsl::is_array' should be preferred.
};

}  // close package namespace


}  // close enterprise namespace

#endif

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
