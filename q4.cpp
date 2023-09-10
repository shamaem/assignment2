#include <iostream>
#include <fstream>
#include <sstream>
struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

class Editor {
private:
    Node* head;
    Node* cursor;
    Node* prevCursor;

    void printList() {
        std::cout << "List: [";
        Node* temp = head;
        while (temp) {
            std::cout << temp->data;
            if (temp->next) std::cout << ", ";
            temp = temp->next;
        }
        std::cout << "]" << std::endl;
    }

public:
    Editor() : head(nullptr), cursor(nullptr), prevCursor(nullptr) {}

    void addNumber(int val) {
        Node* newNode = new Node(val);
        if (!head) {
            head = newNode;
            cursor = newNode;
        } else {
            cursor->next = newNode;
            cursor = newNode;
        }
        printList();
    }

    void deleteTail() {
        if (!head)
            return;
        if (head == cursor) {
            delete head;
            head = cursor = nullptr;
            return;
        }
        Node* temp = head;
        while (temp->next != cursor)
            temp = temp->next;
        delete cursor;
        cursor = temp;
        cursor->next = nullptr;
        printList();
    }

    void addAtIndex(int index, int val) {
        if (index < 0) return;
        Node* newNode = new Node(val);
        if (index == 0) {
            newNode->next = head;
            head = newNode;
        } else {
            Node* temp = head;
            for (int i = 0; i < index - 1 && temp; i++)
                temp = temp->next;
            if (temp) {
                newNode->next = temp->next;
                temp->next = newNode;
            } else {
                delete newNode; // Invalid index, so delete the new node
            }
        }
        printList();
    }

    void deleteAtIndex(int index) {
        if (index < 0 || !head) return;
        if (index == 0) {
            Node* temp = head;
            head = head->next;
            delete temp;
            if (cursor == temp) cursor = head; // Update cursor if necessary
        } else {
            Node* temp = head;
            for (int i = 0; i < index - 1 && temp->next; i++)
                temp = temp->next;
            if (temp->next) {
                Node* toDelete = temp->next;
                temp->next = toDelete->next;
                delete toDelete;
                if (cursor == toDelete) cursor = temp; // Update cursor if necessary
            }
        }
        printList();
    }

    void moveForward(int steps) {
        for (int i = 0; i < steps && cursor && cursor->next; i++)
            cursor = cursor->next;
        std::cout << "Cursor moved forward by " << steps << " step(s)." << std::endl;
    }

    void moveBackward(int steps) {
        for (int i = 0; i < steps && cursor && cursor != head; i++) {
            Node* temp = head;
            while (temp->next != cursor)
                temp = temp->next;
            cursor = temp;
        }
        std::cout << "Cursor moved backward by " << steps << " step(s)." << std::endl;
    }

    void addImmediate(int val) {
        if (!cursor) return;
        Node* newNode = new Node(val);
        newNode->next = cursor->next;
        cursor->next = newNode;
        printList();
    }

    void deleteImmediate() {
        if (!cursor || !cursor->next) return;
        Node* toDelete = cursor->next;
        cursor->next = toDelete->next;
        delete toDelete;
        printList();
    }

    void printCursorData() {
        if (cursor)
            std::cout << cursor->data << std::endl;
        else
            std::cout << "Cursor is null" << std::endl;
    }

    void updateAtIndex(int index, int val) {
        if (index < 0) return;
        Node* temp = head;
        for (int i = 0; i < index && temp; i++)
            temp = temp->next;
        if (temp)
            temp->data = val;
        printList();
    }

    void updateImmediate(int val) {
        if (cursor)
            cursor->data = val;
        printList();
    }

    void shift(int index) {
        if (index < 0 || !cursor || !cursor->next) return;
        Node* temp = head;
        for (int i = 0; i < index && temp; i++)
            temp = temp->next;
        if (temp) {
            int tempData = cursor->data;
            cursor->data = temp->data;
            temp->data = tempData;
        }
        printList();
    }

    void undo() {
        if (prevCursor)
            cursor = prevCursor;
        printList();
    }

    ~Editor() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() {
    Editor editor;

    std::ifstream inputFile("C:/Users/Dell/Desktop/Test01.txt");
    if (inputFile.is_open()) {
        std::string command;
        while (std::getline(inputFile, command)) {
            std::istringstream iss(command);
            std::string cmd;
            iss >> cmd;

            if (cmd == "Add") {
                int val;
                iss >> val;
                editor.addNumber(val);
            } else if (cmd == "Delete") {
                editor.deleteTail();
            } else if (cmd == "AddIndex") {
                int index, val;
                iss >> index >> val;
                editor.addAtIndex(index, val);
            } else if (cmd == "DeleteIndex") {
                int index;
                iss >> index;
                editor.deleteAtIndex(index);
            } else if (cmd == "MoveForward") {
                int steps;
                iss >> steps;
                editor.moveForward(steps);
            } else if (cmd == "MoveBackward") {
                int steps;
                iss >> steps;
                editor.moveBackward(steps);
            } else if (cmd == "AddImmediate") {
                int val;
                iss >> val;
                editor.addImmediate(val);
            } else if (cmd == "DeleteImmediate") {
                editor.deleteImmediate();
            } else if (cmd == "Print"){
                editor.printCursorData();
            }else if (cmd == "Update"){
                int index, val;
                iss >> index >> val;
                editor.updateAtIndex(index, val);
            }else if (cmd == "UpdateImmediate") {
                int val;
                iss >> val;
                editor.updateImmediate(val);
            }else if (cmd == "Shift") {
                int index;
                iss >> index;
                editor.shift(index);
            } else if (cmd == "Undo") {
                editor.undo();
            } else {
                std::cout << "Invalid command: " << command << std::endl;
            }
            
        inputFile.close();
        }
     else {    
            std::cout << "Unable to open file" << std::endl;
    }

    return 0;
};
}


