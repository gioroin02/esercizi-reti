#ifndef PAX_NETWORK_ADDRESS_CPP
#define PAX_NETWORK_ADDRESS_CPP

#include "address.hpp"

namespace pax {

Address
address_any(Address_Type type)
{
    Address result = {};

    result.type = ADDRESS_TYPE_NONE;

    switch (type) {
        case ADDRESS_TYPE_IP4: {
            result.ip4 = address_ip4_any();
        } break;

        case ADDRESS_TYPE_IP6: {
            result.ip6 = address_ip6_any();
        } break;

        default: return result;
    }

    result.type = type;

    return result;
}

Address
address_localhost(Address_Type type)
{
    Address result = {};

    result.type = ADDRESS_TYPE_NONE;

    switch (type) {
        case ADDRESS_TYPE_IP4: {
            result.ip4 = address_ip4_localhost();
        } break;

        case ADDRESS_TYPE_IP6: {
            result.ip6 = address_ip6_localhost();
        } break;

        default: return result;
    }

    result.type = type;

    return result;
}

b32
address_is_equal(Address self, Address value)
{
    if (self.type != value.type) return 0;

    switch (self.type) {
        case ADDRESS_TYPE_IP4:
            return address_ip4_is_equal(self.ip4, value.ip4);

        case ADDRESS_TYPE_IP6:
            return address_ip6_is_equal(self.ip6, value.ip6);

        default: break;
    }

    return 0;
}

b32
address_from_str8(str8 self, Address_Type type, Address *value)
{
    if (value == 0) return 0;

    value->type = ADDRESS_TYPE_NONE;

    switch (type) {
        case ADDRESS_TYPE_IP4: {
            if (ip4_from_str8(self, &value->ip4) == 0)
                return 0;
        } break;

        case ADDRESS_TYPE_IP6: {
            if (ip6_from_str8(self, &value->ip6) == 0)
                return 0;
        } break;

        default: return 0;
    }

    value->type = type;

    return 1;
}

} // namespace pax

#endif // PAX_NETWORK_ADDRESS_CPP
