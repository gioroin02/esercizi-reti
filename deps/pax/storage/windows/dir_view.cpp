#ifndef PAX_STORAGE_WINDOWS_DIR_VIEW_CPP
#define PAX_STORAGE_WINDOWS_DIR_VIEW_CPP

#include "dir_view.hpp"

#define WIN32_LEAN_AND_MEAN
#define NOGDI
#define NOMINMAX

#include <windows.h>

namespace pax {

struct Windows_Dir_View
{
    HANDLE handle = INVALID_HANDLE_VALUE;
    str8   name   = {};

    WIN32_FIND_DATAW data = {};
};

Windows_Dir_View*
windows_dir_view(Arena* arena, str8 path)
{
    uptr offset = arena_offset(arena);

    Windows_Dir_View* result = arena_reserve_one<Windows_Dir_View>(arena);

    if (result != 0) {
        path = str8_copy(arena, path);

        for (uptr i = 0; i < path.length; i += 1) {
            if (path.memory[i] == ASCII_SLASH_BACK)
                path.memory[i] = ASCII_SLASH;
        }

        uptr temp = arena_offset(arena);

        Str_Builder builder = str_builder_make(arena);

        str_builder_str8(&builder, path);
        str_builder_str8(&builder, pax_str8("/*.*"));

        str16 string = str16_from_str_builder(&builder);

        wchar_t* memory = pax_cast(wchar_t*, string.memory);

        result->name   = path;
        result->handle = FindFirstFileW(memory, &result->data);

        arena_rewind(arena, temp);

        if (result->handle != INVALID_HANDLE_VALUE)
            return result;
    }

    arena_rewind(arena, offset);

    return 0;
}

b32
windows_dir_next(Windows_Dir_View* self, Arena* arena, File_Props* value)
{
    if (self->handle == INVALID_HANDLE_VALUE) return 0;

    if (value != 0) {
        u16*  memory = pax_cast(u16*, self->data.cFileName);
        str16 string = str16_count(memory);

        value->path = str8_copy(arena, self->name);
        value->name = str8_from_str16(arena, string);

        for (uptr i = 0; i < value->name.length; i += 1) {
            if (value->name.memory[i] == ASCII_SLASH_BACK)
                value->name.memory[i] = ASCII_SLASH;
        }

        value->type = FILE_TYPE_NORMAL;
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

    FindClose(self->handle);

    self->name   = {};
    self->data   = {};
    self->handle = INVALID_HANDLE_VALUE;

    return 0;
}

} // namespace pax

#endif // PAX_STORAGE_WINDOWS_DIR_VIEW_CPP
