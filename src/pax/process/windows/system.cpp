#ifndef PAX_PROCESS_WINDOWS_SYSTEM_CPP
#define PAX_PROCESS_WINDOWS_SYSTEM_CPP

#include "system.hpp"

#define WIN32_LEAN_AND_MEAN
#define NOGDI
#define NOMINMAX

#include <windows.h>

namespace pax {

void
windows_sleep(u32 millis)
{
    Sleep(millis);
}

isiz
windows_get_number_of_cpus()
{
    SYSTEM_INFO info = {};

    GetSystemInfo(&info);

    return pax_as(isiz, info.dwNumberOfProcessors);
}

isiz
windows_get_thread_ident()
{
    return pax_as(isiz, GetCurrentThreadId());
}

} // namespace pax

#endif // PAX_PROCESS_WINDOWS_SYSTEM_CPP
