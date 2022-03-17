# hyperloop-bot

This is the final project for Software Engineering for Embedded Systems that I implemented using [ENVIRO](https://github.com/klavinslab/enviro/) and [ELMA](https://github.com/klavinslab/elma). Enviro is a multi robot simualtion environment where robots characteristics and behavior like velocity and mass could be controlled. Also, static objects like walls and blocks could be added to the environment to simulate a real time scenario.

## Overview

The goal of the project is to create a Leader-Follower based robot simulation. The leader robot determines the path that is to be taken by the leader as well as the follower robots that flock behind it. Each robot also has a range sensor to avoid collisions with other robots. Each follower robot is spawned periodically in an interval of five seconds and the newly spawned robots follow the robot that was spawned before it thereby creating a train like structure. The leader robot takes a loopy course when both force and torque are applied simulataneously. This inturn makes the followers to also take a loopy course since they follow the parent robot. When the distance between two robots is huge, the child robot is moved towards its parent by applying force and torque. If the child robot gets too close, a negative force is applied to slow it down. Events are used to keep each robot informed about the coordinates of its parent robot.

The code consists of three main blocks:

**Coordinator:**
This is responsible for spawning new follower robots. A coordinator is defined as an inivisble process in the project configuration since it should not be visible in the simulation. Each follower agent is created periodically for every 5 seconds and the maximum number of robots that can be created in the current code is 15. This number can be changed in coordinator.h. However, with increase in number of robots, there is a greater chance to see collisions amongst the robots. However the robots would be ultimately able to follow its parent.

**Leader:**
The leader robot is responsbile for all follower robots. Its main job is to guide the robots that are following it. The leader bot must slow down in case of obstacles that it encounters in the course and it must also emit an event which informs the first follower robot behind it about its current coordinates.

**Follower:**
The follower robot watches for the cooridinates of the parent robot and also emits its own coordinates thorugh an event to the child robot that was spawned using the coordinator.

![alt text](https://github.com/vishnukarthik-1994/hyperloop-bot/blob/main/gif/hyperloop_bot.gif)

## Key Challenges

**Physics behind the robots:**
One of the most challenging task was to determine the Linear velocity, Angular velocity, Force, Torque, Friction and Mass of the robots. It required multiple trials to arrive at ideal values to ensure that the robots actually followed a loopy path.

**Handling Collisions:**
Another major aspect that I had to deal with is to handle collisions when new robots are spawned. This required that all the robots slowed down and maintain a safe distance when a new robot was about to collide with them

**Version Selection:**
I had to try out multiple versions of Enviro to finally settle down at v1.61. There were a lot of segmentation faults that I encountered when I used previous versions. Also some features like invisible process and references were not supported in older versions.


## Installation

### Requirements & Steps to Run

[Docker](https://docs.docker.com/get-docker/) and [Git](https://git-scm.com/) have to be installed on the local machine before following the steps mentioned below.

1. Open the command prompt
2. git clone https://github.com/vishnukarthik-1994/hyperloop-bot.git
3. cd project
4. docker run -p80:80 -p8765:8765 -v $PWD:/source -it klavins/enviro:v1.61 bash
5. Now you must have entered the docker container
6. esm start
7. Open a web browser and enter http://localhost in the search bar
8. enviro
9. You should be able to see the simulation in the localhost

## Acknowledgments

The project used packages provided by [ENVIRO](https://github.com/klavinslab/enviro/) and [ELMA](https://github.com/klavinslab/elma).

The docker image used was provided by [Klavins](https://github.com/klavinslab).

The reference code that I followed to implement my project is [Spawner](https://github.com/klavinslab/enviro/tree/master/examples/spawner/).

I would like to give a shoutout to Sourav Jena, my classmate for helping me figure out the correct dynamic properties for the follower robots that were spawned.
