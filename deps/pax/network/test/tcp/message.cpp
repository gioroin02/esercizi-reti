#ifndef MESSAGE_CPP
#define MESSAGE_CPP

#include "message.hpp"

b32
buffer_encode_msg_exit(Buffer* self)
{
    if (self->length < 1) return 0;

    self->memory[0] = MESSAGE_EXIT;
    self->size      = 1;

    return 1;
}

b32
buffer_encode_msg_file_name(Buffer* self, str8 name)
{
    if (self->length < name.length + 1)
        return 0;

    self->memory[0] = MESSAGE_FILE_NAME;

    for (uptr i = 0; i < name.length; i += 1)
        self->memory[i + 1] = name.memory[i];

    self->size = name.length + 1;

    return 1;
}

b32
buffer_encode_msg_file_size(Buffer* self, u64 value)
{
    uptr length = U64_SIZE;

    if (self->length < length + 1) return 0;

    self->memory[0] = MESSAGE_FILE_SIZE;

    value = u64_net_from_host(value);

    mem8_copy(self->memory + 1, &value, length);

    self->size = length + 1;

    return 1;
}

u8
buffer_decode_msg_type(Buffer* self)
{
    u8 result = 0;

    if (self->size < 1) return result;

    return self->memory[0];
}

str8
buffer_decode_msg_file_name(Buffer* self, Arena* arena)
{
    return str8_copy_mem(arena, self->memory + 1, self->size - 1);
}

u64
buffer_decode_msg_file_size(Buffer* self)
{
    uptr length = U64_SIZE;
    u64  value  = 0;

    mem8_copy(&value, self->memory + 1, length);

    return u64_host_from_net(value);
}

#endif // MESSAGE_CPP
