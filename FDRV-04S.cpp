/*

Copyright (c) 2015, Embedded Adventures
All rights reserved.

Contact us at source [at] embeddedadventures.com
www.embeddedadventures.com

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

- Redistributions of source code must retain the above copyright notice,
  this list of conditions and the following disclaimer.

- Redistributions in binary form must reproduce the above copyright
  notice, this list of conditions and the following disclaimer in the
  documentation and/or other materials provided with the distribution.

- Neither the name of Embedded Adventures nor the names of its contributors
  may be used to endorse or promote products derived from this software
  without specific prior written permission.
 
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF 
THE POSSIBILITY OF SUCH DAMAGE.

*/

// DRV8003 Stepper FDRV-04S Solenoid/Motor Driver Board
// Written originally by Embedded Adventures

#include "FDRV-04S.h"
#include "Wire.h"
#include "Arduino.h"

uns8 cmd_buffer[15];

void FDRV04SClass::init(uns8 addr) {
	FDRV04S_ADDR = addr;
}

void FDRV04SClass::stopDriver(uns8 driver) {
	Wire.beginTransmission(FDRV04S_ADDR);
	Wire.write(0x03);
	Wire.write(driver);
	Wire.endTransmission();
	delay(20);
}

void FDRV04SClass::startDriver(uns8 driver) {
	Wire.beginTransmission(FDRV04S_ADDR);
	Wire.write(0x02);
	Wire.write(driver);
	Wire.endTransmission();
	delay(15);
}

void FDRV04SClass::setupDriver(uns8 driver, uns8 numPhases) {
	buildCommandBuffer(driver, numPhases);
	Wire.beginTransmission(FDRV04S_ADDR);
	for (int i = 0; i < 15; i++) {
		Wire.write(cmd_buffer[i]);
	}
	Wire.endTransmission();
	delay(20);
}

int FDRV04SClass::configPhase(uns8 phase, uns16 phaseLevel, uns16 phaseTime) {
	if (phase == 1) {
		levelPhase1 = phaseLevel;
		timePhase1 = phaseTime;
	}
	else if (phase == 2) {
		levelPhase2 = phaseLevel;
		timePhase2 = phaseTime;
	}
	else if (phase == 3) {
		levelPhase3 = phaseLevel;
		timePhase3 = phaseTime;
	}
	else
		return 0;
	return 1;
}

void FDRV04SClass::buildCommandBuffer(uns8 driver, uns8 numPhases) {
	cmd_buffer[0] = 0x01;
	cmd_buffer[1] = driver;
	cmd_buffer[2] = numPhases;
	cmd_buffer[3] = levelPhase1 & 0xFF;
	cmd_buffer[4] = levelPhase1 >> 8;
	cmd_buffer[5] = levelPhase2 & 0xFF;
	cmd_buffer[6] = levelPhase2 >> 8;
	cmd_buffer[7] = levelPhase3 & 0xFF;
	cmd_buffer[8] = levelPhase3 >> 8;
	cmd_buffer[9] = timePhase1 & 0xFF;
	cmd_buffer[10] = timePhase1 >> 8;
	cmd_buffer[11] = timePhase2 & 0xFF;
	cmd_buffer[12] = timePhase2 >> 8;
	cmd_buffer[13] = timePhase3 & 0xFF;
	cmd_buffer[14] = timePhase3 >> 8;
}

void FDRV04SClass::startMultipleDrivers(uns8 numDrivers, uns8 driver1, uns8 driver2, uns8 driver3, uns8 driver4) {
	Wire.beginTransmission(FDRV04S_ADDR);
	Wire.write(0x04);
	Wire.write(numDrivers);
	Wire.write(0x02);
	Wire.write(driver1);
	if (numDrivers > 1) {
		Wire.write(0x02);
		Wire.write(driver2);
	}
	if (numDrivers > 2) {
		Wire.write(0x02);
		Wire.write(driver3);
	}
	if (numDrivers > 3) {
		Wire.write(0x02);
		Wire.write(driver4);
	}
	Wire.endTransmission();
	delay(15);
}

FDRV04SClass fdrv;
