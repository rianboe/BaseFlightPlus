/*
  June 2012

  BaseFlightPlus Rev -

  An Open Source STM32 Based Multicopter

  Includes code and/or ideas from:

  1)AeroQuad
  2)BaseFlight
  3)CH Robotics
  4)MultiWii
  5)S.O.H. Madgwick

  Designed to run on Naze32 Flight Control Board

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

///////////////////////////////////////////////////////////////////////////////

#include "board.h"

///////////////////////////////////////////////////////////////////////////////

float   attCmd[3];

float   attPID[3];

float   axisPID[3];

float   rateCmd[3];

float   headingReference;

uint8_t previousHeadingHoldEngaged = false;

///////////////////////////////////////////////////////////////////////////////
// Compute Axis Commands
///////////////////////////////////////////////////////////////////////////////

void computeAxisCommands(float dt)
{
    if (flightMode == ATTITUDE)
    {
        attCmd[ROLL ] = rxCommand[ROLL ] * eepromConfig.attitudeScaling;
        attCmd[PITCH] = rxCommand[PITCH] * eepromConfig.attitudeScaling;
    }

    if (flightMode >= ATTITUDE)
    {
        attPID[ROLL]  = updatePID( attCmd[ROLL ],  sensors.attitude200Hz[ROLL ], dt, holdIntegrators, &eepromConfig.PID[ROLL_ATT_PID ] );
        attPID[PITCH] = updatePID( attCmd[PITCH], -sensors.attitude200Hz[PITCH], dt, holdIntegrators, &eepromConfig.PID[PITCH_ATT_PID] );
    }

    if (flightMode == RATE)
    {
        rateCmd[ROLL ] = rxCommand[ROLL ] * eepromConfig.rateScaling;
        rateCmd[PITCH] = rxCommand[PITCH] * eepromConfig.rateScaling;
    }
    else
    {
        rateCmd[ROLL ] = attPID[ROLL ];
        rateCmd[PITCH] = attPID[PITCH];
    }

    ///////////////////////////////////

    if (headingHoldEngaged == true)  // Heading Hold is ON
    {
        if (previousHeadingHoldEngaged == false)
        {
            setPIDintegralError(HEADING_PID, 0.0f);  // First pass heading hold engaged
            setPIDstates(YAW_RATE_PID,       0.0f);
        }
        rateCmd[YAW] = updatePID( headingReference, sensors.attitude200Hz[YAW], dt, holdIntegrators, &eepromConfig.PID[HEADING_PID] );
    }
    else  // Heading Hold is OFF
    {
        rateCmd[YAW] = rxCommand[YAW] * eepromConfig.rateScaling;
        headingReference = sensors.attitude200Hz[YAW];
    }

    if (previousHeadingHoldEngaged == true && headingHoldEngaged ==false)
    	{
    	    setPIDintegralError(HEADING_PID, 0.0f);  // First pass heading hold disengaged
    	    setPIDstates(YAW_RATE_PID,       0.0f);
    	}

    previousHeadingHoldEngaged = headingHoldEngaged;

    ///////////////////////////////////

    axisPID[ROLL ] = updatePID( rateCmd[ROLL ],  sensors.gyro200Hz[ROLL ], dt, holdIntegrators, &eepromConfig.PID[ROLL_RATE_PID ] );
    axisPID[PITCH] = updatePID( rateCmd[PITCH], -sensors.gyro200Hz[PITCH], dt, holdIntegrators, &eepromConfig.PID[PITCH_RATE_PID] );
    axisPID[YAW  ] = updatePID( rateCmd[YAW  ],  sensors.gyro200Hz[YAW  ], dt, holdIntegrators, &eepromConfig.PID[YAW_RATE_PID  ] );
}

///////////////////////////////////////////////////////////////////////////////
