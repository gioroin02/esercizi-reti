#ifndef PAX_NETWORK_ADDRESS_IP_HPP
#define PAX_NETWORK_ADDRESS_IP_HPP

#include "imports.hpp"

namespace pax {

//
// Values
//

static const isiz ADDRESS_IP4_GROUPS = 4;
static const isiz ADDRESS_IP6_GROUPS = 8;

//
// Types
//

struct Address_IP4
{
    union
    {
        struct
        {
            u8 a, b, c, d;
        };

        u8 memory[ADDRESS_IP4_GROUPS] = {};
    };
};

struct Address_IP6
{
    union
    {
        struct
        {
            u16 a, b, c, d;
            u16 e, f, g, h;
        };

        u16 memory[ADDRESS_IP6_GROUPS] = {};
    };
};

//
// Procs
//

/* Address_IP4 */

Address_IP4
address_ip4_any();

Address_IP4
address_ip4_localhost();

b32
address_ip4_is_equal(Address_IP4 self, Address_IP4 value);

/* Address_IP4 reading */

b32
ip4_from_str8(str8 self, Address_IP4* value);

/* Address_IP6 */

Address_IP6
address_ip6_any();

Address_IP6
address_ip6_localhost();

b32
address_ip6_is_equal(Address_IP6 self, Address_IP6 value);

/* Address_IP6 reading */

b32
ip6_from_str8(str8 self, Address_IP6* value);

} // namespace pax

#endif // PAX_NETWORK_ADDRESS_IP_HPP
