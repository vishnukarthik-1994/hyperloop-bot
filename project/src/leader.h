#ifndef __LEADER__H
#define __LEADER__H

#include "enviro.h"

using namespace enviro;


//! Interface that controls the path of the leader robot
class LeaderController : public Process, public AgentInterface {

    public:
	//! Constructor
    LeaderController() : Process(), AgentInterface() {}

    void init() {
        
    }
    void start() {}
	
	//! If something is blocking the leader robot slow it down
	//! If the path is clear, move the leader in a loopy path
	//! A loop can be created by specifying the angular velocity besides linear
	//! Emit an event that notifies the first follower robot
	//! The first follower robot always has an id() of 2
	//! id() 1 is assigned to references specified in the config json file
    void update() {
		if ( sensor_value(0) < 40 ) {
			label(sensor_reflection_type(0), 20, 5);
			apply_force(-10, 0);
		} else {
			apply_force(100, 5);
		}
        decorate("<circle x='-5' y='5' r='5' style='fill: red'></circle>");
		label("Leader", 20, 20);
        emit(Event("robot_position_2", { { "x", x()}, {"y", y() }}));
    }
    void stop() {}

};

//! This class adds a process that represents the leader robot
class Leader : public Agent {
    public:
    Leader(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    LeaderController c;
    
};

DECLARE_INTERFACE(Leader)

#endif