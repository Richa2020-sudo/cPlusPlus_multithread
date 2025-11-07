// Online C++ compiler to run C++ program online
// scoped_lock: use with multiple mutex instead of using lock_guard multiple times and worng order of lock_guard between thread can create deadlock situation.

#include <iostream>
#include <sstream>
#include <map>
#include <string>
#include <limits>
#include <cstdint>
#include <thread>
#include <vector>
#include <mutex>
#include <chrono>
using namespace std;
// scoped_lock: use with multiple mutex instead of using lock_guard multiple times and worng order of lock_guard between thread can create deadlock situation.

std::mutex m1, m2;
int a = 0, b = 0;

// example of unique_lock with defer:
// mean can create object of type unique_lock and can defer the lock on that.
void task1()
{
    std::scoped_lock lock(m1, m2);
    //std::lock_guard<std::mutex> l1(m1);

    std::cout<<"In task-1 before sleep"<<endl;
    std::this_thread::sleep_for(std::chrono::seconds(5));
    cout<<"In task-1 again sleep"<<endl;
    //std::lock_guard<std::mutex> l2(m2);
    std::this_thread::sleep_for(chrono::seconds(5));
    cout<<"In task-1 after sleep"<<endl;
    a = 10; b = 20;
    cout<<"task-1 with a: "<< a << " b: "<<b<<endl;
}

void task2()
{
    std::scoped_lock lock(m1,m2);
    //std::lock_guard<std::mutex> l1(m2);
    //std::lock_guard<std::mutex> l2(m1);
    std::cout<<"In task-2"<<endl;
    a = 30, b = 40;
    cout<<"task-2 with a: "<<a<< " b: "<<b<<endl;
}

int main() 
{
  int num = 1;

    std::thread t1(task1);
    std::thread t2(task2);
  
  t1.join();
  t2.join();
  
    std::cout<<"In main terminate"<<endl;
    return 0;
}
