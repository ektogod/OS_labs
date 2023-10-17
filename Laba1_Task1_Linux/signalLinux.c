#include <iostream>
#include <signal.h>
#include <unistd.h>

void signalHandling(int signalNumber) {
	std::cout << "The programm was finished by the signal with number:  " << signalNumber << '\n';
	exit(signalNumber);
}

int main() {
	signal(SIGINT, signalHandling);
	while (true) {
		std::cout << "Programm running...\n";
		sleep(1);
	}

	return 0;
}
