//Qno:1
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Node {
    int data;
    Node* next;
};

class Restaurant {
private:
    Node* head;
    Node* mid1;
    Node* mid2;
    int size;

public:
    Restaurant() : head(nullptr), mid1(nullptr), mid2(nullptr), size(0) {}

    void Add(int number) {
        Node* new_node = new Node;
        new_node->data = number;
        new_node->next = nullptr;

        if (head == nullptr) {
            head = new_node;
            mid1 = mid2 = head;
        } else {
            head->next = new_node;
            head = new_node;

            if (size % 2 == 1) {
                mid2 = mid2->next;
            } else {
                mid1 = mid1->next;
                mid2 = mid1->next;
            }
        }

        size++;
    }

    void Delete() {
        if (size == 0) {
            cout << "No customers to delete." << endl;
            return;
        }

        Node* temp = head;
        while (temp->next != head) {
            temp = temp->next;
        }

        delete head;
        head = temp;
        head->next = nullptr;

        if (size % 2 == 1) {
            mid2 = temp;
        } else {
            mid1 = temp;
            mid2 = mid1->next;
        }

        size--;
    }

    void GetTrump() {
        if (size == 0) {
            cout << "No customers." << endl;
            return;
        }

        if (size % 2 == 1) {
            cout << "The lucky winner is: " << mid1->data << endl;
        } else {
            cout << "The lucky winners are: " << mid1->data << " and " << mid2->data << endl;
        }
    }
};

int main() {
    Restaurant restaurant;

    ifstream inputFile("C:/Desktop/Test01.txt");

    if (!inputFile.is_open()) {
        cout << "Error opening input file." << endl;
        return 1;
    }

    string command;
    int number;

    while (inputFile >> command) {
        if (command == "ADD") {
            inputFile >> number;
            restaurant.Add(number);
        } else if (command == "DELETE") {
            restaurant.Delete();
        } else if (command == "END") {
            break;
        }
    }

    inputFile.close();

    restaurant.GetTrump();

    return 0;
}
