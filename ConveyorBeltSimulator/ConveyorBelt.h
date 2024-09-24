/**
 * @file ConveyorBelt.h
 * Definition of a single conveyor belt within a conveyor belt system.
 */

#pragma once

#include "Luggage.h"
#include "MessageBroker.h"
#include <vector>
#include <thread>
#include <memory>
#include <mutex>

class ConveyorBelt
{
public:
	ConveyorBelt(MessageBroker& messageBroker, float length, float velocity, uint8_t id);

	/**
	* Get count of the luggage placed on the conveyor belt
	*/
	uint32_t getLuggageCount();

	/**
	* place luggage on the conveyor belt
	*/
	void addLuggage(std::shared_ptr<Luggage> luggage);

private:

	/**
	* main task of the conveyor belt responsible for moving the luggage
	*/
	void task();

	/**
	* moves the luggage by a certain distance [m]
	*/
	void moveLuggages(float distance);	/* moves all luggages that are on the conveyor belt */

	MessageBroker& _messageBroker;	/* message broker for passing messages between threads in a publish-subscribe scheme*/

	std::vector<std::shared_ptr<Luggage>> _luggages;	/* luggages occupying the belt */

	std::thread _task_thread;	/* task in which lugguges are moved by the conveyor belt */

	float _length;		/* length of the belt(top portion of the belt)[m] */
	float _velocity;	/* velocity of the belt [m/s] */
	uint8_t _id;		/* id of the conveyor bet */

	std::mutex _conveyor_belt_mutex;
};

