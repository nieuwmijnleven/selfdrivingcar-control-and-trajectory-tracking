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

PID::PID():err(.0), integral_error(.0), update_error_count(0), delta_time(.0) {}

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
    this->err = .0;
    this->integral_error = .0;
    this->delta_time = .0;
    this->update_error_count = 0;
}


void PID::UpdateError(double cte) {
   /**
   * TODO: Update PID errors based on cte.
   **/
   this->err = cte;
   this->integral_error += cte;
   this->update_error_count += 1;
}

double PID::TotalError() {
   /**
   * TODO: Calculate and return the total error
    * The code should return a value in the interval [output_lim_mini, output_lim_maxi]
   */
    double average_error = this->err / this->update_error_count;
    double control = min(this->output_lim_maxi, max(this->output_lim_mini, average_error));
    return control;
}

double PID::UpdateDeltaTime(double new_delta_time) {
   /**
   * TODO: Update the delta time with new value
   */
    this->delta_time = new_delta_time;
    return this->delta_time;
}
