#pragma once
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <queue>
#include <fstream>

class WatchMQ 
{

public:
    WatchMQ()
    {

    }

    ~WatchMQ()
    {

    }
    void AddMessage(std::function<void()> task)
    {
        std::lock_guard<std::mutex> lock(mtx);
        messageQueue.push(task);
        cv.notify_one(); 

    }

    void MonitorQueue() {
        while (isMonitor == true) 
        {
            std::function<void()> task;
            {
                std::unique_lock<std::mutex> lock(mtx);
                cv.wait(lock, [this] { return !messageQueue.empty(); });
                while (!messageQueue.empty()) 
                {
                    task = messageQueue.front();
                    messageQueue.pop();
                    task();
                }
            }

        }
    }

    bool start()
    {
        isMonitor = true;
        m_monitorThread = std::thread(&WatchMQ::MonitorQueue,this);
        if (m_monitorThread.joinable())
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    void stop()
    {
        AddMessage([this] {isMonitor = false; }); //添加一个任务，重置循环判断。需要保证此任务为队列最后一个任务。
        if (m_monitorThread.joinable()) 
        {
            
            m_monitorThread.join();
        }
    }

private:
    bool isMonitor = false; 
    std::queue<std::function<void()>> messageQueue;
    std::mutex mtx;
    std::condition_variable cv;
    std::thread m_monitorThread;

};