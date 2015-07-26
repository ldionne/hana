/*!
@file
Defines `boost::hana::insert_range`.

@copyright Louis Dionne 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_INSERT_RANGE_HPP
#define BOOST_HANA_INSERT_RANGE_HPP

#include <boost/hana/fwd/insert_range.hpp>

#include <boost/hana/core/datatype.hpp>
#include <boost/hana/core/default.hpp>
#include <boost/hana/core/models.hpp>
#include <boost/hana/core/when.hpp>
#include <boost/hana/detail/dispatch_if.hpp>

#include <boost/hana/concat.hpp>
#include <boost/hana/core/convert.hpp>
#include <boost/hana/drop_front.hpp>
#include <boost/hana/take.hpp>


namespace boost { namespace hana {
    //! @cond
    template <typename Xs, typename N, typename Elements>
    constexpr auto insert_range_t::operator()(Xs&& xs, N&& n, Elements&& elements) const {
        using S = typename datatype<Xs>::type;
        using InsertRange = BOOST_HANA_DISPATCH_IF(insert_range_impl<S>,
            _models<Sequence, Xs>::value &&
            _models<Foldable, Elements>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(_models<Sequence, Xs>::value,
        "hana::insert_range(xs, n, elements) requires 'xs' to be a Sequence");

        static_assert(_models<Foldable, Elements>::value,
        "hana::insert_range(xs, n, elements) requires 'elements' to be a Foldable");
    #endif

        return InsertRange::apply(static_cast<Xs&&>(xs),
                                  static_cast<N&&>(n),
                                  static_cast<Elements&&>(elements));
    }
    //! @endcond

    template <typename S, bool condition>
    struct insert_range_impl<S, when<condition>> {
        template <typename Xs, typename N, typename Elements>
        static constexpr auto apply(Xs&& xs, N const& n, Elements&& e) {
            return hana::concat(
                    hana::concat(
                        hana::take(xs, n),
                        hana::to<S>(static_cast<Elements&&>(e))
                    ),
                    hana::drop_front(xs, n)
                );
        }
    };
}} // end namespace boost::hana

#endif // !BOOST_HANA_INSERT_RANGE_HPP