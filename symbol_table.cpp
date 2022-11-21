#include <bits/stdc++.h>
using namespace std;

class Node
{
public:
    string identifier, scope, type;
    int lineNo;
    Node *next;
    Node(string identifier, string scope, string type, int lineNo)
    {
        this->identifier = identifier;
        this->scope = scope;
        this->type = type;
        this->lineNo = lineNo;
    }
    ~Node()
    {
        if (next != NULL)
        {
            delete next;
        }
    }
    void print()
    {
        cout << "Identifier's Name:" << identifier
             << "\nType:" << type
             << "\nScope: " << scope
             << "\nLine Number: " << lineNo << endl;
    }
};

class SymbolTable
{
    Node **table;
    int table_size;
    int hashFn(string key)
    {
        int index = 0;
        int p = 1;
        for (int i = 0; i < key.length(); i++)
        {
            index = index + (key[i] * p) % table_size;
            index = index % table_size;
            p = (p * 27) % table_size;
        }
        return index;
    }

public:
    SymbolTable(int size = 7)
    {
        table_size = size;
        table = new Node *[table_size];
        for (int i = 0; i < table_size; i++)
        {
            table[i] = NULL;
        }
    }
    void insert(string id, string scope, string type, int lineno)
    {
        int index = hashFn(id);
        Node *n = new Node(id, scope, type, lineno);
        n->next = table[index];
        table[index] = n;
    }
    Node *find(string key)
    {
        int index = hashFn(key);
        Node *ptr = table[index];
        while (ptr != NULL)
        {
            if (ptr->identifier == key)
            {
                return ptr;
            }
            ptr = ptr->next;
        }
        return NULL;
    }
    bool erase(string key)
    {
        int index = hashFn(key);
        Node *ptr = table[index];
        if (ptr != NULL)
        {
            if (ptr->identifier == key)
            {
                table[index] = ptr->next;
                return true;
            }
            Node *prev = ptr;
            ptr = ptr->next;
            while (ptr != NULL)
            {
                if (ptr->identifier == key)
                {
                    prev->next = ptr->next;
                    ptr->next = NULL;
                    delete ptr;
                    return true;
                }
                prev = ptr;
                ptr = ptr->next;
            }
        }
        return false;
    }
    Node *modify(string id, string scope, string type, int lineno)
    {
        int index = hashFn(id);
        Node *ptr = table[index];
        while (ptr != NULL)
        {
            if (ptr->identifier == id)
            {
                ptr->scope = scope;
                ptr->type = type;
                ptr->lineNo = lineno;
                return ptr;
            }
            ptr = ptr->next;
        }
        return NULL;
    }
    void print()
    {
        for (int i = 0; i < table_size; i++)
        {
            cout << "Bucket " << i << " ->";
            Node *ptr = table[i];
            while (ptr != NULL)
            {
                cout << ptr->identifier << "->";
                ptr = ptr->next;
            }
            cout << endl;
        }
    }
};

int main()
{
    SymbolTable s;
    s.insert("if", "local", "keyword", 4);
    s.insert("number", "global", "variable", 2);
    s.insert("add", "global", "function", 1);
    s.insert("sum", "local", "int", 3);
    s.insert("a", "function parameter", "int", 1);
    Node *ptr = s.find("if");
    if (ptr != NULL)
    {
        cout << "if Identifier is present\n";
        ptr->print();
    }
    else
    {
        cout << "if Identifier not present\n";
    }
    if (s.erase("if") == true)
    {
        cout << "\nif Identifier is deleted\n";
    }
    else
    {
        cout << "\nFailed to delete if identifier\n";
    }
    ptr = s.modify("if", "global", "variable", 3);
    if (ptr != NULL)
    {
        cout << "\nif Identifier updated\n";
        ptr->print();
    }
    else
    {
        cout << "\nFailed to update if identifer\n";
    }
    ptr = s.find("if");
    if (ptr != NULL)
    {
        cout << "\nif Identifier is present\n";
        ptr->print();
    }
    else
    {
        cout << "\nif Identifier not present\n";
    }
    ptr = s.modify("number", "global", "variable", 3);
    if (ptr != NULL)
    {
        cout << "\nnumber Identifier updated\n";
        ptr->print();
    }
    else
    {
        cout << "\nFailed to update number identifer\n";
    }
    ptr = s.find("number");
    if (ptr != NULL)
    {
        cout << "\nnumber Identifier is present\n";
        ptr->print();
    }
    else
    {
        cout << "\nnumber Identifier not present\n";
    }
    cout << "\n**** SYMBOL_TABLE ****\n";
    s.print();
    return 0;
}