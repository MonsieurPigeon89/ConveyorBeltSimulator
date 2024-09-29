**How to build on Ubuntu**



**How to run and use**


**Design decisions**

The conveyor belt simulator is build from classes that try to mimic physical conveyor belt system.
ConveyorBeltSimulator is the topmost class responsible for the simulation. It is also responsible for handling the user input.
ConveyorBeltSystem is a class representing the conveyor belt system comprised of several conveyor belts.
ConveyorBelt is a class representing a single conveyor belt on which the luggage is placed.
Luggage is a class representing a single luggage.

Simplified relations between classes can be shown as below: 

ConveyorBeltSimulator
	MessageBroker
	ConveyorBeltSystem
		ConveyorBelt
			Luggage
			Luggage
		ConveyorBelt
			-------
		ConveyorBelt
			Luggage
		ConveyorBelt
			Luggage
			Luggage
			Luggage

Each conveyor belt runs in a separate thread as an individual component.
Information exchange between ConveyorBelts and the ConveyorBeltSystem is done via MessageBroker working in a publish-subscribe scheme.
The publish-subscribe MessageBroker seemed like the best way to handle the communication between the threads.