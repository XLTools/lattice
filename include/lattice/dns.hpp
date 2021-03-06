//  :copyright: (c) 2016 The Regents of the University of California.
//  :license: MIT, see LICENSE.md for more details.
/**
 *  \addtogroup Lattice
 *  \brief Domain name lookups and address caching.
 */

#pragma once

#ifdef _WIN32
#   include <winsock2.h>
#   include <ws2tcpip.h>
#   include <windows.h>
#else
#   include <netdb.h>
#endif

#include <memory>
#include <string>
#include <unordered_map>


namespace lattice
{
// TYPES
// -----

class Cache;
typedef std::shared_ptr<Cache> DnsCache;

// OBJECTS
// -------


/** \brief Iterator over addresses.
 */
class AddressIterator: public std::iterator<
        std::forward_iterator_tag,
        addrinfo*
    >
{
protected:
    typedef addrinfo value_type;

    value_type *value = nullptr;

public:
    AddressIterator() = default;
    AddressIterator(const AddressIterator &other) = default;
    AddressIterator & operator=(const AddressIterator&) = default;
    AddressIterator(AddressIterator&&) = default;
    AddressIterator & operator=(AddressIterator&&) = default;

    AddressIterator(value_type *value);

    const value_type & operator*() const;
    const value_type * operator->() const;
    AddressIterator & operator++();
    AddressIterator operator++(int);
    bool operator==(const AddressIterator& other) const;
    bool operator!=(const AddressIterator& other) const;
};


/** \brief Host address information.
 */
struct Address
{
    int family;
    int socket_type;
    int protocol;
    sockaddr address;
    size_t length;

    Address() = default;
    Address(const Address &other) = default;
    Address & operator=(const Address&) = default;
    Address(Address&&) = default;
    Address & operator=(Address&&) = default;

    Address(const addrinfo &info);

    explicit operator addrinfo() const;
};


/** \brief Cache for DNS lookups.
 */
class Cache: public std::unordered_multimap<std::string, Address>
{
protected:
    typedef std::unordered_multimap<std::string, Address> Base;

public:
    using Base::Base;

    template <typename ...Args>
    friend DnsCache CreateDnsCache(Args&& ...args);
};


/** \brief DNS lookup for a server host.
 *
 *  \param host             Base url of host address, "example.com"
 *  \param service          Service for connection, "http"
 */
class DnsLookup
{
protected:
    addrinfo *info = nullptr;

public:
    DnsLookup() = default;
    DnsLookup(const DnsLookup &other) = delete;
    DnsLookup & operator=(const DnsLookup&) = delete;
    DnsLookup(DnsLookup&&) = default;
    DnsLookup & operator=(DnsLookup&&) = default;
    ~DnsLookup();

    DnsLookup(const std::string &host,
        const std::string &service);

    // ITERATORS
    AddressIterator begin() const;
    AddressIterator end() const;
};

// IMPLEMENTATION
// --------------


/** \brief Only expose cache creator for lifetime management.
 *
 *  Expose only the `CreateDnsCache` function call to set automatic
 *  lifetime management for the API.
 */
template <typename ...Args>
DnsCache CreateDnsCache(Args&& ...args)
{
    return std::make_shared<Cache>(LATTICE_FWD(args)...);
}


}   /* lattice */
