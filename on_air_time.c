/*
 * on_air_time.c
 *
 *  Created on: Jun 4, 2024
 *      Author: KALHARA D.G.S.S
 */

/*
 * include statement section
 * including module stdint
 * including module stdint
 *
*/
#include <math.h>
#include <stdint.h>


/**
 * declaring function calculate_symbol_rate
 * @param int bandwidth
 * @param uint8_t spreding_factor
 * @return double symbol_rate
 *
 */
double calculate_symbol_rate(int bandwidth, uint8_t spreading_factor){
    return bandwidth / pow(2.0, (double)spreading_factor);
}

/**
 * declaring function calculate_symbol_time
 * @param double symbol_rate
 * @return double symbol_time
 *
 */
double calculate_symbol_time(double symbol_rate){
    return 1 / symbol_rate;
}

/**
 * declaring function calculate_preamble_duration
 * @param double symbol_time
 * @param uint8_t preamble_length
 * @return double preamble_time
 *
 */
double calculate_preamble_duration(double symbol_time, uint8_t preamble_length){
    return ((preamble_length + 4.25) * symbol_time);
}

/**
 * declaring function calculate_paylode_number
 * @param uint8_t spreading_factor
 * @param uint8_t low_data_rate_opt
 * @param int paylode_length
 * @param uint8_t crc_enable
 * @param uint8_t coding_rate
 * @return int payload_number
 *
 */
int calculate_paylode_number(uint8_t spreading_factor, uint8_t low_data_rate_opt, int paylode_length, uint8_t crc_enable, uint8_t header_mode, uint8_t coding_rate){

	double numerator = (double)(8 * paylode_length - 4 * spreading_factor + 28 + 16 * coding_rate - 20 * header_mode);
	uint8_t denominator = (4 * (spreading_factor - 2 * low_data_rate_opt));
	uint8_t multiplier = (coding_rate + 4);

	return (8 + fmax((ceil(numerator / denominator)) * multiplier, 0));
}

/**
 * declaring function calculate_paylode_duration
 * @param int payload_number
 * @param double symbol_time
 * @return double payload_duration
 *
 */
double calculate_paylode_duration(int payload_number, double symbol_time){
    return payload_number * symbol_time;
}

/**
 * declaring function calculate_time_on_air
 * @param double preamble_duration
 * @param double paylode_duration
 * @return double time_on_air
 *
 */
double calculate_time_on_air(double preamble_duration, double paylode_duration){
    return preamble_duration + paylode_duration;
}

/**
 * declaring function calculate_lora_waiting_time
 * @param double time_on_air
 * @param int buffer
 * @return double polling_time
 * if we consider abt the time, the return value will be has the form of milliseconds
 *
 */
double calculate_lora_waiting_time(double time_on_air, int buffer){
    return time_on_air * 1000 * 2 + buffer;
}

/**
 * online calculator: https://www.loratools.nl/#/airtime
*/
