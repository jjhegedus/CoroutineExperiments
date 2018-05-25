#include "stdafx.h"

#include "IntProducingCoroutine.h"

IntProducingCoroutine::IntProducingCoroutine(HandleType h)
    : m_coroutineHandle(h) {

}

IntProducingCoroutine IntProducingCoroutine::promise_type::get_return_object() {
    return IntProducingCoroutine(HandleType::from_promise(*this)); }

std::experimental::suspend_never IntProducingCoroutine::promise_type::initial_suspend() { return {}; }

std::experimental::suspend_always IntProducingCoroutine::promise_type::final_suspend() { return {}; }

void IntProducingCoroutine::promise_type::return_value(int i) {
    m_value = i;
}

void IntProducingCoroutine::promise_type::unhandled_exception() {}