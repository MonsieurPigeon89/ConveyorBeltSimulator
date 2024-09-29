/**
 * @file TimeCounter.h
 * Definition of a time counter working in the same manner as a stopwatch.
 */

#pragma once

#include <chrono>

class TimeCounter
{
public:
	TimeCounter();

	/**
	* Get elapsed time from the timer [s]
	*/
	float getElapsedTime();

	/**
	* Reset the timer
	*/
	void resetTimer();

private:

	std::chrono::high_resolution_clock::time_point _time_start;	/* time point of reseting the timer */
	std::chrono::high_resolution_clock::time_point _time_now;	/* current time point*/
	std::chrono::duration<float> _time_span;					/* time span between start and current time points */
	float _time_elapsed;										/* time elapsed since the timer restart [s] */
};

