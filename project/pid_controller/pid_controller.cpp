/**********************************************
 * Self-Driving Car Nano-degree - Udacity
 *  Created on: December 11, 2020
 *      Author: Mathilde Badoual
 **********************************************/

#include "pid_controller.h"
#include <vector>
#include <iostream>
#include <math.h>

using namespace std;

PID::PID()
:Kpi(.0), Kii(.0), Kdi(.0), 
output_lim_maxi(.0), output_lim_mini(.0),
cte(.0), prev_cte(.0), integral_cte(0), 
delta_time(.0) 
{}

PID::~PID() {}

void PID::Init(double Kpi, double Kii, double Kdi, double output_lim_maxi, double output_lim_mini) {
   /**
   * TODO: Initialize PID coefficients (and errors, if needed)
   **/
    this->Kpi = Kpi;
    this->Kii = Kii;
    this->Kdi = Kdi;
    this->output_lim_maxi = output_lim_maxi;
    this->output_lim_mini = output_lim_mini;
    this->cte = .0;
    this->prev_cte = .0;
    this->integral_cte = .0;
    this->delta_time = .0;
}


void PID::UpdateError(double cte) {
   /**
   * TODO: Update PID errors based on cte.
   **/
   this->prev_cte = this->cte;
   this->cte = cte;
   this->integral_cte += cte;
}

double PID::TotalError() {
   /**
   * TODO: Calculate and return the total error
    * The code should return a value in the interval [output_lim_mini, output_lim_maxi]
   */
    double diff_cte = cte - prev_cte;
    double control = -Kpi * cte + -Kii * integral_cte + -Kdi * diff_cte;  
    control = min(this->output_lim_maxi, max(this->output_lim_mini, control));
    return control;
}

double PID::UpdateDeltaTime(double new_delta_time) {
   /**
   * TODO: Update the delta time with new value
   */
    this->delta_time = new_delta_time;
    return this->delta_time;
}
