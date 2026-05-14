#include <iostream>
#include <thread>
#include <string>

using namespace std;

void printHello(string name)
{
    for (int i = 0; i <= 100; ++i)
        cout << i;
    cout << "hello" << endl;
    cout << "hello" << name << endl;
}
int main()
{
    thread thread1(printHello, "world");
    // thread1.join();
    // thread1.detach();
    bool isJoin = thread1.joinable();
    if (isJoin)
    {
        cout << "thread1 is joinable" << endl;
        thread1.join(); // join是阻塞主线程，直到子线程执行完毕
    }
    cout << "over" << endl;
    return 0;
}