# Final Project : Control and Trajectory Tracking for Autonomous Vehicle

## Set up
### 1. Running CARLA Simulator
```
** Create a new terminal **
$> su - student
$> cd /opt/carla-simulator/
$> SDL_VIDEODRIVER=offscreen ./CarlaUE4.sh -opengl
```
### 2. Cloning the project repository
```
** Create a new terminal **
$> git clone https://github.com/nieuwmijnleven/motion-planning-and-decision-making.git
$> cd ./motion-planning-and-decision-making
```
### 3. Installing build essential tools
```
$> cd ./project
$> ./install-ubuntu.sh
```
### 4. Building this project
```
$> cd ./pid_controller
$> rm -rf rpclib
$> git clone https://github.com/rpclib/rpclib.git
$> cmake .
$> make
```
### 5. Running this project
```
$> cd ../
$> ./run_main.sh
// This will silently fail
// ctrl + C to stop 
// run 'run_main.sh' again
$> ./run_main.sh
```
**If error bind is already in use, or address already being used**

* `ps -aux | grep carla`
* `kill id`

## Experimental Results
**It takes times to load the result animation**

**You can download the result animation directly from project/img/result.gif** 
<kbd>
 <img src = "project/img/result.gif?raw=true" width=1280/>
</kbd>

## Answering the Questions
### 1. Add the plots to your report and explain them (describe what you see)
* The following graph shows steer output and steer error
* steer error line is skyrocketed to positive or negative directions four times.
  * There are three obstacles
  * Therefore, our car have to change direction four times.

<kbd>
 <img src = "project/img/steer3.png?raw=true" width=640/>
</kbd>

* The following graph shows throttle output and throttle error
* throttle error line is stable and streight
  * Only our car moves in the simulatior  
  * There are no moving obstacles
  * Thus, There are no need for accelerations or deaccelerations
<kbd>
 <img src = "project/img/throttle3.png?raw=true" width=640/>
</kbd>

### 2. What is the effect of the PID according to the plots, how each part of the PID affects the control command?

