/**
 * @file MessageBroker.cpp
 * Implementation of a message broker working in a publish-subscribe scheme used to exchange messages between threads.
 */

#include "MessageBroker.h"

void MessageBroker::publish(const std::string& topic, const std::shared_ptr<Message> message)
{
    std::lock_guard<std::mutex> lock(mtx);

    /* If there are subscribers for the topic, notify them */
    if (subscribers.find(topic) != subscribers.end()) {
        for (auto& subscriberCallback : subscribers[topic]) {
            /* Notify each subscriber in a separate thread */
            std::thread([subscriberCallback, message]() {
                subscriberCallback(message);
                }).detach();
        }
    }
}

void MessageBroker::subscribe(const std::string& topic, std::function<void(const std::shared_ptr<Message>)> callback)
{
	std::lock_guard<std::mutex> lock(mtx);
	subscribers[topic].push_back(callback);
}

