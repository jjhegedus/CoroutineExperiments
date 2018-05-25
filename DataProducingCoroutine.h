#pragma once

#include <experimental\coroutine>

template<typename T>
class DataProducingCoroutine
{
public:
    struct promise_type
    {
        T m_value;
        DataProducingCoroutine get_return_object() {
            return DataProducingCoroutine(HandleType::from_promise(*this));
        }

        std::experimental::suspend_never initial_suspend() { return {}; }

        std::experimental::suspend_always final_suspend() { return {}; }

        void return_value(T value) {
            m_value = value;
        }

        void unhandled_exception() {}
    };


    using HandleType = std::experimental::coroutine_handle<promise_type>;
    HandleType m_coroutineHandle;

    DataProducingCoroutine(HandleType h)
        : m_coroutineHandle(h) {

    }

    T get() { return m_coroutineHandle.promise().m_value; }
};