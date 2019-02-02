//
// Created by Daemyung Jang on 2019-02-02.
//

#ifndef RAY_TRACING_OPTIONAL_H
#define RAY_TRACING_OPTIONAL_H

#ifndef __APPLE__
#include <optional>
#else
#include <boost/none.hpp>
#include <boost/optional/optional.hpp>

namespace std {

    template<typename T>
    using optional = boost::optional<T>;

    const boost::none_t nullopt { boost::none_t::init_tag() };

}
#endif

#endif //RAY_TRACING_OPTIONAL_H
