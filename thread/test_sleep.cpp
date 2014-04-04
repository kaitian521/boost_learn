#include <boost/thread.hpp> 
#include <iostream> 

void wait(int seconds) 
{ 
  boost::this_thread::sleep(boost::posix_time::seconds(seconds)); 
} 

void thread() 
{ 
  for (int i = 0; i < 5; ++i) 
  { 
    wait(1); 
    std::cout << i << ":" << boost::this_thread::get_id() << std::endl; 
  } 
} 

int main() 
{ 
  boost::thread t(thread); 
  boost::thread t2(thread); 
  t.join(); 
}
