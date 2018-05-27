#pragma once
#include <experimental\coroutine>
#include <iostream>
#include <string>
#include <thread>
#include <chrono>

#include "VoidCoroutine.h"

using namespace std;
using namespace std::experimental;
using namespace std::chrono_literals;

template<typename T>
class ReactiveDataCoroutine {

public:

    struct promise_type {
        T m_value;
        ReactiveDataCoroutine get_return_object() {
            return ReactiveDataCoroutine(HandleType::from_promise(*this));
        }

        auto initial_suspend() { return std::experimental::suspend_always{}; }

        std::experimental::suspend_always final_suspend() { return {}; }

        void return_value(T value) {
            m_value = value;
        }

    };

    using HandleType = std::experimental::coroutine_handle<promise_type>;
    HandleType m_coroutine = nullptr;

    explicit ReactiveDataCoroutine(std::experimental::coroutine_handle<promise_type> coroutine)
        : m_coroutine(coroutine) {
    }

    ~ReactiveDataCoroutine() {
        if (m_coroutine) { m_coroutine.destroy(); }
    }

    ReactiveDataCoroutine() = default;

    ReactiveDataCoroutine(ReactiveDataCoroutine const&) = delete;

    ReactiveDataCoroutine& operator=(ReactiveDataCoroutine const&) = delete;

    ReactiveDataCoroutine(ReactiveDataCoroutine&& other)
        :m_coroutine(other.m_coroutine) {
        other.m_coroutine = nullptr;
    }

    ReactiveDataCoroutine& operator=(ReactiveDataCoroutine&& other) {
        if (&other != this) {
            m_coroutine = other.m_coroutine;
            other.m_coroutine = nullptr;
        }
        return *this;
    }

    T get() {
        return m_coroutine.promise().m_value;
    }

    void set(T value) {
        m_value = value;
        m_set = true;
        m_coroutine.resume();
    }

    struct awaiter;

    awaiter operator co_await() noexcept {
        awaiter returnObject = awaiter{ *this };

        return returnObject;
    }

    struct awaiter {
        ReactiveDataCoroutine& m_resumable;

        awaiter(ReactiveDataCoroutine& resumable)  noexcept
            :m_resumable(resumable) {

        }

        bool await_ready() {
            cout << "ReactiveDataCoroutine::await_ready\n";
            return m_set;
        }

        void await_resume() {
            cout << "ReactiveDataCoroutine::await_resume\n";
        }

        void await_suspend(coroutine_handle<> waitingCoroutine) {
            cout << "ReactiveDataCoroutine::await_suspend\n";
            m_resumable.m_waitingCoroutine = waitingCoroutine;
        }
    };

private:
    coroutine_handle<> m_waitingCoroutine;
    bool m_set = false;

};