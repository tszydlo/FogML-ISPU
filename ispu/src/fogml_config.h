/*
   Copyright 2021 FogML
   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at
       http://www.apache.org/licenses/LICENSE-2.0
   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#include "fogml.h"

#ifdef __cplusplus
extern "C" {
#endif

// DATA ACQUISITION
// accelerometer data X, Y, Z
#define ACC_TIME_TICKS  26 //1s of data
#define ACC_AXIS  3
#define ACC_FREQ  26 //frequency set in the conf.txt

// DIGITAL SIGNAL PROCESSING
// number of features - depends on the DSP blocks
 #define FOGML_VECTOR_SIZE ((TINYML_DSP_BASE_LEN + TINYML_DSP_ENERGY_LEN + TINYML_DSP_CROSSINGS_LEN) * ACC_AXIS)

//BLOCK 1 - BASE
tinyml_block_base_config_t block1_config;
tinyml_dsp_block_t block1 = {
    .type = TINYML_DSP_BASE,
    .config = &block1_config

};

//BLOCK 2 - ENERGY
tinyml_block_energy_config_t block2_config;
tinyml_dsp_block_t block2 = {
    .type = TINYML_DSP_ENERGY,
    .config = &block2_config
};

//BLOCK 3 - CROSSINGS
tinyml_block_crossings_config_t block3_config = {
    .threshold = 0.01
};
tinyml_dsp_block_t block3 = {
    .type = TINYML_DSP_CROSSINGS,
    .config = &block3_config
};

//DSP config
tinyml_dsp_block_t *blocks_tab[] = {&block1, &block2, &block3};

tinyml_dsp_config_t my_dsp_config = {
    .time_ticks = ACC_TIME_TICKS,    
    .axis_n = 3,
    .blocks_num = 3,
    .blocks = blocks_tab
};

int fogml_classification(float *vector) {
    return classifier(vector);
} 


void fogml_features_logger(float *time_series_data, float *vector) {
    tinyml_dsp(time_series_data, vector, &my_dsp_config);
}

#ifdef __cplusplus
} // extern "C"
#endif
