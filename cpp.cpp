#include <iostream>
#include <string>

using namespace std;

int main() {
    string name;
    
    // 提示用户输入名字
    cout << "请输入你的名字: ";
    cin >> name;

    // 输出问候语
    cout << "hello " << name << "!" << endl;

    return 0;
}
