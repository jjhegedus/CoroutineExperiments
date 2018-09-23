#pragma once

#include <experimental\coroutine>

template<typename T>
class LazyDataCoroutine
{
public:
    struct promise_type
    {
        LazyDataCoroutine get_return_object() {
            return LazyDataCoroutine(HandleType::from_promise(*this));
        }

        std::experimental::suspend_never initial_suspend() { return {}; }

        std::experimental::suspend_always final_suspend() { return {}; }

        void return_value(T value) {
            // Do nothing here because the value is set through the setData member
        }

        void unhandled_exception() {}
    };

    using HandleType = std::experimental::coroutine_handle<promise_type>;
    std::experimental::coroutine_handle<> m_waitingCoroutine;
    bool m_set = false;
    T m_value;

    LazyDataCoroutine() = default;

    LazyDataCoroutine(T value):
        m_value(value),
        m_set(true) {
    }

    LazyDataCoroutine(HandleType h) {

    }

    bool await_ready() {
        cout << "LazyDataCoroutine::await_ready\n";
        return m_set;
    }

    auto await_resume() {
        cout << "LazyDataCoroutine::await_resume\n";
        const auto returnValue = m_value;
        return returnValue;
    }

    void await_suspend(coroutine_handle<> waitingCoroutine) {
        cout << "LazyDataCoroutine::await_suspend\n";
        waitingCoroutine.resume();
    }

    void setData(T value) {
        m_value = value;
        m_set = true;
    }

};