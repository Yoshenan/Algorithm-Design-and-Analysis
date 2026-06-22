#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <chrono>
#include <iomanip>
#include "LinkedList.cpp"
using namespace std;

struct Record{
    long long key;
    string value;
    bool operator==(const Record& other) const {
        return key == other.key;
    }
};

template <typename T>
class HashTable {
  vector< LinkedList<T> > table;
  int hashfunction (long long key) {
    return key % table.size();
  }
 public:
  HashTable (int size) {
    table.resize (size);
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
  LinkedList<T>& getBucket(int index) {
    return table[index];
  }
  friend ostream& operator<< (ostream& os, HashTable<T>& ht) {
    for (int i = 0; i < ht.size(); i++)
      os << i << " = " << ht.table[i] << endl;
    return os;
  }
};

double bestCase(HashTable<Record>& ht, vector<Record>& records)
{
    int n = records.size();
    if (n == 0) return 0.0;

    int tableSize = ht.size();
    Record target = records[0];

    for (int i = 0; i < n; i++)
    {
        int idx = records[i].key % tableSize;
        int count = 0;
        for (int j = 0; j < n; j++)
            if (records[j].key % tableSize == idx)
                count++;
        if (count == 1)
        {
            target = records[i];
            break;
        }
    }

    const int RUNS = 10000000;

    auto start = chrono::high_resolution_clock::now();
    for (int i = 0; i < RUNS; i++)
        ht.retrieve(target);
    auto end = chrono::high_resolution_clock::now();

    return chrono::duration<double>(end - start).count() / RUNS;
}

double averageCase(HashTable<Record>& ht, vector<Record>& records)
{
    int n = records.size();
    if (n == 0) return 0.0;

    int tableSize = ht.size();

    // find a record in a bucket with average chain length
    vector<int> freq(tableSize, 0);
    for (int i = 0; i < n; i++)
        freq[records[i].key % tableSize]++;

    // find average bucket size
    int total = 0, count = 0;
    for (int i = 0; i < tableSize; i++)
        if (freq[i] > 0) { total += freq[i]; count++; }
    int avgSize = total / count;

    // pick a record from a bucket closest to average size
    Record target = records[0];
    for (int i = 0; i < n; i++)
    {
        int idx = records[i].key % tableSize;
        if (freq[idx] == avgSize)
        {
            target = records[i];
            break;
        }
    }

    const int RUNS = 10000000;

    auto start = chrono::high_resolution_clock::now();
    for (int i = 0; i < RUNS; i++)
        ht.retrieve(target);
    auto end = chrono::high_resolution_clock::now();

    return chrono::duration<double>(end - start).count() / RUNS;
}

double worstCase(HashTable<Record>& ht, vector<Record>& records)
{
    int n = records.size();
    if (n == 0) return 0.0;

    int tableSize = ht.size();

    // Step 1: find bucket with most collisions
    vector<int> freq(tableSize, 0);
    for (int i = 0; i < n; i++)
        freq[records[i].key % tableSize]++;

    int worstBucket = 0;
    for (int i = 1; i < tableSize; i++)
        if (freq[i] > freq[worstBucket])
            worstBucket = i;

    // Step 2: collect all keys in worst bucket
    vector<long long> bucketKeys;
    for (int i = 0; i < n; i++)
        if (records[i].key % tableSize == worstBucket)
            bucketKeys.push_back(records[i].key);

    // Step 3: generate fake key that maps to worst bucket but does not exist
    long long fakeKey = worstBucket;
    while (true)
    {
        fakeKey += tableSize;
        bool clash = false;
        for (int i = 0; i < bucketKeys.size(); i++)
            if (bucketKeys[i] == fakeKey)
            {
                clash = true;
                break;
            }
        if (!clash) break;
    }

    Record target;
    target.key = fakeKey;
    target.value = "";


    const int RUNS = 10000000;

    auto start = chrono::high_resolution_clock::now();
    for (int i = 0; i < RUNS; i++)
        ht.retrieve(target);
    auto end = chrono::high_resolution_clock::now();

    return chrono::duration<double>(end - start).count() / RUNS;
}

int main()
{
    cout << "Hash Table Search Running"<<"\n";


    vector<Record> records;
    const string filename = "dataset_100000000.csv";
    ifstream file(filename);

    if (!file)
    {
        cout << "   FAILED to open dataset file\n";
        return 0;
    }
    else
    {
        cout << " dataset file opened successfully\n";
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

    double best  = bestCase(ht, records);
    double avg   = averageCase(ht, records);
    double worst = worstCase(ht, records);

    string outFilename = "hash_table_search_" +filename +".txt";
    ofstream out(outFilename);
    if (!out)
    {
        cout << "Failed to create output file!\n";
        return 0;
    }

    out << fixed << setprecision(10);
    out << "Dataset size: "      << records.size() << "\n\n";
    out << "Best Case Time: "    << best            << " seconds\n";
    out << "Average Case Time: " << avg             << " seconds\n";
    out << "Worst Case Time: "   << worst           << " seconds\n";
    out.close();

    cout << fixed << setprecision(10);
    cout << "Output generated to: " << outFilename << "\n";
    cout << "Dataset size: "      << records.size() << "\n";
    cout << "Best Case Time: "    << best            << " seconds\n";
    cout << "Average Case Time: " << avg             << " seconds\n";
    cout << "Worst Case Time: "   << worst           << " seconds\n";

    return 0;
}
