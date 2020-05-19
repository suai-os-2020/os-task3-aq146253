#include "windows.h"
#include "lab3.h"

//
// lab3 code should be located here!
//

using namespace std;

#define MAX_SEM_COUNT 10

//Threads
HANDLE thread_a, thread_b, thread_c, thread_e, thread_d, thread_f, thread_g, thread_h, thread_i, thread_k, thread_m, thread_n;
//Mutex
HANDLE stdout_mutex;
DWORD tid;
//Synchronized semaphores
HANDLE semI, semH, semG, semF, semE, semFirst, semSecond;

unsigned int lab3_thread_graph_id() 
{
    return 2;
}

const char* lab3_unsynchronized_threads()
{
    return "ikm";
}

const char* lab3_sequential_threads()
{
    return "ihgfe";
}

void wait(HANDLE name) 
{
    WaitForSingleObject(name, INFINITE);
}

DWORD WINAPI a(LPVOID pVoid)
{
    for (int i = 0; i < 3; i++) {
        wait(stdout_mutex);
        cout << "a" << flush;
        ReleaseMutex(stdout_mutex);
        computation();
    }
    return 0;
}

DWORD WINAPI b(LPVOID pVoid)
{
    for (int i = 0; i < 3; i++) {
        wait(stdout_mutex);
        cout << "b" << flush;
        ReleaseMutex(stdout_mutex);
        computation();
    }
    wait(thread_a);
    ReleaseSemaphore(semFirst, 1, NULL);
    for (int i = 0; i < 3; i++) {
        //wait(semFirst);
        wait(stdout_mutex);
        cout << "b" << flush;
        ReleaseMutex(stdout_mutex);
        computation();
        //ReleaseSemaphore(semFirst, 1, NULL);
    }
    //wait(thread_e);
    return 0;
}

DWORD WINAPI c(LPVOID pVoid)
{
    for (int i = 0; i < 3; i++) {
        //wait(semFirst);
        wait(stdout_mutex);
        cout << "c" << flush;
        ReleaseMutex(stdout_mutex);
        computation();
        //ReleaseSemaphore(semFirst, 1, NULL);
    }
    return 0;
}

DWORD WINAPI d(LPVOID pVoid)
{
    for (int i = 0; i < 3; i++) {
        wait(stdout_mutex);
        cout << "d" << flush;
        ReleaseMutex(stdout_mutex);
        computation();
    }
    return 0;
}

DWORD WINAPI e(LPVOID pVoid)
{
    for (int i = 0; i < 3; i++) {
        wait(stdout_mutex);
        cout << "e" << flush;
        ReleaseMutex(stdout_mutex);
        computation();
    }
    wait(thread_c);
    wait(thread_d);
    ReleaseSemaphore(semSecond, 1, NULL);
    ReleaseSemaphore(semI, 1, NULL);
    
    for (int i = 0; i < 3; i++) {
        wait(semE);
        wait(stdout_mutex);
        cout << "e" << flush;
        ReleaseMutex(stdout_mutex);
        computation();
        ReleaseSemaphore(semI, 1, NULL);
    }
    //wait(thread_i);
    return 0;
}

DWORD WINAPI f(LPVOID pVoid)
{
    for (int i = 0; i < 3; i++) {
        wait(semF);
        wait(stdout_mutex);
        cout << "f" << flush;
        ReleaseMutex(stdout_mutex);
        computation();
        ReleaseSemaphore(semE, 1, NULL);
    }
    return 0;
}

DWORD WINAPI g(LPVOID pVoid)
{
    for (int i = 0; i < 3; i++) {
        wait(semG);
        wait(stdout_mutex);
        cout << "g" << flush;
        ReleaseMutex(stdout_mutex);
        computation();
        ReleaseSemaphore(semF, 1, NULL);
    }
    return 0;
}

DWORD WINAPI h(LPVOID pVoid)
{
    for (int i = 0; i < 3; i++) {
        wait(semH);
        wait(stdout_mutex);
        cout << "h" << flush;
        ReleaseMutex(stdout_mutex);
        computation();
        ReleaseSemaphore(semG, 1, NULL);
    }
    return 0;
}

DWORD WINAPI i(LPVOID pVoid)
{
    for (int i = 0; i < 3; i++) {
        wait(semI);
        wait(stdout_mutex);
        cout << "i" << flush;
        ReleaseMutex(stdout_mutex);
        computation();
        ReleaseSemaphore(semH, 1, NULL);
    }
    wait(thread_e);
    for (int i = 0; i < 3; i++) {
        wait(stdout_mutex);
        cout << "i" << flush;
        ReleaseMutex(stdout_mutex);
        computation();
    }
    return 0;
}

