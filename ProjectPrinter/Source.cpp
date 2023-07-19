#include <iostream>
#include <queue>
#include <stack>
#include <ctime>

struct Client {
    std::string name;
    int priority;

    Client(const std::string& name, int priority) : name(name), priority(priority) {}
};

std::queue<Client> printQueue;
std::stack<std::string> printStatistics;

void addToPrintQueue(const std::string& name, int priority) {
    printQueue.emplace(name, priority);
}

std::string getCurrentTime() {
    char currentTimeStr[9];
    time_t currentTime;
    time(&currentTime);
    tm timeInfo;
#ifdef _WIN32
    localtime_s(&timeInfo, &currentTime);
#else
    localtime_r(&currentTime, &timeInfo);
#endif
    strftime(currentTimeStr, sizeof(currentTimeStr), "%H:%M:%S", &timeInfo);
    return currentTimeStr;
}

void printNextDocument() {
    if (!printQueue.empty()) {
        Client nextClient = printQueue.front();
        printQueue.pop();
        std::cout << "Printing document for client: " << nextClient.name << " (Priority: " << nextClient.priority << ")" << std::endl;

        std::string printTime = getCurrentTime();
        std::string statistics = "Client: " + nextClient.name + ", Print Time: " + printTime;
        printStatistics.push(statistics);
    }
    else {
        std::cout << "The print queue is empty." << std::endl;
    }
}

void displayPrintStatistics() {
    std::cout << "Print Statistics:" << std::endl;
    while (!printStatistics.empty()) {
        std::cout << printStatistics.top() << std::endl;
        printStatistics.pop();
    }
}

int main() {
    int numClients;
    std::cout << "Enter the number of clients: ";
    std::cin >> numClients;

    for (int i = 0; i < numClients; ++i) {
        std::string name;
        int priority;

        std::cout << "Enter the name of client " << i + 1 << ": ";
        std::cin >> name;
        std::cout << "Enter the priority of client " << i + 1 << ": ";
        std::cin >> priority;

        addToPrintQueue(name, priority);
    }

    std::cout << "Printing documents..." << std::endl;
    while (!printQueue.empty()) {
        printNextDocument();
    }

    int numStatistics;
    std::cout << "Enter the number of print statistics: ";
    std::cin >> numStatistics;

    for (int i = 0; i < numStatistics; ++i) {
        std::string name, printTime;

        std::cout << "Enter the name of the client for statistics " << i + 1 << ": ";
        std::cin >> name;
        std::cout << "Enter the print time for statistics " << i + 1 << ": ";
        std::cin >> printTime;

        std::string statistics = "Client: " + name + ", Print Time: " + printTime;
        printStatistics.push(statistics);
    }

    displayPrintStatistics();

    return 0;
}