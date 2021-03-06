// bslmf_ismemberfunctionpointer.h                                    -*-C++-*-
#ifndef INCLUDED_BSLMF_ISMEMBERFUNCTIONPOINTER
#define INCLUDED_BSLMF_ISMEMBERFUNCTIONPOINTER

#ifndef INCLUDED_BSLS_IDENT
#include <bsls_ident.h>
#endif
BSLS_IDENT("$Id: $")

//@PURPOSE: Provide a compile-time check for member function pointer types.
//
//@CLASSES:
//  bsl::is_member_function_pointer: standard meta-function
//
//@DESCRIPTION: This component defines a meta-function,
// 'bsl::is_member_function_pointer', that may be used to query whether a type
// is a function pointer type to non-static member function.
//
// 'bsl::is_member_function_pointer' meets the requirements of the
// 'is_member_function_pointer' template defined in the C++11 standard
// [meta.unary.cat].
//
///Usage
///-----
// In this section we show intended use of this component.
//
///Example 1: Verify Member Function Pointer Types
///- - - - - - - - - - - - - - - - - - - - - - - -
// Suppose that we want to assert whether a particular type is a class type.
//
// First, we create a user-defined type 'MyStruct':
//..
//  struct MyStruct
//  {
//  };
//..
// Now, we create two 'typedef's -- a function pointer type and a member
// function pointer type:
//..
//  typedef int (MyStruct::*MyStructMethodPtr) ();
//  typedef int (*MyFunctionPtr) ();
//..
// Finally, we instantiate the 'bsl::is_member_function_pointer' template for
// each of the 'typedef's and assert the 'value' static data member of each
// instantiation:
//..
//  assert(false == bsl::is_member_function_pointer<MyFunctionPtr    >::value);
//  assert(true  == bsl::is_member_function_pointer<MyStructMethodPtr>::value);
//..

#ifndef INCLUDED_BSLSCM_VERSION
#include <bslscm_version.h>
#endif

#ifndef INCLUDED_BSLMF_INTEGRALCONSTANT
#include <bslmf_integralconstant.h>
#endif

#ifndef INCLUDED_BSLMF_REMOVECV
#include <bslmf_removecv.h>
#endif

#ifndef INCLUDED_BSLMF_ISREFERENCE
#include <bslmf_isreference.h>
#endif

namespace BloombergLP {
namespace bslmf {

