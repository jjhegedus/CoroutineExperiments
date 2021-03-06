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
#include "AwaitableDataProducingCoroutine.h"
#include "LazyDataCoroutine.h"
#include "LazyData.h"

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

AwaitableDataProducingCoroutine<string> GetDataFromAwaitableDataProducingCoroutine() {

    cout << "Executing GetDataFromAwaitableDataProducingCoroutine\n";

    co_return "string data from AwaitableDataProducingCoroutine";
}

AwaitableDataProducingCoroutine<string> testGetDataFromAwaitableDataProducingCoroutine() {
    cout << "executing testGetDataFromAwaitableDataProducingCoroutine\n";

    string returnValue = co_await GetDataFromAwaitableDataProducingCoroutine();

    cout << "co_await on GetDataFromAwaitableDataProducingCoroutine() produced '" << returnValue << "'\n";

    co_return returnValue;
}

AwaitableDataProducingCoroutine<int> Return1() {
    co_return 1;
}



AwaitableDataProducingCoroutine<int> Return2() {
    co_return 2;
}

AwaitableDataProducingCoroutine<int> testComposingAwaitables() {
    co_return co_await Return1() + co_await Return2();
}



CompletableDataProducingCoroutine<string> TestLazyDataCoroutine() {
    cout << "Executing TestLazyDataCoroutine\n";

    LazyDataCoroutine<string> lazyDataCoroutine;

    co_await lazyDataCoroutine;

    cout << "TestLazyDataCoroutine resumed\n";

    lazyDataCoroutine.setData("Data set to LazyDataCoroutine");

    co_return co_await lazyDataCoroutine;
}


VoidCoroutine TestLazyDataCoroutineWithInitialValue() {
    cout << "Executing TestLazyDataCoroutineWithInitialValue\n";

    LazyDataCoroutine<string> lazyDataCoroutine("Initial Value for LazyDataCoroutine");

    co_await lazyDataCoroutine;

    cout << "lazyDataCoroutine = '" << co_await lazyDataCoroutine << "'\n\n\n";
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

    cout << "returnData.get() = " << returnData.get() << "\n\n\n";




    CompletableDataProducingCoroutine<string> completableDataProducingCoroutine = GetDataFromCompletableDataProducingCoroutine();

    for (int i = 0; ; i++) {
        cout << "i = " << i << "\n";
        this_thread::sleep_for(10ms);

        if (i == 10) {
            completableDataProducingCoroutine.complete();
            break;
        }
    }

    cout << "completableDataProducingCoroutine.get() = '" << completableDataProducingCoroutine.get() << "'\n";


    


    AwaitableDataProducingCoroutine<string> awaitableDataProductingCoroutine = testGetDataFromAwaitableDataProducingCoroutine();
    cout << "awaitableDataProducingCoroutine produced an AwaitableDataProducingCoroutine with the data '" << awaitableDataProductingCoroutine.get() << "'\n\n\n";


    AwaitableDataProducingCoroutine<int> awaitSum = testComposingAwaitables();
    cout << "testComposingAwaitables() returns " << awaitSum.get() << "\n\n\n";



    CompletableDataProducingCoroutine<string> testLazyDataCoroutine = TestLazyDataCoroutine();

    for (int i = 0; ; i++) {
        cout << "i = " << i << "\n";
        this_thread::sleep_for(10ms);

        if (i == 10) {
            testLazyDataCoroutine.complete();
            break;
        }
    }

    cout << "testLazyDataCoroutine.get() = " << testLazyDataCoroutine.get() << "\n\n\n";



    TestLazyDataCoroutineWithInitialValue();


    LazyData<string> lazyData("initial string");
    cout << "lazyData = '" << static_cast<string>(lazyData) << "'\n\n\n";



    LazyData<string> lazyDataNoInitialData;
    cout << "lazyDataNoInitialData = '" << static_cast<string>(lazyDataNoInitialData) << "'\n\n\n";


    system("pause");


    return 0;
}

