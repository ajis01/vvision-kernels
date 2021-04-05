#include "cpu_kernels.h"

namespace cpu {

    struct by_cornerResponse { 
        bool operator()(cornerXY const &left, cornerXY const &right) { 
            return left.cornerResponse > right.cornerResponse;
        }
    };

    int nonMaximaSuppression(float const* src, int srcRows, int srcCols, int srcStep, int srcChannels,
                            float* dest, int destRows, int destCols, int destStep, int destChannels,
                            std::vector<cornerXY> &points, float percentage, int filterRange, int suppressionRadius){

        assert(srcRows == destRows && srcCols == destCols && srcStep == destStep && srcChannels==destChannels);
        // assert(src2Rows == destRows && src2Cols == destCols && src2Step == destStep && src2Channels==destChannels);
        
        for (int r = 0; r < srcRows; r++) {
            for (int c = 0; c < srcCols; c++) {
                
                int index = r*srcStep + c;
                cornerXY d;
                d.cornerResponse = src[index];
                d.x = r;
                d.y = c;

                points.push_back(d);
            }
        }

        // // Sort points by corner Response
        sort(points.begin(), points.end(), by_cornerResponse());

        // Get top points, given by the percentage
        int numberTopPoints = srcCols * srcRows * percentage;
        std::vector<cornerXY> topPoints;

        int i=0;
        while(topPoints.size() < numberTopPoints) {
            if(i == points.size())
                break;

            int supRows = destRows;
            int supCols = destCols;

            // Check if point marked in maximaSuppression matrix
            if(dest[(points[i].x)*destStep + points[i].y] == 0) {
                for (int r = -suppressionRadius; r <= suppressionRadius; r++) {
                    for (int c = -suppressionRadius; c <= suppressionRadius; c++) {
                        int sx = points[i].x+c;
                        int sy = points[i].y+r;

                        // bound checking
                        if(sx > supRows)
                            sx = supRows;
                        if(sx < 0)
                            sx = 0;
                        if(sy > supCols)
                            sy = supCols;
                        if(sy < 0)
                            sy = 0;

                        int index = (points[i].x+r)*destStep + points[i].y+c;
                        if(index>=0 && ((points[i].x+r)*destStep)>=0 && (points[i].y+c)>=0 
                            && ((points[i].x+r)*destStep)<destRows && (points[i].y+c)<destCols) dest[index] = 1;
                    }
                }

                // Convert back to original image coordinate system 
                points[i].x += 1 + filterRange;
                points[i].y += 1 + filterRange;
                topPoints.push_back(points[i]);
            }

            i++;
        }
        return KERNEL_SUCCESS;

    }


}