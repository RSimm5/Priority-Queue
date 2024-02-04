/// @file priorityqueue.h
///
/// Project completed by Rovia Simmons
///
/// Assignment details and provided code are created and
/// owned by Adam T Koehler, PhD - Copyright 2023.
/// University of Illinois Chicago - CS 251 Spring 2023

#pragma once

#include <iostream>
#include <sstream>
#include <set>

using namespace std;

template<typename T>
class priorityqueue {
private:
    struct NODE {
        int priority;  // used to build BST
        T value;  // stored data for the p-queue
        bool dup;  // marked true when there are duplicate priorities
        NODE* parent;  // links back to parent
        NODE* link;  // links to linked list of NODES with duplicate priorities
        NODE* left;  // links to left child
        NODE* right;  // links to right child
    };
    NODE* root;  // pointer to root node of the BST
    int size;  // # of elements in the pqueue
    NODE* curr;  // pointer to next item in pqueue (see begin and next)

    //toString helper function
    void orderedTraversal(NODE* node, ostream& output) {
        if (node == nullptr) {
            return;
        }

        orderedTraversal(node->left, output);
        output << node->priority << " value: " << node->value << "\n";
        orderedTraversal(node->link, output);
        orderedTraversal(node->right, output);
    }


    //clear function helper
    void deleteTree(NODE* node) {
        if (node == nullptr) {
            return;
        }

        deleteTree(node->left);
        node->left = nullptr;
        deleteTree(node->link);
        node->link = nullptr;
        deleteTree(node->right);
        node->right = nullptr;

        delete node;
        node = nullptr;
        size--;
    }

    //operator= helper. Enqueues everything from the other priorityqueue
    void clone(NODE* node) {
        if (node == nullptr) {
            return;
        }

        clone(node->left);
        enqueue(node->value, node->priority);
        clone(node->link);
        clone(node->right);
    }

    //deletes pointer to the beginning
    bool deleteBeginning() {
        NODE* pCurr = root;
        while (pCurr->left != nullptr) {
            pCurr = pCurr->left;
        }
        if (curr->link == pCurr) {
            pCurr = curr;
            curr = curr->link;
            delete pCurr;
            return true;
        }
        return false;
    }
    
    //Next helper. Checks if there is any value after the current one.
    bool nextCheck(NODE* pCurr) {

        if (pCurr == nullptr) {
            return false;
        }

        T value = pCurr->value;
        int priority = pCurr->priority;

        if (pCurr->dup) {
            return true;
        }
        else if (pCurr->right != nullptr) {
            return true;
        }
        else { //start checking parent nodes
            while (pCurr != nullptr) {
                if (pCurr->priority > priority) {
                    return true;
                }
                else if (pCurr->right != nullptr && pCurr->right->priority > priority) {
                    return true;
                }
                pCurr = pCurr->parent;
            }
        }
        return false;
    }

    //helper for operator==
    bool equalityCheck(const NODE* node, const NODE* node2) const {
        if (node == nullptr && node2 == nullptr) {
            return true;
        }
        else if (node == nullptr || node2 == nullptr) {
            return false;
        }
        else {
            if (node->value == node2->value && node->priority == node2->priority
            &&  equalityCheck(node->left, node2->left)
            &&  equalityCheck(node->link, node2->link)
            &&  equalityCheck(node->right, node2->right)) {
                return true;
            }
            else {
                return false;
            }
        }
    }

public:
    //
    // default constructor:
    //
    // Creates an empty priority queue.
    // O(1)
    //
    priorityqueue() {
        root = nullptr;
        size = 0;
        curr = nullptr;
    }

    //
    // operator=
    //
    // Clears "this" tree and then makes a copy of the "other" tree.
    // Sets all member variables appropriately.
    // O(n), where n is total number of nodes in custom BST
    //
    priorityqueue& operator=(const priorityqueue& other) {
        clear();

        NODE* temp = other.root;
        clone(temp);

        return *this;
    }

    //
    // clear:
    //
    // Frees the memory associated with the priority queue but is public.
    // O(n), where n is total number of nodes in custom BST
    //
    void clear() {

        if(root != nullptr) {
            deleteTree(root);
            root = nullptr;
        }

    }

    //
    // destructor:
    //
    // Frees the memory associated with the priority queue.
    // O(n), where n is total number of nodes in custom BST
    //
    ~priorityqueue() {

        if(root != nullptr) {
            deleteTree(root);
            root = nullptr;
        }

    }

    //
    // enqueue:
    //
    // Inserts the value into the custom BST in the correct location based on
    // priority.
    // O(logn + m), where n is number of unique nodes in tree and m is number
    // of duplicate priorities
    //
    void enqueue(T value, int priority) {
        NODE* temp = new NODE;
        temp->priority = priority;
        temp->value = value;
        temp->dup = false;
        temp->parent = nullptr;
        temp->link = nullptr;
        temp->left = nullptr;
        temp->right = nullptr;

        if (root == nullptr) {
            root = temp;
            size++;
            return;
        }

        NODE* pCurr = root;
        while (pCurr != nullptr) {
            temp->parent = pCurr;
            if (priority < pCurr->priority) {
                if (pCurr->left == nullptr) {
                    pCurr->left = temp;
                    size++;
                    return;
                }
                pCurr = pCurr->left;
            }
            else if (priority > pCurr->priority) {
                if (pCurr->right == nullptr) {
                    pCurr->right = temp;
                    size++;
                    return;
                }
                pCurr = pCurr->right;
            }
            else {
                if (pCurr->link == nullptr) {
                    pCurr->link = temp;
                    pCurr->dup = true;
                    size++;
                    return;
                }
                pCurr = pCurr->link;
            }
        }

    }

