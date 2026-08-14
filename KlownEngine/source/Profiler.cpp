#include "Profiler.h"

Profiler& Profiler::Get()
{
    static Profiler instance;
    return instance;
}

void Profiler::BeginFrame()
{
    m_frameStart = std::chrono::high_resolution_clock::now();

    m_samples.clear();
    m_activeSamples.clear();
}

void Profiler::EndFrame()
{
    auto frameEnd = std::chrono::high_resolution_clock::now();

    std::chrono::duration<float, std::milli> elapsed =
        frameEnd - m_frameStart;

    m_frameTime = elapsed.count();

    if (m_frameTime > 0.0f)
        m_fps = 1000.0f / m_frameTime;
    else
        m_fps = 0.0f;
}

void Profiler::BeginSample(const std::string& name)
{
    ActiveSample sample;

    sample.name = name;
    sample.start = std::chrono::high_resolution_clock::now();

    m_activeSamples.push_back(sample);
}

void Profiler::EndSample(const std::string& name)
{
    auto end = std::chrono::high_resolution_clock::now();

    for (auto it = m_activeSamples.begin();
        it != m_activeSamples.end();
        ++it)
    {
        if (it->name == name)
        {
            std::chrono::duration<float, std::milli> elapsed =
                end - it->start;

            Sample result;
            result.name = name;
            result.timeMs = elapsed.count();

            m_samples.push_back(result);

            m_activeSamples.erase(it);
            return;
        }
    }
}

float Profiler::GetFPS() const
{
    return m_fps;
}

float Profiler::GetFrameTime() const
{
    return m_frameTime;
}

const std::vector<Profiler::Sample>& Profiler::GetSamples() const
{
    return m_samples;
}

void Profiler::Reset()
{
    m_samples.clear();
    m_activeSamples.clear();

    m_frameTime = 0.0f;
    m_fps = 0.0f;
}