                     // ==================================
                     // struct IsMemberFunctionPointer_Imp
                     // ==================================

template <typename PROTOTYPE>
struct IsMemberFunctionPointer_Imp : bsl::false_type {
    // This 'struct' template provides a meta-function to determine whether the
    // (template parameter) 'TYPE' is a (non-cv-qualified) pointer type to
    // non-static data member.  This generic default template derives from
    // 'bsl::false_type'.  A template specialization is provided (below) that
    // derives from 'bsl::true_type'.
};

template <typename RETURN, typename CLASS>
struct IsMemberFunctionPointer_Imp<RETURN (CLASS::*)()> : bsl::true_type {
    // This partial specialization of 'IsMemberFunctionPointer_Imp' derives
    // from 'bsl::true_type' for when the (template parameter) 'TYPE' is a
    // pointer type to non-static member function that takes no arguments.
};

template <typename RETURN, typename CLASS, typename ARG1>
struct IsMemberFunctionPointer_Imp<RETURN (CLASS::*)(ARG1)> : bsl::true_type
{
    // This partial specialization of 'IsMemberFunctionPointer_Imp' derives
    // from 'bsl::true_type' for when the (template parameter) 'TYPE' is a
    // pointer type to non-static member function that takes one argument.
};

template <typename RETURN, typename CLASS, typename ARG1, typename ARG2>
struct IsMemberFunctionPointer_Imp<RETURN (CLASS::*)(ARG1, ARG2)>
: bsl::true_type {
    // This partial specialization of 'IsMemberFunctionPointer_Imp' derives
    // from 'bsl::true_type' for when the (template parameter) 'TYPE' is a
    // pointer type to non-static member function that takes two argument.
};

template <typename RETURN, typename CLASS, typename ARG1, typename ARG2,
                                           typename ARG3>
struct IsMemberFunctionPointer_Imp<RETURN (CLASS::*)(ARG1, ARG2, ARG3)>
: bsl::true_type {
    // This partial specialization of 'IsMemberFunctionPointer_Imp' derives
    // from 'bsl::true_type' for when the (template parameter) 'TYPE' is a
    // pointer type to non-static member function that takes three argument.
};

template <typename RETURN, typename CLASS, typename ARG1, typename ARG2,
                                           typename ARG3, typename ARG4>
struct IsMemberFunctionPointer_Imp<RETURN (CLASS::*)(ARG1, ARG2, ARG3, ARG4)>
: bsl::true_type {
    // This partial specialization of 'IsMemberFunctionPointer_Imp' derives
    // from 'bsl::true_type' for when the (template parameter) 'TYPE' is a
    // pointer type to non-static member function that takes four argument.
};

template <typename RETURN, typename CLASS, typename ARG1, typename ARG2,
                                           typename ARG3, typename ARG4,
                                           typename ARG5>
struct IsMemberFunctionPointer_Imp<
                               RETURN (CLASS::*)(ARG1, ARG2, ARG3, ARG4, ARG5)>
: bsl::true_type {
    // This partial specialization of 'IsMemberFunctionPointer_Imp' derives
    // from 'bsl::true_type' for when the (template parameter) 'TYPE' is a
    // pointer type to non-static member function that takes five argument.
};

template <typename RETURN, typename CLASS, typename ARG1, typename ARG2,
                                           typename ARG3, typename ARG4,
                                           typename ARG5, typename ARG6>
struct IsMemberFunctionPointer_Imp<
                         RETURN (CLASS::*)(ARG1, ARG2, ARG3, ARG4, ARG5, ARG6)>
: bsl::true_type {
    // This partial specialization of 'IsMemberFunctionPointer_Imp' derives
    // from 'bsl::true_type' for when the (template parameter) 'TYPE' is a
    // pointer type to non-static member function that takes six argument.
};

template <typename RETURN, typename CLASS, typename ARG1, typename ARG2,
                                           typename ARG3, typename ARG4,
                                           typename ARG5, typename ARG6,
                                           typename ARG7>
struct IsMemberFunctionPointer_Imp<
                   RETURN (CLASS::*)(ARG1, ARG2, ARG3, ARG4, ARG5, ARG6, ARG7)>
: bsl::true_type {
    // This partial specialization of 'IsMemberFunctionPointer_Imp' derives
    // from 'bsl::true_type' for when the (template parameter) 'TYPE' is a
    // pointer type to non-static member function that takes seven argument.
};

template <typename RETURN, typename CLASS, typename ARG1, typename ARG2,
                                           typename ARG3, typename ARG4,
                                           typename ARG5, typename ARG6,
                                           typename ARG7, typename ARG8>
struct IsMemberFunctionPointer_Imp<
             RETURN (CLASS::*)(ARG1, ARG2, ARG3, ARG4, ARG5, ARG6, ARG7, ARG8)>
: bsl::true_type {
    // This partial specialization of 'IsMemberFunctionPointer_Imp' derives
    // from 'bsl::true_type' for when the (template parameter) 'TYPE' is a
    // pointer type to non-static member function that takes eight argument.
};

template <typename RETURN, typename CLASS, typename ARG1, typename ARG2,
                                           typename ARG3, typename ARG4,
                                           typename ARG5, typename ARG6,
                                           typename ARG7, typename ARG8,
                                           typename ARG9>
struct IsMemberFunctionPointer_Imp<
       RETURN (CLASS::*)(ARG1, ARG2, ARG3, ARG4, ARG5, ARG6, ARG7, ARG8, ARG9)>
: bsl::true_type {
    // This partial specialization of 'IsMemberFunctionPointer_Imp' derives
    // from 'bsl::true_type' for when the (template parameter) 'TYPE' is a
    // pointer type to non-static member function that takes nine argument.
};

template <typename RETURN, typename CLASS, typename ARG1, typename ARG2,
                                           typename ARG3, typename ARG4,
                                           typename ARG5, typename ARG6,
                                           typename ARG7, typename ARG8,
                                           typename ARG9, typename ARG10>
struct IsMemberFunctionPointer_Imp<
       RETURN (CLASS::*)(ARG1, ARG2, ARG3, ARG4, ARG5,
                         ARG6, ARG7, ARG8, ARG9, ARG10)> : bsl::true_type {
    // This partial specialization of 'IsMemberFunctionPointer_Imp' derives
    // from 'bsl::true_type' for when the (template parameter) 'TYPE' is a
    // pointer type to non-static member function that takes ten argument.
};

// Match pointer to const member function:
template <typename RETURN, typename CLASS>
struct IsMemberFunctionPointer_Imp<RETURN (CLASS::*)() const>
: bsl::true_type {
    // This partial specialization of 'IsMemberFunctionPointer_Imp' derives
    // from 'bsl::true_type' for when the (template parameter) 'TYPE' is a
    // pointer type to non-static constant member function that takes no
    // arguments.
};

template <typename RETURN, typename CLASS, typename ARG1>
struct IsMemberFunctionPointer_Imp<RETURN (CLASS::*)(ARG1) const>
: bsl::true_type {
    // This partial specialization of 'IsMemberFunctionPointer_Imp' derives
    // from 'bsl::true_type' for when the (template parameter) 'TYPE' is a
    // pointer type to non-static constant member function that takes one
    // argument.
};

template <typename RETURN, typename CLASS, typename ARG1, typename ARG2>
struct IsMemberFunctionPointer_Imp<
       RETURN (CLASS::*)(ARG1, ARG2) const>
: bsl::true_type {
    // This partial specialization of 'IsMemberFunctionPointer_Imp' derives
    // from 'bsl::true_type' for when the (template parameter) 'TYPE' is a
    // pointer type to non-static constant member function that takes two
    // arguments.
};

template <typename RETURN, typename CLASS, typename ARG1, typename ARG2,
                                           typename ARG3>
struct IsMemberFunctionPointer_Imp<
       RETURN (CLASS::*)(ARG1, ARG2, ARG3) const>
: bsl::true_type {
    // This partial specialization of 'IsMemberFunctionPointer_Imp' derives
    // from 'bsl::true_type' for when the (template parameter) 'TYPE' is a
    // pointer type to non-static constant member function that takes three
    // arguments.
};

template <typename RETURN, typename CLASS, typename ARG1, typename ARG2,
                                           typename ARG3, typename ARG4>
struct IsMemberFunctionPointer_Imp<
       RETURN (CLASS::*)(ARG1, ARG2, ARG3, ARG4) const>
: bsl::true_type {
    // This partial specialization of 'IsMemberFunctionPointer_Imp' derives
    // from 'bsl::true_type' for when the (template parameter) 'TYPE' is a
    // pointer type to non-static constant member function that takes four
    // arguments.
};

template <typename RETURN, typename CLASS, typename ARG1, typename ARG2,
                                           typename ARG3, typename ARG4,
                                           typename ARG5>
struct IsMemberFunctionPointer_Imp<
       RETURN (CLASS::*)(ARG1, ARG2, ARG3, ARG4, ARG5) const>
: bsl::true_type {
    // This partial specialization of 'IsMemberFunctionPointer_Imp' derives
    // from 'bsl::true_type' for when the (template parameter) 'TYPE' is a
    // pointer type to non-static constant member function that takes five
    // arguments.
};

template <typename RETURN, typename CLASS, typename ARG1, typename ARG2,
                                           typename ARG3, typename ARG4,
                                           typename ARG5, typename ARG6>
struct IsMemberFunctionPointer_Imp<
       RETURN (CLASS::*)(ARG1, ARG2, ARG3, ARG4, ARG5, ARG6) const>
: bsl::true_type {
    // This partial specialization of 'IsMemberFunctionPointer_Imp' derives
    // from 'bsl::true_type' for when the (template parameter) 'TYPE' is a
    // pointer type to non-static constant member function that takes six
    // arguments.
};

template <typename RETURN, typename CLASS, typename ARG1, typename ARG2,
                                           typename ARG3, typename ARG4,
                                           typename ARG5, typename ARG6,
                                           typename ARG7>
struct IsMemberFunctionPointer_Imp<
       RETURN (CLASS::*)(ARG1, ARG2, ARG3, ARG4, ARG5,
                         ARG6, ARG7) const>
: bsl::true_type {
    // This partial specialization of 'IsMemberFunctionPointer_Imp' derives
    // from 'bsl::true_type' for when the (template parameter) 'TYPE' is a
    // pointer type to non-static constant member function that takes seven
    // arguments.
};

template <typename RETURN, typename CLASS, typename ARG1, typename ARG2,
                                           typename ARG3, typename ARG4,
                                           typename ARG5, typename ARG6,
                                           typename ARG7, typename ARG8>
struct IsMemberFunctionPointer_Imp<
       RETURN (CLASS::*)(ARG1, ARG2, ARG3, ARG4, ARG5,
                         ARG6, ARG7, ARG8) const>
: bsl::true_type {
    // This partial specialization of 'IsMemberFunctionPointer_Imp' derives
    // from 'bsl::true_type' for when the (template parameter) 'TYPE' is a
    // pointer type to non-static constant member function that takes eight
    // arguments.
};

template <typename RETURN, typename CLASS, typename ARG1, typename ARG2,
                                           typename ARG3, typename ARG4,
                                           typename ARG5, typename ARG6,
                                           typename ARG7, typename ARG8,
                                           typename ARG9>
struct IsMemberFunctionPointer_Imp<
       RETURN (CLASS::*)(ARG1, ARG2, ARG3, ARG4, ARG5,
                         ARG6, ARG7, ARG8, ARG9) const>
: bsl::true_type {
    // This partial specialization of 'IsMemberFunctionPointer_Imp' derives
    // from 'bsl::true_type' for when the (template parameter) 'TYPE' is a
    // pointer type to non-static constant member function that takes nine
    // arguments.
};

template <typename RETURN, typename CLASS, typename ARG1, typename ARG2,
                                           typename ARG3, typename ARG4,
                                           typename ARG5, typename ARG6,
                                           typename ARG7, typename ARG8,
                                           typename ARG9, typename ARG10>
struct IsMemberFunctionPointer_Imp<
       RETURN (CLASS::*)(ARG1, ARG2, ARG3, ARG4, ARG5,
                         ARG6, ARG7, ARG8, ARG9, ARG10) const>
: bsl::true_type {
    // This partial specialization of 'IsMemberFunctionPointer_Imp' derives
    // from 'bsl::true_type' for when the (template parameter) 'TYPE' is a
    // pointer type to non-static constant member function that takes ten
    // arguments.
};

// Match pointer to volatile member function:
template <typename RETURN, typename CLASS>
struct IsMemberFunctionPointer_Imp<RETURN (CLASS::*)() volatile>
: bsl::true_type {
    // This partial specialization of 'IsMemberFunctionPointer_Imp' derives
    // from 'bsl::true_type' for when the (template parameter) 'TYPE' is a
    // pointer type to non-static volatile member function that takes no
    // arguments.
};

template <typename RETURN, typename CLASS, typename ARG1>
struct IsMemberFunctionPointer_Imp<RETURN (CLASS::*)(ARG1) volatile>
: bsl::true_type {
    // This partial specialization of 'IsMemberFunctionPointer_Imp' derives
    // from 'bsl::true_type' for when the (template parameter) 'TYPE' is a
    // pointer type to non-static volatile member function that takes one
    // argument.
};

template <typename RETURN, typename CLASS, typename ARG1, typename ARG2>
struct IsMemberFunctionPointer_Imp<
       RETURN (CLASS::*)(ARG1, ARG2) volatile> : bsl::true_type {
    // This partial specialization of 'IsMemberFunctionPointer_Imp' derives
    // from 'bsl::true_type' for when the (template parameter) 'TYPE' is a
    // pointer type to non-static volatile member function that takes two
    // arguments.
};

template <typename RETURN, typename CLASS, typename ARG1, typename ARG2,
                                           typename ARG3>
struct IsMemberFunctionPointer_Imp<
       RETURN (CLASS::*)(ARG1, ARG2, ARG3) volatile> : bsl::true_type {
    // This partial specialization of 'IsMemberFunctionPointer_Imp' derives
    // from 'bsl::true_type' for when the (template parameter) 'TYPE' is a
    // pointer type to non-static volatile member function that takes three
    // arguments.
};

template <typename RETURN, typename CLASS, typename ARG1, typename ARG2,
                                           typename ARG3, typename ARG4>
struct IsMemberFunctionPointer_Imp<
       RETURN (CLASS::*)(ARG1, ARG2, ARG3, ARG4) volatile>
: bsl::true_type {
    // This partial specialization of 'IsMemberFunctionPointer_Imp' derives
    // from 'bsl::true_type' for when the (template parameter) 'TYPE' is a
    // pointer type to non-static volatile member function that takes four
    // arguments.
};

template <typename RETURN, typename CLASS, typename ARG1, typename ARG2,
                                           typename ARG3, typename ARG4,
                                           typename ARG5>
struct IsMemberFunctionPointer_Imp<
       RETURN (CLASS::*)(ARG1, ARG2, ARG3, ARG4, ARG5) volatile>
: bsl::true_type {
    // This partial specialization of 'IsMemberFunctionPointer_Imp' derives
    // from 'bsl::true_type' for when the (template parameter) 'TYPE' is a
    // pointer type to non-static volatile member function that takes five
    // arguments.
};

template <typename RETURN, typename CLASS, typename ARG1, typename ARG2,
                                           typename ARG3, typename ARG4,
                                           typename ARG5, typename ARG6>
struct IsMemberFunctionPointer_Imp<
       RETURN (CLASS::*)(ARG1, ARG2, ARG3, ARG4, ARG5, ARG6) volatile>
: bsl::true_type {
    // This partial specialization of 'IsMemberFunctionPointer_Imp' derives
    // from 'bsl::true_type' for when the (template parameter) 'TYPE' is a
    // pointer type to non-static volatile member function that takes six
    // arguments.
};

template <typename RETURN, typename CLASS, typename ARG1, typename ARG2,
                                           typename ARG3, typename ARG4,
                                           typename ARG5, typename ARG6,
                                           typename ARG7>
struct IsMemberFunctionPointer_Imp<
       RETURN (CLASS::*)(ARG1, ARG2, ARG3, ARG4, ARG5,
                         ARG6, ARG7) volatile>
: bsl::true_type {
    // This partial specialization of 'IsMemberFunctionPointer_Imp' derives
    // from 'bsl::true_type' for when the (template parameter) 'TYPE' is a
    // pointer type to non-static volatile member function that takes seven
    // arguments.
};

template <typename RETURN, typename CLASS, typename ARG1, typename ARG2,
                                           typename ARG3, typename ARG4,
                                           typename ARG5, typename ARG6,
                                           typename ARG7, typename ARG8>
struct IsMemberFunctionPointer_Imp<
       RETURN (CLASS::*)(ARG1, ARG2, ARG3, ARG4, ARG5,
                         ARG6, ARG7, ARG8) volatile>
: bsl::true_type {
    // This partial specialization of 'IsMemberFunctionPointer_Imp' derives
    // from 'bsl::true_type' for when the (template parameter) 'TYPE' is a
    // pointer type to non-static volatile member function that takes eight
    // arguments.
};

template <typename RETURN, typename CLASS, typename ARG1, typename ARG2,
                                           typename ARG3, typename ARG4,
                                           typename ARG5, typename ARG6,
                                           typename ARG7, typename ARG8,
                                           typename ARG9>
struct IsMemberFunctionPointer_Imp<
       RETURN (CLASS::*)(ARG1, ARG2, ARG3, ARG4, ARG5,
                         ARG6, ARG7, ARG8, ARG9) volatile>
: bsl::true_type {
    // This partial specialization of 'IsMemberFunctionPointer_Imp' derives
    // from 'bsl::true_type' for when the (template parameter) 'TYPE' is a
    // pointer type to non-static volatile member function that takes nine
    // arguments.
};

template <typename RETURN, typename CLASS, typename ARG1, typename ARG2,
                                           typename ARG3, typename ARG4,
                                           typename ARG5, typename ARG6,
                                           typename ARG7, typename ARG8,
                                           typename ARG9, typename ARG10>
struct IsMemberFunctionPointer_Imp<
       RETURN (CLASS::*)(ARG1, ARG2, ARG3, ARG4, ARG5,
                         ARG6, ARG7, ARG8, ARG9, ARG10) volatile>
: bsl::true_type {
    // This partial specialization of 'IsMemberFunctionPointer_Imp' derives
    // from 'bsl::true_type' for when the (template parameter) 'TYPE' is a
    // pointer type to non-static volatile member function that takes ten
    // arguments.
};

// Match pointer to const volatile member function:
template <typename RETURN, typename CLASS>
struct IsMemberFunctionPointer_Imp<RETURN (CLASS::*)() const volatile>
: bsl::true_type {
    // This partial specialization of 'IsMemberFunctionPointer_Imp' derives
    // from 'bsl::true_type' for when the (template parameter) 'TYPE' is a
    // pointer type to non-static constant volatile member function that takes
    // no arguments.
};

template <typename RETURN, typename CLASS, typename ARG1>
struct IsMemberFunctionPointer_Imp<
       RETURN (CLASS::*)(ARG1) const volatile>
: bsl::true_type {
    // This partial specialization of 'IsMemberFunctionPointer_Imp' derives
    // from 'bsl::true_type' for when the (template parameter) 'TYPE' is a
    // pointer type to non-static constant volatile member function that takes
    // one argument.
};

template <typename RETURN, typename CLASS, typename ARG1, typename ARG2>
struct IsMemberFunctionPointer_Imp<
       RETURN (CLASS::*)(ARG1, ARG2) const volatile>
: bsl::true_type {
    // This partial specialization of 'IsMemberFunctionPointer_Imp' derives
    // from 'bsl::true_type' for when the (template parameter) 'TYPE' is a
    // pointer type to non-static constant volatile member function that takes
    // two arguments.
};

template <typename RETURN, typename CLASS, typename ARG1, typename ARG2,
                                           typename ARG3>
struct IsMemberFunctionPointer_Imp<
       RETURN (CLASS::*)(ARG1, ARG2, ARG3) const volatile>
: bsl::true_type {
    // This partial specialization of 'IsMemberFunctionPointer_Imp' derives
    // from 'bsl::true_type' for when the (template parameter) 'TYPE' is a
    // pointer type to non-static constant volatile member function that takes
    // three arguments.
};

template <typename RETURN, typename CLASS, typename ARG1, typename ARG2,
                                           typename ARG3, typename ARG4>
struct IsMemberFunctionPointer_Imp<
       RETURN (CLASS::*)(ARG1, ARG2, ARG3, ARG4) const volatile>
: bsl::true_type {
    // This partial specialization of 'IsMemberFunctionPointer_Imp' derives
    // from 'bsl::true_type' for when the (template parameter) 'TYPE' is a
    // pointer type to non-static constant volatile member function that takes
    // four arguments.
};

template <typename RETURN, typename CLASS, typename ARG1, typename ARG2,
                                           typename ARG3, typename ARG4,
                                           typename ARG5>
struct IsMemberFunctionPointer_Imp<
       RETURN (CLASS::*)(ARG1, ARG2, ARG3, ARG4, ARG5) const volatile>
: bsl::true_type{
    // This partial specialization of 'IsMemberFunctionPointer_Imp' derives
    // from 'bsl::true_type' for when the (template parameter) 'TYPE' is a
    // pointer type to non-static constant volatile member function that takes
    // five arguments.
};

template <typename RETURN, typename CLASS, typename ARG1, typename ARG2,
                                           typename ARG3, typename ARG4,
                                           typename ARG5, typename ARG6>
struct IsMemberFunctionPointer_Imp<
       RETURN (CLASS::*)(ARG1, ARG2, ARG3, ARG4, ARG5, ARG6) const volatile>
: bsl::true_type {
    // This partial specialization of 'IsMemberFunctionPointer_Imp' derives
    // from 'bsl::true_type' for when the (template parameter) 'TYPE' is a
    // pointer type to non-static constant volatile member function that takes
    // six arguments.
};

template <typename RETURN, typename CLASS, typename ARG1, typename ARG2,
                                           typename ARG3, typename ARG4,
                                           typename ARG5, typename ARG6,
                                           typename ARG7>
struct IsMemberFunctionPointer_Imp<
       RETURN (CLASS::*)(ARG1, ARG2, ARG3, ARG4, ARG5,
                         ARG6, ARG7) const volatile>
: bsl::true_type {
    // This partial specialization of 'IsMemberFunctionPointer_Imp' derives
    // from 'bsl::true_type' for when the (template parameter) 'TYPE' is a
    // pointer type to non-static constant volatile member function that takes
    // seven arguments.
};

template <typename RETURN, typename CLASS, typename ARG1, typename ARG2,
                                           typename ARG3, typename ARG4,
                                           typename ARG5, typename ARG6,
                                           typename ARG7, typename ARG8>
struct IsMemberFunctionPointer_Imp<
       RETURN (CLASS::*)(ARG1, ARG2, ARG3, ARG4, ARG5,
                         ARG6, ARG7, ARG8) const volatile>
: bsl::true_type {
    // This partial specialization of 'IsMemberFunctionPointer_Imp' derives
    // from 'bsl::true_type' for when the (template parameter) 'TYPE' is a
    // pointer type to non-static constant volatile member function that takes
    // eight arguments.
};

template <typename RETURN, typename CLASS, typename ARG1, typename ARG2,
                                           typename ARG3, typename ARG4,
                                           typename ARG5, typename ARG6,
                                           typename ARG7, typename ARG8,
                                           typename ARG9>
struct IsMemberFunctionPointer_Imp<
       RETURN (CLASS::*)(ARG1, ARG2, ARG3, ARG4, ARG5,
                         ARG6, ARG7, ARG8, ARG9) const volatile>
: bsl::true_type {
    // This partial specialization of 'IsMemberFunctionPointer_Imp' derives
    // from 'bsl::true_type' for when the (template parameter) 'TYPE' is a
    // pointer type to non-static constant volatile member function that takes
    // nine arguments.
};

template <typename RETURN, typename CLASS, typename ARG1, typename ARG2,
                                           typename ARG3, typename ARG4,
                                           typename ARG5, typename ARG6,
                                           typename ARG7, typename ARG8,
                                           typename ARG9, typename ARG10>
struct IsMemberFunctionPointer_Imp<
       RETURN (CLASS::*)(ARG1, ARG2, ARG3, ARG4, ARG5,
                         ARG6, ARG7, ARG8, ARG9, ARG10) const volatile>
: bsl::true_type {
    // This partial specialization of 'IsMemberFunctionPointer_Imp' derives
    // from 'bsl::true_type' for when the (template parameter) 'TYPE' is a
    // pointer type to non-static constant volatile member function that takes
    // ten arguments.
};

}  // close package namespace
}  // close enterprise namespace

namespace bsl {

                       // =================================
                       // struct is_member_function_pointer
                       // =================================

template <typename TYPE>
struct is_member_function_pointer
    : integral_constant<bool,
                        BloombergLP::bslmf::IsMemberFunctionPointer_Imp<
                            typename remove_cv<TYPE>::type>::value
                        && !is_reference<TYPE>::value>
{
    // This 'struct' template implements the 'is_member_function_pointer'
    // meta-function defined in the C++11 standard [meta.unary.cat] to
    // determine if the (template parameter) 'TYPE' is a pointer type to
    // non-static member function.  This 'struct' derives from 'bsl::true_type'
    // if the 'TYPE' is a pointer type to non-static member function, and
    // 'bsl::false_type' otherwise.
};

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
