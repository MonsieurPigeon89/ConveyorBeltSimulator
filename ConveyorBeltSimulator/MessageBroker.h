/**
 * @file MessageBroker.h
 * Definition of a message broker working in a publish-subscribe scheme used to exchange messages between threads.
 */

#pragma once

#include "Message.h"
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <mutex>
#include <thread>
#include <functional>
#include <memory>

class MessageBroker
{
public:
    /**
    * publishes a message of a certain topic
    */
    void publish(const std::string& topic, const std::shared_ptr<Message> message);

    /**
    * subscribes to a topic with a callback function
    */
    void subscribe(const std::string& topic, std::function<void(const std::shared_ptr<Message>)> callback);

private:
    std::unordered_map<std::string, std::vector<std::function<void(const std::shared_ptr<Message>)>>> subscribers;
    std::mutex mtx;
};

