#include <iostream>
#include <algorithm>
using namespace std;

struct Job {
    char id;
    int deadline;
    int profit;
};

bool compare(Job a, Job b) {
    return a.profit > b.profit;
}

int main() {
    int n;

    cout << "Enter number of jobs: ";
    cin >> n;

    Job jobs[n];

    for (int i = 0; i < n; i++) {
        cout << "Enter Job ID, Deadline and Profit for job "
             << i + 1 << ": ";
        cin >> jobs[i].id >> jobs[i].deadline >> jobs[i].profit;
    }

    // Sort jobs according to decreasing profit
    sort(jobs, jobs + n, compare);

    // Find maximum deadline
    int maxDeadline = 0;
    for (int i = 0; i < n; i++) {
        if (jobs[i].deadline > maxDeadline)
            maxDeadline = jobs[i].deadline;
    }

    // Time slots
    char slot[maxDeadline + 1];
    for (int i = 0; i <= maxDeadline; i++)
        slot[i] = '-';

    int totalProfit = 0;

    // Schedule jobs
    for (int i = 0; i < n; i++) {
        for (int j = jobs[i].deadline; j >= 1; j--) {

            if (slot[j] == '-') {
                slot[j] = jobs[i].id;
                totalProfit += jobs[i].profit;
                break;
            }
        }
    }

    cout << "\nJob Sequence: ";

    for (int i = 1; i <= maxDeadline; i++) {
        if (slot[i] != '-')
            cout << slot[i] << " ";
    }

    cout << "\nMaximum Profit: " << totalProfit << endl;

    return 0;
}