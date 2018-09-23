#pragma once

#include "LazyDataCoroutine.h"
#include "AwaitableDataProducingCoroutine.h"

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
        return getData().get();
    }

    void Set(T value) {
        m_coroutine.setData(value);
    }

private:
    LazyDataCoroutine<T> m_coroutine;

    AwaitableDataProducingCoroutine<T> getData() {
        T returnData = co_await m_coroutine;
        
        cout << "LazyData::getData: after co_await returns\n";

        co_return returnData;
    }

};

