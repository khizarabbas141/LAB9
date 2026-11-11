// Name : Syed Khizar Abbas
// Cms ID : 571942
// Section : BSAI-2-A
/* 
Design Explanation :
This program implements an AVL tree to store student information and a queue for managing help requests.
I used AVL Tree Because it will always have to time complexity of O(log n) for insertion, deletion, and search operations.
This is important for maintaining a balanced tree structure and ensuring efficient performance even as the number of students grows.
And i Have used Queue for help desk because it will maintain the order of help requests, ensuring that students are served in the order they arrive.

*/

#include <iostream>
#include <string>

using namespace std;

struct StudentNode {
    int rollno;
    string name;
    StudentNode* left;
    StudentNode* right;
    int height;

    StudentNode(int r, string n) {
        rollno = r;
        name = n;
        left = NULL;
        right = NULL;
        height = 1; }
};

int getHeight(StudentNode* n) {
    if (n == NULL) 
        return 0;
    return n->height;
}

int getMax(int a, int b) {
    if(a > b) return a;
    return b;
}

int getBalanceFactor(StudentNode* n) {
    if (n == NULL) 
        return 0;
    return getHeight(n->left) - getHeight(n->right);
}

StudentNode* rightRotate(StudentNode* y) {
    StudentNode* x = y->left;
    StudentNode* T2 = x->right;

    x->right = y;

    y->left = T2;

    y->height = getMax(getHeight(y->left), getHeight(y->right)) +1;
    x->height = getMax(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

StudentNode* leftRotate(StudentNode* x) {
    StudentNode* y = x->right;
    StudentNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = getMax(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = getMax(getHeight(y->left), getHeight(y->right)) +1;

    return y;
}

StudentNode* insertNode(StudentNode* node, int r, string name, bool &isAdded) {    //O(log n)
    if (node == NULL) {
        isAdded = true;
        return new StudentNode(r, name);
    }

    if (r < node->rollno) {
        node->left = insertNode(node->left, r, name, isAdded);
    } 
    else if (r > node->rollno) {
        node->right = insertNode(node->right, r, name, isAdded);
    } 
    else {
        isAdded = false; 
        return node;
    }

    node->height = 1 + getMax(getHeight(node->left), getHeight(node->right));

    int balance = getBalanceFactor(node);

    if (balance > 1 && r < node->left->rollno)
        return rightRotate(node);

    if (balance < -1 && r > node->right->rollno)
        return leftRotate(node);

    if (balance > 1 && r > node->left->rollno) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && r < node->right->rollno) {
        node->right = rightRotate(node->right);
        return leftRotate(node);}

    return node;
}

StudentNode* searchStudent(StudentNode* root, int r) {       //O(log n)
    if (root == NULL || root->rollno == r)
        return root;

    if (root->rollno > r)
        return searchStudent(root->left, r);

    return searchStudent(root->right, r);
}

void printInOrder(StudentNode* root) {                           //O(n)
    if (root != NULL) {
        printInOrder(root->left);
        cout << "Roll No: " << root->rollno << ", Name: " << root->name << endl;
        printInOrder(root->right);
    }
}

struct QueueNode {
    int rollno;
    string name;   
    QueueNode* next;
    QueueNode(int r, const string& n) : rollno(r), name(n), next(NULL) {
        rollno = r;
        name = n;
        next = NULL;
    }
};

class HelpQueue {                                      
private:
    QueueNode* front;
    QueueNode* rear;
public:
    HelpQueue() {
        front = NULL;
        rear = NULL;
    }

    void enqueue(int r, const string& n) {                     //O(1)
        QueueNode* temp = new QueueNode(r, n);
        if (rear == NULL) {
            front = rear = temp;
        } else {
            rear->next = temp;
            rear = temp;
        }
        cout << "Student added to the help desk queue.\n";
    }

    void dequeue() {                                          //O(1)
        if (front == NULL) {
            cout << "Queue is empty! No students waiting.\n";
            return;
        }
        QueueNode* temp = front;
        cout << "   giving help to student with Roll No: " << temp->rollno << " and Name: " << temp->name << endl;
        front = front->next;
        if (front == NULL) {
            rear = NULL;
        }
        delete temp;
    }

    void displayQueue() {                                     //O(n)
        if (front == NULL) {
            cout << "Help queue is currently empty.\n";
            return;
        }
        QueueNode* curr = front;
        cout << "\n Waiting Help Requests \n";
        while (curr != NULL) {
            cout << "Roll No: " << curr->rollno << ", Name: " << curr->name << endl;
            curr = curr->next;
        }
    }
};

int main() {
    StudentNode* root = NULL;
    HelpQueue hq;
    int choice;

    bool Added;
    root = insertNode(root, 104, "Khizar", Added);
    root = insertNode(root, 102, "Amein", Added);
    root = insertNode(root, 106, "Ali", Added);
    root = insertNode(root, 101, "Abdullah", Added);
    root = insertNode(root, 103, "Mohad", Added);

    cout << " Student Help Desk System Loaded \n";

    do {
        cout << "\n1. Add Student\n";
        cout << "2. Search Student\n";
        cout << "3. Display All Students\n";
        cout << "4. Register for Help \n";
        cout << "5. Serve Help Request\n";
        cout << "6. View Help Queue\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            int r; string name;
            cout << "Enter Roll Number: ";
            cin >> r;
            cout << "Enter Name: ";
            cin.ignore();
            getline(cin, name);

            bool added = false;
            root = insertNode(root, r, name, added);
            if (added) {
                cout << "Student added successfully!\n";
            } else {
                cout << " Error: Duplicate roll number exists!\n";
            }
        }
        else if (choice == 2) {
            int r;
            cout << "Enter roll number to search: ";
            cin >> r;
            StudentNode* found = searchStudent(root, r);
            if (found != NULL) {
                cout << "Found! Name: " << found->name << ", Roll No: " << found->rollno << "\n";
            } else {
                cout << "Student not found in database.\n";
            }
        }
        else if (choice == 3) {
            if (root == NULL) {
                cout << "Database is empty.\n";
            } else {
                cout << "\n Student Records \n";
                printInOrder(root);
            }
        }
        else if (choice == 4) {
            int r;
            cout << "Enter roll number for help request: ";
            cin >> r;

            if (searchStudent(root, r) != NULL) {
                StudentNode* found = searchStudent(root, r);
                hq.enqueue(r, found->name);
            } else {
                cout << "Error: Student not found in records!\n";
            }
        }
        else if (choice == 5) {
            hq.dequeue();
        }
        else if (choice == 6) {
            hq.displayQueue();
        }
        else if (choice == 7) {
            cout << "BYEE!\n";
        }
        else {
            cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 7);

    return 0;
}
