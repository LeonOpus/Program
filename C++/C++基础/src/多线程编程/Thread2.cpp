#include <iostream>
#include <string>
#include <thread>
using namespace std;
thread t;
void foo(int &x)
{
    x += 1;
}
void test(){
    int a = 10;

}
int main(){
    int a = 1;
    t = thread(foo,ref(a));
    cout << a << endl;
    return 0;
}