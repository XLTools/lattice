//  :copyright: (c) 2016 The Regents of the University of California.
//  :license: MIT, see LICENSE.md for more details.
/**
 *  \addtogroup Example
 *  \brief Follow absolute redirects from GET request.
 */

#include "lattice.hpp"

#include <iostream>


int main(int argc, char *argv[])
{
    lattice::Parameters parameters = {
        {"url", "http://httpbin.org/get"},
    };
    lattice::Url url = {"http://httpbin.org/redirect-to"};
    lattice::Timeout timeout(1000);
    lattice::Redirects redirects(5);
    auto response = lattice::Get(url, timeout, redirects, parameters);

    if (response.ok()) {
        std::cout << "Body:\n"
                  << "------------------\n"
                  << response.body()
                  << "------------------\n"
                  << "Encoding: " << response.encoding() << "\n"
                  << "------------------\n";
    } else {
        std::cout << "Response was not successful, error code: "
                  << response.status();
    }

    return 0;
}
