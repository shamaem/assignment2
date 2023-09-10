#include <iostream>
#include <fstream>
using namespace std;

struct Node {
    int Data;
    Node* Next;
};

// Function to find the third last element
int findThirdLast(Node* Start) {
    if (Start == NULL || Start->Next == NULL || Start->Next->Next == NULL) {
        return -1;                                                       // List contains less than 3 elements
    }

    Node* first = Start;
    Node* third = Start;
    Node* last = Start;

    // Move the third pointer two steps ahead
    for (int i = 0; i < 2; i++) {
        third = third->Next;
    }

    // Move all three pointers until third pointer reaches the end
    while (third->Next != NULL) {
        first = first->Next;
        third = third->Next;
        last = last->Next;
    }

    return first->Data;
}

int main() {
    Node* Start = NULL;
    ifstream inputFile("t");     //Taking input from file
    if (!inputFile.is_open()) {
        cout << "Error Opening File" << endl;
        return 1;
    }

    int num;
    while (inputFile >> num) {
        Node* newNode = new Node{num, NULL};

        if (Start == NULL) {
            Start = newNode;
        } else {
            Node* temp = Start;
            while (temp->Next != NULL) {
                temp = temp->Next;
            }
            temp->Next = newNode;
        }
    }

    inputFile.close();

    int result = findThirdLast(Start);

    if (result != -1) {
        cout << "Third Last Element: " << result << endl;
    } else {
        cout << -1 << endl;
    }

    // Clean up: Delete the linked list
    while (Start) {
        Node* temp = Start;
        Start = Start->Next;
        delete temp;
    }

    return 0;
}
