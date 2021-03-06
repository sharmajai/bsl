// bslstl_stringstream.h                                              -*-C++-*-
#ifndef INCLUDED_BSLSTL_STRINGSTREAM
#define INCLUDED_BSLSTL_STRINGSTREAM

#ifndef INCLUDED_BSLS_IDENT
#include <bsls_ident.h>
#endif
BSLS_IDENT("$Id: $")

//@PURPOSE: Provide a C++03-compatible 'stringstream' class.
//
//@CLASSES:
//  bsl::stringstream: C++03-compatible 'stringstream' class
//
//@SEE_ALSO:
//
//@DESCRIPTION: This component is for internal use only.  Please include
// '<bsl_sstream.h>' instead.
//
// This component defines a class template, 'bsl::basic_stringstream',
// implementing a standard stream that provides a constructor and
// manipulator ('str') that allow clients to directly set the internal sequence
// of characters that is accessed (or modified) by the stream, as well as an
// accessor ('str') for obtaining a string having the same sequence of
// characters to which the stream currently refers (see 27.8.5 [stringstream]
// of the C++11 standard).  This component also defines two standard aliases,
// 'bsl::stringstream' and 'bsl::wstringstream', that refer to specializations
// of the 'bsl::basic_stringstream' template for 'char' and 'wchar_t' types,
// respectively.  The 'bsl::basic_stringstream' template has three parameters,
// 'CHAR_TYPE', 'CHAR_TRAITS', and 'ALLOCATOR'.  The 'CHAR_TYPE' and
// 'CHAR_TRAITS' parameters respectively define the character type for the
// string-stream and a type providing a set of operations the string-stream
// will use to manipulate characters of that type, which must meet the
// character traits requirements defined by the C++11 standard, 21.2
// [char.traits].  The 'ALLOCATOR' template parameter is described in the
// "Memory Allocation" section below.
//
///Memory Allocation
///-----------------
// The type supplied as a string-stream's 'ALLOCATOR' template parameter
// determines how that string-stream will allocate memory.  The
// 'basic_stringstream' template supports allocators meeting the requirements
// of the C++11 standard, 17.6.3.5 [allocator.requirements]; in addition, it
// supports scoped-allocators derived from the 'bslma::Allocator' memory
// allocation protocol.  Clients intending to use 'bslma'-style allocators
// should use 'bsl::allocator', which provides a C++11 standard-compatible
// adapter for a 'bslma::Allocator' object.  Note that the standard aliases
// 'bsl::stringstream' and 'bsl::wstringstream' both use 'bsl::allocator'.
//
///'bslma'-Style Allocators
/// - - - - - - - - - - - -
// If the type supplied for the 'ALLOCATOR' template parameter of an
// 'stringstream' instantiation is 'bsl::allocator', then objects of that
// string-stream type will conform to the standard behavior of a
// 'bslma'-allocator-enabled type.  Such a string-stream accepts an optional
// 'bslma::Allocator' argument at construction.  If the address of a
// 'bslma::Allocator' object is explicitly supplied at construction, it will be
// used to supply memory for the string-stream throughout its lifetime;
// otherwise, the string-stream will use the default allocator installed at the
// time of the string-stream's construction (see 'bslma_default').
//
///Usage
///-----
// This section illustrates intended use of this component.
//
///Example 1: Basic Input and Output Operations
/// - - - - - - - - - - - - - - - - - - - - - -
// The following example demonstrates the use of 'bsl::stringstream' to read
// and write data of various types to a 'bsl::string' object.
//
// Suppose we want to implement a simplified converter between a pair of
// generic types, 'TYPE1' and 'TYPE2'.  We use 'bsl::stringstream' to implement
// the 'lexicalCast' function.  We write the data of type 'TYPE1' into the
// stream with 'operator<<' and then read it back as the data of 'TYPE2' with
// 'operator>>':
//..
//  template <class TYPE2, class TYPE1>
//  TYPE2 lexicalCast(const TYPE1& what)
//  {
//      bsl::stringstream converter;
//      converter << what;
//
//      TYPE2 val;
//      converter >> val;
//      return val;
//  }
//..
// Finally, we verify that the 'lexicalCast' function works on some simple test
// cases:
//..
//  assert(lexicalCast<int>("1234") == 1234);
//
//  assert(lexicalCast<short>("-5") == -5);
//
//  assert(lexicalCast<bsl::string>("abc") == "abc");
//
//  assert(lexicalCast<bsl::string>(1234) == "1234");
//
//  assert(lexicalCast<short>(-5) == -5);
//..

