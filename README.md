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

## PID Controller Implementations
### Error Computation
* We used the typical formula for PID controller
* PID Error Computation Formula
  * total error = -kpi * cte + -kdi * diff_cte + -kii * int_cte
    * cte = cross track error
    * diff_cte = the difference between previous cte and current cte
    * int_cte = integral(sum) of cte
    * kpi = the gain of proportional
    * kdi = the gain of derivative(or differential)
    * kii = the gain of integral   
### CTE (Cross Track Error)
* The CTE of Steering = {the actual rotational angle of the car(yaw)} - {angle between the last two points of the desired trajectory}
* The CTE of Throttle = {the actual velocity of the car} - {the desired velocity(The last point of v_points vector contains the velocity computed by the path planner)}
  
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
* throttle error line is stable and straight
  * Only our car moves in the simulatior  
  * There are no moving obstacles
  * Thus, there are no need for accelerations or deaccelerations
<kbd>
 <img src = "project/img/throttle3.png?raw=true" width=640/>
</kbd>

### 2. What is the effect of the PID according to the plots, how each part of the PID affects the control command?
* When you see the following the steering result, you can notice that even though steer error was soared four times the steer output kept stable.   
<kbd>
 <img src = "project/img/steer3.png?raw=true" width=640/>
</kbd>

### 3. How would you design a way to automatically tune the PID parameters?
* It is challenging to tune the PID parameters automatically in the simulation environment
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
