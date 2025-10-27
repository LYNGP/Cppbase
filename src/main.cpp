#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

void test0(){

    // 声明并初始化字符串
    string greeting = "Hello, World!";
    cout << "Greeting: " << greeting << endl;

    // 使用 size() 获取字符串长度
    cout << "Length of the greeting: " << greeting.size() << endl;

    // 使用 empty() 检查字符串是否为空
    cout << "Is the greeting empty? " << (greeting.empty() ? "Yes" : "No") << endl;

    // 使用 operator[] 访问特定位置的字符
    cout << "Character at position 7: " << greeting[7] << endl;

    // 使用 substr() 获取子字符串
    string sub = greeting.substr(7, 5);
    cout << "Substring from position 7 with length 5: " << sub << endl;

    // 使用 find() 查找子字符串
    cout << "Position of 'World' in the greeting: " << greeting.find("World") << endl;

    // 使用 replace() 替换字符串中的部分内容
    // 替换 'World' 为 'C++'
    string modified = greeting;
    string::size_type pos = modified.find("World");
    if (pos != string::npos) {
        modified.replace(pos, 5, "C++"); // 从位置 pos 开始，替换 5 个字符为 "C++"
    }
    cout << "Modified greeting: " << modified << endl;
}
void test1(){
    string str = "Hello, World!";
   
    // size()
    cout << "Length: " << str.size() << endl;

    // empty()
    cout << "Is empty? " << (str.empty() ? "Yes" : "No") << endl;

    // operator[]
    cout << "First character: " << str[0] << endl;

    // at()
    cout << "Character at position 7: " << str.at(7) << endl;

    // substr()
    string sub = str.substr(7, 5);
    cout << "Substring from position 7 with length 5: " << sub << endl;

    // find()
    size_t pos = str.find("World");
    cout << "Position of 'World': " << pos << endl;

    // replace()
    str.replace(pos, 5, "C++");
    cout << "Modified string: " << str << endl;

    // append()
    str.append(" How are you?");
    cout << "Appended string: " << str << endl;

    // insert()
    str.insert(7, " Beautiful");
    cout << "String after insert: " << str << endl;

    // erase()
    str.erase(7, 10);
    cout << "String after erase: " << str << endl;

    // clear()
    str.clear();
    cout << "String after clear: " << (str.empty() ? "Empty" : "Not empty") << endl;

    // c_str()
    str = "Hello, C++!";
    const char* cstr = str.c_str();
    cout << "C-style string: " << cstr << endl;

    // compare()
    int cmp = str.compare("Hello, C++!");
    cout << "Comparison result: " << cmp << endl;

    // find_first_of()
    size_t pos_first_vowel = str.find_first_of("aeiou");
    cout << "First vowel at position: " << pos_first_vowel << endl;

    // find_last_of()
    size_t pos_last_vowel = str.find_last_of("aeiou");
    cout << "Last vowel at position: " << pos_last_vowel << endl;

    // find_first_not_of()
    size_t pos_first_non_vowel = str.find_first_not_of("aeiou");
    cout << "First non-vowel at position: " << pos_first_non_vowel << endl;

    // find_last_not_of()
    size_t pos_last_non_vowel = str.find_last_not_of("aeiou");
    cout << "Last non-vowel at position: " << pos_last_non_vowel << endl;
}

int main(){
    test0();
    cout << "#-------------------------#"<< endl;
    test1();
    return 0;
}