// Prevent 'bslstl' headers from being included directly in 'BSL_OVERRIDES_STD'
// mode.  Doing so is unsupported, and is likely to cause compilation errors.
#if defined(BSL_OVERRIDES_STD) && !defined(BSL_STDHDRS_PROLOGUE_IN_EFFECT)
#error "include <bsl_sstream.h> instead of <bslstl_stringstream.h> in \
BSL_OVERRIDES_STD mode"
#endif

#ifndef INCLUDED_BSLSCM_VERSION
#include <bslscm_version.h>
#endif

#ifndef INCLUDED_BSLSTL_STRING
#include <bslstl_string.h>
#endif

#ifndef INCLUDED_BSLSTL_STRINGBUF
#include <bslstl_stringbuf.h>
#endif

#ifndef INCLUDED_BSLALG_TYPETRAITS
#include <bslalg_typetraits.h>
#endif

#ifndef INCLUDED_BSLALG_TYPETRAITUSESBSLMAALLOCATOR
#include <bslalg_typetraitusesbslmaallocator.h>
#endif

#ifndef INCLUDED_IOS
#include <ios>
#define INCLUDED_IOS
#endif

#ifndef INCLUDED_IOSTREAM
#include <iostream>
#define INCLUDED_IOSTREAM
#endif

namespace bsl {

                          // ========================
                          // class basic_stringstream
                          // ========================

template <class CHAR_TYPE, class CHAR_TRAITS, class ALLOCATOR>
class basic_stringstream
    : private StringBufContainer<CHAR_TYPE, CHAR_TRAITS, ALLOCATOR>
    , public native_std::basic_iostream<CHAR_TYPE, CHAR_TRAITS> {
    // This class implements a standard stream providing operations using
    // 'bsl::basic_string' for modifying or accessing the sequence of
    // characters read from, or written to, the stream.

  private:
    // PRIVATE TYPES
    typedef basic_stringbuf<CHAR_TYPE, CHAR_TRAITS, ALLOCATOR>   StreamBufType;
    typedef StringBufContainer<CHAR_TYPE, CHAR_TRAITS, ALLOCATOR>
                                                                 BaseType;
    typedef bsl::basic_string<CHAR_TYPE, CHAR_TRAITS, ALLOCATOR> StringType;
    typedef native_std::basic_iostream<CHAR_TYPE, CHAR_TRAITS>   BaseStream;
    typedef native_std::ios_base                                 ios_base;

  private:
    // NOT IMPLEMENTED
    basic_stringstream(const basic_stringstream&);             // = delete
    basic_stringstream& operator=(const basic_stringstream&);  // = delete

  public:
    // TYPES
    typedef CHAR_TYPE                       char_type;
    typedef CHAR_TRAITS                     traits_type;
    typedef ALLOCATOR                       allocator_type;
    typedef typename traits_type::int_type  int_type;
    typedef typename traits_type::off_type  off_type;
    typedef typename traits_type::pos_type  pos_type;

    // CREATORS
    explicit
    basic_stringstream(const allocator_type& allocator = allocator_type());
    explicit
    basic_stringstream(ios_base::openmode    modeBitMask,
                       const allocator_type& allocator = allocator_type());
    explicit
    basic_stringstream(const StringType&     initialString,
                       const allocator_type& allocator = allocator_type());
    basic_stringstream(const StringType&     initialString,
                       ios_base::openmode    modeBitMask,
                       const allocator_type& allocator = allocator_type());
        // Create a 'basic_stringstream' object.  Optionally specify a
        // 'modeBitMask' indicating whether the underlying stream-buffer may
        // be read from, written to, or both ('rdbuf' is created using
        // 'modeBitMask').  If 'modeBitMask' is not supplied, 'rdbuf' will be
        // created using 'ios_base::in | ios_base::out'.  Optionally specify
        // an 'initialString' indicating the initial sequence of characters
        // that this stream may access or manipulate.  If 'initialString' is
        // not supplied, the initial sequence of characters will be empty.
        // Optionally specify an 'allocator' used to supply memory.  If
        // 'allocator' is not supplied, a default-constructed object of the
        // (template parameter) 'ALLOCATOR' type is used.  If the 'ALLOCATOR'
        // argument is of type 'bsl::allocator' (the default), then
        // 'allocator', if supplied, shall be convertible to
        // 'bslma::Allocator *'.  If the 'ALLOCATOR' argument is of type
        // 'bsl::allocator' and 'allocator' is not supplied, the currently
        // installed default allocator will be used to supply memory.

    //! ~basic_stringstream() = default;
        // Destroy this object.

    // MANIPULATORS
    void str(const StringType& value);
        // Reset the internally buffered sequence of characters maintained by
        // this stream object to the specified 'value'.

    // ACCESSORS
    StringType str() const;
        // Return the sequence of characters referred to by this stream object.

    StreamBufType *rdbuf() const;
        // Return an address providing modifiable access to the
        // 'basic_stringbuf' object that is internally used by this stream
        // object to buffer unformatted characters.
};

// STANDARD TYPEDEFS
typedef basic_stringstream<char, char_traits<char>, allocator<char> >
                                                                  stringstream;
typedef basic_stringstream<wchar_t, char_traits<wchar_t>, allocator<wchar_t> >
                                                                 wstringstream;

}

