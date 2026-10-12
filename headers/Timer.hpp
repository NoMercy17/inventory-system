#pragma once
#include <iostream>
#include <chrono>
#include <string_view>

class SystemTimer
{
public:
    using Clock = std::chrono::steady_clock;
    
    explicit SystemTimer(std::string_view name) : m_name_(name) , m_point_(Clock::now()) {}

    ~SystemTimer(){
        auto end = Clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end-m_point_).count();
        std::cout << "\n[TIMER] " << m_name_ << " TOOK: " << duration << " µs\n" << std::endl;        }

    // timer shouldn't be copied
    SystemTimer& operator=(const SystemTimer& rhs) = delete;
    SystemTimer(const SystemTimer& rhs) = delete;

private:

    // we  scope the SystemTimer so the initially short-lived string_view will be destroyed right after by {}, only problem is if we do: 
    // SystemTimer timer(std::string("Temporary ") + "Timer")
    // at 1 allocation price we can have std::string m_name_ and just move the string in the constructor
    std::string_view m_name_;


    // the point in time at which we meassure
    std::chrono::time_point<Clock> m_point_;
};

