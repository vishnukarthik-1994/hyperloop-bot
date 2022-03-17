#ifndef __COORDINATOR_AGENT__H
#define __COORDINATOR_AGENT__H 

#include "enviro.h"
#define NUMROBOTS 15

using namespace enviro;

//!CoordinatorController is a process that spawns follower robots
//!Robots are spawned every 5 seconds
//!Maximum of 15 robots are added dynamically
//!The number of follower robots can be increased by changing NUMROBOTS

class CoordinatorController : public Process, public AgentInterface {
    public:
	//!Constructor
    CoordinatorController() : _current_things(0), Process(), AgentInterface() {}
	
	//!Initializer
	//!Get the start time and store it in _last_time
	//!Zero out the time measured since last time
    void init() {
        _last_time = std::chrono::high_resolution_clock::now();
        _time_duration = std::chrono::high_resolution_clock::duration::zero();
    }
    void start() {}
	
	//!Add Follower agent for every 5 sec.
	//!Keeps track of the number of agents created dynamically
	//!This function could be used to add some other agents as well
    void update() {
		typedef duration<double,std::ratio<1,1>> seconds_type;
        _current_time = std::chrono::high_resolution_clock::now();
        _time_duration = _current_time - _last_time;
        auto elapsed = seconds_type(_time_duration);
        if(elapsed.count() > 5 && _current_things < NUMROBOTS) {
			add_agent("Follower",  -400, 300, 0, { {"fill", "blue"}});
            _last_time = _current_time;
            _current_things++;
        }
	}
	
    void stop() {}

    private:
	//!Keeps track of the last time a robot was spawned
    std::chrono::high_resolution_clock::time_point _last_time;
	//!Keeps track of the current time when the robot was spawned
    std::chrono::high_resolution_clock::time_point _current_time;
	//!Difference between current time and last time
    std::chrono::duration<double, std::nano> _time_duration;
	//!Counter for number of robots spawned
    int _current_things;

};


//! Coordinator class that inherits from Agent
//! This class is used to add a process that spawns robots periodically
class Coordinator : public Agent {
    public:
    Coordinator(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    CoordinatorController c;
};

DECLARE_INTERFACE(Coordinator)

#endif