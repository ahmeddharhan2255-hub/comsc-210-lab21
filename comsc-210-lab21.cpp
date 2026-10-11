// COMSC-210 | Lab 21 | Ahmad Dharhan

#include <iostream>
#include <string>
#include <random>
#include <cstdlib>


using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MAX_ARR = 15, MIN_LS = 5, MAX_LS = 20;

class Goat{
private:
    int age;
    string name;
    string color;
    string names[MAX_ARR] = {
        "Billy",
        "Nanny",
        "Capri",
        "Butter",
        "Shadow",
        "Gizmo",
        "Ziggy",
        "Clover",
        "Pip",
        "Goofy",
        "Truffle",
        "Biscuit",
        "Coco",
        "Peanut",
        "Scout"
    };

    string colors[MAX_ARR] = {        
        "Crimson",
        "Teal",
        "Lavender",
        "Amber",
        "Charcoal",
        "Coral",
        "Indigo",
        "Mint",
        "Peach",
        "Periwinkle",
        "Sage",
        "Turquoise",
        "Maroon",
        "Olive",
        "Magenta"

    };

public:
    Goat()          {age = randAge(); name = randName(); color = randColor();}

    Goat(int a, string n, string c) {age = a; name = n; color = c;}

    int randAge()             {return (rand() % (MAX_LS) + 1);}

    string randName()         {return names[randNum()];}

    string randColor()        {return colors[randNum()];}

    int randNum()             {return (rand() % (MAX_ARR));}

};

class DoublyLinkedList {
private:
    struct Node {
        Goat data;
        Node* prev;
        Node* next;
        Node(Goat val, Node* p = nullptr, Node* n = nullptr) {
            data = val; 
            prev = p;
            next = n;
        }
    };

    Node* head;
    Node* tail;

public:
    // constructor
    DoublyLinkedList() { head = nullptr; tail = nullptr; }

    void push_back(Goat value) {
        Node* newNode = new Node(value);
        if (!tail)  // if there's no tail, the list is empty
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void push_front(Goat value) {
        Node* newNode = new Node(value);
        if (!head)  // if there's no head, the list is empty
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    void insert_after(Goat value, int position) {
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }

        Node* newNode = new Node(value);
        if (!head) {
            head = tail = newNode;
            return;
        }

        Node* temp = head;
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;

        if (!temp) {
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;
            return;
        }

        newNode->next = temp->next;
        newNode->prev = temp;
        if (temp->next)
            temp->next->prev = newNode;
        else
            tail = newNode; // Inserting at the end
        temp->next = newNode;
    }

    void print() {
        Node* current = head;
        if (!current) return;
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse() {
        Node* current = tail;
        if (!current) return;
        while (current) {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

// Driver program
int main() {

    srand(time(0));

    DoublyLinkedList list;
    int size = rand() % (MAX_LS-MIN_LS+1) + MIN_LS;

    for (int i = 0; i < size; ++i)
        list.push_back(rand() % (MAX_NR-MIN_NR+1) + MIN_NR);
    cout << "List forward: ";
    list.print();

    cout << "List backward: ";
    list.print_reverse();

    cout << "Deleting list, then trying to print.\n";
    list.~DoublyLinkedList();
    cout << "List forward: ";
    list.print();

    return 0;
}
