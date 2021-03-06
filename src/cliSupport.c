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
// Mixer CLI
///////////////////////////////////////////////////////////////////////////////

void mixerCLI()
{
    float    tempFloat;

    uint8_t  index;
    uint8_t  rows, columns;

    uint8_t  mixerQuery;
    uint8_t  validQuery = false;

    cliBusy = true;

    cliPrint("\nEntering Mixer CLI....\n\n");

    while(true)
    {
        cliPrint("Mixer CLI -> ");

		while ((cliAvailable() == false) && (validQuery == false));

		if (validQuery == false)
		    mixerQuery = cliRead();

		cliPrint("\n");

		switch(mixerQuery)
		{
            ///////////////////////////

            case 'a': // Mixer Configuration
                cliPrint("\nMixer Configuration:            ");
                switch (eepromConfig.mixerConfiguration)
                {
                    case MIXERTYPE_GIMBAL:
                    	cliPrint("MIXERTYPE GIMBAL\n");
                    	break;

                    ///////////////////////

                    case MIXERTYPE_FLYING_WING:
                    	cliPrint("MIXERTYPE FLYING WING\n");
                    	break;

                    ///////////////////////

                    case MIXERTYPE_BI:
                        cliPrint("MIXERTYPE BICOPTER\n");
                        break;

                    ///////////////////////

                    case MIXERTYPE_TRI:
                        cliPrint("MIXERTYPE TRICOPTER\n");
                        break;

                    ///////////////////////

                    case MIXERTYPE_QUADP:
                        cliPrint("MIXERTYPE QUAD PLUS\n");
                        break;

                    case MIXERTYPE_QUADX:
                        cliPrint("MIXERTYPE QUAD X\n");
                        break;

                    case MIXERTYPE_VTAIL4_NO_COMP:
                    	cliPrint("MULTITYPE VTAIL NO COMP\n");
                    	break;

                    case MIXERTYPE_VTAIL4_Y_COMP:
                    	cliPrint("MULTITYPE VTAIL Y COMP\n");
                    	break;

                    case MIXERTYPE_VTAIL4_RY_COMP:
                    	cliPrint("MULTITYPE VTAIL RY COMP\n");
                    	break;

                    case MIXERTYPE_VTAIL4_PY_COMP:
                    	cliPrint("MULTITYPE VTAIL PY COMP\n");
                    	break;

                    case MIXERTYPE_VTAIL4_RP_COMP:
                    	cliPrint("MULTITYPE VTAIL RP COMP\n");
                    	break;

                    case MIXERTYPE_VTAIL4_RPY_COMP:
                    	cliPrint("MULTITYPE VTAIL RPY COMP\n");
                    	break;

                    case MIXERTYPE_Y4:
                    	cliPrint("MIXERTYPE Y4\n");
                    	break;

                    ///////////////////////

                    case MIXERTYPE_HEX6P:
                        cliPrint("MIXERTYPE HEX PLUS\n");
                        break;

                    case MIXERTYPE_HEX6X:
                        cliPrint("MIXERTYPE HEX X\n");
                        break;

                    case MIXERTYPE_Y6:
                        cliPrint("MIXERTYPE Y6\n");
                        break;

                    ///////////////////////

                    case MIXERTYPE_FREEMIX:
                    	cliPrint("MIXERTYPE FREE MIX\n");
                    	break;
                }

                cliPrintF("Number of Motors:                  %1d\n",  numberMotor);
                cliPrintF("ESC PWM Rate:                    %3ld\n", eepromConfig.escPwmRate);
                cliPrintF("Servo PWM Rate:                  %3ld\n", eepromConfig.servoPwmRate);

                if ( eepromConfig.mixerConfiguration == MIXERTYPE_BI )
                {
                    cliPrintF("BiCopter Left Servo Min:        %4ld\n", (uint16_t)eepromConfig.biLeftServoMin);
                    cliPrintF("BiCopter Left Servo Mid:        %4ld\n", (uint16_t)eepromConfig.biLeftServoMid);
                    cliPrintF("BiCopter Left Servo Max:        %4ld\n", (uint16_t)eepromConfig.biLeftServoMax);
                    cliPrintF("BiCopter Right Servo Min:       %4ld\n", (uint16_t)eepromConfig.biRightServoMin);
                    cliPrintF("BiCopter Right Servo Mid:       %4ld\n", (uint16_t)eepromConfig.biRightServoMid);
                    cliPrintF("BiCopter Right Servo Max:       %4ld\n", (uint16_t)eepromConfig.biRightServoMax);
                }

                if ( eepromConfig.mixerConfiguration == MIXERTYPE_FLYING_WING )
                {
                    cliPrintF("Roll Direction Left:            %4ld\n", (uint16_t)eepromConfig.rollDirectionLeft);
                    cliPrintF("Roll Direction Right:           %4ld\n", (uint16_t)eepromConfig.rollDirectionRight);
                    cliPrintF("Pitch Direction Left:           %4ld\n", (uint16_t)eepromConfig.pitchDirectionLeft);
                    cliPrintF("Pitch Direction Right:          %4ld\n", (uint16_t)eepromConfig.pitchDirectionRight);
                    cliPrintF("Wing Left Minimum:              %4ld\n", (uint16_t)eepromConfig.wingLeftMinimum);
                    cliPrintF("Wing Left Maximum:              %4ld\n", (uint16_t)eepromConfig.wingLeftMaximum);
                    cliPrintF("Wing Right Minimum:             %4ld\n", (uint16_t)eepromConfig.wingRightMinimum);
                    cliPrintF("Wing Right Maximum:             %4ld\n", (uint16_t)eepromConfig.wingRightMaximum);
                }

                if ( eepromConfig.mixerConfiguration == MIXERTYPE_GIMBAL )
                {
                    cliPrintF("Gimbal Roll Servo Min:          %4ld\n",   (uint16_t)eepromConfig.gimbalRollServoMin);
                    cliPrintF("Gimbal Roll Servo Mid:          %4ld\n",   (uint16_t)eepromConfig.gimbalRollServoMid);
                    cliPrintF("Gimbal Roll Servo Max:          %4ld\n",   (uint16_t)eepromConfig.gimbalRollServoMax);
                    cliPrintF("Gimbal Roll Servo Gain:          %7.3f\n", eepromConfig.gimbalRollServoGain);
                    cliPrintF("Gimbal Pitch Servo Min:         %4ld\n",   (uint16_t)eepromConfig.gimbalPitchServoMin);
                    cliPrintF("Gimbal Pitch Servo Mid:         %4ld\n",   (uint16_t)eepromConfig.gimbalPitchServoMid);
                    cliPrintF("Gimbal Pitch Servo Max:         %4ld\n",   (uint16_t)eepromConfig.gimbalPitchServoMax);
                    cliPrintF("Gimbal Pitch Servo Gain:         %7.3f\n", eepromConfig.gimbalPitchServoGain);
                 }

                if ( eepromConfig.mixerConfiguration == MIXERTYPE_TRI )
                {
                    cliPrintF("TriCopter Yaw Servo Min:        %4ld\n", (uint16_t)eepromConfig.triYawServoMin);
                    cliPrintF("TriCopter Yaw Servo Mid:        %4ld\n", (uint16_t)eepromConfig.triYawServoMid);
                    cliPrintF("TriCopter Yaw Servo Max:        %4ld\n", (uint16_t)eepromConfig.triYawServoMax);
                }

                if (eepromConfig.mixerConfiguration == MIXERTYPE_VTAIL4_Y_COMP  ||
                    eepromConfig.mixerConfiguration == MIXERTYPE_VTAIL4_RY_COMP ||
                    eepromConfig.mixerConfiguration == MIXERTYPE_VTAIL4_PY_COMP ||
                    eepromConfig.mixerConfiguration == MIXERTYPE_VTAIL4_RP_COMP ||
                    eepromConfig.mixerConfiguration == MIXERTYPE_VTAIL4_RPY_COMP)
                {
                    cliPrintF("V Tail Angle                     %6.2f\n", eepromConfig.vTailAngle);
                 }

                cliPrintF("Yaw Direction:                    %2d\n\n", (uint16_t)eepromConfig.yawDirection);

                validQuery = false;
                break;

            ///////////////////////////

            case 'b': // Free Mix Matrix
        	    cliPrintF("\nNumber of Free Mixer Motors:  %1d\n         Roll    Pitch   Yaw\n", eepromConfig.freeMixMotors);

        	    for ( index = 0; index < eepromConfig.freeMixMotors; index++ )
        	    {
        	    	cliPrintF("Motor%1d  %6.3f  %6.3f  %6.3f\n", index,
        	    			                                     eepromConfig.freeMix[index][ROLL ],
        	    			                                     eepromConfig.freeMix[index][PITCH],
        	    			                                     eepromConfig.freeMix[index][YAW  ]);
        	    }

        	    cliPrint("\n");
        	    validQuery = false;
        	    break;

            ///////////////////////////

			case 'x':
			    cliPrint("\nExiting Mixer CLI....\n\n");
			    cliBusy = false;
			    return;
			    break;

            ///////////////////////////

            case 'A': // Read Mixer Configuration
                eepromConfig.mixerConfiguration = (uint8_t)readFloatCLI();
                initMixer();

        	    mixerQuery = 'a';
                validQuery = true;
		        break;

            ///////////////////////////

            case 'B': // Read ESC and Servo PWM Update Rates
                eepromConfig.escPwmRate   = (uint16_t)readFloatCLI();
                eepromConfig.servoPwmRate = (uint16_t)readFloatCLI();

                pwmOutputConfig.escPwmRate   = eepromConfig.escPwmRate;
                pwmOutputConfig.servoPwmRate = eepromConfig.servoPwmRate;

                pwmOutputInit(&pwmOutputConfig);

                mixerQuery = 'a';
                validQuery = true;
        	    break;

            ///////////////////////////

            case 'C': // Read BiCopter Left Servo Parameters
           	    eepromConfig.biLeftServoMin = readFloatCLI();
           	    eepromConfig.biLeftServoMid = readFloatCLI();
           	    eepromConfig.biLeftServoMax = readFloatCLI();

           	    mixerQuery = 'a';
                validQuery = true;
                break;

            ///////////////////////////

            case 'D': // Read BiCopter Right Servo Parameters
           	    eepromConfig.biRightServoMin = readFloatCLI();
           	    eepromConfig.biRightServoMid = readFloatCLI();
           	    eepromConfig.biRightServoMax = readFloatCLI();

           	    mixerQuery = 'a';
                validQuery = true;
                break;

            ///////////////////////////

            case 'E': // Read Flying Wing Servo Directions
                eepromConfig.rollDirectionLeft   = readFloatCLI();
                eepromConfig.rollDirectionRight  = readFloatCLI();
                eepromConfig.pitchDirectionLeft  = readFloatCLI();
                eepromConfig.pitchDirectionRight = readFloatCLI();

         	    mixerQuery = 'a';
                validQuery = true;
                break;

            ///////////////////////////

            case 'F': // Read Flying Wing Servo Limits
           	    eepromConfig.wingLeftMinimum  = readFloatCLI();
           	    eepromConfig.wingLeftMaximum  = readFloatCLI();
           	    eepromConfig.wingRightMinimum = readFloatCLI();
           	    eepromConfig.wingRightMaximum = readFloatCLI();

                mixerQuery = 'a';
                validQuery = true;
                break;

            ///////////////////////////

            case 'G': // Read Free Mix Motor Number
           	    eepromConfig.freeMixMotors = (uint8_t)readFloatCLI();
           	    initMixer();

           	    mixerQuery = 'b';
                validQuery = true;
                break;

            ///////////////////////////

            case 'H': // Read Free Mix Matrix Element
                rows    = (uint8_t)readFloatCLI();
                columns = (uint8_t)readFloatCLI();
                eepromConfig.freeMix[rows][columns] = readFloatCLI();

                mixerQuery = 'b';
                validQuery = true;
                break;

            ///////////////////////////

            case 'I': // Read Gimbal Roll Servo Parameters
         	    eepromConfig.gimbalRollServoMin  = readFloatCLI();
           	    eepromConfig.gimbalRollServoMid  = readFloatCLI();
           	    eepromConfig.gimbalRollServoMax  = readFloatCLI();
           	    eepromConfig.gimbalRollServoGain = readFloatCLI();

           	    mixerQuery = 'a';
                validQuery = true;
                break;

            ///////////////////////////

            case 'J': // Read Gimbal Pitch Servo Parameters
           	    eepromConfig.gimbalPitchServoMin  = readFloatCLI();
           	    eepromConfig.gimbalPitchServoMid  = readFloatCLI();
           	    eepromConfig.gimbalPitchServoMax  = readFloatCLI();
           	    eepromConfig.gimbalPitchServoGain = readFloatCLI();

           	    mixerQuery = 'a';
                validQuery = true;
                break;

            ///////////////////////////

            case 'K': // Read TriCopter YawServo Parameters
        	    eepromConfig.triYawServoMin = readFloatCLI();
           	    eepromConfig.triYawServoMid = readFloatCLI();
           	    eepromConfig.triYawServoMax = readFloatCLI();

           	    mixerQuery = 'a';
                validQuery = true;
                break;

            ///////////////////////////

            case 'L': // Read V Tail Angle
        	    eepromConfig.vTailAngle = readFloatCLI();

        	    mixerQuery = 'a';
                validQuery = true;
                break;

            ///////////////////////////

            case 'M': // Read yaw direction
                tempFloat = readFloatCLI();
                if (tempFloat >= 0.0)
                    tempFloat = 1.0;
                else
                	tempFloat = -1.0;

                eepromConfig.yawDirection = tempFloat;

                mixerQuery = 'a';
                validQuery = true;
                break;

            ///////////////////////////

            case 'W': // Write EEPROM Parameters
                cliPrint("\nWriting EEPROM Parameters....\n\n");
                writeEEPROM();
                break;

			///////////////////////////

			case '?':
			   	cliPrint("\n");
			   	cliPrint("'a' Mixer Configuration Data               'A' Set Mixer Configuration              A1 thru 17, see baseFlightPlus.h\n");
   		        cliPrint("'b' Free Mixer Configuration               'B' Set PWM Rates                        BESC;Servo\n");
			   	cliPrint("                                           'C' Set BiCopter Left Servo Parameters   CMin;Mid;Max\n");
			   	cliPrint("                                           'D' Set BiCopter Right Servo Parameters  DMin;Mid;Max\n");
			   	cliPrint("                                           'E' Set Flying Wing Servo Directions     ERollLeft;RollRight;PitchLeft;PitchRight\n");
			   	cliPrint("                                           'F' Set Flying Wing Servo Limits         FLeftMin;LeftMax;RightMin;RightMax\n");
   		        cliPrint("                                           'G' Set Number of FreeMix Motors         GNumber\n");
   		        cliPrint("                                           'H' Set FreeMix Matrix Element           HRow;Column;Element\n");
   		        cliPrint("                                           'I' Set Gimbal Roll Servo Parameters     IMin;Mid;Max;Gain\n");
   		        cliPrint("                                           'J' Set Gimbal Pitch Servo Parameters    JMin;Mid;Max;Gain\n");
   		        cliPrint("                                           'K' Set TriCopter Servo Parameters       KMin;Mid;Max\n");
   		        cliPrint("                                           'L' Set V Tail Angle                     LAngle\n");
   		        cliPrint("                                           'M' Set Yaw Direction                    M1 or M-1\n");
   		        cliPrint("                                           'W' Write EEPROM Parameters\n");
   		        cliPrint("'x' Exit Sensor CLI                        '?' Command Summary\n");
   		        cliPrint("\n");
	    	    break;

	    	///////////////////////////
	    }
	}

}

