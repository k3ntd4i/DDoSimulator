#pragma once

#include <chrono>

class Timer
{
private:
	using Clock = std::chrono::steady_clock;
	using Milliseconds = std::chrono::duration<double, std::milli>;
	using Seconds = std::chrono::seconds;
	using Minutes = std::chrono::minutes;

	std::chrono::time_point<Clock> inicio{ Clock::now() };

public:
	Timer() = default;
	void reset() { inicio = Clock::now(); }

	double elapsed() const
	{
		return std::chrono::duration_cast<Milliseconds>(Clock::now() - inicio).count();
	}

	double elapsed_seconds() const
	{
		return std::chrono::duration_cast<Seconds>(Clock::now() - inicio).count();
	}

	double elapsed_minutes() const
	{
		return std::chrono::duration_cast<Minutes>(Clock::now() - inicio).count();
	}
};