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


#ifndef __FDRV-04S_h
#define __FDRV-04S_h

#include "Arduino.h"

#define uns8 unsigned char
#define uns16 unsigned int

class FDRV04SClass {
private:
	uns8 FDRV04S_ADDR;
	uns16 levelPhase1, levelPhase2, levelPhase3;
	uns16 timePhase1, timePhase2, timePhase3;
	void buildCommandBuffer(uns8 driver, uns8 numPhases);
public:
	void init(uns8 addr);
	/*Returns 1 if assignment was successful. 0 if invalid phase passed*/
	int configPhase(uns8 phase, uns16 phaseLevel, uns16 phaseTime);
	/*Driver can be 1-4. Number of phases = 1-3*/
	void startDriver(uns8 driver);
	void stopDriver(uns8 driver);
	void setupDriver(uns8 driver, uns8 numPhases);
	/*If less than 4 drivers, place 0 for the unused drivers*/
	void startMultipleDrivers(uns8 numDrivers, uns8 driver1, uns8 driver2, uns8 driver3, uns8 driver4);
};

extern FDRV04SClass fdrv;

#endif