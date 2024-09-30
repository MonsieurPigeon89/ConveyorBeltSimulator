/**
 * @file Luggage.cpp
 * Implementation of a single luggage.
 */

#include "Luggage.h"
#include <iostream>
#include <mutex>

Luggage::Luggage(uint32_t id)
	: _id{ id }
	, _position_on_belt{ 0.0f }
	, _position_total{ 0.0f }
	, _belt_number{ 0 }
{}

void Luggage::setPositionOnBelt(float position)
{
	_position_on_belt = position;
}

void Luggage::setPositionTotal(float position)
{
	_position_total = position;
}

void Luggage::setBeltNumber(uint8_t belt_number)
{
	_belt_number = belt_number;
}

uint32_t Luggage::getId() const
{
	return _id;
}

float Luggage::getPositionOnBelt() const
{
	return _position_on_belt;
}

float Luggage::getPositionTotal() const
{
	return _position_total;
}

uint8_t Luggage::getBeltNumber() const
{
	return _belt_number;
}

void Luggage::printStatus()
{
	std::cout.precision(2);
	std::cout << std::fixed;

	std::cout 
		<< "luggage id: " << _id << "\n"
		<< "belt number: " << static_cast<uint32_t>(_belt_number+1) << "\n"
		<< "position on the belt: " << _position_on_belt << "\n"
		<< "position on the conveyor system: " << _position_total << "\n" << std::endl;
}

