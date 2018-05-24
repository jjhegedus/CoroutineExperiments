// CoroutineExperiments.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <experimental\coroutine>
#include <iostream>
#include <string>
#include <thread>
#include <chrono>

#include "VoidCoroutine.h"

#include "CompletableCoroutine.h"

using namespace std;
using namespace std::experimental;
using namespace std::chrono_literals;




VoidCoroutine WaitForCompletion(CompletableCoroutine& completableCoroutine) {

    co_await completableCoroutine;

    cout << "Completed\n";
}


int main() {

    CompletableCoroutine completableCoroutine;
    WaitForCompletion(completableCoroutine);

    for (int i = 0; ; i++) {
        cout << "i = " << i << "\n";
        this_thread::sleep_for(10ms);

        if (i == 10) {
            completableCoroutine.complete();
            break;
        }
    }

    system("pause");

    return 0;
}

