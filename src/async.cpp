//  :copyright: (c) 2016 The Regents of the University of California.
//  :license: MIT, see LICENSE.md for more details.
/**
 *  \addtogroup Lattice
 *  \brief Asynchronous requests.
 */

#include "lattice/async.hpp"


namespace lattice
{
// OBJECTS
// -------


/** \brief Block and return all queries.
 */
std::vector<Response> Pool::perform()
{
    std::vector<Response> responses;
    responses.reserve(futures.size());

    for (auto &&future: futures) {
        if (future.valid()) {
            responses.emplace_back(future.get());
        }
    }

    return responses;
}


/** \brief Check if more items can be returns.
 */
Pool::operator bool() const
{
    return !futures.empty();
}


}   /* lattice */
