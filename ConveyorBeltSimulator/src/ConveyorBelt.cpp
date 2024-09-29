/**
 * @file ConveyorBelt.cpp
 * Implementation of a single conveyor belt within a conveyor belt system.
 */

#include "ConveyorBelt.h"
#include "SimulationConfig.h"
#include "MsgLuggageChangingBelt.h"
#include "TimeCounter.h"
#include <chrono>
#include <iostream>

ConveyorBelt::ConveyorBelt(MessageBroker& messageBroker, float length, float velocity, uint8_t id)
	: _messageBroker{ messageBroker }
	, _task_thread{ &ConveyorBelt::task, this }
	, _length{ length }
	, _velocity{ velocity }
	, _id{ id }
{}

uint32_t ConveyorBelt::getLuggageCount()
{
	std::lock_guard<std::mutex> lock(_conveyor_belt_mutex);
	return static_cast<uint8_t>(_luggages.size());
}

void ConveyorBelt::addLuggage(std::shared_ptr<Luggage> luggage)
{
	std::lock_guard<std::mutex> lock(_conveyor_belt_mutex);
	_luggages.push_back(luggage);
}

void ConveyorBelt::moveLuggages(float move_distance)
{
	std::lock_guard<std::mutex> lock(_conveyor_belt_mutex);

	for (uint32_t i=0; i< _luggages.size(); i++) {	
		float position_on_belt = _luggages.at(i)->getPositionOnBelt();
		float position_total = _luggages.at(i)->getPositionTotal();
		uint8_t belt_number = _luggages.at(i)->getBeltNumber();

		/* move the luggage */
		position_on_belt += move_distance;
		position_total += move_distance;

		if (position_on_belt < _length) { 
			/* luggage stays on the belt */
			_luggages.at(i)->setPositionOnBelt(position_on_belt);
			_luggages.at(i)->setPositionTotal(position_total);
		} else {
			/* luggage leaves the belt */
			/* notify the conveyor belt system about the luggage changing the belts */
			std::string topic{ message_topics::luggage_changing_belt };
			const std::shared_ptr<MsgLuggageChangingBelt> msg_luggage_changing_belt = std::make_shared<MsgLuggageChangingBelt>();
			msg_luggage_changing_belt->_luggage_changing_belt = _luggages.at(i);
			_messageBroker.publish(topic, msg_luggage_changing_belt);

			_luggages.erase(_luggages.cbegin() + i); /* remove the luggage from the belt */
		};
	}
}

void ConveyorBelt::task()
{
	TimeCounter time_counter;
	uint64_t expected_invoke_count = 0; /* expected number of simulation steps within a time period */
	uint64_t actual_invoke_count = 0;	/* actual number of simulation steps within a time period */

	while (1) {

		/* compute expected number of simulation steps based on the elapsed time */
		expected_invoke_count = static_cast<uint64_t>(time_counter.getElapsedTime() * sim_config::sim_freq + 0.5f); 
		/* 0.5 compensates for float to int truncation */

		/* perform simulation step while the actual simulation step count is less than the expected one */
		while (actual_invoke_count < expected_invoke_count) {
			moveLuggages(_velocity * sim_config::sim_dt);
			actual_invoke_count++;
		}

		/* sleep for a while to leave room for other threads */
		std::this_thread::sleep_for(std::chrono::milliseconds(2));
	}
}
