#pragma once

#include <experimental\coroutine>

class IntProducingCoroutine
{
public:
    struct promise_type
    {
        int m_value;
        IntProducingCoroutine get_return_object();
        std::experimental::suspend_never initial_suspend();
        std::experimental::suspend_always final_suspend();
        void return_value(int i);
        void unhandled_exception();
    };


    using HandleType = std::experimental::coroutine_handle<promise_type>;
    HandleType m_coroutineHandle;
    IntProducingCoroutine(HandleType h);
    int get() { return m_coroutineHandle.promise().m_value; }
};