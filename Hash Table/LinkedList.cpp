// *********************************************************
// Program: YOUR_FILENAME.cpp
// Course: CCP6214 Algorithm Design and Analysis
// Lecture Class: TC4L
// Tutorial Class: T15L
// Trimester: 2610
// Member_1: 243UC247CZ | ABDULLAH HAKEEM BIN AHMAD KAMAL | ABDULLAH.HAKEEM.AHMAD.KAMALr@student.mmu.edu.my  | 012-418-8300
// Member_2: 242UC244GD | Yoshenan A/L Shanker |YOSHENAN.SHANKER@student.mmu.edu.my  | 011-3310-7367
// Member_3: 243UC2463Z | PRABU NATAR A/L DHARMENDRA | PRABU.NATAR.DHARMENDRA@student.mmu.edu.my  | 017-322-0572
// Member_4: 243UC247BQ | HEMARAJ A/L RAJAN  | HEMARAJ.RAJAN@student.mmu.edu.my   | 014-377-3108
// *********************************************************
// Task Distribution
// Member_1: Implementation of dataset generator
// Member_2:Implementation of radix sort and radix sort step
// Member_3:Implementation of heap sort and heap sort step
// Member_4:Implementation of hash table and hash table search
// *********************************************************



#ifndef LINKEDLIST_CPP
#define LINKEDLIST_CPP

#include <iostream>
using namespace std;

template <typename T>
struct Node {
  T info;
  Node<T>* next;
};

template <typename T>
class LinkedList {
private:
  Node<T>* start;
public:
  LinkedList() { start = nullptr; }
  ~LinkedList() { makeEmpty(); }
  // inserts at the beginning of the linked list
  void insertFront(T& element) {
    Node<T>* newNode = new Node<T>;
    newNode->info = element;
    newNode->next = start;
    start = newNode;
  }
  Node<T>* getStart() {
        return start;
    }
  // returns true if element is found; returns false if element is not found
  bool find(T& target) {
    bool found = false;
    Node<T>* ptr = start;
    while (ptr != nullptr && !found) {
      if (ptr->info == target) {
        found = true;
      }
      else
        ptr = ptr->next;
    }
    return found;
  }
  bool isEmpty() { return start == nullptr; }
  void makeEmpty() {
    while (start != nullptr) {
      Node<T>* ptr  = start;
      start = start->next;
      delete ptr;
	}
  }
  friend ostream& operator<< (ostream& os, LinkedList<T>& list) {
    Node<T>* ptr = list.start;
    while (ptr != nullptr) {
      os << ptr->info << " ";
      ptr = ptr->next;
    }
    return os;
  }
};

#endif
