// *********************************************************
// Program: hash_table_search_step.cpp
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
    cout << "Hash Table Search Step Running\n";

    const string filename = "dataset_1000.csv";
    vector<Record> records;

    ifstream file(filename);
    if (!file)
    {
        cout << "FAILED to open dataset file\n";
        return 0;
    }
    else
    {
        cout << filename << " opened successfully\n";
    }

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
        records.push_back(r);
    }
    file.close();

    HashTable<Record> ht(records.size());
    for (int i = 0; i < records.size(); i++)
        ht.insert(records[i]);

    long long target = 1111966624;

    string outFilename = "hash_table_search_step_" + filename + ".txt";
    ofstream out(outFilename);
    if (!out)
    {
        cout << "Failed to create output file!\n";
        return 0;
    }

    out << "Dataset: "      << filename        << "\n";
    out << "Dataset size: " << records.size()  << "\n\n";
    out << "Target key: "   << target          << "\n\n";
    stepSearch(ht, target, out);
    out.close();

    cout << "Output generated to: " << outFilename << "\n";

    return 0;
}
