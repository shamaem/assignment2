#include <iostream>
#include <fstream>
#include <unordered_set>
using namespace std;

struct Transaction {
    int transactionId;
    double transactionAmount;
    Transaction* next;
    Transaction(int id, double amount) : transactionId(id), transactionAmount(amount), next(nullptr) {}
};

struct TransactionList {
    Transaction* start;
    Transaction* last;

    TransactionList() : start(nullptr), last(nullptr) {}

    void addTransaction(int id, double amount) {
        Transaction* newTransaction = new Transaction(id, amount);
        if (start == nullptr) {
            start = last = newTransaction;
        } else {
            last->next = newTransaction;
            last = newTransaction;
        }
    }

    void reverseFraudulentTransactions(const unordered_set<int>& fraudIds) {
        Transaction* curr = start;
        Transaction* prev = nullptr;

        while (curr) {
            if (fraudIds.find(curr->transactionId) != fraudIds.end()) {
                curr->transactionAmount *= -1; // Reverse the amount
            }

            prev = curr;
            curr = curr->next;
        }
    }

    ~TransactionList() {
        while (start) {
            Transaction* temp = start;
            start = start->next;
            delete temp;
        }
    }
};

int main() {
    TransactionList transactions;
    unordered_set<int> fraudIds;

    ifstream inputFile("C:/Users/Dell/Desktop/Test04.txt"); 

    if (!inputFile.is_open()) {
        cout << "Error Opening File" << endl;
        return 1;
    }

    int numTransactions, numFraudulentTransactions;
    inputFile >> numTransactions >> numFraudulentTransactions;

    for (int i = 0; i < numTransactions; ++i) {
        int id;
        double amount;
        inputFile >> id >> amount;
        transactions.addTransaction(id, amount);
    }

    for (int i = 0; i < numFraudulentTransactions; ++i) {
        int fraudId;
        inputFile >> fraudId;
        fraudIds.insert(fraudId);
    }

    inputFile.close();

    // Reverse fraudulent transactions
    transactions.reverseFraudulentTransactions(fraudIds);

    // Print transactions
    Transaction* curr = transactions.start;
    while (curr) {
        cout << "Transaction ID: " << curr->transactionId << ", Amount: " << curr->transactionAmount << endl;
        curr = curr->next;
    }

    return 0;
}
