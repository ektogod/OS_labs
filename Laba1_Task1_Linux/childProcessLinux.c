#include <iostream>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

void signalHandling(int signalNumber){}

int main() {
        int wstatus;
        pid_t pid = fork();
        if (pid < 0) {
                std::cout << "We couldn't create a new process";
                exit(EXIT_FAILURE);
        }
        else if (pid == 0) {
                        for (int i = 0; i < 5; ++i) {
                                std::cout << "I'm the child process and I'm doing something...\n";
                                sleep(1);
                        }

                        _exit(2);
        }
        else {
                signal(SIGINT, signalHandling);
                wait(&wstatus);
                if(WIFEXITED(wstatus)){
                        std::cout << "The child process was stopped normally\n";
                }
                else if(WIFSIGNALED(wstatus)){
                        std::cout << "The child process was stopped by a signal " << WTERMSIG(wstatus) << '\n';
			exit(EXIT_SUCCESS);
                }
        }
	
        return 0;
}
                    
