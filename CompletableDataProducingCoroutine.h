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
class CompletableDataProducingCoroutine {

public:

    struct promise_type {
        T m_value;
        CompletableDataProducingCoroutine get_return_object() {
            return CompletableDataProducingCoroutine(HandleType::from_promise(*this));
        }

        auto initial_suspend() { return std::experimental::suspend_always{}; }

        std::experimental::suspend_always final_suspend() { return {}; }

        void return_value(T value) {
            m_value = value;
        }

    };

    using HandleType = std::experimental::coroutine_handle<promise_type>;
    HandleType m_coroutine = nullptr;

    explicit CompletableDataProducingCoroutine(std::experimental::coroutine_handle<promise_type> coroutine)
        : m_coroutine(coroutine) {
    }

    ~CompletableDataProducingCoroutine() {
        if (m_coroutine) { m_coroutine.destroy(); }
    }

    CompletableDataProducingCoroutine() = default;

    CompletableDataProducingCoroutine(CompletableDataProducingCoroutine const&) = delete;

    CompletableDataProducingCoroutine& operator=(CompletableDataProducingCoroutine const&) = delete;

    CompletableDataProducingCoroutine(CompletableDataProducingCoroutine&& other)
        :m_coroutine(other.m_coroutine) {
        other.m_coroutine = nullptr;
    }

    CompletableDataProducingCoroutine& operator=(CompletableDataProducingCoroutine&& other) {
        if (&other != this) {
            m_coroutine = other.m_coroutine;
            other.m_coroutine = nullptr;
        }
        return *this;
    }

    T get() {
        return m_coroutine.promise().m_value;
    }

    struct awaiter;

    awaiter operator co_await() noexcept {
        awaiter returnObject = awaiter{ *this };

        return returnObject;
    }

    void complete() {
        m_coroutine.resume();
    }

    struct awaiter {
        CompletableDataProducingCoroutine& m_resumable;

        awaiter(CompletableDataProducingCoroutine& resumable)  noexcept
            :m_resumable(resumable) {

        }

        bool await_ready() {
            cout << "CompletableDataProducingCoroutine::await_ready\n";
            return false;
        }

        void await_resume() {
            cout << "CompletableDataProducingCoroutine::await_resume\n";
        }

        void await_suspend(coroutine_handle<> waitingCoroutine) {
            cout << "CompletableDataProducingCoroutine::await_suspend\n";
            m_resumable.m_waitingCoroutine = waitingCoroutine;
        }
    };

private:
    coroutine_handle<> m_waitingCoroutine;

};