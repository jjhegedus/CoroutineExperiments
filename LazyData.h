#pragma once

#include "LazyDataCoroutine.h"

template <typename T>
class LazyData
{
public:
    LazyData() {

    }

    LazyData(T value)
        : m_coroutine(value) {
    }

    ~LazyData() {

    }

    operator T() {
        return getData();
    }

    void Set(T value) {
        m_coroutine.setData(value);
    }

private:
    LazyDataCoroutine<T> m_coroutine;

    AwaitableDataProducingCoroutine<T> getData() {
        co_return m_coroutine;
    }

};

