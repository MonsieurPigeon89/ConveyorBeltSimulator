/**
 * @file MessageList.h
 * List of message IDs used in the system.
 */

#pragma once

#include <cstdint>

enum class MessageId : uint32_t
{
	NULL_MSG = 0,
	LUGGAGE_CHANGING_BELT = 1,
	ANOTHER_MESSAGE_1 = 2,
	ANOTHER_MESSAGE_2 = 3,
};
