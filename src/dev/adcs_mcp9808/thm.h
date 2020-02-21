/*
 * thm.h
 *
 *  Created on: Feb 19, 2020
 *      Author: tengo
 *
 */

#ifndef THM_H_
#define THM_H_

/*
 * Represents a desired temperature unit.
 *     THM_CELSIUS
 *     THM_KELVIN
 *     THM_FAHRENHEIT
 */
typedef enum _thm_conversion {
    THM_CELSIUS,
    THM_KELVIN,
    THM_FAHRENHEIT
} thm_conversion;

/*
 * Conversions from celsius to kelvin and fahrenheit, and conversions from kelvin and fahrenheit to celsius.
 *
 * Returns the temperature in the given unit.
 */
inline float thm_celsius_to_kelvin(float celsius) { return celsius + 273.15f; }
inline float thm_celsius_to_fahrenheit(float celsius) { return (celsius * 1.8f) + 32; }
float thm_convert_from_celsius(float celsius, thm_conversion to);

inline float thm_kelvin_to_celsius(float kelvin) { return kelvin - 273.15f; }
inline float thm_fahrenheit_to_celsius(float fahrenheit) { return (fahrenheit - 32) * 5 / 9.0f; }
float thm_convert_to_celsius(float temp, thm_conversion from);

#endif /* THM_H_ */
