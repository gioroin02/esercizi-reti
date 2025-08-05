#ifndef PAX_NETWORK_ADDRESS_IP_CPP
#define PAX_NETWORK_ADDRESS_IP_CPP

#include "address_ip.hpp"

namespace pax {

static u8  LOCALHOST_IP4[ADDRESS_IP4_GROUPS] = {127, 0, 0, 1};
static u16 LOCALHOST_IP6[ADDRESS_IP6_GROUPS] = {0, 0, 0, 0, 0, 0, 0, 1};

Address_IP4
address_ip4_any()
{
    Address_IP4 result = {};

    return result;
}

Address_IP4
address_ip4_localhost()
{
    Address_IP4 result = {};

    for (isiz i = 0; i < ADDRESS_IP4_GROUPS; i += 1)
        result.memory[i] = LOCALHOST_IP4[i];

    return result;
}

b32
address_ip4_is_equal(Address_IP4 self, Address_IP4 value)
{
    return mem8_is_equal(self.memory, value.memory, ADDRESS_IP4_GROUPS);
}

b32
ip4_from_str8(str8 self, Address_IP4* value)
{
    u8 groups[ADDRESS_IP4_GROUPS] = {};

    Format_Options options = format_options(10, FORMAT_FLAG_LEADING_ZERO);

    if (str8_contains(self, pax_str8(".")) != ADDRESS_IP4_GROUPS - 1)
        return 0;

    str8 group = self;
    str8 tail  = self;

    for (isiz i = 0; i < ADDRESS_IP4_GROUPS; i += 1) {
        group = str8_split_on(tail, pax_str8("."), &tail);

        if (u8_from_str8(group, options, &groups[i]) == 0)
            return 0;
    }

    if (tail.length > 0) return 0;

    if (value != 0)
        mem8_copy(value->memory, groups, ADDRESS_IP4_GROUPS);

    return 1;
}

Address_IP6
address_ip6_any()
{
    Address_IP6 result = {};

    return result;
}

Address_IP6
address_ip6_localhost()
{
    Address_IP6 result = {};

    for (isiz i = 0; i < ADDRESS_IP6_GROUPS; i += 1)
        result.memory[i] = LOCALHOST_IP6[i];

    return result;
}

b32
address_ip6_is_equal(Address_IP6 self, Address_IP6 value)
{
    return mem16_is_equal(self.memory, value.memory, ADDRESS_IP6_GROUPS);
}

b32
ip6_from_str8(str8 self, Address_IP6* value)
{
    u16 groups[ADDRESS_IP6_GROUPS] = {};

    Format_Options options = format_options(16, FORMAT_FLAG_LEADING_ZERO);

    switch (str8_contains(self, pax_str8("::"))) {
        case 0: {
            if (str8_contains(self, pax_str8(":"))  != ADDRESS_IP6_GROUPS - 1)
                return 0;

            str8 group = self;
            str8 tail  = self;

            for (isiz i = 0; i < ADDRESS_IP6_GROUPS; i += 1) {
                group = str8_split_on(tail, pax_str8(":"), &tail);

                if (u16_from_str8(group, options, &groups[i]) == 0)
                    return 0;
            }

            if (tail.length > 0) return 0;
        } break;

        case 1: {
            str8 group = self;
            str8 left  = self;
            str8 right = self;

            left = str8_split_on(self, pax_str8("::"), &right);

            isiz start = 0;
            isiz index = str8_contains(left, pax_str8(":")) + 1;
            isiz stop  = ADDRESS_IP6_GROUPS;

            if (index >= stop) return 0;

            for (isiz i = start; i < index; i += 1) {
                group = str8_split_on(left, pax_str8(":"), &left);

                if (group.length <= 0) break;

                if (u16_from_str8(group, options, &groups[i]) == 0)
                    return 0;
            }

            if (left.length > 0) return 0;

            start = index;
            index = str8_contains(right, pax_str8(":")) + 1;

            if (start + index >= stop) return 0;

            for (isiz i = stop - index; i < stop; i += 1) {
                group = str8_split_on(right, pax_str8(":"), &right);

                if (group.length <= 0) break;

                if (u16_from_str8(group, options, &groups[i]) == 0)
                    return 0;
            }

            if (right.length > 0) return 0;
        } break;

        default: return 0;
    }

    if (value != 0)
        mem16_copy(value->memory, groups, ADDRESS_IP6_GROUPS);

    return 1;
}

} // namespace pax

#endif // PAX_NETWORK_ADDRESS_IP_CPP
