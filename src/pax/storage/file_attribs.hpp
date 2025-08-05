#ifndef PAX_STORAGE_FILE_ATTRIBS_HPP
#define PAX_STORAGE_FILE_ATTRIBS_HPP

#include "imports.hpp"

namespace pax {

//
// Types
//

enum File_Perm
{
    FILE_PERM_NONE       = 0x0,
    FILE_PERM_READ       = 0x1,
    FILE_PERM_WRITE      = 0x2,
    FILE_PERM_READ_WRITE = 0x3,
    FILE_PERM_EXEC       = 0x4,
    FILE_PERM_READ_EXEC  = 0x5,
    FILE_PERM_WRITE_EXEC = 0x6,
    FILE_PERM_FULL       = 0x7,
};

enum File_Type
{
    FILE_TYPE_NONE      = 0,
    FILE_TYPE_SIMPLE    = 1,
    FILE_TYPE_DIRECTORY = 2,
};

struct File_Attribs
{
    File_Type type = FILE_TYPE_NONE;
    File_Perm perm = FILE_PERM_NONE;
    str8      path = {};
    str8      name = {};
    isiz      size = 0;
};

//
// Procs
//

/* File_Attribs */

isiz
file_size(File_Attribs* self);

b32
file_is_simple(File_Attribs* self);

b32
file_is_directory(File_Attribs* self);

} // namespace pax

#endif // PAX_STORAGE_FILE_ATTRIBS_HPP
