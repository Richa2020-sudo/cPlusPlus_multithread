// Online C++ compiler to run C++ program online
// Use of unique_lock with multithreads.
// lock()/unlock() manually.
// defer the lock()
// use this with condition_variable (cannot use lock_guard)

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
// unique_lock: use lock_guard for small chunk of code.Also it unlock automatically.

std::mutex m;
// example: lock(), unlock()
void task(int thread, int num)
{
    std::cout<<"In task function"<<endl;
    for(auto i = 0; i < 10000; i++)
    {
        std::unique_lock<std::mutex> lock(m);
        num += i;    
        lock.unlock();
    }
    
    cout<<"Thread: "<< thread <<" total: "<<num<<endl;
    
}

// example of unique_lock with defer:
// mean can create object of type unique_lock and can defer the lock on that.
void testDefer(int thread)
{
    std::unique_lock<std::mutex> lock(m, std::defer_lock);
    std::cout<<"Before lock by thread: "<<thread<<endl;
    lock.lock();
    cout<<"In lock area by thread: "<<thread<<endl;
    lock.unlock();
    cout<<"after unlock by thread: "<<thread<<endl;
}

int main() 
{
  int num = 1;

  std::thread t1(task,1, std::ref(num));
  //std::chrono::seconds(10);
  std::thread t2(task, 2, std::ref(num));
  
  t1.join();
  t2.join();
  
  std::thread t3(testDefer,1);
  std::thread t4(testDefer,2);
  
  t3.join();
  t4.join();
    std::cout<<"In main terminate"<<endl;
    return 0;
}
