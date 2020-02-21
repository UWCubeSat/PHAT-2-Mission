/*
 * thm.c
 *
 *  Created on: Feb 19, 2020
 *      Author: tengo
 */

#include "thm.h"

float thm_convert_from_celsius(float celsius, thm_conversion to) {
    switch(to) {
        case THM_KELVIN:
            return thm_celsius_to_kelvin(celsius);
        case THM_FAHRENHEIT:
            return thm_celsius_to_fahrenheit(celsius);
        case THM_CELSIUS:
        default:
            return celsius;
    }
}

float thm_convert_to_celsius(float temp, thm_conversion from) {
    switch(from) {
        case THM_KELVIN:
            return thm_kelvin_to_celsius(temp);
        case THM_FAHRENHEIT:
            return thm_fahrenheit_to_celsius(temp);
        case THM_CELSIUS:
        default:
            return temp;
    }
}
