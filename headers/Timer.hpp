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
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - m_point_).count();
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


// used for over time dmg / calculations or other needs
class GameClock
{
public:
    using Clock = std::chrono::steady_clock;

    // default constructor is enough so far
    GameClock() = default;

    void tick(){
        auto now = Clock::now();
        std::chrono::duration<double> rawDelta = now - m_lastTicks_;
        m_lastTicks_ = now;

        m_deltaTime = rawDelta.count() * m_timeScale_;
        m_elapsedSeconds += m_deltaTime;

    }

    double getDeltaTime() const noexcept { return m_deltaTime; };
    double getTotalTime() const noexcept { return m_elapsedSeconds; };
    void setTimeScale(double timescale) { m_timeScale_ = timescale; };


private:
    std::chrono::time_point<Clock> m_lastTicks_ { Clock::now() };
    // the speed multiplier, 1.0 - normal, 0.5 - slow motion, 2.0 - fast-forward, 0.0 - Pause
    double m_timeScale_ {1.0}; 
    // how much game time it passes during the single most recent tick 
    // e.g poison does 10 dmg a sec: this frame it deals 10 * m_deltaTime_
    // Game at 60fps -> deltaTime ~= 0.016 seconds
    double m_deltaTime {0.0};
    // total game time since the clock has been created
    // for example "How long has the batter been going on"
    double m_elapsedSeconds {0.0};

};
