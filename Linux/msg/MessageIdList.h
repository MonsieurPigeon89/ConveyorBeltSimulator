/**
 * @file MessageList.h
 * List of message IDs used in the system.
 */

#pragma once

#include <cstdint>

namespace message_topics
{
	inline constexpr char luggage_changing_belt[] = "luggage_changing_belt";
	inline constexpr char another_topic_1[] = "another_topic_1";
	inline constexpr char another_topic_2[] = "another_topic_2";
}

enum class MessageId : uint32_t
{
	NULL_MSG = 0,
	LUGGAGE_CHANGING_BELT = 1,
	ANOTHER_MESSAGE_1 = 2,
	ANOTHER_MESSAGE_2 = 3,
};
