#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

int N = 180;
int MinCus = 30;
int MaxCus = 100;
int MinServ = 2;
int MaxServ = 15;
int Cashiers = 1;

struct Customer {
    int id;
    int arrival;
    int service;
    int wait;
    int departure;
};

int randint(int min, int max) {
    return min + rand() % (max - min + 1);
}

void getSettings() {
    cout << "enter num of minutes for simulation default " << N << ": ";
    string input;
    getline(cin, input);
    if (!input.empty()) N = stoi(input);

    cout << "enter min customers default " << MinCus << ": ";
    getline(cin, input);
    if (!input.empty()) MinCus = stoi(input);

    cout << "enter max customers default " << MaxCus << ": ";
    getline(cin, input);
    if (!input.empty()) MaxCus = stoi(input);

    cout << "enter min service time default " << MinServ << ": ";
    getline(cin, input);
    if (!input.empty()) MinServ = stoi(input);

    cout << "enter max service time default " << MaxServ << ": ";
    getline(cin, input);
    if (!input.empty()) MaxServ = stoi(input);

    cout << "enter num of cashiers default " << Cashiers << ": ";
    getline(cin, input);
    if (!input.empty()) Cashiers = stoi(input);
}

int main() {
    srand(time(0));

    cout << "queue simulation bank manager edition" << endl;
    cout << "use default settings  y/n: ";
    string choice;
    getline(cin, choice);
    if (choice == "n" || choice == "N") {
        getSettings();
    }

    int numCus = randint(MinCus, MaxCus);
    vector<Customer> customers;
    for (int i = 0; i < numCus; i++) {
        Customer c;
        c.id = i + 1;
        c.arrival = randint(0, N);
        c.service = randint(MinServ, MaxServ);
        c.wait = 0;
        c.departure = 0;
        customers.push_back(c);
    }

    sort(customers.begin(), customers.end(), [](Customer a, Customer b) {
        return a.arrival < b.arrival;
    });

    queue<Customer> q;
    vector<int> cashierFree(Cashiers, 0);
    int nextCustomer = 0;
    int totalWait = 0;
    int totalService = 0;
    int served = 0;

    for (int t = 0; t <= N * 3; t++) {
        while (nextCustomer < numCus && customers[nextCustomer].arrival <= t) {
            q.push(customers[nextCustomer]);
            nextCustomer++;
        }

        for (int c = 0; c < Cashiers; c++) {
            if (cashierFree[c] <= t && !q.empty()) {
                Customer cur = q.front();
                q.pop();
                cur.wait = t - cur.arrival;
                if (cur.wait < 0) cur.wait = 0;
                cur.departure = t + cur.service;
                cashierFree[c] = cur.departure;
                totalWait += cur.wait;
                totalService += cur.service;
                served++;

                cout << "customer #" << cur.id
                     << " arrival " << cur.arrival
                     << " wait " << cur.wait
                     << " service " << cur.service
                     << " departure " << cur.departure << endl;
            }
        }
    }

    int remaining = q.size();

    cout << endl;
    cout << "  simulation summary " << endl;
    cout << "number of cashiers  " << Cashiers << endl;
    cout << "number of customers  " << numCus << endl;
    cout << "average service time " << fixed << setprecision(2) << (double)totalService / served << endl;
    cout << "average wait time  " << fixed << setprecision(2) << (double)totalWait / served << endl;
    cout << "customers at end of simulation " << remaining << endl;

    return 0;
}
