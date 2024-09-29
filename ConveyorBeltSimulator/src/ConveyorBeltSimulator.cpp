/**
 * @file ConveyorBeltSimulator.cpp
 * Implementation of a conveyor belt system simulator.
 */

#include "ConveyorBeltSimulator.h"
#include "TimeCounter.h"
#include <cstdio>
#include <iostream>
#include <chrono>
#include <vector>
#include <memory>

static void clearConsole();

ConveyorBeltSimulator::ConveyorBeltSimulator()
	: _message_broker{}
	, _conv_belt_system{_message_broker}
	, _luggages{}
{
	_conv_belt_system.addConveyorBelt(std::make_shared<ConveyorBelt>(_message_broker, 10.0f, 1.0f, 1));
	_conv_belt_system.addConveyorBelt(std::make_shared<ConveyorBelt>(_message_broker, 10.0f, 1.0f, 2));
	_conv_belt_system.addConveyorBelt(std::make_shared<ConveyorBelt>(_message_broker, 10.0f, 1.0f, 3));
	_conv_belt_system.addConveyorBelt(std::make_shared<ConveyorBelt>(_message_broker, 10.0f, 2.0f, 4));
}

void ConveyorBeltSimulator::run()
{
	TimeCounter time_counter;
	std::thread key_input_thread(&ConveyorBeltSimulator::keyInputTask, this);
	constexpr uint8_t task_sleep_time_ms = 5;
	constexpr float task_sleep_time_s = static_cast<float>(task_sleep_time_ms) * 1.0e-3f;

	while (1) {
		/* updates the state of the conveyor belt system */
		{
			std::lock_guard<std::mutex> lock(_add_luggage_mutex); /* scope-based lock */
			_conv_belt_system.update(); /* update the conveyor belt system */

			/* print status every second; compensate for thread sleep time */
			if (time_counter.getElapsedTime() >= (1.0f - task_sleep_time_s)) {
				time_counter.resetTimer();

				clearConsole();
				_conv_belt_system.printStatus();
			}
		} /* release the lock */

		/* sleep for a while to leave room for other threads */
		std::this_thread::sleep_for(std::chrono::milliseconds(task_sleep_time_ms));
	}
}

void ConveyorBeltSimulator::keyInputTask()
{
	char key_pressed;
	uint32_t luggage_id = 0;

	while (1) {
		key_pressed = std::getchar();
		if (key_pressed == 'l' || key_pressed == 'L') {
			if (luggage_id < UINT32_MAX) {
				std::shared_ptr<Luggage> luggage = std::make_shared<Luggage>(luggage_id);
				luggage_id++;
				std::lock_guard<std::mutex> lock(_add_luggage_mutex);
				_luggages.push_back(luggage);
				_conv_belt_system.addLuggage(luggage);
			}
		}

		/* sleep for a while to leave room for other threads */
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}

static void clearConsole()
{
	// CSI[2J clears screen, CSI[H moves the cursor to top-left corner
	std::cout << "\x1B[2J\x1B[H";
}

