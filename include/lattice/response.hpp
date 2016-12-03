//  :copyright: (c) 2015 Huu Nguyen.
//  :copyright: (c) 2016 The Regents of the University of California.
//  :license: MIT, see LICENSE.md for more details.
/**
 *  \addtogroup Lattice
 *  \brief HTTP response object.
 */

#pragma once

#include <string>


namespace lattice
{
// OBJECTS
// -------


/** \brief Generate response from a request.
 */
class Response
{
protected:
    int code;
    std::string body;

    void parseHeader(const std::string &line);

public:
    Response();
    Response(const std::string &data);
    Response(const Response &other);
    ~Response();
};

}   /* lattice */
