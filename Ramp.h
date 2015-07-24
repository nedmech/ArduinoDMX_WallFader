/*
 Name:		Ramp.h
 Created:	7/22/2015
 Author:	Nathan Durnan
*/
#pragma once

/*-----------------------------------------------
--> Delay in milliseconds between updates.
--> Increase this value for slower ramping.
-----------------------------------------------*/
#define RAMP_UPDATE_DELAY 10
/*-----------------------------------------------
--> Number of updates to ramp from minimum to maximum.
--> Increase this value for smoother ramping.
-----------------------------------------------*/
#define RAMP_UPDATE_STEPS 100
/*-----------------------------------------------
* NOTE:  10ms delay with 100 steps yields
*	approximately a 1sec fade time.
-----------------------------------------------*/

template <typename T> class Ramp
{
private:
	T value;	//* internal ramped value
	T rampStep;	//* size of change allowed for each update
public:
	/**	Reset the internal values to defaults.
	*/
	T reset(void)
	{
		rampStep = (sizeof(T) * 256 / RAMP_UPDATE_STEPS);
		value = 0;
		return value;
	}
	/**	Pre-load an internal value.
	*	@param _value : the value to pre-load into the Ramp.
	*	returns the new value of the Ramp.
	*/
	T setValue(T _value)
	{
		value = _value;
		return value;
	}
	/**	Set the Ramp Step value.
	*	@param _step : amount of change allowed for each update.
	*	NOTE: _step must be positive and non-zero;
	*	returns the new value of the ramp step.
	*/
	T setRampStep(T _step)
	{
		if (_step > 0)
		{
			rampStep = _step;
		}
		return rampStep;
	}
	/**	Update the Ramp and step towards a new value.
	*	@param _newValue : the new target value.
	*	returns the updated Ramp value.
	*/
	T update(T _newValue)
	{
		if (_newValue > value)
		{
			value = min((value + rampStep), _newValue);
		}
		else if (_newValue < value)
		{
			value = max((value - rampStep), _newValue);
		}
		return value;
	}
	/**	Get the current value of the Ramp.
	*/
	T getValue(void)
	{
		return value;
	}

};
