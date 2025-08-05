#ifndef PAX_STORAGE_WINDOWS_FILE_CPP
#define PAX_STORAGE_WINDOWS_FILE_CPP

#include "file.hpp"

#define WIN32_LEAN_AND_MEAN
#define NOGDI
#define NOMINMAX

#include <windows.h>

namespace pax {

struct Windows_File
{
    HANDLE handle = INVALID_HANDLE_VALUE;
};

b32
windows_file_delete(Arena* arena, str8 path, str8 name)
{
    isiz  offset = arena_offset(arena);
    buf16 buffer = buf16_reserve(arena, MEMORY_KIB);

    buf16_write_str8_tail(&buffer, path);
    buf16_write_str8_tail(&buffer, pax_str8("\\"));
    buf16_write_str8_tail(&buffer, name);

    str16 string = buf16_read_str16_head(&buffer, arena, buffer.size);

    b32 state = DeleteFileW(pax_as(wchar_t*, string.memory));

    arena_rewind(arena, offset);

    if (state != 0) return 1;

    return 0;
}

Windows_File*
windows_file_open(Arena* arena, str8 path, str8 name, File_Perm perm)
{
    isiz offset = arena_offset(arena);
    isiz access = 0;

    if ((perm & FILE_PERM_READ)  != 0) access |= GENERIC_READ;
    if ((perm & FILE_PERM_WRITE) != 0) access |= GENERIC_WRITE;
    if ((perm & FILE_PERM_EXEC)  != 0) access |= GENERIC_EXECUTE;

    Windows_File* result = pax_arena_reserve_one(arena, Windows_File);

    if (result != 0) {
        isiz  temp   = arena_offset(arena);
        buf16 buffer = buf16_reserve(arena, MEMORY_KIB);

        buf16_write_str8_tail(&buffer, path);
        buf16_write_str8_tail(&buffer, pax_str8("\\"));
        buf16_write_str8_tail(&buffer, name);

        str16 string = buf16_read_str16_head(&buffer, arena, buffer.size);

        result->handle = CreateFileW(pax_as(wchar_t*, string.memory),
            access, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

        arena_rewind(arena, temp);

        if (result->handle != INVALID_HANDLE_VALUE)
            return result;

        arena_rewind(arena, offset);
    }

    return 0;
}

Windows_File*
windows_file_open_always(Arena* arena, str8 path, str8 name, File_Perm perm)
{
    isiz offset = arena_offset(arena);
    isiz access = 0;

    if ((perm & FILE_PERM_READ)  != 0) access |= GENERIC_READ;
    if ((perm & FILE_PERM_WRITE) != 0) access |= GENERIC_WRITE;
    if ((perm & FILE_PERM_EXEC)  != 0) access |= GENERIC_EXECUTE;

    Windows_File* result = pax_arena_reserve_one(arena, Windows_File);

    if (result != 0) {
        isiz  temp   = arena_offset(arena);
        buf16 buffer = buf16_reserve(arena, MEMORY_KIB);

        buf16_write_str8_tail(&buffer, path);
        buf16_write_str8_tail(&buffer, pax_str8("\\"));
        buf16_write_str8_tail(&buffer, name);

        str16 string = buf16_read_str16_head(&buffer, arena, buffer.size);

        result->handle = CreateFileW(pax_as(wchar_t*, string.memory),
            access, FILE_SHARE_READ, 0, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);

        arena_rewind(arena, temp);

        if (result->handle != INVALID_HANDLE_VALUE)
            return result;

        arena_rewind(arena, offset);
    }

    return 0;
}

Windows_File*
windows_file_open_new(Arena* arena, str8 path, str8 name, File_Perm perm)
{
    isiz offset = arena_offset(arena);
    isiz access = 0;

    if ((perm & FILE_PERM_READ)  != 0) access |= GENERIC_READ;
    if ((perm & FILE_PERM_WRITE) != 0) access |= GENERIC_WRITE;
    if ((perm & FILE_PERM_EXEC)  != 0) access |= GENERIC_EXECUTE;

    Windows_File* result = pax_arena_reserve_one(arena, Windows_File);

    if (result != 0) {
        isiz  temp   = arena_offset(arena);
        buf16 buffer = buf16_reserve(arena, MEMORY_KIB);

        buf16_write_str8_tail(&buffer, path);
        buf16_write_str8_tail(&buffer, pax_str8("\\"));
        buf16_write_str8_tail(&buffer, name);

        str16 string = buf16_read_str16_head(&buffer, arena, buffer.size);

        result->handle = CreateFileW(pax_as(wchar_t*, string.memory),
            access, FILE_SHARE_READ, 0, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, 0);

        arena_rewind(arena, temp);

        if (result->handle != INVALID_HANDLE_VALUE)
            return result;

        arena_rewind(arena, offset);
    }

    return 0;
}

void
windows_file_close(Windows_File* self)
{
    if (self == 0) return;

    if (self->handle != INVALID_HANDLE_VALUE)
        CloseHandle(self->handle);

    self->handle = INVALID_HANDLE_VALUE;
}

isiz
windows_file_offset(Windows_File* self)
{
    LARGE_INTEGER value = {};

    value.QuadPart = 0;

    b32 state = SetFilePointerEx(self->handle,
        value, &value, FILE_CURRENT);

    if (state != 0)
        return pax_as_isiz(value.QuadPart);

    return 0;
}

b32
windows_file_rewind(Windows_File* self, isiz offset)
{
    LARGE_INTEGER value = {};

    value.QuadPart = offset;

    b32 state = SetFilePointerEx(self->handle,
        value, &value, FILE_BEGIN);

    if (state != 0) return 1;

    return 0;
}

b32
windows_file_write(Windows_File* self, buf8* buffer)
{
    buf8_normalize(buffer);

    u8*  memory = buffer->memory;
    isiz length = buffer->size;

    b32 state = windows_file_write_mem8(self,
        memory, length);

    if (state == 0) return 0;

    buffer->size = 0;
    buffer->head = 0;
    buffer->tail = 0;

    return 1;
}

b32
windows_file_write_mem8(Windows_File* self, u8* memory, isiz length)
{
    DWORD size  = 0;
    b32   state = WriteFile(self->handle, memory, length, &size, 0);

    if (state == 0 || size != length) return 0;

    return 1;
}

b32
windows_file_read(Windows_File* self, buf8* buffer)
{
    buf8_normalize(buffer);

    u8*  memory = buffer->memory + buffer->size;
    isiz length = buffer->length - buffer->size;
    isiz size   = 0;

    if (length <= 0) return 0;

    b32 state = windows_file_read_mem8(self,
        memory, length, &size);

    if (state == 0 || size <= 0 || size > length)
        return 0;

    buffer->size += size;
    buffer->tail += size;

    return 1;
}

b32
windows_file_read_mem8(Windows_File* self, u8* memory, isiz length, isiz* size)
{
    DWORD result = 0;
    b32   state  = ReadFile(self->handle, memory, length, &result, 0);

    if (state == 0 || result <= 0 || result > length)
        return 0;

    if (size != 0) *size = result;

    return 1;
}

File_Attribs
windows_file_attribs(Arena* arena, str8 path, str8 name)
{
    File_Attribs result = {};

    WIN32_FIND_DATAW data = {};

    isiz  offset = arena_offset(arena);
    buf16 buffer = buf16_reserve(arena, MEMORY_KIB);

    buf16_write_str8_tail(&buffer, path);
    buf16_write_str8_tail(&buffer, pax_str8("\\"));
    buf16_write_str8_tail(&buffer, name);

    str16 string = buf16_read_str16_head(&buffer, arena, buffer.size);

    HANDLE handle = FindFirstFileW(
        pax_as(wchar_t*, string.memory), &data);

    arena_rewind(arena, offset);

    if (handle == INVALID_HANDLE_VALUE) return result;

    result.path = str8_copy(arena, path);
    result.name = str8_copy(arena, name);

    result.type = FILE_TYPE_SIMPLE;
    result.perm = FILE_PERM_READ_WRITE;

    if ((data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0)
        result.type = FILE_TYPE_DIRECTORY;

    if (result.type != FILE_TYPE_DIRECTORY) {
        result.size  = data.nFileSizeLow;
        result.size += data.nFileSizeHigh * (MAXWORD + 1);

        if ((data.dwFileAttributes & FILE_ATTRIBUTE_READONLY) != 0)
            result.perm = FILE_PERM_READ;
    }

    FindClose(handle);

    return result;
}

} // namespace pax

#endif // PAX_STORAGE_WINDOWS_FILE_CPP
