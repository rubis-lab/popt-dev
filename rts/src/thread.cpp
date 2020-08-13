#include "thread.hpp"

namespace rts {
    Thread::Thread(int thr_id){
        tid = thr_id;
        thread_print();
    }    
    void Thread::thread_print(){
        std::cout << "Thread id: " << tid << "\t";
        this->task_print();
    }
}