#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include "common.hpp"

//
// Types
//

enum Message_Type
{
    MESSAGE_NONE,
    MESSAGE_EXIT,
    MESSAGE_FILE_NAME,
    MESSAGE_FILE_SIZE,
};

//
// Procs
//

b32
buffer_encode_msg_exit(Buffer* self);

b32
buffer_encode_msg_file_name(Buffer* self, str8 name);

b32
buffer_encode_msg_file_size(Buffer* self, u64 value);

u8
buffer_decode_msg_type(Buffer* self);

str8
buffer_decode_msg_file_name(Buffer* self, Arena* arena);

u64
buffer_decode_msg_file_size(Buffer* self);

#endif // MESSAGE_HPP
