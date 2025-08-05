#ifndef PAX_NETWORK_ADDRESS_HPP
#define PAX_NETWORK_ADDRESS_HPP

#include "address_ip.hpp"

namespace pax {

//
// Types
//

enum Address_Type
{
    ADDRESS_TYPE_NONE,
    ADDRESS_TYPE_IP4,
    ADDRESS_TYPE_IP6,
};

struct Address
{
    Address_Type type = ADDRESS_TYPE_NONE;

    union
    {
        Address_IP4 ip4;
        Address_IP6 ip6;
    };
};

//
// Procs
//

/* Address*/

Address
address_any(Address_Type type);

Address
address_localhost(Address_Type type);

b32
address_is_equal(Address self, Address value);

/* Address reading */

b32
address_from_str8(str8 self, Address_Type type, Address* value);

} // namespace pax

#endif // PAX_NETWORK_ADDRESS_HPP