///////////////////////////////////////////////////////////////////////////////
// Receiver CLI
///////////////////////////////////////////////////////////////////////////////

void receiverCLI()
{
    char     rcOrderString[9];
    float    tempFloat;
    uint8_t  index;
    uint8_t  receiverQuery;
    uint8_t  validQuery = false;

    cliBusy = true;

    cliPrint("\nEntering Receiver CLI....\n\n");

    while(true)
    {
        cliPrint("Receiver CLI -> ");

		while ((cliAvailable() == false) && (validQuery == false));

		if (validQuery == false)
		    receiverQuery = cliRead();

		cliPrint("\n");

		switch(receiverQuery)
		{
            ///////////////////////////

            case 'a': // Receiver Configuration
                cliPrint("\nReceiver Type:                  ");
                switch(eepromConfig.receiverType)
                {
                    case PARALLEL_PWM:
                        cliPrint("Parallel\n");
                        break;
                    case SERIAL_PWM:
                        cliPrint("Serial\n");
                        break;
                    case SPEKTRUM:
                        cliPrint("Spektrum\n");
                        break;
		        }

                cliPrint("Current RC Channel Assignment:  ");
                for (index = 0; index < 8; index++)
                    rcOrderString[eepromConfig.rcMap[index]] = rcChannelLetters[index];

                rcOrderString[index] = '\0';

                cliPrint(rcOrderString);  cliPrint("\n");

                cliPrintF("Spektrum Resolution:            %s\n",     eepromConfig.spektrumHires ? "11 Bit Mode" : "10 Bit Mode");
                cliPrintF("Number of Spektrum Channels:    %2d\n",    eepromConfig.spektrumChannels);
                cliPrintF("Mid Command:                    %4ld\n",   (uint16_t)eepromConfig.midCommand);
				cliPrintF("Min Check:                      %4ld\n",   (uint16_t)eepromConfig.minCheck);
				cliPrintF("Max Check:                      %4ld\n",   (uint16_t)eepromConfig.maxCheck);
				cliPrintF("Min Throttle:                   %4ld\n",   (uint16_t)eepromConfig.minThrottle);
				cliPrintF("Max Thottle:                    %4ld\n\n", (uint16_t)eepromConfig.maxThrottle);

				tempFloat = eepromConfig.rateScaling * 180000.0 / PI;
				cliPrintF("Max Rate Command:               %6.2f DPS\n", tempFloat);

				tempFloat = eepromConfig.attitudeScaling * 180000.0 / PI;
                cliPrintF("Max Attitude Command:           %6.2f Degrees\n\n", tempFloat);

				cliPrintF("Arm Delay Count:                %3d Frames\n",   eepromConfig.armCount);
				cliPrintF("Disarm Delay Count:             %3d Frames\n\n", eepromConfig.disarmCount);

				validQuery = false;
				break;

            ///////////////////////////

            case 'b': // Read Max Rate Value
                eepromConfig.rateScaling = readFloatCLI() / 180000 * PI;

                receiverQuery = 'a';
                validQuery = true;
                break;

            ///////////////////////////

            case 'c': // Read Max Attitude Value
                eepromConfig.attitudeScaling = readFloatCLI() / 180000 * PI;

                receiverQuery = 'a';
                validQuery = true;
                break;

            ///////////////////////////

			case 'x':
			    cliPrint("\nExiting Receiver CLI....\n\n");
			    cliBusy = false;
			    return;
			    break;

            ///////////////////////////

            case 'A': // Read RX Input Type
                eepromConfig.receiverType = (uint8_t)readFloatCLI();
			    cliPrint( "\nReceiver Type Changed....\n");

			    cliPrint("\nSystem Resetting....\n");
			    delay(100);
			    writeEEPROM();
			    systemReset(false);

		        break;

            ///////////////////////////

            case 'B': // Read RC Control Order
                readStringCLI( rcOrderString, 8 );
                parseRcChannels( rcOrderString );

          	    receiverQuery = 'a';
                validQuery = true;
        	    break;

            ///////////////////////////

            case 'C': // Read Spektrum Resolution
                eepromConfig.spektrumHires = (uint8_t)readFloatCLI();

                receiverQuery = 'a';
                validQuery = true;
                break;

            ///////////////////////////

            case 'D': // Read Number of Spektrum Channels
                eepromConfig.spektrumChannels = (uint8_t)readFloatCLI();

                receiverQuery = 'a';
                validQuery = true;
                break;

            ///////////////////////////

            case 'E': // Read RC Control Points
                eepromConfig.midCommand   = readFloatCLI();
    	        eepromConfig.minCheck     = readFloatCLI();
    		    eepromConfig.maxCheck     = readFloatCLI();
    		    eepromConfig.minThrottle  = readFloatCLI();
    		    eepromConfig.maxThrottle  = readFloatCLI();

                receiverQuery = 'a';
                validQuery = true;
                break;

            ///////////////////////////

            case 'F': // Read Arm/Disarm Counts
                eepromConfig.armCount    = (uint8_t)readFloatCLI();
        	    eepromConfig.disarmCount = (uint8_t)readFloatCLI();

                receiverQuery = 'a';
                validQuery = true;
                break;

            ///////////////////////////

            case 'W': // Write EEPROM Parameters
                cliPrint("\nWriting EEPROM Parameters....\n\n");
                writeEEPROM();
                break;

			///////////////////////////

			case '?':
			   	cliPrint("\n");
			   	cliPrint("'a' Receiver Configuration Data            'A' Set RX Input Type                    AX, 1=Parallel, 2=Serial, 3=Spektrum\n");
   		        cliPrint("'b' Set Maximum Rate Command               'B' Set RC Control Order                 BTAER1234\n");
			   	cliPrint("'c' Set Maximum Attitude Command           'C' Set Spektrum Resolution              C0 or C1\n");
			   	cliPrint("                                           'D' Set Number of Spektrum Channels      D6 thru D12\n");
			   	cliPrint("                                           'E' Set RC Control Points                EmidCmd;minChk;maxChk;minThrot;maxThrot\n");
			   	cliPrint("                                           'F' Set Arm/Disarm Counts                FarmCount;disarmCount\n");
			   	cliPrint("                                           'W' Write EEPROM Parameters\n");
			   	cliPrint("'x' Exit Receiver CLI                      '?' Command Summary\n");
			   	cliPrint("\n");
	    	    break;

	    	///////////////////////////
	    }
	}

}

