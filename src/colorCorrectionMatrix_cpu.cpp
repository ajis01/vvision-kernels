#include "cpu_kernels.h"

namespace cpu {


    const float bt2020_bt709_arr[3][3] = {
        {1.6605, -0.5876, -0.0728}, {-0.1246, 1.1329, -0.0083}, {-0.0182, -0.1006, 1.1187}};

    const float bt2020_bt709_off[3] = {0.0, 0.0, 0.0};

    const float bt709_bt2020_arr[3][3] = {{0.627, 0.329, 0.0433}, {0.0691, 0.92, 0.0113}, {0.0164, 0.088, 0.896}};

    const float bt709_bt2020_off[3] = {0.0, 0.0, 0.0};

    const float rgb_yuv_601_arr[3][3] = {{0.257, 0.504, 0.098}, {-0.148, -0.291, 0.439}, {0.439, -0.368, -0.071}};

    const float rgb_yuv_601_off[3] = {0.0625, 0.500, 0.500};

    const float rgb_yuv_709_arr[3][3] = {{0.183, 0.614, 0.062}, {-0.101, -0.338, 0.439}, {0.439, -0.399, -0.040}};

    const float rgb_yuv_709_off[3] = {0.0625, 0.500, 0.500};

    const float rgb_yuv_2020_arr[3][3] = {
        {0.225613, 0.582282, 0.050928}, {-0.119918, -0.309494, 0.429412}, {0.429412, -0.394875, -0.034537}};

    const float rgb_yuv_2020_off[3] = {0.062745, 0.500, 0.500};

    const float yuv_rgb_601_arr[3][3] = {{1.164, 0.000, 1.596}, {1.164, -0.813, -0.391}, {1.164, 2.018, 0.000}};

    const float yuv_rgb_601_off[3] = {-0.87075, 0.52925, -1.08175};

    const float yuv_rgb_709_arr[3][3] = {{1.164, 0.000, 1.793}, {1.164, -0.213, -0.534}, {1.164, 2.115, 0.000}};

    const float yuv_rgb_709_off[3] = {-0.96925, 0.30075, -1.13025};

    const float yuv_rgb_2020_arr[3][3] = {
        {1.164384, 0.000000, 1.717000}, {1.164384, -0.191603, -0.665274}, {1.164384, 2.190671, 0.000000}};

    const float yuv_rgb_2020_off[3] = {-0.931559, 0.355379, -1.168395};

    const float full_to_16_235_arr[3][3] = {
        {0.856305, 0.000000, 0.000000}, {0.000000, 0.856305, 0.000000}, {0.000000, 0.000000, 0.856305}};

    const float full_to_16_235_off[3] = {0.0625, 0.0625, 0.0625};

    const float full_from_16_235_arr[3][3] = {
        {1.167808, 0.000000, 0.000000}, {0.000000, 1.167808, 0.000000}, {0.000000, 0.000000, 1.167808}};

    const float full_from_16_235_off[3] = {-0.0729880, -0.0729880, -0.0729880};

    inline unsigned char satcast_ccm(int v) {
        v = (v > 255 ? 255 : v);
        v = (v < 0 ? 0 : v);
        return v;
    };


