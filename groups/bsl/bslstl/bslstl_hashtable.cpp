// bslstl_hashtable.cpp                                               -*-C++-*-
#include <bslstl_hashtable.h>

#include <bsls_ident.h>
BSLS_IDENT("$Id$ $CSID$")

#include <bsls_nativestd.h>

#include <algorithm>
#include <cstddef>

namespace BloombergLP
{
namespace bslstl
{

                    // --------------------------
                    // class HashTable_ImpDetails
                    // --------------------------

bslalg::HashTableBucket *HashTable_ImpDetails::defaultBucketAddress()
{
    static bslalg::HashTableBucket s_bucket = {0 , 0};
                                                  // Aggregative initialization
                                                  // of a POD should be thread-
                                                  // safe static initialization
    return &s_bucket;
}

native_std::size_t HashTable_ImpDetails::nextPrime(native_std::size_t n)
{   // An abbreviated list of prime numbers in the domain of 32-bit
    // unsigned integers.  Essentially, a subset where each successive
    // element is the next prime after doubling.
    // Note that at least one of these numbers was mis-computed and
    // undershoots, messing up the doubling pattern, not critical while the
    // code remains proof-of-concept code.

    static const native_std::size_t s_primes[] = { 2, 5, 13, 29, 61,
        127, 257, 521, 1049, 2099, 4201, 8419, 16843, 33703, 67409, 134837,
        269513, 539039, 1078081, 2156171, 5312353, 10624709, 21249443,
        42498893, 84997793, 169995589, 339991181, 679982363, 1359964751,
        2719929503u

    };
    static const native_std::size_t s_nPrimes =
                                         sizeof(s_primes)/sizeof(&s_primes[0]);
    static const native_std::size_t *const s_beginPrimes = s_primes;
    static const native_std::size_t *const s_endPrimes = s_primes + s_nPrimes;

    return *native_std::lower_bound(s_beginPrimes, s_endPrimes, n);
}

}  // close package namespace
}  // close enterprise namespace
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
