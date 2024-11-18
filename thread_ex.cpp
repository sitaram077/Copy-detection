#include <iostream>
#include <thread>  

void monitorClipboard() {
    std::cout << "Monitoring clipboard..." << std::endl;
}

int main() {
    std::thread clipboardThread(monitorClipboard); 
    clipboardThread.join(); 
    return 0;
}
