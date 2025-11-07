// Online C++ compiler to run C++ program online
// Use of lock_guard with multithreads.

#include <iostream>
#include <sstream>
#include <map>
#include <string>
#include <limits>
#include <cstdint>
#include <thread>
#include <vector>
#include <mutex>
using namespace std;
// use lock_guard for small chunk of code.Also it unlock automatically.

std::mutex m;
void task(int thread, int num)
{
    std::cout<<"In task function"<<endl;
    for(auto i = 0; i < 10000; i++)
    {
        std::lock_guard<std::mutex> lock(m);
        num += i;    
    }
    
    cout<<"Thread: "<< thread <<" total: "<<num<<endl;
    
}

int main() 
{
  int num = 1;

  std::thread t1(task,1, std::ref(num));
  std::thread t2(task, 2, std::ref(num));
  
  t1.join();
  t2.join();
  
    std::cout<<"In main terminate"<<endl;
    return 0;
}
