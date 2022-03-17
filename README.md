# hyperloop-bot

This is the final project for Software Engineering for Embedded Systems that I implemented using [ENVIRO](https://github.com/klavinslab/enviro/) and [ELMA](https://github.com/klavinslab/elma).

##Overview

The goal of the project is to create a Leader-Follower based robot simulation. The leader robot determines the path that is to be taken by the leader as well as the follower robots that flock behind it. Each robot also has a range sensor to avoid collisions with other robots. Each follower robot is spawned periodically in an interval of five seconds and the newly spawned robot follows the robot that was spawned before it thereby creating a train like structure. The leader robot takes a loopy course when both force and torque are applied simulataneously. This inturn makes the followers to also take a loopy course since they follow the parent robot in front of it. When the distance between two robots is huge, the robot is moved towards it's parent by applying force and torque. If the child robot gets too close, a negative force is applied to slow down the robot.
