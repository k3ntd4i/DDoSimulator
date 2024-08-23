#pragma once

#include <chrono>

class Timer
{
private:
	using Clock = std::chrono::steady_clock;
	using Milisecond = std::chrono::duration<double, std::milli>;

	std::chrono::time_point<Clock> inicio{ Clock::now() };

public:
	Timer() = default;
	void reset() { inicio = Clock::now(); }

	double elapsed() const
	{
		return std::chrono::duration_cast<Milisecond>(Clock::now() - inicio).count();
	}
};