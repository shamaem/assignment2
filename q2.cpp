#include <iostream>
#include <fstream>

struct Node {
    int Value;
    Node* next;
};

struct mediancalculator {
    Node* Start;
    int count;

    void initialize() {
        Start = NULL;
        count = 0;
    }

    void insertvalue(int Value) {
        Node* newnode = new Node;
        newnode->Value = Value;

        if (!Start || Value < Start->Value) {
            newnode->next = Start;
            Start = newnode;
        } else {
            Node* current = Start;
            Node* previous = NULL;

            while (current && Value >= current->Value) {
                previous = current;
                current = current->next;
            }

            previous->next = newnode;
            newnode->next = current;
        }

        count++;
    }

    double calculatemedian() {
        if (count == 0) {
            return -1;                     // No elements in the stream
        }

        Node* slow = Start;
        Node* fast = Start;
        Node* previous = NULL;

        while (fast != NULL && fast->next != NULL) {
            previous = slow;
            slow = slow->next;
            fast = fast->next->next;
        }

        if (count % 2 == 1) {
            return slow->Value;
        } else {
            return (double)(previous->Value + slow->Value) / 2.0;
        }
    }
};

int main() {
    mediancalculator calculator;
    calculator.initialize();

    std::ifstream input_file("C:/Users/Dell/Desktop/Test03.txt");
    int Value;

    while (input_file >> Value) {
        calculator.insertvalue(Value);
        std::cout << Value << " median " << calculator.calculatemedian() << std::endl;
    }

    input_file.close();

    return 0;
}
