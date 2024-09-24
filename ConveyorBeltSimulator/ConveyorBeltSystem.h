/**
 * @file ConveyorBeltSystem.h
 * Definition of a conveyor belt system comprised of several conveyor belts.
 */

#pragma once

#include "ConveyorBelt.h"
#include "MessageBroker.h"
#include <array>
#include <mutex>

class ConveyorBeltSystem
{
public:
	ConveyorBeltSystem(MessageBroker& message_broker);

	/**
	* get total count of luggages occupying the conveyor belt system
	*/
	uint32_t getTotalLuggageCount();

	/**
	* add conveyor belt to the conveyor belt system
	* should only be invoked at the conveyor belt system initialization
	*/
	void addConveyorBelt(std::shared_ptr<ConveyorBelt> conveyor_belt);

	/**
	* add a luggage to the conveyor belt system
	*/
	void addLuggage(std::shared_ptr<Luggage> luggage);

	/**
	* update state of the conveyor belt system 
	* manages transition of the luggage between the belts
	*/
	void update();

	/**
	* print status of the conveyor belt system
	*/
	void printStatus();

private:

	void onBeltChangeMsgRcvd(const std::shared_ptr<Message> message);

	/**
	* moves luggage to the next belt (belt transition)
	*/
	void changeBelt(std::shared_ptr<Luggage> luggage);

	MessageBroker& _messageBroker;	/* message broker for passing messages between threads in a publish-subscribe scheme*/

	std::vector<std::shared_ptr<ConveyorBelt>> _conveyor_belts;		/* conveyor belts building the conveyor belt system */
	std::vector<std::shared_ptr<Luggage>> _luggages;				/* luggages ocupying the belt system */
	std::vector<std::shared_ptr<Luggage>> _luggages_changing_belts;	/* lugguges that currently are changing the belts */

	uint8_t _conveyor_belts_count;	/* number of conveyor belts in the conveyor belt system */
	uint32_t _luggage_count;		/* number of luggages stored on the conveyor belt system */

	bool _is_luggage_changing_belt;				/* flag indicating wether there is a luggage (one or more) that is currently changing the belt */
	std::mutex _luggage_changing_belt_mutex;
};

