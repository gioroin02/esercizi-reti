#ifndef PAX_STRUCTURE_HASH_MAP_HPP
#define PAX_STRUCTURE_HASH_MAP_HPP

#include "array.hpp"
#include "table.hpp"

namespace pax {

//
// Types
//

template <class Key>
using Hash_Proc = usiz (Key);

struct Hash_Info
{
    isiz index = 0;
    usiz hash  = 0;
    usiz dist  = 0;
};

template <class Key, class Val>
struct Hash_Map
{
    Table<usiz> outer = {};
    Array<usiz> inner = {};
    Array<Key>  key   = {};
    Array<Val>  value = {};

    Hash_Proc<Key>* hash = 0;
};

//
// Procs
//

/* Hashing */

template <class Key>
usiz
empty_hash_proc(Key key);

/* Hash_Map */

template <class Key, class Val>
Hash_Map<Key, Val>
hash_map_reserve(Arena* arena, isiz length, Hash_Proc<Key>* proc);

template <class Key, class Val>
Hash_Proc<Key>*
hash_map_set_hash_proc(Hash_Map<Key, Val>* self, Hash_Proc<Key>* proc);

template <class Key, class Val>
void
hash_map_clear(Hash_Map<Key, Val>* self);

template <class Key, class Val>
b32
hash_map_insert(Hash_Map<Key, Val>* self, Key key, Val value);

template <class Key, class Val>
b32
hash_map_update(Hash_Map<Key, Val>* self, Key key, Val value, Val* other);

template <class Key, class Val>
b32
hash_map_remove(Hash_Map<Key, Val>* self, Key key, Val* value);

template <class Key, class Val>
Val
hash_map_remove_or(Hash_Map<Key, Val>* self, Key key, Val other);

template <class Key, class Val>
b32
hash_map_get(Hash_Map<Key, Val>* self, Key key, Val* value);

template <class Key, class Val>
Val
hash_map_get_or(Hash_Map<Key, Val>* self, Key key, Val other);

template <class Key, class Val>
b32
hash_map_put(Hash_Map<Key, Val>* self, Key key, Val value);

} // namespace pax

#include "hash_map.cpp"

#endif // PAX_STRUCTURE_HASH_MAP_HPP
