/**
 * @file TimeCounter.cpp
 * Implementation of a time counter working in the same manner as a stopwatch.
 */

#include "TimeCounter.h"

using namespace std::chrono;

TimeCounter::TimeCounter()
{
	_time_start = high_resolution_clock::now();
}

float TimeCounter::getElapsedTime()
{
	_time_now = high_resolution_clock::now();
	_time_span = duration_cast<duration<float>>(_time_now - _time_start);
	_time_elapsed = _time_span.count();

	return _time_elapsed;
}

void TimeCounter::resetTimer()
{
	_time_start = high_resolution_clock::now();
}