    //ccm
    int colorCorrectionMatrix(unsigned char const* src, int srcRows, int srcCols, int srcStep, int srcChannels,
                    unsigned char* dest, int destRows, int destCols, int destStep, int destChannels,
                    ccmTypeEnum ccmType){

        assert(srcRows == destRows && srcCols == destCols && srcStep == destStep && srcChannels==destChannels);

        float ccm_matrix[3][3];
        float offsetarray[3];

        switch (ccmType) {
            case bt2020_bt709:
                for (int i = 0; i < 3; i++) {
                    for (int j = 0; j < 3; j++) {
                        ccm_matrix[i][j] = bt2020_bt709_arr[i][j];
                    }
                    offsetarray[i] = bt2020_bt709_off[i];
                }

                break;
            case bt709_bt2020:
                for (int i = 0; i < 3; i++) {
                    for (int j = 0; j < 3; j++) {
                        ccm_matrix[i][j] = bt709_bt2020_arr[i][j];
                    }
                    offsetarray[i] = bt709_bt2020_off[i];
                }

                break;
            case rgb_yuv_601:
                for (int i = 0; i < 3; i++) {
                    for (int j = 0; j < 3; j++) {
                        ccm_matrix[i][j] = rgb_yuv_601_arr[i][j];
                    }
                    offsetarray[i] = rgb_yuv_601_off[i];
                }

                break;
            case rgb_yuv_709:
                for (int i = 0; i < 3; i++) {
                    for (int j = 0; j < 3; j++) {
                        ccm_matrix[i][j] = rgb_yuv_709_arr[i][j];
                    }
                    offsetarray[i] = rgb_yuv_709_off[i];
                }

                break;
            case rgb_yuv_2020:
                for (int i = 0; i < 3; i++) {
                    for (int j = 0; j < 3; j++) {
                        ccm_matrix[i][j] = rgb_yuv_2020_arr[i][j];
                    }
                    offsetarray[i] = rgb_yuv_2020_off[i];
                }

                break;
            case yuv_rgb_601:
                for (int i = 0; i < 3; i++) {
                    for (int j = 0; j < 3; j++) {
                        ccm_matrix[i][j] = yuv_rgb_601_arr[i][j];
                    }
                    offsetarray[i] = yuv_rgb_601_off[i];
                }

                break;
            case yuv_rgb_709:
                for (int i = 0; i < 3; i++) {
                    for (int j = 0; j < 3; j++) {
                        ccm_matrix[i][j] = yuv_rgb_709_arr[i][j];
                    }
                    offsetarray[i] = yuv_rgb_709_off[i];
                }

                break;
            case yuv_rgb_2020:
                for (int i = 0; i < 3; i++) {
                    for (int j = 0; j < 3; j++) {
                        ccm_matrix[i][j] = yuv_rgb_2020_arr[i][j];
                    }
                    offsetarray[i] = yuv_rgb_2020_off[i];
                }

                break;
            case full_to_16_235:
                for (int i = 0; i < 3; i++) {
                    for (int j = 0; j < 3; j++) {
                        ccm_matrix[i][j] = full_to_16_235_arr[i][j];
                    }
                    offsetarray[i] = full_to_16_235_off[i];
                }

                break;
            case full_from_16_235:
                for (int i = 0; i < 3; i++) {
                    for (int j = 0; j < 3; j++) {
                        ccm_matrix[i][j] = full_from_16_235_arr[i][j];
                    }
                    offsetarray[i] = full_from_16_235_off[i];
                }

                break;
            default:
                break;
        }


        float r;
        float g;
        float b;

        int value_r;
        int value_g;
        int value_b;

        for(int jj=0; jj<srcCols; jj+=BLOCK_SIZE){
            for(int i=0; i<srcRows; ++i){
                for(int j=jj; j<std::min(jj+BLOCK_SIZE,srcCols); ++j){
                        r = src[i*srcStep + j*srcChannels];
                        g = src[i*srcStep + j*srcChannels + 1];
                        b = src[i*srcStep + j*srcChannels + 2];

                        float value1 = (r * ccm_matrix[0][0]);
                        float value2 = (g * ccm_matrix[0][1]);
                        float value3 = (b * ccm_matrix[0][2]);

                        float value4 = (r * ccm_matrix[1][0]);
                        float value5 = (g * ccm_matrix[1][1]);
                        float value6 = (b * ccm_matrix[1][2]);

                        float value7 = (r * ccm_matrix[2][0]);
                        float value8 = (g * ccm_matrix[2][1]);
                        float value9 = (b * ccm_matrix[2][2]);

                        value_r = (int)(value1 + value2 + value3 + offsetarray[0]);
                        value_g = (int)(value4 + value5 + value6 + offsetarray[1]);
                        value_b = (int)(value7 + value8 + value9 + offsetarray[2]);

                        dest[i*srcStep + j*srcChannels]     = satcast_ccm(value_r);
                        dest[i*srcStep + j*srcChannels + 1] = satcast_ccm(value_g);
                        dest[i*srcStep + j*srcChannels + 2] = satcast_ccm(value_b);

                }
            }
        }

        return KERNEL_SUCCESS;

    }


}