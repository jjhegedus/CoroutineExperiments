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

class CompletableCoroutine {

public:

    struct promise_type {
        CompletableCoroutine get_return_object();

        auto initial_suspend();
        auto final_suspend();

        void return_void();

    };

    std::experimental::coroutine_handle<promise_type> _coroutine = nullptr;

    explicit CompletableCoroutine(std::experimental::coroutine_handle<promise_type> coroutine);

    ~CompletableCoroutine();

    CompletableCoroutine() = default;

    CompletableCoroutine(CompletableCoroutine const&) = delete;

    CompletableCoroutine& operator=(CompletableCoroutine const&) = delete;

    CompletableCoroutine(CompletableCoroutine&& other);

    CompletableCoroutine& operator=(CompletableCoroutine&& other);

    struct awaiter;

    awaiter operator co_await() noexcept;

    void complete();

    struct awaiter {
        CompletableCoroutine& m_resumable;

        awaiter(CompletableCoroutine& resumable) noexcept;

        bool await_ready();

        void await_resume();

        void await_suspend(coroutine_handle<> waitingCoroutine);
    };

private:
    coroutine_handle<> m_waitingCoroutine;

};