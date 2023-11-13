#include <iostream>
#include <vector>
#include <cmath>
#include <stdlib.h>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <unistd.h>

using namespace std;

mutex bankAccountMutex;
mutex lockMutex;
condition_variable cv;
double bankAccountValue = 120;

void changeBalance(double operation) {
    cout << "Changing balance...\n";
    sleep(1);
    bankAccountValue += operation;
    cout << "Balance has been changed successfully!\n";
}


void performScenario(vector<double> operations) {
    unique_lock<mutex> lck(bankAccountMutex);
    double oldValue;
    int counter = 0;
    for (int i = 0; i < operations.size(); ++i) {
        oldValue = bankAccountValue;
        if (operations[i] < 0 && abs(operations[i]) > oldValue) {
            cout << "Failed to carry out the operation!\n\n";
            lck.unlock();
            while(true) {
                sleep(2);
                cout << "Trying to carry out failed operation...\n\n";
                if (bankAccountValue >= abs(operations[i])) {
                    thread balance(changeBalance, operations[i]);
                    cout << "Carrying out a failed operation...\n\n";
                    balance.join();
                    //lck.lock();    // при добавлении процесс ждет, пока завершаться все остальные
                    break;
                }
                if (counter == 5) {
                    cout << "closing...";
                    return;
                }
            }
           
            continue;
        }

        thread balance (changeBalance, operations[i]);
        balance.join();
        cout << "Old value: " << oldValue << "\nOperation: " << operations[i] << "\nCurrent value: " << bankAccountValue << "\n\n";
        
        sleep(2);
    }
}

void user() {
    string str;
    while (true) {
        cin >> str;
        if (str == "1") {
            cout << "Current bank account value: " << bankAccountValue << '\n';
        }
        else if (str == "2") {
            int n, maxValue, minValue;
            cout << "Enter number of operations: \n";
            cin >> n;
            cout << "Enter minimal possible value: \n";
            cin >> minValue;
            cout << "Enter max possible value: \n";
            cin >> maxValue;
            vector<double> newScenario;
            for (int i = 0; i < n; ++i) {
                int operation = minValue + rand() % (maxValue - minValue + 1);
                newScenario.push_back(operation);
            }

            thread operation(performScenario, newScenario);
            operation.detach();
        }
    }
}


int main()
{
    vector<double> operations1 = { 0, -150, 30, 0, 0 };
    vector<double> operations2 = { 20, 5, 5 };
    vector<double> operations3 = { 20, 5, 5 };

    thread userThread(user);
    userThread.detach();

    thread thread1 (performScenario, operations1);
    thread thread2 (performScenario, operations2);
    thread thread3 (performScenario, operations3);

    thread1.join();
    thread2.join();
    thread3.join();

    return 0;
}
