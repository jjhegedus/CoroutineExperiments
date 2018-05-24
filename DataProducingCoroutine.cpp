#include "stdafx.h"

#include "DataProducingCoroutine.h"

DataProducingCoroutine DataProducingCoroutine::promise_type::get_return_object() { return {}; }
std::experimental::suspend_never DataProducingCoroutine::promise_type::initial_suspend() { return {}; }
std::experimental::suspend_never DataProducingCoroutine::promise_type::final_suspend() { return {}; }
void DataProducingCoroutine::promise_type::return_void() {}
void DataProducingCoroutine::promise_type::unhandled_exception() {}