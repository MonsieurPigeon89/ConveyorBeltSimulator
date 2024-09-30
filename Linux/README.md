# Conveyor Belt Simulator
## How to build on Ubuntu

To build the application open the terminal in the `conveyor_belt_sim/build` directory

and run the command:

```
cmake .. && make
```

### Dependencies:

**pthread** - to support multithreading
**ncurses** - for text-based user interface

## How to run and use

To run the application, open the terminal in the `conveyor_belt_sim/build` directory and enter:
```
./luggage_belts
```

The simulation will start with no luggages. To add a luggage, simply press the "L" key.

> [!NOTE]
> The luggage is placed at the moment of pressing the "L" key. The luggage status is outputted every second. If the luggage is placed between the status outputs, the first position outputted will not be equal to 0.0. 

## Design decisions

The conveyor belt simulator is build from classes that try to mimic a physical conveyor belt system.
ConveyorBeltSimulator is the topmost class responsible for the simulation. It is also responsible for handling the user input.
ConveyorBeltSystem is a class representing the conveyor belt system comprised of several conveyor belts.
ConveyorBelt is a class representing a single conveyor belt on which the luggage is placed.
Luggage is a class representing a single luggage.

Simplified relations between the classes can be shown as below: 

* **ConveyorBeltSimulator**
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

