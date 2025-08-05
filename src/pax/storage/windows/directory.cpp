#ifndef PAX_STORAGE_WINDOWS_DIRECTORY_CPP
#define PAX_STORAGE_WINDOWS_DIRECTORY_CPP

#include "directory.hpp"

#define WIN32_LEAN_AND_MEAN
#define NOGDI
#define NOMINMAX

#include <windows.h>

namespace pax {

struct Windows_Directory
{
    HANDLE handle = INVALID_HANDLE_VALUE;
    str8   name   = {};

    WIN32_FIND_DATAW data = {};
};

Windows_Directory*
windows_directory_open(Arena* arena, str8 path)
{
    isiz offset = arena_offset(arena);

    Windows_Directory* result = pax_arena_reserve_one(arena, Windows_Directory);

    if (result != 0) {
        isiz  temp   = arena_offset(arena);
        buf16 buffer = buf16_reserve(arena, MEMORY_KIB);

        buf16_write_str8_tail(&buffer, path);
        buf16_write_str8_tail(&buffer, pax_str8("\\*.*"));

        str16 string = buf16_read_str16_head(&buffer, arena, buffer.size);

        result->handle = FindFirstFileW(
            pax_as(wchar_t*, string.memory), &result->data);

        result->name = str8_copy(arena, path);

        arena_rewind(arena, temp);

        if (result->handle != INVALID_HANDLE_VALUE)
            return result;
    }

    arena_rewind(arena, offset);

    return 0;
}

void
windows_directory_close(Windows_Directory* self)
{
    if (self == 0) return;

    if (self->handle != INVALID_HANDLE_VALUE)
        FindClose(self->handle);

    self->name   = {};
    self->data   = {};
    self->handle = INVALID_HANDLE_VALUE;
}

b32
windows_directory_next(Windows_Directory* self, Arena* arena, File_Attribs* value)
{
    if (self == 0 || self->handle == INVALID_HANDLE_VALUE) return 0;

    if (value != 0) {
        str16 string = pax_str16_cnt(self->data.cFileName);

        value->path = str8_copy(arena, self->name);
        value->name = str8_from_str16(arena, string);

        value->type = FILE_TYPE_SIMPLE;
        value->perm = FILE_PERM_READ_WRITE;

        if ((self->data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0)
            value->type = FILE_TYPE_DIRECTORY;

        if (value->type != FILE_TYPE_DIRECTORY) {
            value->size  = self->data.nFileSizeLow;
            value->size += self->data.nFileSizeHigh * (MAXWORD + 1);

            if ((self->data.dwFileAttributes & FILE_ATTRIBUTE_READONLY) != 0)
                value->perm = FILE_PERM_READ;
        }
    }

    if (FindNextFileW(self->handle, &self->data) != 0) return 1;

    windows_directory_close(self);

    return 0;
}

} // namespace pax

#endif // PAX_STORAGE_WINDOWS_DIRECTORY_CPP
