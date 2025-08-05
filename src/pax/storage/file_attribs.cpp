#ifndef PAX_STORAGE_FILE_ATTRIBS_CPP
#define PAX_STORAGE_FILE_ATTRIBS_CPP

#include "file_attribs.hpp"

namespace pax {

isiz
file_size(File_Attribs* self)
{
    if (self != 0)
        return self->size;

    return 0;
}

b32
file_is_simple(File_Attribs* self)
{
    if (self == 0) return 0;

    if (self->type == FILE_TYPE_SIMPLE)
        return 1;

    return 0;
}

b32
file_is_directory(File_Attribs* self)
{
    if (self == 0) return 0;

    if (self->type == FILE_TYPE_DIRECTORY)
        return 1;

    return 0;
}

} // namespace pax

#endif // PAX_STORAGE_FILE_ATTRIBS_CPP
