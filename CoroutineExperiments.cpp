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
#include "IntProducingCoroutine.h"
#include "DataProducingCoroutine.h"
#include "CompletableDataProducingCoroutine.h"

using namespace std;
using namespace std::experimental;
using namespace std::chrono_literals;




VoidCoroutine WaitForCompletion(CompletableCoroutine& completableCoroutine) {

    co_await completableCoroutine;

    cout << "Completed\n";
}

IntProducingCoroutine ProduceInt() {
    co_return 40;
}

DataProducingCoroutine<string> ProduceString() {
    co_return "Returned String\n";
}

DataProducingCoroutine<string> WaitForStringDataCompletion(CompletableCoroutine& completableCoroutine) {

    co_await completableCoroutine;

    cout << "Completed\n";

    co_return "string data from DataProducingCoroutine";
}



CompletableDataProducingCoroutine<string> GetDataFromCompletableDataProducingCoroutine() {
    
    cout << "Executing GetDataFromCompletableDataProducingCoroutine\n";

    co_return "string data from CompletableDataProducingCoroutine";
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

    IntProducingCoroutine x = ProduceInt();
    cout << "x = " << x.get() << "\n";

    DataProducingCoroutine<string> stringData = ProduceString();
    cout << "stringData = " << stringData.get() << "\n";

    CompletableCoroutine completable2;
    DataProducingCoroutine<string> returnData = WaitForStringDataCompletion(completable2);

    for (int i = 0; ; i++) {
        cout << "i = " << i << "\n";
        this_thread::sleep_for(10ms);

        if (i == 10) {
            completable2.complete();
            break;
        }
    }

    cout << "returnData.get() = " << returnData.get() << "\n";

    CompletableDataProducingCoroutine<string> completableDataProducingCoroutine = GetDataFromCompletableDataProducingCoroutine();

    for (int i = 0; ; i++) {
        cout << "i = " << i << "\n";
        this_thread::sleep_for(10ms);

        if (i == 10) {
            completableDataProducingCoroutine.complete();
            break;
        }
    }

    cout << "completableDataProducingCoroutine.get() = " << completableDataProducingCoroutine.get() << "\n";

    system("pause");

    return 0;
}

