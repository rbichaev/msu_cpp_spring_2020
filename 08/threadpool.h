#include <iostream>
#include <functional>
#include <queue>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>

// структура, содержащая информацию об ответе вызываемой функции
template<class Res_T> 
struct Result 
{ 	
    volatile bool ready; 	
    Res_T out; 

    Result()
        :ready(false)
    {
    } 	

    Res_T get() const
    {
        while(!ready) {}
        return out;
    }
}; 

// класс ThreadPool
class ThreadPool
{
    size_t pool_size;
    bool off = false;
    std::mutex mut;
    std::condition_variable cond;

    std::queue<std::function<void()>> funct_queue;
    std::vector<std::thread> threads;

    // отдельный thread
    // находится в рабочем состоянии, пока off == false
    // находится в спящем состоянии, пока очередь пуста
    void worker_thread()
    {
        while (!off)
        {
            std::unique_lock<std::mutex> lock(mut);
            cond.wait(lock, [this](){ return (!funct_queue.empty() || off); });
            if (off)
                break;
            std::function<void()> task = funct_queue.front();
            funct_queue.pop();
            lock.unlock();
            task();
        }
    }

public:

    // конструктор
    // заполняет созданную очередь thread'ов thread'ами
    ThreadPool(size_t size)
        : pool_size(size)
    {
        for (size_t i=0; i<pool_size; i++)
        {
            threads.push_back(std::thread(&ThreadPool::worker_thread, this));
        }
    }

    // деструктор
    // меняет off на true, пробуждает все спящие thread'ы, 
    // дожидается завершения их работы
    ~ThreadPool()
    {
        off = true;
        cond.notify_all();
        for (size_t i=0; i<pool_size; i++)
        {
            threads[i].join();
        }
    }

    // функция, реализующая интерфейс запуска из функции main
    template<class F, class ...Args> 
    auto exec(F f, Args ...args)
    {
        return push_function<decltype(f(args...))>(f, args...);
    }

    // кладет обработанную функцию в очередь и пробуждает спящий thread
    template<class Res_T, class F, class ...Args> 
    std::shared_ptr<Result<Res_T>> push_function(F f, Args ...args) 
    { 	
        std::function<Res_T()> bind_funct = std::bind(f, args...);   	
        std::shared_ptr<Result<Res_T>> result(new Result<Res_T>());

        std::function<void()> funct = [=]() 	
        { 		
            result->out = bind_funct(); 		
            result->ready = true; 	
        };

        funct_queue.push(funct);
        cond.notify_one();

        return result; 
    } 
};
