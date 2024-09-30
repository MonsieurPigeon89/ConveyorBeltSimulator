/**
 * @file Luggage.h
 * Definition of a single luggage.
 */

#pragma once

#include <cstdint>
#include <mutex>

class Luggage
{
public:
	Luggage(uint32_t id);

	/**
	* Set position on the conveyor belt
	* 
	* @param position - postion on the belt [m]
	*/
	void setPositionOnBelt(float position);

	/**
	* Set postion on the entire conveyor belt system consisting of multiple belts
	*
	* @param position - postion on the entire conveyor belt system [m]
	*/
	void setPositionTotal(float position);

	/**
	* Set number of the belt that the luggage currently occupies
	*
	* @param belt number - number of the currently occupied belt
	*/
	void setBeltNumber(uint8_t belt_number);

	/**
	* Get ID of the luggage
	*/
	uint32_t getId() const;

	/**
	* Get position of the luggage on the currently occupied belt [m]
	*/
	float getPositionOnBelt() const;

	/**
	* Get position of the luggage on the entire conveyor belt system [m]
	*/
	float getPositionTotal() const;

	/**
	* Get number of the currently occupied belt
	*/
	uint8_t getBeltNumber() const;

	/**
	* Print status of the luggage
	*/
	void printStatus();

private:
	uint32_t _id;				/* ID of the luggage */
	float _position_on_belt;	/* Position of the luggage on the currently occupied belt [m] */
	float _position_total;		/* Position of the luggage on the entire conveyor belt system [m] */
	uint8_t _belt_number;		/* Number of the currently occupied belt*/
};

