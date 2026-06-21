// *********************************************************
// Program: hash table search step.cpp
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






#include <iostream>
#include <string>
#include <vector>
#include <fstream>
//#include <filesystem>
#include <sstream>
#include "LinkedList.cpp"
using namespace std;

struct Record{
    long long key;
    string value;
};



template <typename T>
class HashTable {
  vector< LinkedList<T> > table;
  int hashfunction (long long key) { // hash function
    return key % table.size();
  }
 public:
  HashTable (int size) {
    table.resize (size); // resize vector to support size elements.
  }
  ~HashTable() {
    for (int i = 0; i < table.size(); i++)
      table[i].makeEmpty();
  }
  int size() {
    return table.size();
  }
  void insert (T newItem) {

    int index = hashfunction(newItem.key);
    table[index].insertFront(newItem);

  }
  bool retrieve (T & target) {

     int index = hashfunction(target.key);
     return table[index].find(target);


  }

  LinkedList<T>& getBucket(int index)
{
    return table[index];
}
  friend ostream& operator<< (ostream& os, HashTable<T>& ht) {
    for (int i = 0; i < ht.size(); i++)
      os << i << " = " << ht.table[i] << endl;
    return os;
  }
};

void stepSearch(HashTable<Record>& ht, long long target, ofstream& out)
{
    int index = target % ht.size();

    out << "Search target: " << target << "\n\n";

    Node<Record>* ptr = ht.getBucket(index).getStart(); // requires getStart()

    bool found = false;

    while (ptr != nullptr)
    {
        if (ptr->info.key == target)
        {
            out << ptr->info.key << " = " << target
                << "/" << ptr->info.value << "\n";
            found = true;
            break;
        }
        else
        {
            out << ptr->info.key << " != " << target << "\n";
        }

        ptr = ptr->next;
    }

    if (!found)
    {
        out << "-1 != " << target << "\n";
    }
}



int main()
{
    cout << "RUNNING HERE\n";
    cout << "1\n";
    HashTable<Record> ht(1009);   // or bigger size if needed

    cout << "2\n";
    ifstream file("dataset_test.csv");
    cout << "3\n";
    ofstream out("output_hash_table_search_step.txt");
     cout << "4\n";

     cout << "File path: hash_table_search_step.txt\n";
     if (!file)
    {
    cout << "   FAILED to open dataset file\n";
    return 0;
    }
    else
    {
    cout << " dataset file opened successfully\n";
     }
    if (!out)
    {
    cout << "Failed to create output file!\n";
    return 0;
    }

    Record r;

    // ======================
    // 1. READ + INSERT DATA
    // ======================
    string line;

while (getline(file, line))
{
    stringstream ss(line);
    string keyStr, value;

    getline(ss, keyStr, ',');
    getline(ss, value);

    Record r;
    r.key = stoll(keyStr);
    r.value = value;

    ht.insert(r);
}

    file.close();

    // ======================
    // 2. GET TARGET
    // ======================

    long long target = 1000000090;


    // ======================
    // 3. STEP SEARCH
    // ======================
    stepSearch(ht, target, out);

    out.close();

    cout << "Step output generated.\n";

    return 0;
}