// TYPE TRAITS
namespace BloombergLP {
namespace bslma {

template <typename CHAR_TYPE, typename CHAR_TRAITS, typename ALLOCATOR>
struct UsesBslmaAllocator<
        bsl::basic_stringstream<CHAR_TYPE, CHAR_TRAITS, ALLOCATOR> >
    : bsl::true_type
{};

}
}

namespace bsl {

// ==========================================================================
//                       TEMPLATE FUNCTION DEFINITIONS
// ============================================================================

                          // ------------------------
                          // class basic_stringstream
                          // ------------------------

// CREATORS
template <class CHAR_TYPE, class CHAR_TRAITS, class ALLOCATOR>
inline
basic_stringstream<CHAR_TYPE, CHAR_TRAITS, ALLOCATOR>::
basic_stringstream(const allocator_type& allocator)
: BaseType(ios_base::in | ios_base::out, allocator)
, BaseStream(this->rdbuf())
{
}

template <class CHAR_TYPE, class CHAR_TRAITS, class ALLOCATOR>
inline
basic_stringstream<CHAR_TYPE, CHAR_TRAITS, ALLOCATOR>::
    basic_stringstream(ios_base::openmode    modeBitMask,
                       const allocator_type& allocator)
: BaseType(modeBitMask, allocator)
, BaseStream(this->rdbuf())
{
}

template <class CHAR_TYPE, class CHAR_TRAITS, class ALLOCATOR>
inline
basic_stringstream<CHAR_TYPE, CHAR_TRAITS, ALLOCATOR>::
basic_stringstream(const StringType&     initialString,
                   const allocator_type& allocator)
: BaseType(initialString, ios_base::in | ios_base::out, allocator)
, BaseStream(this->rdbuf())
{
}

template <class CHAR_TYPE, class CHAR_TRAITS, class ALLOCATOR>
inline
basic_stringstream<CHAR_TYPE, CHAR_TRAITS, ALLOCATOR>::
basic_stringstream(const StringType&     initialString,
                   ios_base::openmode    modeBitMask,
                   const allocator_type& allocator)
: BaseType(initialString, modeBitMask, allocator)
, BaseStream(this->rdbuf())
{
}

// MANIPULATORS
template <class CHAR_TYPE, class CHAR_TRAITS, class ALLOCATOR>
inline
void basic_stringstream<CHAR_TYPE, CHAR_TRAITS, ALLOCATOR>::str(
                                                       const StringType& value)
{
    this->rdbuf()->str(value);
}

// ACCESSORS
template <class CHAR_TYPE, class CHAR_TRAITS, class ALLOCATOR>
inline
typename basic_stringstream<CHAR_TYPE, CHAR_TRAITS, ALLOCATOR>::StringType
basic_stringstream<CHAR_TYPE, CHAR_TRAITS, ALLOCATOR>::str() const
{
    return this->rdbuf()->str();
}

template <class CHAR_TYPE, class CHAR_TRAITS, class ALLOCATOR>
inline
typename basic_stringstream<CHAR_TYPE, CHAR_TRAITS, ALLOCATOR>::StreamBufType *
basic_stringstream<CHAR_TYPE, CHAR_TRAITS, ALLOCATOR>::rdbuf() const
{
    return this->BaseType::rdbuf();
}

}  // close namespace bsl

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
