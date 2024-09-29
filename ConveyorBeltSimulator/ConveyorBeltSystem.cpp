/**
 * @file ConveyorBeltSystem.cpp
 * Implementation of a conveyor belt system comprised of several conveyor belts.
 */

#include "ConveyorBeltSystem.h"
#include "MsgLuggageChangingBelt.h"
#include <mutex>
#include <iostream>

ConveyorBeltSystem::ConveyorBeltSystem(MessageBroker& message_broker)
	: _messageBroker {message_broker}
	, _conveyor_belts_count{ 0 } 
	, _luggage_count{ 0 }
{
	std::string topic{ message_topics::luggage_changing_belt };
	std::function<void(const std::shared_ptr<Message>)> luggage_belt_change_callback =
		std::bind(&ConveyorBeltSystem::onBeltChangeMsgRcvd, this, std::placeholders::_1);
	_messageBroker.subscribe(topic, luggage_belt_change_callback);
}

void ConveyorBeltSystem::addConveyorBelt(std::shared_ptr<ConveyorBelt> conveyor_belt)
{
	_conveyor_belts.push_back(conveyor_belt);
	_conveyor_belts_count++;
}

void ConveyorBeltSystem::addLuggage(std::shared_ptr<Luggage> luggage)
{
	_luggages.push_back(luggage);
	_conveyor_belts[0]->addLuggage(luggage);
	_luggage_count++;
}

void ConveyorBeltSystem::update()
{
	std::lock_guard<std::mutex> lock(_luggage_changing_belt_mutex);
	
	/* check if the luggages are changing belts */
	if (_is_luggage_changing_belt) {
		while (!_luggages_changing_belts.empty()) {
			/* if there are luggages in the queue that are currently changing belts invoke belt change on them */
			changeBelt(_luggages_changing_belts.front());
			_luggages_changing_belts.erase(_luggages_changing_belts.begin());
		}
		_is_luggage_changing_belt = false;
	}
}

void ConveyorBeltSystem::printStatus()
{
	std::cout.precision(1);
	std::cout << std::fixed;

	for (uint8_t i = 0; i < _conveyor_belts_count; i++) {
		std::cout 
			<< "B" << static_cast<uint32_t>(i+1) 
			<< "\t" << _conveyor_belts[i]->getLuggageCount() << "\t";
	}
	std::cout << std::endl;

	if (_luggage_count == 0) {
		std::cout << "No luggage" << std::endl;
	} else {
		for (uint32_t i = 0; i < _luggage_count; i++) {
			std::cout 
				<< "L" << i+1 
				<< "\t" << static_cast<uint32_t>(_luggages.at(i)->getBeltNumber()+1)
				<< "\t" << _luggages.at(i)->getPositionOnBelt() << std::endl;
		}
	}
}

void ConveyorBeltSystem::onBeltChangeMsgRcvd(const std::shared_ptr<Message> message)
{
	std::lock_guard<std::mutex> lock(_luggage_changing_belt_mutex);

	_is_luggage_changing_belt = true;

	const MsgLuggageChangingBelt* msg_change_belt = dynamic_cast<const MsgLuggageChangingBelt*>(message.get());
	if (msg_change_belt)
	{
		/* add the luggage to the queue of luggages currently changing belts */
		_luggages_changing_belts.push_back(msg_change_belt->_luggage_changing_belt);
	} else {
		std::cout << "error: dynamic cast failed - unexpected message received" << std::endl;
	}
}

void ConveyorBeltSystem::changeBelt(std::shared_ptr<Luggage> luggage)
{
	uint8_t belt_number_new = luggage->getBeltNumber() + 1;

	/* if the luggage reaches last belt then it goes back to the first belt (circular system) */
	if (belt_number_new == _conveyor_belts_count) {
		belt_number_new = 0;
		luggage->setPositionTotal(0.0);
	}

	/* place the luggage on the next belt */
	luggage->setBeltNumber(belt_number_new);
	luggage->setPositionOnBelt(0.0);
	_conveyor_belts[belt_number_new]->addLuggage(luggage);
}