### 3. How would you design a way to automatically tune the PID parameters?
* It is challenging to tuning the PID parameters automatically in the simulation environment
* We decided to follow the advice for tuning the PID parameters manually.
  * (Link) https://robotics.stackexchange.com/questions/167/what-are-good-strategies-for-tuning-pid-loops
    * 1. Set all gains to zero
    * 2. Increase the P gain until the response to a disturbance is steady oscillation
    * 3. Increase the D gain until the the oscillations go away (i.e. it's critically damped)
    * 4. Repeat steps 2 and 3 until increasing the D gain does not stop the oscillations
    * 5. Set P and D to the last stable values
    * 6. Increase the I gain until it brings you to the setpoint with the number of oscillations desired (normally zero but a quicker response can be had if you don't mind a couple oscillations of overshoot)


### 4. PID controller is a model free controller, i.e. it does not use a model of the car. Could you explain the pros and cons of this type of controller?
* Advantage
  * feasibility
  * easy to be implemented
  * PID gains can be designed based upon the system parameters
  * PID helps you control a system adequately without full information of the its characteristics

* Disadvantage
  * Three control elements are not exclusively independent from each other
    *  one element can change by adjusting the other
      *  thus, designing PID is more complex than P, PD or PI
  *  PID controller has low robustness compared with the other robust controller

# Proportional-Integral-Derivative (PID)

In this project, you will apply the skills you have acquired in this course to design a PID controller to perform vehicle trajectory tracking. Given a trajectory as an array of locations, and a simulation environment, you will design and code a PID controller and test its efficiency on the CARLA simulator used in the industry.

### Installation

Run the following commands to install the starter code in the Udacity Workspace:

Clone the <a href="https://github.com/udacity/nd013-c6-control-starter/tree/master" target="_blank">repository</a>:

`git clone https://github.com/udacity/nd013-c6-control-starter.git`

## Run Carla Simulator

Open new window

* `su - student`
// Will say permission denied, ignore and continue
* `cd /opt/carla-simulator/`
* `SDL_VIDEODRIVER=offscreen ./CarlaUE4.sh -opengl`

## Compile and Run the Controller

Open new window

* `cd nd013-c6-control-starter/project`
* `./install-ubuntu.sh`
* `cd pid_controller/`
* `rm -rf rpclib`
* `git clone https://github.com/rpclib/rpclib.git`
* `cmake .`
* `make` (This last command compiles your c++ code, run it after every change in your code)

## Testing

To test your installation run the following commands.

* `cd nd013-c6-control-starter/project`
* `./run_main_pid.sh`
This will silently fail `ctrl + C` to stop
* `./run_main_pid.sh` (again)
Go to desktop mode to see CARLA

If error bind is already in use, or address already being used

* `ps -aux | grep carla`
* `kill id`


## Project Instructions

In the previous project you built a path planner for the autonomous vehicle. Now you will build the steer and throttle controller so that the car follows the trajectory.

You will design and run the a PID controller as described in the previous course.

In the directory [/pid_controller](https://github.com/udacity/nd013-c6-control-starter/tree/mathilde/project_c6/project/pid_controller)  you will find the files [pid.cpp](https://github.com/udacity/nd013-c6-control-starter/tree/mathilde/project_c6/project/pid_controller/pid.cpp)  and [pid.h](https://github.com/udacity/nd013-c6-control-starter/tree/mathilde/project_c6/project/pid_controller/pid.h). This is where you will code your pid controller.
The function pid is called in [main.cpp](https://github.com/udacity/nd013-c6-control-starter/tree/mathilde/project_c6/project/pid_controller/main.cpp).

### Step 1: Build the PID controller object
Complete the TODO in the [pid_controller.h](https://github.com/udacity/nd013-c6-control-starter/tree/mathilde/project_c6/project/pid_controller/pid_controller.h) and [pid_controller.cpp](https://github.com/udacity/nd013-c6-control-starter/tree/mathilde/project_c6/project/pid_controller/pid_controller.cpp).

Run the simulator and see in the desktop mode the car in the CARLA simulator. Take a screenshot and add it to your report. The car should not move in the simulation.
### Step 2: PID controller for throttle:
1) In [main.cpp](https://github.com/udacity/nd013-c6-control-starter/tree/mathilde/project_c6/project/pid_controller/main.cpp), complete the TODO (step 2) to compute the error for the throttle pid. The error is the speed difference between the actual speed and the desired speed.

Useful variables:
- The last point of **v_points** vector contains the velocity computed by the path planner.
- **velocity** contains the actual velocity.
- The output of the controller should be inside [-1, 1].

2) Comment your code to explain why did you computed the error this way.

3) Tune the parameters of the pid until you get satisfying results (a perfect trajectory is not expected).

### Step 3: PID controller for steer:
1) In [main.cpp](https://github.com/udacity/nd013-c6-control-starter/tree/mathilde/project_c6/project/pid_controller/main.cpp), complete the TODO (step 3) to compute the error for the steer pid. The error is the angle difference between the actual steer and the desired steer to reach the planned position.

Useful variables:
- The variable **y_points** and **x_point** gives the desired trajectory planned by the path_planner.
- **yaw** gives the actual rotational angle of the car.
- The output of the controller should be inside [-1.2, 1.2].
- If needed, the position of the car is stored in the variables **x_position**, **y_position** and **z_position**

2) Comment your code to explain why did you computed the error this way.

3) Tune the parameters of the pid until you get satisfying results (a perfect trajectory is not expected).

### Step 4: Evaluate the PID efficiency
The values of the error and the pid command are saved in thottle_data.txt and steer_data.txt.
Plot the saved values using the command (in nd013-c6-control-refresh/project):

```
python3 plot_pid.py
```

You might need to install a few additional python modules: 

```
pip3 install pandas
pip3 install matplotlib
```

Answer the following questions:
- Add the plots to your report and explain them (describe what you see)
- What is the effect of the PID according to the plots, how each part of the PID affects the control command?
- How would you design a way to automatically tune the PID parameters?
- PID controller is a model free controller, i.e. it does not use a model of the car. Could you explain the pros and cons of this type of controller?
- (Optional) What would you do to improve the PID controller?


### Tips:

- When you wil be testing your c++ code, restart the Carla simulator to remove the former car from the simulation.
- If the simulation freezes on the desktop mode but is still running on the terminal, close the desktop and restart it.
- When you will be tuning the PID parameters, try between those values:

