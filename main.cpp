#include<iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

struct LinkedList {
    Node* head;
    int size;

    LinkedList() : head(nullptr), size(0) {}

    void initialize() {
        int n;
        scanf("%d", &n);
        int *a = new int[n];
        for(int i = 0; i < n; i++) scanf("%d", &a[i]);

        // Build linked list from array
        if(n > 0) {
            head = new Node(a[0]);
            Node* curr = head;
            for(int i = 1; i < n; i++) {
                curr->next = new Node(a[i]);
                curr = curr->next;
            }
            size = n;
        }

        delete[] a;
    }

    void insert(int i, int x) {
        // Insert x after position i (1-indexed)
        if(i == 0) {
            // Insert at beginning
            Node* newNode = new Node(x);
            newNode->next = head;
            head = newNode;
            size++;
            return;
        }

        Node* curr = head;
        for(int j = 1; j < i; j++) {
            curr = curr->next;
        }

        Node* newNode = new Node(x);
        newNode->next = curr->next;
        curr->next = newNode;
        size++;
    }

    void erase(int i) {
        // Delete the i-th element (1-indexed)
        if(i == 1) {
            Node* temp = head;
            head = head->next;
            delete temp;
            size--;
            return;
        }

        Node* curr = head;
        for(int j = 1; j < i - 1; j++) {
            curr = curr->next;
        }

        Node* temp = curr->next;
        curr->next = temp->next;
        delete temp;
        size--;
    }

    void swap() {
        // Swap odd-even positions with O(1) space
        if(size < 2) return;

        Node* prev = nullptr;
        Node* curr = head;

        while(curr && curr->next) {
            Node* first = curr;
            Node* second = curr->next;
            Node* nextPair = second->next;

            // Swap the pair
            first->next = nextPair;
            second->next = first;

            if(prev == nullptr) {
                head = second;
            } else {
                prev->next = second;
            }

            prev = first;
            curr = nextPair;
        }
    }

    void moveback(int i, int x) {
        // Move first i elements x positions back with O(1) space
        // Example: a1->a2->a3->a4->a5, move first 2 elements 2 positions back
        // Result: a3->a4->a1->a2->a5

        if(i == 0 || x == 0 || i + x > size) return;

        // Find the i-th node and the (i+x)-th node
        Node* beforeI = nullptr;
        Node* nodeI = head;
        for(int j = 1; j < i; j++) {
            nodeI = nodeI->next;
        }

        Node* nodeIPlusX = head;
        for(int j = 1; j < i + x; j++) {
            if(j == i) beforeI = nodeIPlusX;
            nodeIPlusX = nodeIPlusX->next;
        }

        // Save the segments
        Node* firstSegStart = head;
        Node* firstSegEnd = nodeI;
        Node* middleSegStart = nodeI->next;
        Node* insertAfter = nodeIPlusX;
        Node* remaining = insertAfter->next;

        // Rearrange: middle segment comes first
        head = middleSegStart;
        insertAfter->next = firstSegStart;
        firstSegEnd->next = remaining;
    }

    int query(int i) {
        // Query the i-th element (1-indexed)
        Node* curr = head;
        for(int j = 1; j < i; j++) {
            curr = curr->next;
        }
        return curr->data;
    }

    void printAll() {
        Node* curr = head;
        bool first = true;
        while(curr) {
            if(!first) printf(" ");
            printf("%d", curr->data);
            first = false;
            curr = curr->next;
        }
        printf("\n");
    }

    void ClearMemory() {
        Node* curr = head;
        while(curr) {
            Node* temp = curr;
            curr = curr->next;
            delete temp;
        }
        head = nullptr;
        size = 0;
    }
};

int main() {
    LinkedList List;
    int m, op, i, x;
    List.initialize();
    scanf("%d", &m);
    while(m--) {
        scanf("%d", &op);
        if(op == 1) {
            scanf("%d%d", &i, &x);
            List.insert(i, x);
        }
        else if(op == 2) {
            scanf("%d", &i);
            List.erase(i);
        }
        else if(op == 3) {
            List.swap();
        }
        else if(op == 4) {
            scanf("%d%d",&i, &x);
            List.moveback(i, x);
        }
        else if(op == 5) {
            scanf("%d", &i);
            printf("%d\n", List.query(i));
        }
        else if(op == 6) {
            List.printAll();
        }
    }
    List.ClearMemory();
    return 0;
}
