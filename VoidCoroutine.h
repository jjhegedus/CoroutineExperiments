#pragma once

#include <experimental\coroutine>

class VoidCoroutine
{
public:
    struct promise_type
    {
        int m_int = 1;
        VoidCoroutine get_return_object();
        std::experimental::suspend_never initial_suspend();
        std::experimental::suspend_never final_suspend();
        void return_void();
        void unhandled_exception();
    };
};