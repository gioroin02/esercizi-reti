#ifndef PAX_STORAGE_WINDOWS_DIRECTORY_HPP
#define PAX_STORAGE_WINDOWS_DIRECTORY_HPP

#include "imports.hpp"

namespace pax {

//
// Types
//

struct Windows_Directory;

//
// Procs
//

/* Windows_Directory */

Windows_Directory*
windows_directory_open(Arena* arena, str8 path);

void
windows_directory_close(Windows_Directory* self);

b32
windows_directory_next(Windows_Directory* self, Arena* arena, File_Attribs* value);

} // namespace pax

#endif // PAX_STORAGE_WINDOWS_DIRECTORY_HPP
