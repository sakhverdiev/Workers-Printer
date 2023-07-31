#include <iostream>
#include <string>
#include <Windows.h> // Sleep() ucun

using namespace std;

class Worker {
public:
    int id;
    string name;
    string surname;
    int age;
    int pageCount;

    Worker(int id, const string& name, const string& surname, int age, int pageCount)
        : id(id), name(name), surname(surname), age(age), pageCount(pageCount) {}
};

class Printer {
private:
    Worker** workerQueue;
    int queueSize;
    int currentIndex;

public:
    Printer() : workerQueue(nullptr), queueSize(0), currentIndex(0) {}

    void addToQueue(const Worker& worker) {
        Worker** newQueue = new Worker*[queueSize + 1];

        for (int i = 0; i < queueSize; i++) {
            newQueue[i] = workerQueue[i];
        }

        newQueue[queueSize] = new Worker(worker);

        delete[] workerQueue;
        workerQueue = newQueue;
        queueSize++;
    }

    void start() {
        while (currentIndex < queueSize) {
            Worker* currentWorker = workerQueue[currentIndex];
            printDocuments(*currentWorker);
            delete currentWorker;
            currentIndex++;
        }
    }

    void printDocuments(const Worker& worker) {
        cout << "Isci " << worker.name << " " << worker.surname << " ucun fayl kserks edilir..." << endl;
        Sleep(2000);
        cout << "Isci " << worker.name << " " << worker.surname << " ucun fayl kserks edildi." << endl;
        Sleep(1000);
        cout << endl;
    }

    ~Printer() {
        for (int i = 0; i < queueSize; i++) {
            delete workerQueue[i];
        }
        delete[] workerQueue;
    }
};

int main() {
    Worker worker1(1, "Eli", "Elizade", 30, 10);
    Worker worker2(2, "Veli", "Velizade", 25, 5);
    Worker worker3(3, "Ehmed", "Ehmedov", 35, 8);

    Printer printer;
    printer.addToQueue(worker1);
    printer.addToQueue(worker2);
    printer.addToQueue(worker3);

    printer.start();

    return 0;
}