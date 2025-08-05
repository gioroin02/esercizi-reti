#ifndef PAX_STORAGE_DIRECTORY_CPP
#define PAX_STORAGE_DIRECTORY_CPP

#include "directory.hpp"

#if PAX_SYSTEM == PAX_SYSTEM_WINDOWS

    #include "windows/directory.cpp"

    #define __Directory__ Windows_Directory

    #define __directory_open__  windows_directory_open
    #define __directory_close__ windows_directory_close
    #define __directory_next__  windows_directory_next

#else

    #error "Platform not supported or unknown"

#endif

#define pax_directory(self) pax_as(__Directory__*, self)

namespace pax {

Directory
directory_open(Arena* arena, str8 path)
{
    return __directory_open__(arena, path);
}

void
directory_close(Directory self)
{
    __directory_close__(pax_directory(self));
}

b32
directory_next(Directory self, Arena* arena, File_Attribs* value)
{
    return __directory_next__(pax_directory(self), arena, value);
}

} // namespace pax

#endif // PAX_STORAGE_DIRECTORY_CPP
