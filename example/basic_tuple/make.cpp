/*
@copyright Louis Dionne 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#include <boost/hana/basic_tuple.hpp>
#include <boost/hana/core/make.hpp>
#include <boost/hana/equal.hpp>
namespace hana = boost::hana;


int main() {
    constexpr hana::basic_tuple<int, char, double> xs{1, '2', 3.3};
    constexpr auto ys = hana::make<hana::BasicTuple>(1, '2', 3.3);

    (void)xs; (void)ys;
}
