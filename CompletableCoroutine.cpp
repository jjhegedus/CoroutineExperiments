#include "stdafx.h"
#include "CompletableCoroutine.h"



CompletableCoroutine CompletableCoroutine::promise_type::get_return_object() {
    return CompletableCoroutine(std::experimental::coroutine_handle<promise_type>::from_promise(*this));
}

auto CompletableCoroutine::promise_type::initial_suspend() { return std::experimental::suspend_never{}; }
auto CompletableCoroutine::promise_type::final_suspend() { return std::experimental::suspend_never{}; }

void CompletableCoroutine::promise_type::return_void() {};


CompletableCoroutine::CompletableCoroutine(std::experimental::coroutine_handle<promise_type> coroutine)
    : _coroutine(coroutine) {}

CompletableCoroutine::~CompletableCoroutine() {
    if (_coroutine) { _coroutine.destroy(); }
}

CompletableCoroutine::CompletableCoroutine(CompletableCoroutine&& other)
    :_coroutine(other._coroutine) {
    other._coroutine = nullptr;
}

CompletableCoroutine& CompletableCoroutine::operator=(CompletableCoroutine&& other) {
    if (&other != this) {
        _coroutine = other._coroutine;
        other._coroutine = nullptr;
    }
    return *this;
}

CompletableCoroutine::awaiter::awaiter(CompletableCoroutine& resumable) noexcept
    :m_resumable(resumable) {

}

bool CompletableCoroutine::awaiter::await_ready() {
    cout << "CompletableCoroutine::await_ready\n";
    return false;
}

void CompletableCoroutine::awaiter::await_resume() {
    cout << "CompletableCoroutine::await_resume\n";
}

void CompletableCoroutine::awaiter::await_suspend(coroutine_handle<> waitingCoroutine) {
    cout << "CompletableCoroutine::await_suspend\n";
    m_resumable.m_waitingCoroutine = waitingCoroutine;
}

CompletableCoroutine::awaiter CompletableCoroutine::operator co_await() noexcept {
    awaiter returnObject = awaiter{ *this };

    return returnObject;
}

void CompletableCoroutine::complete() {

    m_waitingCoroutine.resume();
}