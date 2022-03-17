#ifndef __FOLLOWER_AGENT__H
#define __FOLLOWER_AGENT__H 

#include "enviro.h"

using namespace enviro;

//! The interface used to communicate and control the path of follower robots
class FollowerController : public Process, public AgentInterface {
    public:
	//!Constructor
    FollowerController() : Process(), AgentInterface(), follow_x(0), follow_y(0) {}
	
	//!Initializer
	//!Register for robot_position_<id> event
	//This event is passed by the parent robot in front of it
	//!id is the current or child object id
	//!This event contains the coordinates of the parent robot that is to be followed
    void init() {
		watch("robot_position_" + std::to_string((int)id()), [&](Event& e) {
			follow_x = e.value()["x"];
			follow_y = e.value()["y"];
		});
    }
    void start() {}
	
	//!Get reading from range sensor
	//!If the parent robot in front is far, move towards it
	//!If the child/current robot is too close, apply a negative force to slow down
	//!Emit the current position of the child robot
	//!The child robot will act as a parent for the next follower agent spawned
    void update() {
		if(sensor_value(0) > 100) {
			move_toward(follow_x,follow_y);
		} else {
			apply_force(-10, 0);
		}
		decorate("<circle x='-5' y='5' r='5' style='fill: red'></circle>");
        label("Follower_" + std::to_string((int)id()-1), 20, 20);
		emit(Event("robot_position_" + std::to_string((int)id()+1), { { "x", x()}, {"y", y() }}));
    }
    void stop() {}

    double follow_x, follow_y;

};

//! This class adds a process that communicates with other follower robots
class Follower : public Agent {
    public:
    Follower(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    FollowerController c;
};

DECLARE_INTERFACE(Follower)

#endif