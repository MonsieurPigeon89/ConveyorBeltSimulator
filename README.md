# Conveyor Belt Simulator
## How to build on Ubuntu


## How to run and use
To run, open the terminal in the program directory and enter command:
```
./luggage_belts
```

The simulation will start with no luggage. To add luggage, simply press "L" key.

## Design decisions
The conveyor belt simulator is build from classes that try to mimic a physical conveyor belt system.
ConveyorBeltSimulator is the topmost class responsible for the simulation. It is also responsible for handling the user input.
ConveyorBeltSystem is a class representing the conveyor belt system comprised of several conveyor belts.
ConveyorBelt is a class representing a single conveyor belt on which the luggage is placed.
Luggage is a class representing a single luggage.

Simplified relations between classes can be shown as below: 

* ConveyorBeltSimulator
    * MessageBroker
    * ConveyorBeltSystem
	    * ConveyorBelt
			* Luggage
			* Luggage
		* ConveyorBelt
			* Empty
		* ConveyorBelt
			* Luggage
		* ConveyorBelt
			* Luggage
			* Luggage
			* Luggage

Each conveyor belt runs in a separate thread as an independent component.
Information exchange between ConveyorBelts and the ConveyorBeltSystem is done via MessageBroker working in a publish-subscribe pattern.
The publish-subscribe MessageBroker seemed like the best way to handle the communication between the threads.