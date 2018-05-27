#pragma once

#include "ReactiveDataCoroutine.h"

template <typename T>
class ReactiveData
{
public:
    ReactiveData() {

    }

    ReactiveData(T value) 
        : m_value(value) {
    }

    ~ReactiveData() {

    }

    operator T() {
        return getData();
    }

    void Set(T value) {
        m_value = value;
        m_set = true;
        m_reactiveDataCoroutine.complete();
    }

private:
    T m_value;
    bool m_set = false;
    ReactiveDataCoroutine<T> m_reactiveDataCoroutine = getDataCoawait();

    T getData() {
        if (m_set) {
            return m_value;
        }
        else {
            m_reactiveDataCoroutine.get();
        }
    }

    ReactiveDataCoroutine<T> getDataCoawait() {
        co_return m_value;
    }

};

