#pragma once

#include <chrono>
#include <string>
#include <vector>

class Profiler
{
public:

    struct Sample
    {
        std::string name;
        float timeMs = 0.0f;
    };

    static Profiler& Get();

    void BeginFrame();
    void EndFrame();

    void BeginSample(const std::string& name);
    void EndSample(const std::string& name);

    float GetFPS() const;
    float GetFrameTime() const;

    const std::vector<Sample>& GetSamples() const;

    void Reset();

private:

    Profiler() = default;

    struct ActiveSample
    {
        std::string name;
        std::chrono::high_resolution_clock::time_point start;
    };

    std::chrono::high_resolution_clock::time_point m_frameStart;

    std::vector<Sample> m_samples;
    std::vector<ActiveSample> m_activeSamples;

    float m_frameTime = 0.0f;
    float m_fps = 0.0f;
};