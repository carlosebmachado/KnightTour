/*
 * Autor: Carlos Eduardo de Borba Machado
 * Fonte: https://github.com/carlosebmachado/watch/
 */

#ifndef WATCH_H
#define WATCH_H

#include <time.h>
#include <chrono>
#include <string>
#include <sstream>

#define MILLISECOND 1
#define SECOND (1000 * MILLISECOND)
#define MINUTE (60 * SECOND)
#define HOUR (60 * MINUTE)
#define DAY (24 * HOUR)

#define C_NANOSECOND 1
#define C_MICROSECOND (1000 * C_NANOSECOND)
#define C_MILLISECOND (1000 * C_MICROSECOND)
#define C_SECOND (1000 * C_MILLISECOND)


// Stopwatch class.
class Stopwatch
{
private:
	clock_t elapsed;
	clock_t startTime;

public:
	Stopwatch()
	{
		elapsed = 0;
		startTime = 0;
	}

	~Stopwatch() {}

public:
	void start()
	{
		startTime = clock();
	}

	void stop()
	{
		elapsed = clock() - startTime;
	}

	void reset()
	{
		elapsed = 0;
		startTime = 0;
	}

	void restart()
	{
		reset();
		start();
	}

public:
	clock_t getElapsed()
	{
		return elapsed;
	}

	std::string getElapsedFormated()
	{
		long long d = 0, h = 0, m = 0, s = 0, mil = 0, auxElapsed = elapsed;
		d = auxElapsed / DAY;
		auxElapsed %= DAY;
		h = auxElapsed / HOUR;
		auxElapsed %= HOUR;
		m = auxElapsed / MINUTE;
		auxElapsed %= MINUTE;
		s = auxElapsed / SECOND;
		auxElapsed %= SECOND;
		mil = auxElapsed;
		std::stringstream r;
		r << d << "d " << h << "h " << m << "m " << s << "s " << mil << "mil";
		return r.str();
	}
};

// ChronoStopwatch class.
class ChronoStopwatch
{
private:
	long long elapsed;
	std::chrono::steady_clock::time_point startTime;

public:
	ChronoStopwatch()
	{
		elapsed = 0;
		startTime = std::chrono::high_resolution_clock::now();
	}

	~ChronoStopwatch() {}

public:
	void start()
	{
		startTime = std::chrono::high_resolution_clock::now();
	}

	void stop()
	{
		elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - startTime).count();
	}

	void reset()
	{
		elapsed = 0;
		startTime = std::chrono::high_resolution_clock::now();
	}

	void restart()
	{
		reset();
		start();
	}

public:
	long long getElapsed()
	{
		return elapsed;
	}

	std::string getElapsedFormated()
	{
		long long min = 0, sec = 0, mil = 0, mic = 0, nan = 0, auxElapsed = elapsed;
		sec = auxElapsed / C_SECOND;
		auxElapsed %= C_SECOND;
		mil = auxElapsed / C_MILLISECOND;
		auxElapsed %= C_MILLISECOND;
		mic = auxElapsed / C_MICROSECOND;
		auxElapsed %= C_MICROSECOND;
		nan = auxElapsed;
		while (sec >= 60)
		{
			sec -= 60;
			min++;
		}
		std::stringstream r;
		r << min << "min " << sec << "sec " << mil << "mil " << mic << "mic " << nan << "nan";
		return r.str();
	}
};


// Timer class.
class Timer
{
private:
	clock_t startTime;
	clock_t interval;

public:
	Timer()
	{
		startTime = 0;
		interval = 0;
	}

	Timer(clock_t interval)
	{
		startTime = 0;
		this->interval = interval;
	}

	~Timer() {}

public:
	void start()
	{
		startTime = clock();
	}

	bool timeout()
	{
		if (clock() - startTime > interval)
		{
			startTime = clock();
			return true;
		}
		return false;
	}

public:
	void setInterval(clock_t interval)
	{
		this->interval = interval;
	}

	clock_t getInterval()
	{
		return interval;
	}
};

#endif // WATCH_H
