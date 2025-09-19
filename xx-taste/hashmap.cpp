#include<iostream>
#include <string>
#include <vector>
using namespace std;

int get_hash(string s)
{
    int h = 0;
    for (int i = 0; i < s.size(); i++)
    {
        h = (h * 31) + static_cast<int>(s[i]);
    }
    return h;
}

class HashNode
{
private:
    string key;
    int value;
    HashNode *next;

public:
    HashNode(string k, int v) : key(k), value(v), next(NULL) {}
    string getKey() { return key; }
    int getValue() { return value; }
    void setValue(int value) { this->value = value; }
    HashNode *getNext() { return next; }
    void setNext(HashNode *next) { this->next = next; }
};

class HashMap {
private:
    size_t capacity;
    vector<HashNode *> table;

public:
    HashMap(size_t capacity) : capacity(capacity) { table.resize(capacity); }

    void print()
    {
        // 0:  [k|v] -> [k|v] -> NULL
        // 1: NULL
        // 2: ...
        // ...
        for (int i = 0; i < this->capacity; i++)
        {
            cout << i << ": ";
            HashNode *entry = this->table[i];
            while (entry != nullptr)
            {
                cout << "[" << entry->getKey() << ", " << entry->getValue() << "] -> ";
                entry = entry->getNext();
            }
            cout << "NULL\n";
        }
    }

    void put(string key, int value)
    {
        // calculate hash
        int hash_index = get_hash(key) % capacity;
        HashNode *needed_node = nullptr;
        HashNode *entry = table[hash_index];
        // find last entry
        // 7: [a|1|b] -> [a|2|c] -> NULL
        // TODO: modification for equal keys
        while (entry != nullptr)
        {
            if (entry->getKey() == key)
            {
                entry->setValue(value);
                return;
            }
            needed_node = entry;
            entry = entry->getNext();
        }
        // 7: [a|1|b] -> [b|2|c] -> [c|3|NULL] -> {NULL}
        // 7: {NULL}
        // if entry is empty
        HashNode *new_entry = new HashNode(key, value);
        if (needed_node == nullptr)
        {
            table[hash_index] = new_entry;
        }
        else
        {
            needed_node->setNext(new_entry);
        }
        // if we need to set next
        // rewrite  value
    }



};

int main()
{
    HashMap hm(10);
    hm.put("apple", 10);
    hm.put("banana", 11);
    hm.put("kiwi", 12);
    hm.print();
    hm.put("apple", 12);
    hm.print();
    // Hometask
    // get: returns value by key if key exists
    // hm.get("apple");
    // remove: removes element by key if key exists
    //>> [apple, 12] -> NULL
    // 1: NULL
    // 2: NULL
    // 3: NULL
    // 4: NULL
    // 5: NULL
    // 6: [kiwi, 12] -> [kiwi1, 13] -> [kiwi2, 14] -> NULL
    // 7: NULL
    // 8: NULL
    // 9: [banana, 11] -> NULL
    // hm.remove("apple")
    // hm.remove("kiwi1")
    //>> 0: NULL
    // 1: NULL
    // 2: NULL
    // 3: NULL
    // 4: NULL
    // 5: NULL
    // 6: [kiwi, 12] -> [kiwi2, 14] -> NULL
    // 7: NULL
    // 8: NULL
    // 9: [banana, 11] -> NULL
}