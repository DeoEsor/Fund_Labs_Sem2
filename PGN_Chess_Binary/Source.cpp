#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <string>
#include <fstream>

using namespace std;
string Meta_binary(vector<string> text);

class Node//node of binary search
{
public:
    int count;//frequency of sym UPD: no its not UPD2: count=depth=frequency so its it
    char symbol;
    Node* left;
    Node* right;

    Node(){}

    Node(char __symbol, int __count):symbol(__symbol), count(__count) {}

    Node(Node* l, Node* r): left(l),right(r)
    {
        symbol = 0;
        count = l->count + r->count;
    }

    static void Print(Node* root, int depth = 0)
    {
        if (!root) return;

        if (root->symbol)
        {
            for (int i = 0; i < depth; i++)
                cout << ".";
            cout << root->symbol << endl;
        }
        else depth++;
        Print(root->left, depth);
        Print(root->right, depth);
    }
};

void BuildTable(Node* root, vector<bool>& code, map<char, vector<bool>>& table)
{
    if (root->left)
    {
        code.push_back(0);
        BuildTable(root->left, code, table);
    }

    if (root->right)
    {
        code.push_back(1);
        BuildTable(root->right, code, table);
    }

    if (root->symbol)
        table[root->symbol] = code;
    if (code.size())
        code.pop_back();
}

bool SortNode(const Node* a, const Node* b)//comparator
{
    return a->count < b->count;
}

string Decode(string& str, map<vector<bool>, char>& table)
{
    string out = "";
    vector<bool> code;
    for (int i = 0; i < str.length(); i++)
    {
        code.push_back(str[i] == '0' ? false : true);
        if (table[code])
        {
            out += table[code];
            code.clear();
        }
    }
    return out;
}

int main()
{
    string path, raw;
    cout << "Input PGN file path : ";
    cin >> path;
    ofstream output;               ifstream in(path);
    int step = 0; int last = 0;
    int n = 5;
    map<char, int> symbols;
    vector<string> text(700);
    output.open("output.bin");

    if (in.is_open())
    {
        int i= 0;
        while (in >> raw)
        {
            if (raw[0] == '\n') { } //TODO: to optimize (precompile)
            if (raw[0] == '{' || *(--raw.cend()) == '}') { continue; }
            if (isdigit(raw[0])) { step++; continue; }
            text[i++] = raw; 
            if (i + 1 == n) text.resize(n+i); n += i;
            for (int j = 0; j < raw.length(); j++)
                symbols[raw[j]]++;//frequence
            if (*(--(--raw.cend())) == ']') last = i-1;
        }
    }

    int a = 0;

    list<Node*> trees;
    map<char, int>::iterator itr;
    for (itr = symbols.begin(); itr != symbols.end(); itr++)
    {
        Node* p = new Node(itr->first, itr->second);
        trees.push_back(p);
    }
    if (trees.size() == 0) {
        cout << "File is empty" << endl;
        system("pause");
        return 0;
    }
    else
    {
        
            while (trees.size() != 1)
            {
                trees.sort(SortNode);

                Node* l = trees.front();
                trees.pop_front();
                Node* r = trees.front();
                trees.pop_front();

                Node* parent = new Node(l, r);
                trees.push_back(parent);
            }

            cout << "Frequency of symbols(depth):" << endl;
            Node* root = trees.front();
            root->Print(root);

            vector<bool> code;
            map<char, vector<bool> > table;
            BuildTable(root, code, table);

            cout << "[Symbol] - [Code]:" << endl;
            for (itr = symbols.begin(); itr != symbols.end(); itr++)
            {
                cout << itr->first << " - ";
                for (int j = 0; j < table[itr->first].size(); j++)
                    cout << table[itr->first][j];
                cout << endl;
            }

            string out = "";
            //coding
            for (int a = 0; a < text.size(); a++) {

                raw = text[a];

                for (int i = 0; i < raw.length(); i++)
                    if(i==last)
                    for (int j = 0; j < table[raw[i]].size(); j++)
                    {
                        out += table[raw[i]][j] + '0';
                        output << table[raw[i]][j]<<endl;
                    }
            }
            cout << endl;
            cout << "Output:" << endl;
            cout << out<< endl;



            map<vector<bool>, char> ftable;
            for (auto i = table.begin(); i != table.end(); i++)
                ftable[i->second] = i->first;

            cout << "Decode:" << endl;

            cout<< " " +Decode(out, ftable) << endl;

            system("pause");
    }
    in.close();
    output.close();
    return 0;
}