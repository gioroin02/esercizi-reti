#ifndef PAX_STORAGE_DIRECTORY_HPP
#define PAX_STORAGE_DIRECTORY_HPP

#include "file_attribs.hpp"

namespace pax {

//
// Types
//

using Directory = void*;

//
// Procs
//

/* Directory */

Directory
directory_open(Arena* arena, str8 path);

void
directory_close(Directory self);

b32
directory_next(Directory self, Arena* arena, File_Attribs* value);

} // namespace pax

#endif // PAX_STORAGE_DIRECTORY_HPP
