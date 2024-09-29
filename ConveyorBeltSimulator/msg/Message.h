/**
 * @file Message.h
 * Generic message to be used by a publish-subscribe message broker.
 */

#pragma once

#include "MessageIdList.h"

class Message
{
public:
	/**
	* returns id of the message
	*/
	virtual uint32_t getId() const { return static_cast<uint32_t>(MessageId::NULL_MSG); }
};