    //
    // dequeue:
    //
    // returns the value of the next element in the priority queue and removes
    // the element from the priority queue.
    // O(logn + m), where n is number of unique nodes in tree and m is number
    // of duplicate priorities
    //
    T dequeue() {

        if (root == nullptr) {
            return T{};
        }

        NODE* pCurr = root;

        while (pCurr->left != nullptr) {
            pCurr = pCurr->left;
        }

        T valueOut = pCurr->value;

        if (pCurr->dup) {
            if (pCurr->right != nullptr) {
                pCurr->link->right = pCurr->right;
                pCurr->right->parent = pCurr->link;
            }
            if (pCurr != root) {
                if (pCurr->parent != nullptr) {
                    pCurr->parent->left = pCurr->link;
                    pCurr->link->parent = pCurr->parent;
                }
            }
            else {
                root = pCurr->link;
                root->parent = nullptr;
            }
        }
        else if (pCurr->right != nullptr) { //no duplicates, only right
            if (pCurr != root) {
                if (pCurr->parent != nullptr) {
                    pCurr->parent->left = pCurr->right;
                    pCurr->right->parent = pCurr->parent;
                }
            }
            else {
                root = pCurr->right;
                root->parent = nullptr;
            }
        } 
        else { //no duplicates or right
            if (pCurr != root) {
                    pCurr->parent->left = nullptr;
            } 
            else {
                root = nullptr;
            }
        }

        pCurr->left = nullptr;
        delete pCurr;
        pCurr = nullptr;
        size--;
        return valueOut; 
    }

    //
    // Size:
    //
    // Returns the # of elements in the priority queue, 0 if empty.
    // O(1)
    //
    int Size() {

        return size;

    }

    //
    // begin
    //
    // Resets internal state for an inorder traversal.  After the
    // call to begin(), the internal state denotes the first inorder
    // node; this ensure that first call to next() function returns
    // the first inorder node value.
    //
    // O(logn), where n is number of unique nodes in tree
    //
    // Example usage:
    //    pq.begin();
    //    while (tree.next(value, priority)) {
    //      cout << priority << " value: " << value << endl;
    //    }
    //    cout << priority << " value: " << value << endl;
    void begin() {
        if (root == nullptr) {
            return;
        }
        NODE* pCurr = root;
        while (pCurr->left != nullptr) {
            pCurr = pCurr->left;
        }
        curr = new NODE;
        curr->priority = 0;
        curr->value = T{};
        curr->parent = nullptr;
        curr->left = nullptr;
        curr->right = nullptr;
        curr->dup = true;
        curr->link = pCurr;
    }

    //
    // next
    //
    // Uses the internal state to return the next inorder priority, and
    // then advances the internal state in anticipation of future
    // calls.  If a value/priority are in fact returned (via the reference
    // parameter), true is also returned.
    //
    // False is returned when the internal state has reached null,
    // meaning no more values/priorities are available.  This is the end of the
    // inorder traversal.
    //
    // O(logn), where n is the number of unique nodes in tree
    //
    // Example usage:
    //    pq.begin();
    //    while (pq.next(value, priority)) {
    //      cout << priority << " value: " << value << endl;
    //    }
    //    cout << priority << " value: " << value << endl;
    //
    bool next(T& value, int &priority) {

        if (curr == nullptr) {
            return false;
        }

        value = curr->value;
        priority = curr->priority;

        if (curr->dup) { //traverse duplicates first
            if(!deleteBeginning()){
                curr = curr->link;
            }
            value = curr->value;
            priority = curr->priority;
            return nextCheck(curr);
        }
        else if (curr->right != nullptr) { //traverse leftmost of right node
            curr = curr->right;
            while (curr->left != nullptr) {
                curr = curr->left;
            }
            value = curr->value;
            priority = curr->priority;
            return nextCheck(curr);
        }
        else { //start checking parent nodes
            while (curr != nullptr) {
                if (curr->priority > priority) {
                    value = curr->value;
                    priority = curr->priority;
                    return nextCheck(curr);
                }
                else if (curr->right != nullptr && curr->right->priority > priority) { //traverse leftmost of right node
                    curr = curr->right;
                    while (curr->left != nullptr) {
                        curr = curr->left;
                    }
                    value = curr->value;
                    priority = curr->priority;
                    return nextCheck(curr);
                }
                curr = curr->parent;
            }
        }

        return false;

    }


    //
    // toString:
    //
    // Returns a string of the entire priority queue, in order.  Format:
    // "1 value: Ben
    //  2 value: Jen
    //  2 value: Sven
    //  3 value: Gwen"
    //
    string toString() {
        if (root == nullptr) {
            return "";
        }
        stringstream ss;

        orderedTraversal(root, ss);
        return ss.str();
    }

    //
    // peek:
    //
    // returns the value of the next element in the priority queue but does not
    // remove the item from the priority queue.
    // O(logn + m), where n is number of unique nodes in tree and m is number
    // of duplicate priorities
    //
    T peek() {

        NODE* pCurr = root;
        while (pCurr->left != nullptr) {
            pCurr = pCurr->left;
        }

        T valueOut = pCurr->value;

        return valueOut; // TO DO: update this return

    }



    //
    // ==operator
    //
    // Returns true if this priority queue as the priority queue passed in as
    // other.  Otherwise returns false.
    // O(n), where n is total number of nodes in custom BST
    //
    bool operator==(const priorityqueue& other) const {
        return equalityCheck(root, other.root);

    }

    //
    // getRoot - Do not edit/change!
    //
    // Used for testing the BST.
    // return the root node for testing.
    //
    void* getRoot() {
        return root;
    }
};