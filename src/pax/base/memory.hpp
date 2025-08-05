#ifndef PAX_BASE_MEMORY_HPP
#define PAX_BASE_MEMORY_HPP

#include "types.hpp"

//
// Defines
//

#define pax_arena_reserve(self, type, amount) \
    pax_as(type*, arena_reserve(self, pax_size_of(type), amount).memory)

#define pax_arena_reserve_one(self, type) \
    pax_as(type*, arena_reserve_one(self, pax_size_of(type)).memory)

namespace pax {

//
// Values
//

static const isiz MEMORY_KB = 1000;
static const isiz MEMORY_MB = MEMORY_KB * MEMORY_KB;
static const isiz MEMORY_GB = MEMORY_MB * MEMORY_KB;

static const isiz MEMORY_KIB = 1024;
static const isiz MEMORY_MIB = MEMORY_KIB * MEMORY_KIB;
static const isiz MEMORY_GIB = MEMORY_MIB * MEMORY_KIB;

//
// Types
//

struct Arena
{
    u8*  memory = 0;
    isiz length = 0;
    isiz offset = 0;
};

//
// Procs
//

/* Memory */

void*
mem8_zero(void* memory, isiz length);

void*
mem8_copy(void* memory, void* value, isiz length);

void*
mem8_copy_flipped(void* memory, void* value, isiz length);

void*
mem8_move_back(void* memory, isiz length, isiz offset);

void*
mem8_move_forw(void* memory, isiz length, isiz offset);

void*
mem8_flip(void* memory, isiz length);

b32
mem8_is_equal(void* memory, void* value, isiz length);

void*
mem16_zero(void* memory, isiz length);

void*
mem16_copy(void* memory, void* value, isiz length);

void*
mem16_copy_flipped(void* memory, void* value, isiz length);

void*
mem16_move_back(void* memory, isiz length, isiz offset);

void*
mem16_move_forw(void* memory, isiz length, isiz offset);

void*
mem16_flip(void* memory, isiz length);

b32
mem16_is_equal(void* memory, void* value, isiz length);

void*
mem32_zero(void* memory, isiz length);

void*
mem32_copy(void* memory, void* value, isiz length);

void*
mem32_copy_flipped(void* memory, void* value, isiz length);

void*
mem32_move_back(void* memory, isiz length, isiz offset);

void*
mem32_move_forw(void* memory, isiz length, isiz offset);

void*
mem32_flip(void* memory, isiz length);

b32
mem32_is_equal(void* memory, void* value, isiz length);

void*
mem64_zero(void* memory, isiz length);

void*
mem64_copy(void* memory, void* value, isiz length);

void*
mem64_copy_flipped(void* memory, void* value, isiz length);

void*
mem64_move_back(void* memory, isiz length, isiz offset);

void*
mem64_move_forw(void* memory, isiz length, isiz offset);

void*
mem64_flip(void* memory, isiz length);

b32
mem64_is_equal(void* memory, void* value, isiz length);

/* Arena */

Arena
arena_make(u8* memory, isiz length);

Arena
arena_reserve(Arena* self, isiz stride, isiz amount);

Arena
arena_reserve_one(Arena* self, isiz size);

b32
arena_release(Arena* self, void* value);

void
arena_clear(Arena* self);

isiz
arena_offset(Arena* self);

b32
arena_rewind(Arena* self, isiz offset);

isiz
arena_align_forward(Arena* self, isiz align);

} // namespace pax

#endif // PAX_BASE_MEMORY_HPP
