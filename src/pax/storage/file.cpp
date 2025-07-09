#ifndef PAX_STORAGE_FILE_CPP
#define PAX_STORAGE_FILE_CPP

#include "file.hpp"

#if PAX_PLATFORM == PAX_PLATFORM_WINDOWS

    #include "windows/file.cpp"

    #define __File__ Windows_File

    #define __file_delete__      windows_file_delete
    #define __file_open__        windows_file_open
    #define __file_open_always__ windows_file_open_always
    #define __file_open_new__    windows_file_open_new
    #define __file_close__       windows_file_close
    #define __file_offset__      windows_file_offset
    #define __file_rewind__      windows_file_rewind
    #define __file_write__       windows_file_write
    #define __file_read__        windows_file_read

#else

    #error "Platform not supported or unknown"

#endif

#define PAX_FILE(self) pax_cast(__File__*, self)

namespace pax {

b32
file_delete(Arena* arena, str8 path, str8 name)
{
    return __file_delete__(arena, path, name);
}

File
file_open(Arena* arena, str8 path, str8 name, File_Perm perm)
{
    return __file_open__(arena, path, name, perm);
}

File
file_open_always(Arena* arena, str8 path, str8 name, File_Perm perm)
{
    return __file_open_always__(arena, path, name, perm);
}

File
file_open_new(Arena* arena, str8 path, str8 name, File_Perm perm)
{
    return __file_open_new__(arena, path, name, perm);
}

void
file_close(File self)
{
    __file_close__(PAX_FILE(self));
}

uptr
file_offset(File self)
{
    return __file_offset__(PAX_FILE(self));
}

b32
file_rewind(File self, uptr offset)
{
    return __file_rewind__(PAX_FILE(self), offset);
}

b32
file_write(File self, Buffer buffer)
{
    return __file_write__(PAX_FILE(self), buffer);
}

b32
file_read(File self, Buffer* buffer)
{
    return __file_read__(PAX_FILE(self), buffer);
}

} // namespace pax

#endif // PAX_STORAGE_FILE_CPP
