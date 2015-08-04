/*
Name:		Linearizer.h
Created:	8/04/2015
Author:	Nathan Durnan
*/
#pragma once

// - implied - #include <math.h>

/**	Linearize a logarithmic curve value.
*	NOTE: The linear and logarithmic curves are assumed to intersect once at zero.
*	@param _value : the value to be linearized.
*	@param _span  : the non-zero value where the linear and logarithmic curves intersect.
*	@param _power : the non-zero power of the logarithmic curve (larger value means deeper curve).
*/
template <typename T> T deLog(T _value, T _span, double _power)
{
	if ((_span == 0) || (_power == 0))
		return _value;
	double k = (double)_span / (pow(M_E, _power) - 1.0);
	double v = (double)_span * log(1.0 + ((double)_value / k)) / _power;
	return T(v);
}
