// bslmf_enableif.h                                                   -*-C++-*-
#ifndef INCLUDED_BSLMF_ENABLEIF
#define INCLUDED_BSLMF_ENABLEIF

#ifndef INCLUDED_BSLS_IDENT
#include <bsls_ident.h>
#endif
BSLS_IDENT("$Id: $")

//@PURPOSE: Provide a utility to set up SFINAE conditions in type deduction.
//
//@CLASSES:
//  bsl::enable_if: standard meta-function to drop function templates from
//                  overload sets
//
//  bslmf::EnableIf: meta-function to drop function templates from overload
//                   sets
//
//@DESCRIPTION: This component defines two meta-functions, 'bsl::enable_if' and
// 'bslmf::EnableIf', both of which may be used to conditionally remove
// (potential) template instantiations as candidates for overload resolution by
// causing a deduced template instantiation to fail in a way compatible with
// the C++ SFINAE rules.
//
// 'bsl::enable_if' meets the requirements of the 'enable_if' template defined
// in the C++11 standard [meta.trans.ptr], while 'bslmf::EnableIf' was devised
// before 'enable_if' was standardized.
//
// The two meta-functions provide identical functionality.  Both meta-functions
// provide a 'typedef' 'type' that is an alias to a (template parameter) type
// if a (template parameter) condition is 'true'; otherwise, 'type' is not
// provided.
//
// Note that 'bsl::enable_if' should be preferred over 'bslmf::EnableIf', and
// in general, should be used by new components.
//
///Visual Studio Workaround
///------------------------
// Because of a Visual Studio bug, described here:
// http://connect.microsoft.com/VisualStudio/feedback/details/332179/ The
// Microsoft Visual Studio compiler may not correctly associate a function
// declaration that uses 'bsl::enable_if' with that function's definition, if
// the definition is not inline to the declaration.  This bug effects at least
// Visual Studio 2008 and 2010.  The work-around is to implement functions
// using 'bsl::enable_if' in-line with their declaration.
//
///Usage
///-----
// The following snippets of code illustrate basic use of the 'bsl::enable_if'
// meta-function.  We will demonstrate how to use this utility to control
// overload sets with three increasingly complex examples.
//
///Example 1: Implementing a Simple Function with 'bsl::enable_if'
///- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// For the first example we will implement a simple 'Swap' function template to
// exchange two arbitrary values, as if declared as below:
//..
//  template<class T>
//  void DummySwap(T& a, T& b)
//      // Exchange the values of the specified objects, 'a' and 'b'.
//  {
//      T temp(a);
//      a = b;
//      b = temp;
//  }
//..
// However, we want to take advantage of member-swap methods supplied by user-
// defined types, so we define a trait that can be customized by a class
// implementer to indicate that their class supports an optimized member-swap
// method:
//..
//  template<class T>
//  struct HasMemberSwap : bsl::false_type {
//      // This traits class indicates whether the specified template type
//      // parameter 'T' has a public 'swap' method to exchange values.
//  };
//..
// Now we can implement a generic 'Swap' function template that will invoke the
// member swap operation for any type that specialized our trait.  The use of
// 'bsl::enable_if' to declare the result type causes an attempt to deduce the
// type 'T' to fail unless the specified condition is 'true', and this falls
// under the "Substitution Failure Is Not An Error" (SFINAE) clause of the C++
// standard, so the compiler will look for a more suitable overload rather than
// fail with an error.  Note that we provide two overloaded declarations that
// appear to differ only in their return type, which would normally raise an
// ambiguity error.  This works, and is in fact required, in this case as the
// "enable-if" conditions are mutually exclusive, so that only one overload
// will ever be present in an overload set.
//..
//  template<class T>
//  typename bsl::enable_if<HasMemberSwap<T>::value>::type
//  Swap(T& a, T& b)
//  {
//      a.swap(b);
//  }
//
//  template<class T>
//  typename bsl::enable_if< ! HasMemberSwap<T>::value>::type
//  Swap(T& a, T& b)
//  {
//      T temp(a);
//      a = b;
//      b = temp;
//  }
//..
// Next we define a simple container template, that supports an optimized
// 'swap' operation by merely swapping the internal pointers, rather than
// exchanging each element:
//..
//  template<class T>
//  class MyContainer {
//      // This is a simple container implementation for demonstration purposes
//      // that is modeled after 'std::vector'.
//
//      // DATA
//      T           *d_storage;
//      std::size_t  d_length;
//
//      // NOT IMPLEMENTED
//      MyContainer(const MyContainer&);
//      MyContainer& operator=(const MyContainer&);
//
//  public:
//      MyContainer(const T& value, int n);
//          // Create a 'MyContainer' object having the specified 'n' copies of
//          // the specified 'value'.
//
//      ~MyContainer();
//          // Destroy this container and all of its elements, reclaiming any
//          // allocated memory.
//
//      void swap(MyContainer &other);
//          // Exchange the contents of 'this' container with those of the
//          // specified 'other'.  No memory will be allocated, and no
//          // exceptions are thrown.
//
//      const T& front() const;
//          // Return a reference with 'const' access to the first element in
//          // this container.
//
//      size_t size() const;
//          // Return the number of elements held by this container.
//  };
//..
// Then we specialize our 'HasMemberSwap' trait for this new container type.
//..
//  template<class T>
//  struct HasMemberSwap<MyContainer<T> > : bsl::true_type {
//  };
//..
// Next we implement the methods of this class:
//..
//  template<class T>
//  MyContainer<T>::MyContainer(const T& value, int n)
//  : d_storage(new T[n])
//  , d_length(n)
//  {
//      for (int i = 0; i !=n; ++i) {
//          d_storage[i] = value;
//      }
//  }
//
//  template<class T>
//  MyContainer<T>::~MyContainer()
//  {
//      delete[] d_storage;
//  }
//
//  template<class T>
//  void MyContainer<T>::swap(MyContainer& other)
//  {
//      Swap(d_storage, other.d_storage);
//      Swap(d_length,  other.d_length);
//  }
//
//  template<class T>
//  const T& MyContainer<T>::front() const
//  {
//      return d_storage[0];
//  }
//
//  template<class T>
//  size_t MyContainer<T>::size() const
//  {
//      return d_length;
//  }
//..
// Finally we can test that the member-'swap' method is called by the generic
// 'Swap' function.  Note that the following code will not compile unless the
// member-function 'swap' is used, as the copy constructor and assignment
// operator for the 'MyContainer' class template are declared as private.
//..
//  void TestSwap()
//  {
//      MyContainer<int> x(3, 14);
//      MyContainer<int> y(2, 78);
//      assert(14 == x.size());
//      assert( 3 == x.front());
//      assert(78 == y.size());
//      assert( 2 == y.front());
//
//      Swap(x, y);
//
//      assert(78 == x.size());
//      assert( 2 == x.front());
//      assert(14 == y.size());
//      assert( 3 == y.front());
//  }
//..
//
///Example 2: Using the 'bsl::enable_if' Result Type
///- - - - - - - - - - - - - - - - - - - - - - - - -
// For the next example, we will demonstrate the use of the second template
// parameter in the 'bsl::enable_if' template, which serves as the "result"
// type if the test condition passes.  Assume we want to write a generic
// function to allow us to cast between pointers of different types.  If the
// types are polymorphic, we can use 'dynamic_cast' to potentially cast between
// two seemingly unrelated types.  However, if either type is not polymorphic
// then the attempt to use 'dynamic_cast' would be a compile-time failure, and
// we must use 'static_cast' instead.
//
//..
//  template<class TO, class FROM>
//  typename bsl::enable_if<bsl::is_polymorphic<FROM>::value &&
//                                              bsl::is_polymorphic<TO>::value,
//                          TO>::type *
//  smart_cast(FROM *from)
//      // Returns a pointer to the specified 'TO' type if the specified 'from'
//      // pointer refers to an object whose complete class publicly derives,
//      // directly or indirectly, from 'TO', and a null pointer otherwise.
//  {
//      return dynamic_cast<TO *>(from);
//  }
//
//  template<class TO, class FROM>
//  typename bsl::enable_if<not(bsl::is_polymorphic<FROM>::value &&
//                                             bsl::is_polymorphic<TO>::value),
//                          TO>::type *
//  smart_cast(FROM *from)
//      // Return the specified 'from' pointer value cast as a pointer to type
//      // 'TO'.  Behavior is undefined unless such a conversion is valid.
//  {
//      return static_cast<TO *>(from);
//  }
//..
// Next we define a small number of classes to demonstrate that this casting
// utility works correctly:
//..
//  class A {
//     // Sample non-polymorphic class
//
//    public:
//      ~A() {}
//  };
//
//  class B {
//      // Sample polymorphic base-class
//
//    public:
//      virtual ~B() {}
//  };
//
//  class C {
//      // Sample polymorphic base-class
//
//    public:
//      virtual ~C() {}
//  };
//
//  class ABC : public A, public B, public C {
//      // Most-derived example class using multiple bases in order to
//      // demonstrate cross-casting.
//  };
//..
// Finally we demonstrate the correct behavior of the 'smart_cast' utility:
//..
//  void TestSmartCast()
//  {
//      ABC object;
//      ABC *pABC = &object;
//      A   *pA   = &object;
//      B   *pB   = &object;
//      C   *pC   = &object;
//
//      A *pA2 = smart_cast<A>(pABC);
//      B *pB2 = smart_cast<B>(pC);
//      C *pC2 = smart_cast<C>(pB);
//
//      assert(&object == pA2);
//      assert(&object == pB2);
//      assert(&object == pC2);
//
//      // These lines would fail to compile
//      // A *pA3 = smart_cast<A>(pB);
//      // C *pC3 = smart_cast<C>(pA);
//  }
//..
//
///Example 3: Controlling Constructor Selection with 'bsl::enable_if'
/// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// The final example demonstrates controlling the selection of a constructor
// template in a class with (potentially) many constructors.  We define a
// simple container template based on 'std::vector', that illustrates a problem
// that may occur when trying to call the constructor the user expects.  For
// this example, assume we are trying to create a 'vector<int>' with '42'
// copies of the value '13'.  When we pass the literal values '42' and '13' the
// compiler, the "best" candidate constructor should be the template
// constructor that takes two arguments of the same kind, deducing that type to
// be 'int'.  Unfortunately, that constructor expects those values to be of an
// iterator type, forming a valid range.  We need to avoid calling this
// constructor unless the deduced type really is an iterator, otherwise a
// compile-error will occur trying to instantiate that constructor with an
// incompatible argument type.  We use 'bsl::enable_if' to create a deduction
// context where SFINAE can kick in.  Note that we cannot deduce the '::type'
// result of a metafunction, and there is no result type (as with a regular
// function) to decorate, so we add an extra dummy argument using a pointer
// type (produced from 'bslma::EnableIf::type') with a default null argument:
//..
//  template<class T>
//  class MyVector {
//      // This is a simple container implementation for demonstration purposes
//      // that is modeled after 'std::vector'.
//
//      // DATA
//      T           *d_storage;
//      std::size_t  d_length;
//
//      // NOT IMPLEMENTED
//      MyVector(const MyVector&);
//      MyVector& operator=(const MyVector&);
//
//  public:
//      MyVector(const T& value, int n);
//          // Create a 'MyVector' object having the specified 'n' copies of
//          // the specified 'value'.
//
//      template<typename FORWARD_ITERATOR>
//      MyVector(FORWARD_ITERATOR first, FORWARD_ITERATOR last,
//                  typename bsl::enable_if<
//                      !bsl::is_fundamental<FORWARD_ITERATOR>::value
//                                                               >::type * = 0)
//          // Create a 'MyVector' object having the same sequence of values as
//          // found in range described by the iterators '[first, last)'.
//          // Note that this function is currently defined inline to work
//          // around an issue with the Microsoft Visual Studio compiler.
//
//      {
//          d_length = 0;
//          for (FORWARD_ITERATOR cursor = first; cursor != last; ++cursor) {
//               ++d_length;
//          }
//
//         d_storage = new T[d_length];
//         for (int i = 0; i != d_length; ++i) {
//            d_storage[i] = *first++;
//         }
//      }
//
//      ~MyVector();
//          // Destroy this container and all of its elements, reclaiming any
//          // allocated memory.
//
//      const T& operator[](int index) const;
//          // Return a reference with 'const' access to the element held by
//          // this container at the specified 'index'.
//
//      int size() const;
//          // Return the number of elements held by this container.
//  };
//..
// Note that there is no easy test for whether a type is an iterator, so we
// assume any attempt to call a constructor with two arguments that are not
// fundamental (such as int) must be passing iterators.  Now that we have
// defined the class template, we implement its methods:
//..
//  template<class T>
//  MyVector<T>::MyVector(const T& value, int n)
//  : d_storage(new T[n])
//  , d_length(n)
//  {
//      for (int i = 0; i !=n; ++i) {
//          d_storage[i] = value;
//      }
//  }
//
//  template<class T>
//  MyVector<T>::~MyVector()
//  {
//      delete[] d_storage;
//  }
//
//  template<class T>
//  const T& MyVector<T>::operator[](int index) const
//  {
//      return d_storage[index];
//  }
//
//  template<class T>
//  int MyVector<T>::size() const
//  {
//      return d_length;
//  }
//..
// Finally we demonstrate that the correct constructors are called when invoked
// with appropriate arguments.
//..
//  void TestContainerConstructor()
//  {
//      const unsigned int TEST_DATA[] = { 1, 2, 3, 4, 5 };
//
//      const MyVector<unsigned int> x(&TEST_DATA[0], &TEST_DATA[5]);
//      const MyVector<unsigned int> y(13, 42);
//
//      assert(5 == x.size());
//      for(int i = 0; i != 5; ++i) {
//          assert(TEST_DATA[i] == x[i]);
//      }
//
//      assert(42 == y.size());
//      for(int i = 0; i != 42; ++i) {
//          assert(13 == y[i]);
//      }
//  }
//..

