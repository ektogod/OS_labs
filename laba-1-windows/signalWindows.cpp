
#include <stdlib.h>
#include <signal.h>
#include<cstdio>
#include<Windows.h>

void SignalHandler(int signal)
{
    printf("The process was finished by a signal (%d) ", signal);
    _exit(3);
}

int main()
{
    typedef void (*SignalHandlerPointer)(int);

    SignalHandlerPointer previousHandler;
    previousHandler = signal(SIGINT, SignalHandler);

    while (true) {
        printf("I'm working...\n");
        Sleep(1000);
    }

    abort();
}