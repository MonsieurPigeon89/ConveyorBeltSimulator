/**
 * @file MessageLuggageChangingBelt.h
 * Message informing that there is a luggage currently changing conveyor belts
 */

#pragma once

#include "Message.h"
#include "Luggage.h"
#include <memory>

class MsgLuggageChangingBelt : public Message
{
public:
	uint32_t getId() const override { return static_cast<uint32_t>(MessageId::LUGGAGE_CHANGING_BELT); }

	std::shared_ptr<Luggage> _luggage_changing_belt;
};

