#include <iostream>
#include <string>
#include <signal.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>

using namespace std;

void signalHandler(int signal){
	cout << "The process was ended with a signal " << signal << '\n';
	exit(0);
}

void* printRandomNumber(void*) {
    while (true) {
        cout << (double)rand() / (double)RAND_MAX << '\n';
        sleep(2);
    }
}

void* reverseString(void*) {
    while (true) {
        string str;
        cin >> str;
        for(int i = str.length() - 1; i >= 0; --i){
		cout << str[i];
	}

	cout << '\n';
    }
}

int main(){
	signal(SIGINT, signalHandler);
	pthread_t thread1, thread2;

	int ret1 = pthread_create(&thread1, NULL, printRandomNumber, NULL);
	int ret2 = pthread_create(&thread2, NULL, reverseString, NULL);
	while(true);
	return 0;
}
