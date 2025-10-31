#include <iostream>
#include "logger.hpp"

#include <algorithm>

using std::cout;
using std::endl;
using std::string;
using std::vector;
// 统计一篇英文文章中出现的单词与词频

struct Record
{
    Record(const string &word, int freq) : _word(word), _freq(freq) {}
    string _word;
    int _freq;
};

class Dictionary
{
public:
    void read(const string &filename);
    void store(const string &filename);

private:
    vector<Record> _dict;
};

void test0()
{
}

int main()
{
    LOG_INIT();
    test0();

    return 0;
    LOG_CLEANUP();
}

void Dictionary::read(const string &filename)
{
}

void Dictionary::store(const string &filename)
{
}
