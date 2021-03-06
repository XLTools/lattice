//  :copyright: (c) 2016 The Regents of the University of California.
//  :license: MIT, see LICENSE.md for more details.
/**
 *  \addtogroup Example
 *  \brief GET request to a certificate validated through an intermediate CA.
 */

#include "lattice.hpp"

#include <iostream>


int main(int argc, char *argv[])
{
    lattice::Url url = {"https://xn--rksmrgs-5wao1o.josefsson.org"};
    lattice::Timeout timeout(1000);
    lattice::CertificateFile certificate("/usr/lib/python3/dist-packages/websocket/cacert.pem");
    auto response = lattice::Get(url, timeout, certificate);

    if (response.status() == 200) {
        std::cout << "Body:\n"
                  << "------------------\n"
                  << response.body()
                  << "------------------\n"
                  << "Encoding: " << response.encoding() << "\n"
                  << "------------------\n";
    } else {
        std::cout << "Response was not successful, error code: "
                  << response.status()  << std::endl;
    }

    return 0;
}