///////////////////////////////////////////////////////////////////////////////
// Sensor CLI
///////////////////////////////////////////////////////////////////////////////

void sensorCLI()
{
    uint8_t  sensorQuery;
    uint8_t  validQuery = false;

    cliBusy = true;

    cliPrint("\nEntering Sensor CLI....\n\n");

    while(true)
    {
        cliPrint("Sensor CLI -> ");

		while ((cliAvailable() == false) && (validQuery == false));

		if (validQuery == false)
		    sensorQuery = cliRead();

		cliPrint("\n");

		switch(sensorQuery)
		{
            ///////////////////////////

            case 'a': // Sensor Data
                cliPrintF("\nAccel Scale Factor:        %9.4f, %9.4f, %9.4f\n", eepromConfig.accelScaleFactor[XAXIS],
                                                		                        eepromConfig.accelScaleFactor[YAXIS],
                                                		                        eepromConfig.accelScaleFactor[ZAXIS]);
                cliPrintF("Accel Bias:                %9.4f, %9.4f, %9.4f\n",   eepromConfig.accelBias[XAXIS],
                                                		                        eepromConfig.accelBias[YAXIS],
                                                		                        eepromConfig.accelBias[ZAXIS]);
                cliPrintF("Gyro TC Bias Slope:        %9.4f, %9.4f, %9.4f\n",   eepromConfig.gyroTCBiasSlope[ROLL ],
                                                                		        eepromConfig.gyroTCBiasSlope[PITCH],
                                                                		        eepromConfig.gyroTCBiasSlope[YAW  ]);
                cliPrintF("Gyro TC Bias Intercept:    %9.4f, %9.4f, %9.4f\n",   eepromConfig.gyroTCBiasIntercept[ROLL ],
                		                                                        eepromConfig.gyroTCBiasIntercept[PITCH],
                		                                                        eepromConfig.gyroTCBiasIntercept[YAW  ]);
                cliPrintF("Mag Bias:                  %9.4f, %9.4f, %9.4f\n",   eepromConfig.magBias[XAXIS],
                                                		                        eepromConfig.magBias[YAXIS],
                                                		                        eepromConfig.magBias[ZAXIS]);
                cliPrintF("Accel One G:               %9.4f\n",   accelOneG);
                cliPrintF("Accel Cutoff:              %9.4f\n",   eepromConfig.accelCutoff);
                cliPrintF("KpAcc (MARG):              %9.4f\n",   eepromConfig.KpAcc);
                cliPrintF("KiAcc (MARG):              %9.4f\n",   eepromConfig.KiAcc);
                cliPrintF("KpMag (MARG):              %9.4f\n",   eepromConfig.KpMag);
                cliPrintF("KiMag (MARG):              %9.4f\n",   eepromConfig.KiMag);
                cliPrintF("hdot est/h est Comp Fil A: %9.4f\n",   eepromConfig.compFilterA);
                cliPrintF("hdot est/h est Comp Fil B: %9.4f\n\n", eepromConfig.compFilterB);

                validQuery = false;
                break;

            ///////////////////////////

            case 'b': // Accel Calibration
                accelCalibration();

                sensorQuery = 'a';
                validQuery = true;
                break;

            ///////////////////////////

            case 'c': // Magnetometer Calibration
                magCalibration();

                sensorQuery = 'a';
                validQuery = true;
                break;

            ///////////////////////////

            case 'd': // GyroTemp Calibration
                gyroTempCalibration();
                computeGyroRTBias();

                sensorQuery = 'a';
                validQuery = true;
                break;

			///////////////////////////

			case 'x':
			    cliPrint("\nExiting Sensor CLI....\n\n");
			    cliBusy = false;
			    return;
			    break;

            ///////////////////////////

            case 'B': // Accel Cutoff
                eepromConfig.accelCutoff = readFloatCLI();

                sensorQuery = 'a';
                validQuery = true;
        	    break;

            ///////////////////////////

            case 'C': // kpAcc, kiAcc
                eepromConfig.KpAcc = readFloatCLI();
                eepromConfig.KiAcc = readFloatCLI();

                sensorQuery = 'a';
                validQuery = true;
                break;

            ///////////////////////////

            case 'D': // kpMag, kiMag
                eepromConfig.KpMag = readFloatCLI();
                eepromConfig.KiMag = readFloatCLI();

                sensorQuery = 'a';
                validQuery = true;
                break;

            ///////////////////////////

            case 'E': // h dot est/h est Comp Filter A/B
                eepromConfig.compFilterA = readFloatCLI();
                eepromConfig.compFilterB = readFloatCLI();

                sensorQuery = 'a';
                validQuery = true;
                break;

            ///////////////////////////

            case 'W': // Write EEPROM Parameters
                cliPrint("\nWriting EEPROM Parameters....\n\n");
                writeEEPROM();
                break;

			///////////////////////////

			case '?':
			   	cliPrint("\n");
			   	cliPrint("'a' Display Sensor Data\n");
			   	cliPrint("'b' Accel Calibration                      'B' Set Accel Cutoff                     BAccelCutoff\n");
			   	cliPrint("'c' Magnetometer Calibration               'C' Set kpAcc/kiAcc                      CKpAcc;KiAcc\n");
			   	cliPrint("'d' Gyro Temp Calibration                  'D' Set kpMag/kiMag                      DKpMag;KiMag\n");
			   	cliPrint("                                           'E' Set h dot est/h est Comp Filter A/B  EA;B\n");
			   	cliPrint("                                           'W' Write EEPROM Parameters\n");
			   	cliPrint("'x' Exit Sensor CLI                        '?' Command Summary\n");
			    cliPrint("\n");
	    	    break;

	    	///////////////////////////
	    }
	}

}

///////////////////////////////////////////////////////////////////////////////
