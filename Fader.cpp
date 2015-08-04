/*
 Name:		Fader.h
 Created:	7/14/2015
 Author:	Nathan Durnan
*/

#include "Fader.h"
//#define DEBUG_ // un-comment this line for serial debug output

/* constructor */
Fader::Fader()
{
	// Initialize members
	dmxUniverse = NULL;
	faderValue  = 0;
	faderPin    = 1;
	off_LED_Pin = 8;
	on_LED_Pin  = 9;
	clearDmxMap();
	inputValue.reset();
}

/*-----------------------------------------------
	C++ wrapper (public methods)
-----------------------------------------------*/

/**	Set Analog Input Pin
*	@param _pin : Input Analog pin to use (1...NUM_ANALOG_INPUTS)
*/
void Fader::setFaderPin(uint8_t _pin)
{
	if ((_pin >= 1) || (_pin <= NUM_ANALOG_INPUTS))
		faderPin = _pin;
}

/**	Set Digital Output Pin for OFF state indication
*	@param _pin : Output Digital pin to use (1...NUM_DIGITAL_PINS)
*/
void Fader::setOffPin(uint8_t _pin)
{
	if ((_pin >= 1) || (_pin <= NUM_DIGITAL_PINS))
		off_LED_Pin = _pin;
	pinMode(off_LED_Pin, OUTPUT);
}

/**	Set PWM Output Pin for ON state indication
*	@param _pin : Output PWM pin to use (1...NUM_DIGITAL_PINS)
*/
void Fader::setOnPin(uint8_t _pin)
{
	if ((_pin >= 1) || (_pin <= NUM_DIGITAL_PINS))
		on_LED_Pin = _pin;
	pinMode(on_LED_Pin, OUTPUT);
}

/**  Set DMX Universe Pointer
*	@param _universe : Pointer to DmxSimpleClass object to use for output
*/
void Fader::setDmxUniverse(DmxSimpleClass* _universe)
{
	if (_universe != NULL)
		dmxUniverse = _universe;
}

/** Reset all DMX Channel mapping to false (OFF)
*/
void Fader::clearDmxMap()
{
	for (byte i = 0; i < DMX_CHANNEL_BLOCK; i++)
		dmxMap[i] = false;
}

/**	Set DMX Mapping for specified channel
*	@param _ch : DMX Channel to assign mapping (1...DMX_CHANNEL_BLOCK)
*	@param _map : Turn mapping ON/Off (true/false)
*/
void Fader::setDmxMap(int _ch, bool _map)
{
	if ((_ch >= 1) && (_ch <= DMX_CHANNEL_BLOCK))
		dmxMap[_ch - 1] = _map;
}

/** Update Fader input and output values
*/
void Fader::update()
{
#ifdef DEBUG_
	Serial.print("FADER: ");
	Serial.print(faderPin);
	Serial.print("\tIN: ");
	Serial.print(analogRead(faderPin));
#endif
	inputValue.update(analogRead(faderPin));
	this->update(inputValue.getValue());
}
/** Update Fader scaled output value
*	@param _value : Input value (0-1023) to be rescaled and output
*/
void Fader::update(int _value)
{
	faderValue = constrain(_value, 0, 1023);
	// rescale analog input to DMX output range
	uint8_t dmxValue = constrain(
		map(faderValue, FADER_LO, FADER_HI, DMX_MIN, DMX_MAX)
		, DMX_MIN
		, DMX_MAX
		);
	dmxValue = deLog<int>(dmxValue, DMX_MAX, 4);
#ifdef DEBUG_
	Serial.print("\tDMX: ");
	Serial.print(dmxValue);
	Serial.println("");
#endif
	// only send output if channel is mapped to Fader
	for (byte i = 1; i <= DMX_CHANNEL_BLOCK; i++)
		if (dmxMap[i - 1]) dmxUniverse->write(i, dmxValue);
	if (dmxValue == DMX_MIN)
	{
		digitalWrite(off_LED_Pin, HIGH);
		digitalWrite(on_LED_Pin, LOW);
	}
	else
	{
		digitalWrite(off_LED_Pin, LOW);
		analogWrite(on_LED_Pin, dmxValue);
	}
}
