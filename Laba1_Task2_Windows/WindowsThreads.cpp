
#include <iostream>
#include <stdio.h>
#include <string>
#include <Windows.h>
#include <processthreadsapi.h>
#include <signal.h>

using namespace std;

void printRandomNumber() {
    while (true) {
        cout << (double)rand() / (double)RAND_MAX << '\n';
        Sleep(2500);
    }
}

void reverseString() {
    while (true) {
        string str;
        cin >> str;
        reverse(str.begin(), str.end());
        cout << str << '\n';
    }
}

void SignalHandler(int signal)
{
    cout << "The process was finished by a signal " << signal;
    _exit(3);
}

int main() {
    CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) reverseString, NULL, 0, NULL);
    CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)printRandomNumber, NULL, 0, NULL);

    typedef void (*SignalHandlerPointer)(int);
    SignalHandlerPointer previousHandler;
    previousHandler = signal(SIGINT, SignalHandler);

    while (true);

    return 0;
}

