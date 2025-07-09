#ifndef PAX_PROCESS_THREAD_CPP
#define PAX_PROCESS_THREAD_CPP

#include "thread.hpp"

#if PAX_PLATFORM == PAX_PLATFORM_WINDOWS

    #include "windows/thread.cpp"

    #define __Routine__ Windows_Routine
    #define __Thread__  Windows_Thread

    #define __thread_create__     windows_thread_create
    #define __thread_destroy__    windows_thread_destroy
    #define __thread_wait__       windows_thread_wait
    #define __thread_detach__     windows_thread_detach
    #define __thread_is_running__ windows_thread_is_running

#else

    #error "Platform not supported or unknown"

#endif

#define PAX_ROUTINE(self) pax_cast(__Routine__*, self)
#define PAX_THREAD(self)  pax_cast(__Thread__*, self)

namespace pax {

Thread
thread_create(Arena* arena, Routine* routine, addr argumns)
{
    return __thread_create__(arena, PAX_ROUTINE(routine), argumns);
}

void
thread_destroy(Thread self)
{
    __thread_destroy__(PAX_THREAD(self));
}

void
thread_wait(Thread self)
{
    __thread_wait__(PAX_THREAD(self));
}

void
thread_detach(Thread self)
{
    __thread_detach__(PAX_THREAD(self));
}

b32
thread_is_running(Thread self)
{
    return __thread_is_running__(PAX_THREAD(self));
}

} // namespace pax

#endif // PAX_PROCESS_THREAD_CPP
