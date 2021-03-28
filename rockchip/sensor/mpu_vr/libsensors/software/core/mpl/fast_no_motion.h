/*
 $License:
    Copyright (C) 2011-2012 InvenSense Corporation, All Rights Reserved.
    See included License.txt for License information.
 $
 */

/******************************************************************************
 *
 * $Id$
 *
 *****************************************************************************/

#ifndef MLDMP_FAST_NO_MOTION_H__
#define MLDMP_FAST_NO_MOTION_H__

#include "mltypes.h"

#ifdef __cplusplus
extern "C" {
#endif

    inv_error_t inv_enable_fast_nomot(void);
    inv_error_t inv_disable_fast_nomot(void);
    inv_error_t inv_start_fast_nomot(void);
    inv_error_t inv_stop_fast_nomot(void);
    inv_error_t inv_init_fast_nomot(void);
    void inv_set_default_number_of_samples(int N);
    inv_error_t inv_fast_nomot_is_enabled(unsigned char *is_enabled);
    inv_error_t inv_update_fast_nomot(long *gyro);

    void inv_get_fast_nomot_accel_param(long *cntr, long long *param);
    void inv_get_fast_nomot_compass_param(long *cntr, long long *param);
    void inv_set_fast_nomot_accel_threshold(long long thresh);
    void inv_set_fast_nomot_compass_threshold(long long thresh);
    void int_set_fast_nomot_gyro_threshold(long long thresh);

    inv_time_t fast_nomot_get_gyro_bias_update_time(void);
    void fast_nomot_set_gyro_bias_update_time(struct inv_sensor_cal_t *sensor_cal);

    int fast_nomot_get_gyro_calibration_confidence_level(struct inv_sensor_cal_t *sensor_cal);
    void fast_nomot_set_gyro_calibration_confidence_level_time_threshold(float time_seconds);

    void inv_fnm_debug_print(void);

#ifdef __cplusplus
}
#endif


#endif // MLDMP_FAST_NO_MOTION_H__