DWORD WINAPI k(LPVOID pVoid)
{
    for (int i = 0; i < 3; i++) {
        wait(stdout_mutex);
        cout << "k" << flush;
        ReleaseMutex(stdout_mutex);
        computation();
    }
    return 0;
}

DWORD WINAPI m(LPVOID pVoid)
{
    for (int i = 0; i < 3; i++) {
        wait(stdout_mutex);
        cout << "m" << flush;
        ReleaseMutex(stdout_mutex);
        computation();
    }
    return 0;
}

DWORD WINAPI n(LPVOID pVoid)
{
    for (int i = 0; i < 3; i++) {
        wait(stdout_mutex);
        cout << "n" << flush;
        ReleaseMutex(stdout_mutex);
        computation();
    }
    return 0;
}

int lab3_init()
{
    int inc = 10;

    stdout_mutex = CreateMutex(NULL, false, NULL);
    if (stdout_mutex == NULL)
        return GetLastError();

    semFirst = CreateSemaphore(NULL, 0, MAX_SEM_COUNT, NULL);
    semSecond = CreateSemaphore(NULL, 0, MAX_SEM_COUNT, NULL);
    semI = CreateSemaphore(NULL, 0, MAX_SEM_COUNT, NULL);
    semH = CreateSemaphore(NULL, 0, MAX_SEM_COUNT, NULL);
    semG = CreateSemaphore(NULL, 0, MAX_SEM_COUNT, NULL);
    semF = CreateSemaphore(NULL, 0, MAX_SEM_COUNT, NULL);
    semE = CreateSemaphore(NULL, 0, MAX_SEM_COUNT, NULL);

    // start thread A, B
    thread_a = CreateThread(NULL, 0, (a), 0, 0, &tid);
    if (thread_a == NULL)
        return GetLastError();
    thread_b = CreateThread(NULL, 0, (b), 0, 0, &tid);
    if (thread_b == NULL)
        return GetLastError();

    // wait for thread A to finish
    wait(thread_a);

    wait(semFirst);

    thread_c = CreateThread(NULL, 0, (c), 0, 0, &tid);
    if (thread_c == NULL)
        return GetLastError();
    thread_d = CreateThread(NULL, 0, (d), 0, 0, &tid);
    if (thread_d == NULL)
        return GetLastError();
    thread_e = CreateThread(NULL, 0, (e), 0, 0, &tid);
    if (thread_e == NULL)
        return GetLastError();

    wait(thread_c);
    wait(thread_b);
    wait(thread_d);

    wait(semSecond);
    thread_i = CreateThread(NULL, 0, (i), 0, 0, &tid);
    if (thread_i == NULL)
        return GetLastError();
    thread_h = CreateThread(NULL, 0, (h), 0, 0, &tid);
    if (thread_h == NULL)
        return GetLastError();
    thread_g = CreateThread(NULL, 0, (g), 0, 0, &tid);
    if (thread_g == NULL)
        return GetLastError();
    thread_f = CreateThread(NULL, 0, (f), 0, 0, &tid);
    if (thread_f == NULL)
        return GetLastError();

    wait(thread_g);
    wait(thread_f);
    wait(thread_e);
    wait(thread_h);
    
    thread_k = CreateThread(NULL, 0, (k), 0, 0, &tid);
    if (thread_k == NULL)
        return GetLastError();
    thread_m = CreateThread(NULL, 0, (m), 0, 0, &tid);
    if (thread_m == NULL)
        return GetLastError(); 

    wait(thread_m);
    wait(thread_k); 
    wait(thread_i);

    thread_n = CreateThread(NULL, 0, (n), 0, 0, &tid);
    if (thread_n == NULL)
        return GetLastError();
    wait(thread_n);
    
    CloseHandle(thread_a);
    CloseHandle(thread_b);
    CloseHandle(thread_c);
    CloseHandle(thread_d);
    CloseHandle(thread_e);
    CloseHandle(thread_f);
    CloseHandle(thread_g);
    CloseHandle(thread_h);
    CloseHandle(thread_i);
    CloseHandle(thread_k);
    CloseHandle(thread_m);

    CloseHandle(stdout_mutex);
    cout << endl;
    return 0;
}

