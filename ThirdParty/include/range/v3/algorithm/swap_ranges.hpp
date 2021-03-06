/// \file
// Range v3 library
//
//  Copyright Eric Niebler 2013-2014
//
//  Use, modification and distribution is subject to the
//  Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// Project home: https://github.com/ericniebler/range-v3
//
#ifndef RANGES_V3_ALGORITHM_SWAP_RANGES_HPP
#define RANGES_V3_ALGORITHM_SWAP_RANGES_HPP

#include <range/v3/range_fwd.hpp>
#include <range/v3/begin_end.hpp>
#include <range/v3/range_concepts.hpp>
#include <range/v3/range_traits.hpp>
#include <range/v3/utility/iterator_concepts.hpp>
#include <range/v3/utility/iterator_traits.hpp>
#include <range/v3/utility/static_const.hpp>
#include <range/v3/utility/tagged_pair.hpp>
#include <range/v3/algorithm/tagspec.hpp>

namespace ranges
{
    inline namespace v3
    {
        /// \addtogroup group-algorithms
        /// @{
        struct swap_ranges_fn
        {
            template<typename I1Ref, typename S1, typename I2,
                typename I1 = uncvref_t<I1Ref>,
#ifdef RANGES_WORKAROUND_MSVC_SFINAE_CONSTEXPR
                CONCEPT_REQUIRES_(InputIterator<I1>::value && IteratorRange<I1, S1>::value &&
                    WeakInputIterator<I2>::value &&
                    IndirectlySwappable<I1, I2>::value)>
#else
                CONCEPT_REQUIRES_(InputIterator<I1>() && IteratorRange<I1, S1>() &&
                                  WeakInputIterator<I2>() &&
                                  IndirectlySwappable<I1, I2>())>
#endif
            tagged_pair<tag::in1(I1), tag::in2(I2)> operator()(I1Ref&& begin1, S1 end1, I2 begin2) const
            {
                for(; begin1 != end1; ++begin1, ++begin2)
                    ranges::iter_swap(begin1, begin2);
                return {begin1, begin2};
            }

            template<typename I1, typename S1, typename I2, typename S2,
#ifdef RANGES_WORKAROUND_MSVC_SFINAE_CONSTEXPR
                CONCEPT_REQUIRES_(InputIterator<I1>::value && IteratorRange<I1, S1>::value &&
                    InputIterator<I2>::value && IteratorRange<I2, S2>::value &&
                    IndirectlySwappable<I1, I2>::value)>
#else
                CONCEPT_REQUIRES_(InputIterator<I1>() && IteratorRange<I1, S1>() &&
                                  InputIterator<I2>() && IteratorRange<I2, S2>() &&
                                  IndirectlySwappable<I1, I2>())>
#endif
            tagged_pair<tag::in1(I1), tag::in2(I2)> operator()(I1 begin1, S1 end1, I2 begin2, S2 end2) const
            {
                for(; begin1 != end1 && begin2 != end2; ++begin1, ++begin2)
                    ranges::iter_swap(begin1, begin2);
                return {begin1, begin2};
            }

            template<typename Rng1, typename I2,
                typename I1 = range_iterator_t<Rng1>,
#ifdef RANGES_WORKAROUND_MSVC_SFINAE_CONSTEXPR
                CONCEPT_REQUIRES_(InputRange<Rng1>::value &&
                    WeakInputIterator<I2>::value &&
                    IndirectlySwappable<I1, I2>::value)>
#else
                CONCEPT_REQUIRES_(InputRange<Rng1>() &&
                                  WeakInputIterator<I2>() &&
                                  IndirectlySwappable<I1, I2>())>
#endif
            tagged_pair<tag::in1(I1), tag::in2(I2)> operator()(Rng1 & rng1, I2 begin2) const
            {
                return (*this)(begin(rng1), end(rng1), std::move(begin2));
            }

            template<typename Rng1, typename Rng2,
                typename I1 = range_iterator_t<Rng1>,
                typename I2 = range_iterator_t<Rng2>,
#ifdef RANGES_WORKAROUND_MSVC_SFINAE_CONSTEXPR
                CONCEPT_REQUIRES_(InputRange<Rng1>::value &&
                    InputRange<Rng2>::value &&
                    IndirectlySwappable<I1, I2>::value)>
#else
                CONCEPT_REQUIRES_(InputRange<Rng1>() &&
                                  InputRange<Rng2>() &&
                                  IndirectlySwappable<I1, I2>())>
#endif
            tagged_pair<tag::in1(range_safe_iterator_t<Rng1>), tag::in2(range_safe_iterator_t<Rng2>)>
            operator()(Rng1 &&rng1, Rng2 &&rng2) const
            {
                return (*this)(begin(rng1), end(rng1), begin(rng2), end(rng2));
            }
        };

        /// \sa `swap_ranges_fn`
        /// \ingroup group-algorithms
        namespace
        {
            constexpr auto&& swap_ranges = static_const<with_braced_init_args<swap_ranges_fn>>::value;
        }

        /// @}
    } // namespace v3
} // namespace ranges

#endif // include guard
