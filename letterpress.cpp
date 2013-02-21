#include <string>
#include <algorithm>
#include <list>
#include <cstring>
#include <fstream>
#include <iostream>
#include <cctype>
#include <vector>
#include <set>

using namespace std;

struct trie
{
    trie * children[26];
    bool word;
};

trie * new_trie()
{
    trie * t = new trie;
    memset(t->children, 0, sizeof(t->children));
    t->word = false;
}

trie * root = new_trie();
string line;
string letters;

list<char> current_chars;
set<string> found_words;

vector<bool> used;

int cti(char c)
{
    return c - 'a';
}

void add_word(string &word, trie * parent, int pos)
{
    if(pos == (int)word.size())
    {
        parent->word = true;
        return;
    }
    int i = cti(tolower(word[pos]));
    if(i < 0 || i > 25)
    {
        return;
    }
    if(!parent->children[i])
    {
        parent->children[i] = new_trie();
    }
    add_word(word, parent->children[i], pos + 1);
}

void go(trie * parent)
{
    if(parent->word)
    {
        string result;
        for(list<char>::iterator iter = current_chars.begin(); iter != current_chars.end(); iter++)
        {
            result.push_back(*iter);
        }
        found_words.insert(result);
    }
    for(int i = 0; i < (int)letters.size(); i++)
    {
        if(!used[i])
        {
            int index = cti(letters[i]);
            if(parent->children[index])
            {
                used[i] = true;
                current_chars.push_back(letters[i]);
                go(parent->children[index]);
                current_chars.pop_back();
                used[i] = false;
            }
        }
    }
}


bool sortfunc(const string & a, const string & b)
{
    if(a.size() == b.size())
    {
        return a < b;
    }
    else
    {
        return a.size() > b.size();
    }
}

int main(int argc, char * argv[])
{
    ifstream fin;
    if(argc == 2)
    {
        fin.open(argv[1]);
    }
    else
    {
        fin.open("/usr/share/dict/words");
    }
    while(true)
    {
        fin >> line;
        if(fin.eof())
        {
            break;
        }
        add_word(line, root, 0);
    }
    fin.close();
    cin >> letters;
    used.assign(letters.size(), false);
    go(root);
    vector<string> words(found_words.begin(), found_words.end());
    sort(words.begin(), words.end());
    cout << "Found " << words.size() << " words:" << endl;
    for(int i = 0; i < (int)words.size(); i++)
    {
        if(words[i].size() == 1)
        {
            continue;
        }
        cout << words[i] << endl;
    }
    /*
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            cout << board[i][j];
        }
        cout << endl;
    }
    */
    return 0;
}
