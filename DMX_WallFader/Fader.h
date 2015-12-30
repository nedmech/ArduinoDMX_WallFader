/*
 Name:		Fader.h
 Created:	7/14/2015
 Author:	Nathan Durnan
*/
#pragma once
#include <stddef.h>
#include <Arduino.h>
#include <DmxSimple.h>
#include <BitBool.h>
#include "Ramp.h"
#include "Linearizer.h"

/*-----------------------------------------------
--> Defines the number of DMX channels that can be controlled.
--> Can be changed in blocks of 8 (e.g. 8, 16, 24, 32, etc.)
-----------------------------------------------*/
#define DMX_CHANNEL_BLOCK 64

/*-----------------------------------------------
 Define the calibration of the Fader inputs.
 This is based on the dimmer switch circuit used.
-----------------------------------------------*/
#define FADER_LO 164 // ~0.8V
#define FADER_HI 612 // ~3.0V
#define DMX_MIN 0
#define DMX_MAX 255

class Fader
{
public:
	Fader();
private:
	uint8_t faderPin;
	uint8_t off_LED_Pin; // Digital Output indication when Fader is OFF
	uint8_t on_LED_Pin;  // PWM Output indication mirrors Fader output.
	int faderValue;
	DmxSimpleClass* dmxUniverse;
	BitBool<DMX_CHANNEL_BLOCK> dmxMap;
	Ramp<int> inputValue;
public:
	void setFaderPin(uint8_t);
	void setOffPin(uint8_t);
	void setOnPin(uint8_t);
	void setDmxUniverse(DmxSimpleClass*);
	void clearDmxMap();
	void setDmxMap(int, bool);
	void update();
	void update(int);
};

