/**
 * @file ConveyorBeltSimulator.h
 * Definition of a conveyor belt system simulator.
 */

#pragma once

#include "ConveyorBeltSystem.h"
#include <vector>
#include <memory>
#include <mutex>

class ConveyorBeltSimulator
{
public:
	ConveyorBeltSimulator();

	/**
	* runs the simulation
	*/
	void run();

private:
	MessageBroker _message_broker;	/* message broker for passing messages between threads in a publish-subscribe pattern */

	ConveyorBeltSystem _conv_belt_system;				/* conveyor belt system consisting of several belts */
	std::vector<std::shared_ptr<Luggage>> _luggages;	/* luggages occupying the conveyor belt system */

	void keyInputTask();	/* a task reading user input from the keyboard */

	std::mutex _add_luggage_mutex;	/* mutex for adding a luggage from another thread */
};