#include <iostream>
#include <functional>

using namespace std;

int main()
{
    // 返回一个计算两个数之和的lamda表达式
    auto addTwoIntegers = [](int x) -> function<int (int)> {
        return [=](int y) {return x+y;};
    };
    // 接受另一个函数参数 f 作为参数，返回f(z)的两倍
    auto higherorder = [] (const function<int(int)> &f, int z) {
        return f(z) * 2;
    };

    // 调用绑定到 higherorder 的 lamda表达式
    auto answer = higherorder(addTwoIntegers(7), 8 );
    cout << answer << endl;
}