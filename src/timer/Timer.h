#pragma once

#include <chrono>

class Timer {

public:
    using clock_t = std::chrono::steady_clock;
    using timepoint_t = clock_t::time_point;

    Timer();
    void pause();
    void resume();
    double stop();

private:
    timepoint_t last_resume;
    std::chrono::steady_clock::duration inter_duration;
    bool is_counting;
};