namespace bsl {

                         // ================
                         // struct enable_if
                         // ================

template <bool COND, typename TYPE = void>
struct enable_if {
    // This 'struct' template implements the 'enable_if' meta-function defined
    // in the C++11 standard [meta.trans.ptr].  This 'struct' template provides
    // a 'typedef' 'type' that is an alias to the (template parameter) 'TYPE'
    // if the (template parameter) 'COND' is 'true'; otherwise, 'type' is not
    // provided.  Note that this generic default template provides 'type' for
    // when 'COND' is 'true'; a template specialization is sprovided (below)
    // that omits 'type' for when 'COND' is 'false'.

    typedef TYPE type;
        // This 'typedef' is an alias to the (template parameter) 'TYPE'.
};

                         // =============================
                         // struct enable_if<false, TYPE>
                         // =============================

template <typename TYPE>
struct enable_if<false, TYPE> {
    // This partial specialization of the 'enable_if', for when the (template
    // parameter) 'COND' is 'false', guarantees that no 'typedef' 'type' is
    // supplied.  Note that this class definition is intentionally empty.
};

}  // close namespace bsl

namespace BloombergLP {

namespace bslmf {

                               // ===============
                               // struct EnableIf
                               // ===============


template<bool BSLMA_CONDITION, class BSLMA_TYPE = void>
struct EnableIf {
    // This 'struct' template implements a meta-function that provides a
    // 'typedef' 'type' that is an alias to the (template parameter)
    // 'BSLMA_TYPE' if the (template parameter) 'BSLMA_CONDITION' is 'true';
    // otherwise, 'type' is not provided.  Note that this generic default
    // template provides 'type' for when 'BSLMA_COND' is 'true'; a template
    // specialization is sprovided (below) that omits 'type' for when
    // 'BSLMA_COND' is 'false'.  Note that this generic default template
    // provides 'type' for when 'BSLMA_COND' is 'true'; a template
    // specialization is sprovided (below) that omits 'type' for when
    // 'BSLMA_COND' is 'false'.
    //
    // Note that although this 'struct' is functionally identical to
    // 'bsl::enable_if', the use of 'bsl::enable_if' should be preferred.

    typedef BSLMA_TYPE type;
        // This 'typedef' is an alias to the (template parameter) 'TYPE'.
};

template<class BSLMA_TYPE>
struct EnableIf <false, BSLMA_TYPE> {
    // This partial specialization of the 'EnableIf', for when the (template
    // parameter) 'BSLMA_COND' is 'false', guarantees that no 'typedef' 'type'
    // is supplied.  Note that this class definition is intentionally empty.
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
