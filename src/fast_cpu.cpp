#include "cpu_kernels.h"

namespace cpu {


// Copyright (c) 2006, 2008 Edward Rosten
// All rights reserved.

// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:


// 	*Redistributions of source code must retain the above copyright
// 	 notice, this list of conditions and the following disclaimer.

// 	*Redistributions in binary form must reproduce the above copyright
// 	 notice, this list of conditions and the following disclaimer in the
// 	 documentation and/or other materials provided with the distribution.

// 	*Neither the name of the University of Cambridge nor the names of 
// 	 its contributors may be used to endorse or promote products derived 
// 	 from this software without specific prior written permission.

// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
// LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

    int fast12_corner_score(const byte* p, const int pixel[], int bstart)
    {    
        int bmin = bstart;
        int bmax = 255;
        int b = (bmax + bmin)/2;
        
        /*Compute the score using binary search*/
        for(;;)
        {
            int cb = *p + b;
            int c_b= *p - b;


            if( p[pixel[0]] > cb)
            if( p[pixel[1]] > cb)
            if( p[pixel[2]] > cb)
            if( p[pixel[3]] > cb)
                if( p[pixel[4]] > cb)
                if( p[pixel[5]] > cb)
                if( p[pixel[6]] > cb)
                if( p[pixel[7]] > cb)
                    if( p[pixel[8]] > cb)
                    if( p[pixel[9]] > cb)
                    if( p[pixel[10]] > cb)
                    if( p[pixel[11]] > cb)
                        goto is_a_corner;
                    else
                        if( p[pixel[15]] > cb)
                        goto is_a_corner;
                        else
                        goto is_not_a_corner;
                    else
                    if( p[pixel[14]] > cb)
                        if( p[pixel[15]] > cb)
                        goto is_a_corner;
                        else
                        goto is_not_a_corner;
                    else
                        goto is_not_a_corner;
                    else
                    if( p[pixel[13]] > cb)
                    if( p[pixel[14]] > cb)
                        if( p[pixel[15]] > cb)
                        goto is_a_corner;
                        else
                        goto is_not_a_corner;
                    else
                        goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                    else
                    if( p[pixel[12]] > cb)
                    if( p[pixel[13]] > cb)
                    if( p[pixel[14]] > cb)
                        if( p[pixel[15]] > cb)
                        goto is_a_corner;
                        else
                        goto is_not_a_corner;
                    else
                        goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                else
                    if( p[pixel[11]] > cb)
                    if( p[pixel[12]] > cb)
                    if( p[pixel[13]] > cb)
                    if( p[pixel[14]] > cb)
                        if( p[pixel[15]] > cb)
                        goto is_a_corner;
                        else
                        goto is_not_a_corner;
                    else
                        goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                else
                if( p[pixel[10]] > cb)
                    if( p[pixel[11]] > cb)
                    if( p[pixel[12]] > cb)
                    if( p[pixel[13]] > cb)
                    if( p[pixel[14]] > cb)
                        if( p[pixel[15]] > cb)
                        goto is_a_corner;
                        else
                        goto is_not_a_corner;
                    else
                        goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                else
                    goto is_not_a_corner;
                else
                if( p[pixel[9]] > cb)
                if( p[pixel[10]] > cb)
                    if( p[pixel[11]] > cb)
                    if( p[pixel[12]] > cb)
                    if( p[pixel[13]] > cb)
                    if( p[pixel[14]] > cb)
                        if( p[pixel[15]] > cb)
                        goto is_a_corner;
                        else
                        goto is_not_a_corner;
                    else
                        goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                else
                    goto is_not_a_corner;
                else
                goto is_not_a_corner;
                else if( p[pixel[4]] < c_b)
                if( p[pixel[8]] > cb)
                if( p[pixel[9]] > cb)
                if( p[pixel[10]] > cb)
                    if( p[pixel[11]] > cb)
                    if( p[pixel[12]] > cb)
                    if( p[pixel[13]] > cb)
                    if( p[pixel[14]] > cb)
                        if( p[pixel[15]] > cb)
                        goto is_a_corner;
                        else
                        goto is_not_a_corner;
                    else
                        goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                else
                    goto is_not_a_corner;
                else
                goto is_not_a_corner;
                else if( p[pixel[8]] < c_b)
                if( p[pixel[5]] < c_b)
                if( p[pixel[6]] < c_b)
                    if( p[pixel[7]] < c_b)
                    if( p[pixel[9]] < c_b)
                    if( p[pixel[10]] < c_b)
                    if( p[pixel[11]] < c_b)
                        if( p[pixel[12]] < c_b)
                        if( p[pixel[13]] < c_b)
                        if( p[pixel[14]] < c_b)
                        if( p[pixel[15]] < c_b)
                            goto is_a_corner;
                        else
                            goto is_not_a_corner;
                        else
                        goto is_not_a_corner;
                        else
                        goto is_not_a_corner;
                        else
                        goto is_not_a_corner;
                    else
                        goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                else
                    goto is_not_a_corner;
                else
                goto is_not_a_corner;
                else
                goto is_not_a_corner;
                else
                if( p[pixel[8]] > cb)
                if( p[pixel[9]] > cb)
                if( p[pixel[10]] > cb)
                    if( p[pixel[11]] > cb)
                    if( p[pixel[12]] > cb)
                    if( p[pixel[13]] > cb)
                    if( p[pixel[14]] > cb)
                        if( p[pixel[15]] > cb)
                        goto is_a_corner;
                        else
                        goto is_not_a_corner;
                    else
                        goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                else
                    goto is_not_a_corner;
                else
                goto is_not_a_corner;
                else
                goto is_not_a_corner;
            else if( p[pixel[3]] < c_b)
                if( p[pixel[15]] > cb)
                if( p[pixel[7]] > cb)
                if( p[pixel[8]] > cb)
                if( p[pixel[9]] > cb)
                    if( p[pixel[10]] > cb)
                    if( p[pixel[11]] > cb)
                    if( p[pixel[12]] > cb)
                    if( p[pixel[13]] > cb)
                        if( p[pixel[14]] > cb)
                        goto is_a_corner;
                        else
                        goto is_not_a_corner;
                    else
                        goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                else
                    goto is_not_a_corner;
                else
                goto is_not_a_corner;
                else if( p[pixel[7]] < c_b)
                if( p[pixel[4]] < c_b)
                if( p[pixel[5]] < c_b)
                    if( p[pixel[6]] < c_b)
                    if( p[pixel[8]] < c_b)
                    if( p[pixel[9]] < c_b)
                    if( p[pixel[10]] < c_b)
                        if( p[pixel[11]] < c_b)
                        if( p[pixel[12]] < c_b)
                        if( p[pixel[13]] < c_b)
                        if( p[pixel[14]] < c_b)
                            goto is_a_corner;
                        else
                            goto is_not_a_corner;
                        else
                        goto is_not_a_corner;
                        else
                        goto is_not_a_corner;
                        else
                        goto is_not_a_corner;
                    else
                        goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                else
                    goto is_not_a_corner;
                else
                goto is_not_a_corner;
                else
                goto is_not_a_corner;
                else
                if( p[pixel[4]] < c_b)
                if( p[pixel[5]] < c_b)
                if( p[pixel[6]] < c_b)
                    if( p[pixel[7]] < c_b)
                    if( p[pixel[8]] < c_b)
                    if( p[pixel[9]] < c_b)
                    if( p[pixel[10]] < c_b)
                        if( p[pixel[11]] < c_b)
                        if( p[pixel[12]] < c_b)
                        if( p[pixel[13]] < c_b)
                        if( p[pixel[14]] < c_b)
                            goto is_a_corner;
                        else
                            goto is_not_a_corner;
                        else
                        goto is_not_a_corner;
                        else
                        goto is_not_a_corner;
                        else
                        goto is_not_a_corner;
                    else
                        goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                else
                    goto is_not_a_corner;
                else
                goto is_not_a_corner;
                else
                goto is_not_a_corner;
            else
                if( p[pixel[7]] > cb)
                if( p[pixel[8]] > cb)
                if( p[pixel[9]] > cb)
                if( p[pixel[10]] > cb)
                    if( p[pixel[11]] > cb)
                    if( p[pixel[12]] > cb)
                    if( p[pixel[13]] > cb)
                    if( p[pixel[14]] > cb)
                        if( p[pixel[15]] > cb)
                        goto is_a_corner;
                        else
                        goto is_not_a_corner;
                    else
                        goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                else
                    goto is_not_a_corner;
                else
                goto is_not_a_corner;
                else
                goto is_not_a_corner;
                else if( p[pixel[7]] < c_b)
                if( p[pixel[4]] < c_b)
                if( p[pixel[5]] < c_b)
                if( p[pixel[6]] < c_b)
                    if( p[pixel[8]] < c_b)
                    if( p[pixel[9]] < c_b)
                    if( p[pixel[10]] < c_b)
                    if( p[pixel[11]] < c_b)
                        if( p[pixel[12]] < c_b)
                        if( p[pixel[13]] < c_b)
                        if( p[pixel[14]] < c_b)
                        if( p[pixel[15]] < c_b)
                            goto is_a_corner;
                        else
                            goto is_not_a_corner;
                        else
                        goto is_not_a_corner;
                        else
                        goto is_not_a_corner;
                        else
                        goto is_not_a_corner;
                    else
                        goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                else
                    goto is_not_a_corner;
                else
                goto is_not_a_corner;
                else
                goto is_not_a_corner;
                else
                goto is_not_a_corner;
            else if( p[pixel[2]] < c_b)
            if( p[pixel[6]] > cb)
                if( p[pixel[7]] > cb)
                if( p[pixel[8]] > cb)
                if( p[pixel[9]] > cb)
                if( p[pixel[10]] > cb)
                    if( p[pixel[11]] > cb)
                    if( p[pixel[12]] > cb)
                    if( p[pixel[13]] > cb)
                    if( p[pixel[14]] > cb)
                        if( p[pixel[15]] > cb)
                        goto is_a_corner;
                        else
                        if( p[pixel[3]] > cb)
                        if( p[pixel[4]] > cb)
                        if( p[pixel[5]] > cb)
                            goto is_a_corner;
                        else
                            goto is_not_a_corner;
                        else
                        goto is_not_a_corner;
                        else
                        goto is_not_a_corner;
                    else
                        goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                else
                    goto is_not_a_corner;
                else
                goto is_not_a_corner;
                else
                goto is_not_a_corner;
                else
                goto is_not_a_corner;
            else if( p[pixel[6]] < c_b)
                if( p[pixel[4]] < c_b)
                if( p[pixel[5]] < c_b)
                if( p[pixel[7]] < c_b)
                if( p[pixel[8]] < c_b)
                    if( p[pixel[9]] < c_b)
                    if( p[pixel[10]] < c_b)
                    if( p[pixel[11]] < c_b)
                    if( p[pixel[12]] < c_b)
                        if( p[pixel[13]] < c_b)
                        if( p[pixel[3]] < c_b)
                        goto is_a_corner;
                        else
                        if( p[pixel[14]] < c_b)
                        if( p[pixel[15]] < c_b)
                            goto is_a_corner;
                        else
                            goto is_not_a_corner;
                        else
                        goto is_not_a_corner;
                        else
                        goto is_not_a_corner;
                    else
                        goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                else
                    goto is_not_a_corner;
                else
                goto is_not_a_corner;
                else
                goto is_not_a_corner;
                else
                goto is_not_a_corner;
            else
                goto is_not_a_corner;
            else
            if( p[pixel[6]] > cb)
                if( p[pixel[7]] > cb)
                if( p[pixel[8]] > cb)
                if( p[pixel[9]] > cb)
                if( p[pixel[10]] > cb)
                    if( p[pixel[11]] > cb)
                    if( p[pixel[12]] > cb)
                    if( p[pixel[13]] > cb)
                    if( p[pixel[14]] > cb)
                        if( p[pixel[15]] > cb)
                        goto is_a_corner;
                        else
                        if( p[pixel[3]] > cb)
                        if( p[pixel[4]] > cb)
                        if( p[pixel[5]] > cb)
                            goto is_a_corner;
                        else
                            goto is_not_a_corner;
                        else
                        goto is_not_a_corner;
                        else
                        goto is_not_a_corner;
                    else
                        goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                else
                    goto is_not_a_corner;
                else
                goto is_not_a_corner;
                else
                goto is_not_a_corner;
                else
                goto is_not_a_corner;
            else if( p[pixel[6]] < c_b)
                if( p[pixel[4]] < c_b)
                if( p[pixel[5]] < c_b)
                if( p[pixel[7]] < c_b)
                if( p[pixel[8]] < c_b)
                    if( p[pixel[9]] < c_b)
                    if( p[pixel[10]] < c_b)
                    if( p[pixel[11]] < c_b)
                    if( p[pixel[12]] < c_b)
                        if( p[pixel[13]] < c_b)
                        if( p[pixel[14]] < c_b)
                        if( p[pixel[3]] < c_b)
                        goto is_a_corner;
                        else
                        if( p[pixel[15]] < c_b)
                            goto is_a_corner;
                        else
                            goto is_not_a_corner;
                        else
                        goto is_not_a_corner;
                        else
                        goto is_not_a_corner;
                    else
                        goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                else
                    goto is_not_a_corner;
                else
                goto is_not_a_corner;
                else
                goto is_not_a_corner;
                else
                goto is_not_a_corner;
            else
                goto is_not_a_corner;
            else if( p[pixel[1]] < c_b)
            if( p[pixel[5]] > cb)
            if( p[pixel[6]] > cb)
                if( p[pixel[7]] > cb)
                if( p[pixel[8]] > cb)
                if( p[pixel[9]] > cb)
                if( p[pixel[10]] > cb)
                    if( p[pixel[11]] > cb)
                    if( p[pixel[12]] > cb)
                    if( p[pixel[13]] > cb)
                    if( p[pixel[14]] > cb)
                        if( p[pixel[15]] > cb)
                        goto is_a_corner;
                        else
                        if( p[pixel[3]] > cb)
                        if( p[pixel[4]] > cb)
                        goto is_a_corner;
                        else
                        goto is_not_a_corner;
                        else
                        goto is_not_a_corner;
                    else
                        if( p[pixel[2]] > cb)
                        if( p[pixel[3]] > cb)
                        if( p[pixel[4]] > cb)
                        goto is_a_corner;
                        else
                        goto is_not_a_corner;
                        else
                        goto is_not_a_corner;
                        else
                        goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                else
                    goto is_not_a_corner;
                else
                goto is_not_a_corner;
                else
                goto is_not_a_corner;
                else
                goto is_not_a_corner;
            else
                goto is_not_a_corner;
            else if( p[pixel[5]] < c_b)
            if( p[pixel[4]] < c_b)
                if( p[pixel[6]] < c_b)
                if( p[pixel[7]] < c_b)
                if( p[pixel[8]] < c_b)
                if( p[pixel[9]] < c_b)
                    if( p[pixel[10]] < c_b)
                    if( p[pixel[11]] < c_b)
                    if( p[pixel[12]] < c_b)
                    if( p[pixel[3]] < c_b)
                        if( p[pixel[2]] < c_b)
                        goto is_a_corner;
                        else
                        if( p[pixel[13]] < c_b)
                        if( p[pixel[14]] < c_b)
                        goto is_a_corner;
                        else
                        goto is_not_a_corner;
                        else
                        goto is_not_a_corner;
                    else
                        if( p[pixel[13]] < c_b)
                        if( p[pixel[14]] < c_b)
                        if( p[pixel[15]] < c_b)
                        goto is_a_corner;
                        else
                        goto is_not_a_corner;
                        else
                        goto is_not_a_corner;
                        else
                        goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                else
                    goto is_not_a_corner;
                else
                goto is_not_a_corner;
                else
                goto is_not_a_corner;
                else
                goto is_not_a_corner;
            else
                goto is_not_a_corner;
            else
            goto is_not_a_corner;
            else
            if( p[pixel[5]] > cb)
            if( p[pixel[6]] > cb)
                if( p[pixel[7]] > cb)
                if( p[pixel[8]] > cb)
                if( p[pixel[9]] > cb)
                if( p[pixel[10]] > cb)
                    if( p[pixel[11]] > cb)
                    if( p[pixel[12]] > cb)
                    if( p[pixel[13]] > cb)
                    if( p[pixel[14]] > cb)
                        if( p[pixel[15]] > cb)
                        goto is_a_corner;
                        else
                        if( p[pixel[3]] > cb)
                        if( p[pixel[4]] > cb)
                        goto is_a_corner;
                        else
                        goto is_not_a_corner;
                        else
                        goto is_not_a_corner;
                    else
                        if( p[pixel[2]] > cb)
                        if( p[pixel[3]] > cb)
                        if( p[pixel[4]] > cb)
                        goto is_a_corner;
                        else
                        goto is_not_a_corner;
                        else
                        goto is_not_a_corner;
                        else
                        goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                else
                    goto is_not_a_corner;
                else
                goto is_not_a_corner;
                else
                goto is_not_a_corner;
                else
                goto is_not_a_corner;
            else
                goto is_not_a_corner;
            else if( p[pixel[5]] < c_b)
            if( p[pixel[4]] < c_b)
                if( p[pixel[6]] < c_b)
                if( p[pixel[7]] < c_b)
                if( p[pixel[8]] < c_b)
                if( p[pixel[9]] < c_b)
                    if( p[pixel[10]] < c_b)
                    if( p[pixel[11]] < c_b)
                    if( p[pixel[12]] < c_b)
                    if( p[pixel[13]] < c_b)
                        if( p[pixel[3]] < c_b)
                        if( p[pixel[2]] < c_b)
                        goto is_a_corner;
                        else
                        if( p[pixel[14]] < c_b)
                        goto is_a_corner;
                        else
                        goto is_not_a_corner;
                        else
                        if( p[pixel[14]] < c_b)
                        if( p[pixel[15]] < c_b)
                        goto is_a_corner;
                        else
                        goto is_not_a_corner;
                        else
                        goto is_not_a_corner;
                    else
                        goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                else
                    goto is_not_a_corner;
                else
                goto is_not_a_corner;
                else
                goto is_not_a_corner;
                else
                goto is_not_a_corner;
            else
                goto is_not_a_corner;
            else
            goto is_not_a_corner;
            else if( p[pixel[0]] < c_b)
            if( p[pixel[1]] > cb)
            if( p[pixel[5]] > cb)
            if( p[pixel[4]] > cb)
                if( p[pixel[6]] > cb)
                if( p[pixel[7]] > cb)
                if( p[pixel[8]] > cb)
                if( p[pixel[9]] > cb)
                    if( p[pixel[10]] > cb)
                    if( p[pixel[11]] > cb)
                    if( p[pixel[12]] > cb)
                    if( p[pixel[3]] > cb)
                        if( p[pixel[2]] > cb)
                        goto is_a_corner;
                        else
                        if( p[pixel[13]] > cb)
                        if( p[pixel[14]] > cb)
                        goto is_a_corner;
                        else
                        goto is_not_a_corner;
                        else
                        goto is_not_a_corner;
                    else
                        if( p[pixel[13]] > cb)
                        if( p[pixel[14]] > cb)
                        if( p[pixel[15]] > cb)
                        goto is_a_corner;
                        else
                        goto is_not_a_corner;
                        else
                        goto is_not_a_corner;
                        else
                        goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                else
                    goto is_not_a_corner;
                else
                goto is_not_a_corner;
                else
                goto is_not_a_corner;
                else
                goto is_not_a_corner;
            else
                goto is_not_a_corner;
            else if( p[pixel[5]] < c_b)
            if( p[pixel[6]] < c_b)
                if( p[pixel[7]] < c_b)
                if( p[pixel[8]] < c_b)
                if( p[pixel[9]] < c_b)
                if( p[pixel[10]] < c_b)
                    if( p[pixel[11]] < c_b)
                    if( p[pixel[12]] < c_b)
                    if( p[pixel[13]] < c_b)
                    if( p[pixel[14]] < c_b)
                        if( p[pixel[15]] < c_b)
                        goto is_a_corner;
                        else
                        if( p[pixel[3]] < c_b)
                        if( p[pixel[4]] < c_b)
                        goto is_a_corner;
                        else
                        goto is_not_a_corner;
                        else
                        goto is_not_a_corner;
                    else
                        if( p[pixel[2]] < c_b)
                        if( p[pixel[3]] < c_b)
                        if( p[pixel[4]] < c_b)
                        goto is_a_corner;
                        else
                        goto is_not_a_corner;
                        else
                        goto is_not_a_corner;
                        else
                        goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                else
                    goto is_not_a_corner;
                else
                goto is_not_a_corner;
                else
                goto is_not_a_corner;
                else
                goto is_not_a_corner;
            else
                goto is_not_a_corner;
            else
            goto is_not_a_corner;
            else if( p[pixel[1]] < c_b)
            if( p[pixel[2]] > cb)
            if( p[pixel[6]] > cb)
                if( p[pixel[4]] > cb)
                if( p[pixel[5]] > cb)
                if( p[pixel[7]] > cb)
                if( p[pixel[8]] > cb)
                    if( p[pixel[9]] > cb)
                    if( p[pixel[10]] > cb)
                    if( p[pixel[11]] > cb)
                    if( p[pixel[12]] > cb)
                        if( p[pixel[13]] > cb)
                        if( p[pixel[3]] > cb)
                        goto is_a_corner;
                        else
                        if( p[pixel[14]] > cb)
                        if( p[pixel[15]] > cb)
                            goto is_a_corner;
                        else
                            goto is_not_a_corner;
                        else
                        goto is_not_a_corner;
                        else
                        goto is_not_a_corner;
                    else
                        goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                else
                    goto is_not_a_corner;
                else
                goto is_not_a_corner;
                else
                goto is_not_a_corner;
                else
                goto is_not_a_corner;
            else if( p[pixel[6]] < c_b)
                if( p[pixel[7]] < c_b)
                if( p[pixel[8]] < c_b)
                if( p[pixel[9]] < c_b)
                if( p[pixel[10]] < c_b)
                    if( p[pixel[11]] < c_b)
                    if( p[pixel[12]] < c_b)
                    if( p[pixel[13]] < c_b)
                    if( p[pixel[14]] < c_b)
                        if( p[pixel[15]] < c_b)
                        goto is_a_corner;
                        else
                        if( p[pixel[3]] < c_b)
                        if( p[pixel[4]] < c_b)
                        if( p[pixel[5]] < c_b)
                            goto is_a_corner;
                        else
                            goto is_not_a_corner;
                        else
                        goto is_not_a_corner;
                        else
                        goto is_not_a_corner;
                    else
                        goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                else
                    goto is_not_a_corner;
                else
                goto is_not_a_corner;
                else
                goto is_not_a_corner;
                else
                goto is_not_a_corner;
            else
                goto is_not_a_corner;
            else if( p[pixel[2]] < c_b)
            if( p[pixel[3]] > cb)
                if( p[pixel[15]] < c_b)
                if( p[pixel[7]] > cb)
                if( p[pixel[4]] > cb)
                if( p[pixel[5]] > cb)
                    if( p[pixel[6]] > cb)
                    if( p[pixel[8]] > cb)
                    if( p[pixel[9]] > cb)
                    if( p[pixel[10]] > cb)
                        if( p[pixel[11]] > cb)
                        if( p[pixel[12]] > cb)
                        if( p[pixel[13]] > cb)
                        if( p[pixel[14]] > cb)
                            goto is_a_corner;
                        else
                            goto is_not_a_corner;
                        else
                        goto is_not_a_corner;
                        else
                        goto is_not_a_corner;
                        else
                        goto is_not_a_corner;
                    else
                        goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                else
                    goto is_not_a_corner;
                else
                goto is_not_a_corner;
                else if( p[pixel[7]] < c_b)
                if( p[pixel[8]] < c_b)
                if( p[pixel[9]] < c_b)
                    if( p[pixel[10]] < c_b)
                    if( p[pixel[11]] < c_b)
                    if( p[pixel[12]] < c_b)
                    if( p[pixel[13]] < c_b)
                        if( p[pixel[14]] < c_b)
                        goto is_a_corner;
                        else
                        goto is_not_a_corner;
                    else
                        goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                else
                    goto is_not_a_corner;
                else
                goto is_not_a_corner;
                else
                goto is_not_a_corner;
                else
                if( p[pixel[4]] > cb)
                if( p[pixel[5]] > cb)
                if( p[pixel[6]] > cb)
                    if( p[pixel[7]] > cb)
                    if( p[pixel[8]] > cb)
                    if( p[pixel[9]] > cb)
                    if( p[pixel[10]] > cb)
                        if( p[pixel[11]] > cb)
                        if( p[pixel[12]] > cb)
                        if( p[pixel[13]] > cb)
                        if( p[pixel[14]] > cb)
                            goto is_a_corner;
                        else
                            goto is_not_a_corner;
                        else
                        goto is_not_a_corner;
                        else
                        goto is_not_a_corner;
                        else
                        goto is_not_a_corner;
                    else
                        goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                else
                    goto is_not_a_corner;
                else
                goto is_not_a_corner;
                else
                goto is_not_a_corner;
            else if( p[pixel[3]] < c_b)
                if( p[pixel[4]] > cb)
                if( p[pixel[8]] > cb)
                if( p[pixel[5]] > cb)
                if( p[pixel[6]] > cb)
                    if( p[pixel[7]] > cb)
                    if( p[pixel[9]] > cb)
                    if( p[pixel[10]] > cb)
                    if( p[pixel[11]] > cb)
                        if( p[pixel[12]] > cb)
                        if( p[pixel[13]] > cb)
                        if( p[pixel[14]] > cb)
                        if( p[pixel[15]] > cb)
                            goto is_a_corner;
                        else
                            goto is_not_a_corner;
                        else
                        goto is_not_a_corner;
                        else
                        goto is_not_a_corner;
                        else
                        goto is_not_a_corner;
                    else
                        goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                else
                    goto is_not_a_corner;
                else
                goto is_not_a_corner;
                else if( p[pixel[8]] < c_b)
                if( p[pixel[9]] < c_b)
                if( p[pixel[10]] < c_b)
                    if( p[pixel[11]] < c_b)
                    if( p[pixel[12]] < c_b)
                    if( p[pixel[13]] < c_b)
                    if( p[pixel[14]] < c_b)
                        if( p[pixel[15]] < c_b)
                        goto is_a_corner;
                        else
                        goto is_not_a_corner;
                    else
                        goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                else
                    goto is_not_a_corner;
                else
                goto is_not_a_corner;
                else
                goto is_not_a_corner;
                else if( p[pixel[4]] < c_b)
                if( p[pixel[5]] < c_b)
                if( p[pixel[6]] < c_b)
                if( p[pixel[7]] < c_b)
                    if( p[pixel[8]] < c_b)
                    if( p[pixel[9]] < c_b)
                    if( p[pixel[10]] < c_b)
                    if( p[pixel[11]] < c_b)
                        goto is_a_corner;
                    else
                        if( p[pixel[15]] < c_b)
                        goto is_a_corner;
                        else
                        goto is_not_a_corner;
                    else
                    if( p[pixel[14]] < c_b)
                        if( p[pixel[15]] < c_b)
                        goto is_a_corner;
                        else
                        goto is_not_a_corner;
                    else
                        goto is_not_a_corner;
                    else
                    if( p[pixel[13]] < c_b)
                    if( p[pixel[14]] < c_b)
                        if( p[pixel[15]] < c_b)
                        goto is_a_corner;
                        else
                        goto is_not_a_corner;
                    else
                        goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                    else
                    if( p[pixel[12]] < c_b)
                    if( p[pixel[13]] < c_b)
                    if( p[pixel[14]] < c_b)
                        if( p[pixel[15]] < c_b)
                        goto is_a_corner;
                        else
                        goto is_not_a_corner;
                    else
                        goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                else
                    if( p[pixel[11]] < c_b)
                    if( p[pixel[12]] < c_b)
                    if( p[pixel[13]] < c_b)
                    if( p[pixel[14]] < c_b)
                        if( p[pixel[15]] < c_b)
                        goto is_a_corner;
                        else
                        goto is_not_a_corner;
                    else
                        goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                else
                if( p[pixel[10]] < c_b)
                    if( p[pixel[11]] < c_b)
                    if( p[pixel[12]] < c_b)
                    if( p[pixel[13]] < c_b)
                    if( p[pixel[14]] < c_b)
                        if( p[pixel[15]] < c_b)
                        goto is_a_corner;
                        else
                        goto is_not_a_corner;
                    else
                        goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                else
                    goto is_not_a_corner;
                else
                if( p[pixel[9]] < c_b)
                if( p[pixel[10]] < c_b)
                    if( p[pixel[11]] < c_b)
                    if( p[pixel[12]] < c_b)
                    if( p[pixel[13]] < c_b)
                    if( p[pixel[14]] < c_b)
                        if( p[pixel[15]] < c_b)
                        goto is_a_corner;
                        else
                        goto is_not_a_corner;
                    else
                        goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                else
                    goto is_not_a_corner;
                else
                goto is_not_a_corner;
                else
                if( p[pixel[8]] < c_b)
                if( p[pixel[9]] < c_b)
                if( p[pixel[10]] < c_b)
                    if( p[pixel[11]] < c_b)
                    if( p[pixel[12]] < c_b)
                    if( p[pixel[13]] < c_b)
                    if( p[pixel[14]] < c_b)
                        if( p[pixel[15]] < c_b)
                        goto is_a_corner;
                        else
                        goto is_not_a_corner;
                    else
                        goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                else
                    goto is_not_a_corner;
                else
                goto is_not_a_corner;
                else
                goto is_not_a_corner;
            else
                if( p[pixel[7]] > cb)
                if( p[pixel[4]] > cb)
                if( p[pixel[5]] > cb)
                if( p[pixel[6]] > cb)
                    if( p[pixel[8]] > cb)
                    if( p[pixel[9]] > cb)
                    if( p[pixel[10]] > cb)
                    if( p[pixel[11]] > cb)
                        if( p[pixel[12]] > cb)
                        if( p[pixel[13]] > cb)
                        if( p[pixel[14]] > cb)
                        if( p[pixel[15]] > cb)
                            goto is_a_corner;
                        else
                            goto is_not_a_corner;
                        else
                        goto is_not_a_corner;
                        else
                        goto is_not_a_corner;
                        else
                        goto is_not_a_corner;
                    else
                        goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                else
                    goto is_not_a_corner;
                else
                goto is_not_a_corner;
                else
                goto is_not_a_corner;
                else if( p[pixel[7]] < c_b)
                if( p[pixel[8]] < c_b)
                if( p[pixel[9]] < c_b)
                if( p[pixel[10]] < c_b)
                    if( p[pixel[11]] < c_b)
                    if( p[pixel[12]] < c_b)
                    if( p[pixel[13]] < c_b)
                    if( p[pixel[14]] < c_b)
                        if( p[pixel[15]] < c_b)
                        goto is_a_corner;
                        else
                        goto is_not_a_corner;
                    else
                        goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                else
                    goto is_not_a_corner;
                else
                goto is_not_a_corner;
                else
                goto is_not_a_corner;
                else
                goto is_not_a_corner;
            else
            if( p[pixel[6]] > cb)
                if( p[pixel[4]] > cb)
                if( p[pixel[5]] > cb)
                if( p[pixel[7]] > cb)
                if( p[pixel[8]] > cb)
                    if( p[pixel[9]] > cb)
                    if( p[pixel[10]] > cb)
                    if( p[pixel[11]] > cb)
                    if( p[pixel[12]] > cb)
                        if( p[pixel[13]] > cb)
                        if( p[pixel[14]] > cb)
                        if( p[pixel[3]] > cb)
                        goto is_a_corner;
                        else
                        if( p[pixel[15]] > cb)
                            goto is_a_corner;
                        else
                            goto is_not_a_corner;
                        else
                        goto is_not_a_corner;
                        else
                        goto is_not_a_corner;
                    else
                        goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                else
                    goto is_not_a_corner;
                else
                goto is_not_a_corner;
                else
                goto is_not_a_corner;
                else
                goto is_not_a_corner;
            else if( p[pixel[6]] < c_b)
                if( p[pixel[7]] < c_b)
                if( p[pixel[8]] < c_b)
                if( p[pixel[9]] < c_b)
                if( p[pixel[10]] < c_b)
                    if( p[pixel[11]] < c_b)
                    if( p[pixel[12]] < c_b)
                    if( p[pixel[13]] < c_b)
                    if( p[pixel[14]] < c_b)
                        if( p[pixel[15]] < c_b)
                        goto is_a_corner;
                        else
                        if( p[pixel[3]] < c_b)
                        if( p[pixel[4]] < c_b)
                        if( p[pixel[5]] < c_b)
                            goto is_a_corner;
                        else
                            goto is_not_a_corner;
                        else
                        goto is_not_a_corner;
                        else
                        goto is_not_a_corner;
                    else
                        goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                else
                    goto is_not_a_corner;
                else
                goto is_not_a_corner;
                else
                goto is_not_a_corner;
                else
                goto is_not_a_corner;
            else
                goto is_not_a_corner;
            else
            if( p[pixel[5]] > cb)
            if( p[pixel[4]] > cb)
                if( p[pixel[6]] > cb)
                if( p[pixel[7]] > cb)
                if( p[pixel[8]] > cb)
                if( p[pixel[9]] > cb)
                    if( p[pixel[10]] > cb)
                    if( p[pixel[11]] > cb)
                    if( p[pixel[12]] > cb)
                    if( p[pixel[13]] > cb)
                        if( p[pixel[3]] > cb)
                        if( p[pixel[2]] > cb)
                        goto is_a_corner;
                        else
                        if( p[pixel[14]] > cb)
                        goto is_a_corner;
                        else
                        goto is_not_a_corner;
                        else
                        if( p[pixel[14]] > cb)
                        if( p[pixel[15]] > cb)
                        goto is_a_corner;
                        else
                        goto is_not_a_corner;
                        else
                        goto is_not_a_corner;
                    else
                        goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                else
                    goto is_not_a_corner;
                else
                goto is_not_a_corner;
                else
                goto is_not_a_corner;
                else
                goto is_not_a_corner;
            else
                goto is_not_a_corner;
            else if( p[pixel[5]] < c_b)
            if( p[pixel[6]] < c_b)
                if( p[pixel[7]] < c_b)
                if( p[pixel[8]] < c_b)
                if( p[pixel[9]] < c_b)
                if( p[pixel[10]] < c_b)
                    if( p[pixel[11]] < c_b)
                    if( p[pixel[12]] < c_b)
                    if( p[pixel[13]] < c_b)
                    if( p[pixel[14]] < c_b)
                        if( p[pixel[15]] < c_b)
                        goto is_a_corner;
                        else
                        if( p[pixel[3]] < c_b)
                        if( p[pixel[4]] < c_b)
                        goto is_a_corner;
                        else
                        goto is_not_a_corner;
                        else
                        goto is_not_a_corner;
                    else
                        if( p[pixel[2]] < c_b)
                        if( p[pixel[3]] < c_b)
                        if( p[pixel[4]] < c_b)
                        goto is_a_corner;
                        else
                        goto is_not_a_corner;
                        else
                        goto is_not_a_corner;
                        else
                        goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                else
                    goto is_not_a_corner;
                else
                goto is_not_a_corner;
                else
                goto is_not_a_corner;
                else
                goto is_not_a_corner;
            else
                goto is_not_a_corner;
            else
            goto is_not_a_corner;
            else
            if( p[pixel[4]] > cb)
            if( p[pixel[5]] > cb)
            if( p[pixel[6]] > cb)
                if( p[pixel[7]] > cb)
                if( p[pixel[8]] > cb)
                if( p[pixel[9]] > cb)
                if( p[pixel[10]] > cb)
                    if( p[pixel[11]] > cb)
                    if( p[pixel[12]] > cb)
                    if( p[pixel[3]] > cb)
                    if( p[pixel[2]] > cb)
                        if( p[pixel[1]] > cb)
                        goto is_a_corner;
                        else
                        if( p[pixel[13]] > cb)
                        goto is_a_corner;
                        else
                        goto is_not_a_corner;
                    else
                        if( p[pixel[13]] > cb)
                        if( p[pixel[14]] > cb)
                        goto is_a_corner;
                        else
                        goto is_not_a_corner;
                        else
                        goto is_not_a_corner;
                    else
                    if( p[pixel[13]] > cb)
                        if( p[pixel[14]] > cb)
                        if( p[pixel[15]] > cb)
                        goto is_a_corner;
                        else
                        goto is_not_a_corner;
                        else
                        goto is_not_a_corner;
                    else
                        goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                else
                    goto is_not_a_corner;
                else
                goto is_not_a_corner;
                else
                goto is_not_a_corner;
                else
                goto is_not_a_corner;
            else
                goto is_not_a_corner;
            else
            goto is_not_a_corner;
            else if( p[pixel[4]] < c_b)
            if( p[pixel[5]] < c_b)
            if( p[pixel[6]] < c_b)
                if( p[pixel[7]] < c_b)
                if( p[pixel[8]] < c_b)
                if( p[pixel[9]] < c_b)
                if( p[pixel[10]] < c_b)
                    if( p[pixel[11]] < c_b)
                    if( p[pixel[12]] < c_b)
                    if( p[pixel[3]] < c_b)
                    if( p[pixel[2]] < c_b)
                        if( p[pixel[1]] < c_b)
                        goto is_a_corner;
                        else
                        if( p[pixel[13]] < c_b)
                        goto is_a_corner;
                        else
                        goto is_not_a_corner;
                    else
                        if( p[pixel[13]] < c_b)
                        if( p[pixel[14]] < c_b)
                        goto is_a_corner;
                        else
                        goto is_not_a_corner;
                        else
                        goto is_not_a_corner;
                    else
                    if( p[pixel[13]] < c_b)
                        if( p[pixel[14]] < c_b)
                        if( p[pixel[15]] < c_b)
                        goto is_a_corner;
                        else
                        goto is_not_a_corner;
                        else
                        goto is_not_a_corner;
                    else
                        goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                    else
                    goto is_not_a_corner;
                else
                    goto is_not_a_corner;
                else
                goto is_not_a_corner;
                else
                goto is_not_a_corner;
                else
                goto is_not_a_corner;
            else
                goto is_not_a_corner;
            else
            goto is_not_a_corner;
            else
            goto is_not_a_corner;

            is_a_corner:
                bmin=b;
                goto end_if;

            is_not_a_corner:
                bmax=b;
                goto end_if;

            end_if:

            if(bmin == bmax - 1 || bmin == bmax)
                return bmin;
            b = (bmin + bmax) / 2;
        }
    }

    static void make_offsets(int pixel[], int row_stride)
    {
            pixel[0] = 0 + row_stride * 3;
            pixel[1] = 1 + row_stride * 3;
            pixel[2] = 2 + row_stride * 2;
            pixel[3] = 3 + row_stride * 1;
            pixel[4] = 3 + row_stride * 0;
            pixel[5] = 3 + row_stride * -1;
            pixel[6] = 2 + row_stride * -2;
            pixel[7] = 1 + row_stride * -3;
            pixel[8] = 0 + row_stride * -3;
            pixel[9] = -1 + row_stride * -3;
            pixel[10] = -2 + row_stride * -2;
            pixel[11] = -3 + row_stride * -1;
            pixel[12] = -3 + row_stride * 0;
            pixel[13] = -3 + row_stride * 1;
            pixel[14] = -2 + row_stride * 2;
            pixel[15] = -1 + row_stride * 3;
    }



    int* fast12_score(const byte* i, int stride, xy* corners, int num_corners, int b)
    {	
        int* scores = (int*)malloc(sizeof(int)* num_corners);
        int n;

        int pixel[16];
        make_offsets(pixel, stride);

        for(n=0; n < num_corners; n++)
            scores[n] = fast12_corner_score(i + corners[n].y*stride + corners[n].x, pixel, b);

        return scores;
    }


    xy* fast12_detect(const byte* im, int xsize, int ysize, int stride, int b, int* ret_num_corners)
    {
        int num_corners=0;
        xy* ret_corners;
        int rsize=512;
        int pixel[16];
        int x, y;

        ret_corners = (xy*)malloc(sizeof(xy)*rsize);
        make_offsets(pixel, stride);

        for(y=3; y < ysize - 3; y++)
            for(x=3; x < xsize - 3; x++)
            {
                const byte* p = im + y*stride + x;
            
                int cb = *p + b;
                int c_b= *p - b;
            if(p[pixel[0]] > cb)
            if(p[pixel[1]] > cb)
            if(p[pixel[2]] > cb)
            if(p[pixel[3]] > cb)
                if(p[pixel[4]] > cb)
                if(p[pixel[5]] > cb)
                if(p[pixel[6]] > cb)
                if(p[pixel[7]] > cb)
                    if(p[pixel[8]] > cb)
                    if(p[pixel[9]] > cb)
                    if(p[pixel[10]] > cb)
                    if(p[pixel[11]] > cb)
                        {}
                    else
                        if(p[pixel[15]] > cb)
                        {}
                        else
                        continue;
                    else
                    if(p[pixel[14]] > cb)
                        if(p[pixel[15]] > cb)
                        {}
                        else
                        continue;
                    else
                        continue;
                    else
                    if(p[pixel[13]] > cb)
                    if(p[pixel[14]] > cb)
                        if(p[pixel[15]] > cb)
                        {}
                        else
                        continue;
                    else
                        continue;
                    else
                    continue;
                    else
                    if(p[pixel[12]] > cb)
                    if(p[pixel[13]] > cb)
                    if(p[pixel[14]] > cb)
                        if(p[pixel[15]] > cb)
                        {}
                        else
                        continue;
                    else
                        continue;
                    else
                    continue;
                    else
                    continue;
                else
                    if(p[pixel[11]] > cb)
                    if(p[pixel[12]] > cb)
                    if(p[pixel[13]] > cb)
                    if(p[pixel[14]] > cb)
                        if(p[pixel[15]] > cb)
                        {}
                        else
                        continue;
                    else
                        continue;
                    else
                    continue;
                    else
                    continue;
                    else
                    continue;
                else
                if(p[pixel[10]] > cb)
                    if(p[pixel[11]] > cb)
                    if(p[pixel[12]] > cb)
                    if(p[pixel[13]] > cb)
                    if(p[pixel[14]] > cb)
                        if(p[pixel[15]] > cb)
                        {}
                        else
                        continue;
                    else
                        continue;
                    else
                    continue;
                    else
                    continue;
                    else
                    continue;
                else
                    continue;
                else
                if(p[pixel[9]] > cb)
                if(p[pixel[10]] > cb)
                    if(p[pixel[11]] > cb)
                    if(p[pixel[12]] > cb)
                    if(p[pixel[13]] > cb)
                    if(p[pixel[14]] > cb)
                        if(p[pixel[15]] > cb)
                        {}
                        else
                        continue;
                    else
                        continue;
                    else
                    continue;
                    else
                    continue;
                    else
                    continue;
                else
                    continue;
                else
                continue;
                else if(p[pixel[4]] < c_b)
                if(p[pixel[8]] > cb)
                if(p[pixel[9]] > cb)
                if(p[pixel[10]] > cb)
                    if(p[pixel[11]] > cb)
                    if(p[pixel[12]] > cb)
                    if(p[pixel[13]] > cb)
                    if(p[pixel[14]] > cb)
                        if(p[pixel[15]] > cb)
                        {}
                        else
                        continue;
                    else
                        continue;
                    else
                    continue;
                    else
                    continue;
                    else
                    continue;
                else
                    continue;
                else
                continue;
                else if(p[pixel[8]] < c_b)
                if(p[pixel[5]] < c_b)
                if(p[pixel[6]] < c_b)
                    if(p[pixel[7]] < c_b)
                    if(p[pixel[9]] < c_b)
                    if(p[pixel[10]] < c_b)
                    if(p[pixel[11]] < c_b)
                        if(p[pixel[12]] < c_b)
                        if(p[pixel[13]] < c_b)
                        if(p[pixel[14]] < c_b)
                        if(p[pixel[15]] < c_b)
                            {}
                        else
                            continue;
                        else
                        continue;
                        else
                        continue;
                        else
                        continue;
                    else
                        continue;
                    else
                    continue;
                    else
                    continue;
                    else
                    continue;
                else
                    continue;
                else
                continue;
                else
                continue;
                else
                if(p[pixel[8]] > cb)
                if(p[pixel[9]] > cb)
                if(p[pixel[10]] > cb)
                    if(p[pixel[11]] > cb)
                    if(p[pixel[12]] > cb)
                    if(p[pixel[13]] > cb)
                    if(p[pixel[14]] > cb)
                        if(p[pixel[15]] > cb)
                        {}
                        else
                        continue;
                    else
                        continue;
                    else
                    continue;
                    else
                    continue;
                    else
                    continue;
                else
                    continue;
                else
                continue;
                else
                continue;
            else if(p[pixel[3]] < c_b)
                if(p[pixel[15]] > cb)
                if(p[pixel[7]] > cb)
                if(p[pixel[8]] > cb)
                if(p[pixel[9]] > cb)
                    if(p[pixel[10]] > cb)
                    if(p[pixel[11]] > cb)
                    if(p[pixel[12]] > cb)
                    if(p[pixel[13]] > cb)
                        if(p[pixel[14]] > cb)
                        {}
                        else
                        continue;
                    else
                        continue;
                    else
                    continue;
                    else
                    continue;
                    else
                    continue;
                else
                    continue;
                else
                continue;
                else if(p[pixel[7]] < c_b)
                if(p[pixel[4]] < c_b)
                if(p[pixel[5]] < c_b)
                    if(p[pixel[6]] < c_b)
                    if(p[pixel[8]] < c_b)
                    if(p[pixel[9]] < c_b)
                    if(p[pixel[10]] < c_b)
                        if(p[pixel[11]] < c_b)
                        if(p[pixel[12]] < c_b)
                        if(p[pixel[13]] < c_b)
                        if(p[pixel[14]] < c_b)
                            {}
                        else
                            continue;
                        else
                        continue;
                        else
                        continue;
                        else
                        continue;
                    else
                        continue;
                    else
                    continue;
                    else
                    continue;
                    else
                    continue;
                else
                    continue;
                else
                continue;
                else
                continue;
                else
                if(p[pixel[4]] < c_b)
                if(p[pixel[5]] < c_b)
                if(p[pixel[6]] < c_b)
                    if(p[pixel[7]] < c_b)
                    if(p[pixel[8]] < c_b)
                    if(p[pixel[9]] < c_b)
                    if(p[pixel[10]] < c_b)
                        if(p[pixel[11]] < c_b)
                        if(p[pixel[12]] < c_b)
                        if(p[pixel[13]] < c_b)
                        if(p[pixel[14]] < c_b)
                            {}
                        else
                            continue;
                        else
                        continue;
                        else
                        continue;
                        else
                        continue;
                    else
                        continue;
                    else
                    continue;
                    else
                    continue;
                    else
                    continue;
                else
                    continue;
                else
                continue;
                else
                continue;
            else
                if(p[pixel[7]] > cb)
                if(p[pixel[8]] > cb)
                if(p[pixel[9]] > cb)
                if(p[pixel[10]] > cb)
                    if(p[pixel[11]] > cb)
                    if(p[pixel[12]] > cb)
                    if(p[pixel[13]] > cb)
                    if(p[pixel[14]] > cb)
                        if(p[pixel[15]] > cb)
                        {}
                        else
                        continue;
                    else
                        continue;
                    else
                    continue;
                    else
                    continue;
                    else
                    continue;
                else
                    continue;
                else
                continue;
                else
                continue;
                else if(p[pixel[7]] < c_b)
                if(p[pixel[4]] < c_b)
                if(p[pixel[5]] < c_b)
                if(p[pixel[6]] < c_b)
                    if(p[pixel[8]] < c_b)
                    if(p[pixel[9]] < c_b)
                    if(p[pixel[10]] < c_b)
                    if(p[pixel[11]] < c_b)
                        if(p[pixel[12]] < c_b)
                        if(p[pixel[13]] < c_b)
                        if(p[pixel[14]] < c_b)
                        if(p[pixel[15]] < c_b)
                            {}
                        else
                            continue;
                        else
                        continue;
                        else
                        continue;
                        else
                        continue;
                    else
                        continue;
                    else
                    continue;
                    else
                    continue;
                    else
                    continue;
                else
                    continue;
                else
                continue;
                else
                continue;
                else
                continue;
            else if(p[pixel[2]] < c_b)
            if(p[pixel[6]] > cb)
                if(p[pixel[7]] > cb)
                if(p[pixel[8]] > cb)
                if(p[pixel[9]] > cb)
                if(p[pixel[10]] > cb)
                    if(p[pixel[11]] > cb)
                    if(p[pixel[12]] > cb)
                    if(p[pixel[13]] > cb)
                    if(p[pixel[14]] > cb)
                        if(p[pixel[15]] > cb)
                        {}
                        else
                        if(p[pixel[3]] > cb)
                        if(p[pixel[4]] > cb)
                        if(p[pixel[5]] > cb)
                            {}
                        else
                            continue;
                        else
                        continue;
                        else
                        continue;
                    else
                        continue;
                    else
                    continue;
                    else
                    continue;
                    else
                    continue;
                else
                    continue;
                else
                continue;
                else
                continue;
                else
                continue;
            else if(p[pixel[6]] < c_b)
                if(p[pixel[4]] < c_b)
                if(p[pixel[5]] < c_b)
                if(p[pixel[7]] < c_b)
                if(p[pixel[8]] < c_b)
                    if(p[pixel[9]] < c_b)
                    if(p[pixel[10]] < c_b)
                    if(p[pixel[11]] < c_b)
                    if(p[pixel[12]] < c_b)
                        if(p[pixel[13]] < c_b)
                        if(p[pixel[3]] < c_b)
                        {}
                        else
                        if(p[pixel[14]] < c_b)
                        if(p[pixel[15]] < c_b)
                            {}
                        else
                            continue;
                        else
                        continue;
                        else
                        continue;
                    else
                        continue;
                    else
                    continue;
                    else
                    continue;
                    else
                    continue;
                else
                    continue;
                else
                continue;
                else
                continue;
                else
                continue;
            else
                continue;
            else
            if(p[pixel[6]] > cb)
                if(p[pixel[7]] > cb)
                if(p[pixel[8]] > cb)
                if(p[pixel[9]] > cb)
                if(p[pixel[10]] > cb)
                    if(p[pixel[11]] > cb)
                    if(p[pixel[12]] > cb)
                    if(p[pixel[13]] > cb)
                    if(p[pixel[14]] > cb)
                        if(p[pixel[15]] > cb)
                        {}
                        else
                        if(p[pixel[3]] > cb)
                        if(p[pixel[4]] > cb)
                        if(p[pixel[5]] > cb)
                            {}
                        else
                            continue;
                        else
                        continue;
                        else
                        continue;
                    else
                        continue;
                    else
                    continue;
                    else
                    continue;
                    else
                    continue;
                else
                    continue;
                else
                continue;
                else
                continue;
                else
                continue;
            else if(p[pixel[6]] < c_b)
                if(p[pixel[4]] < c_b)
                if(p[pixel[5]] < c_b)
                if(p[pixel[7]] < c_b)
                if(p[pixel[8]] < c_b)
                    if(p[pixel[9]] < c_b)
                    if(p[pixel[10]] < c_b)
                    if(p[pixel[11]] < c_b)
                    if(p[pixel[12]] < c_b)
                        if(p[pixel[13]] < c_b)
                        if(p[pixel[14]] < c_b)
                        if(p[pixel[3]] < c_b)
                        {}
                        else
                        if(p[pixel[15]] < c_b)
                            {}
                        else
                            continue;
                        else
                        continue;
                        else
                        continue;
                    else
                        continue;
                    else
                    continue;
                    else
                    continue;
                    else
                    continue;
                else
                    continue;
                else
                continue;
                else
                continue;
                else
                continue;
            else
                continue;
            else if(p[pixel[1]] < c_b)
            if(p[pixel[5]] > cb)
            if(p[pixel[6]] > cb)
                if(p[pixel[7]] > cb)
                if(p[pixel[8]] > cb)
                if(p[pixel[9]] > cb)
                if(p[pixel[10]] > cb)
                    if(p[pixel[11]] > cb)
                    if(p[pixel[12]] > cb)
                    if(p[pixel[13]] > cb)
                    if(p[pixel[14]] > cb)
                        if(p[pixel[15]] > cb)
                        {}
                        else
                        if(p[pixel[3]] > cb)
                        if(p[pixel[4]] > cb)
                        {}
                        else
                        continue;
                        else
                        continue;
                    else
                        if(p[pixel[2]] > cb)
                        if(p[pixel[3]] > cb)
                        if(p[pixel[4]] > cb)
                        {}
                        else
                        continue;
                        else
                        continue;
                        else
                        continue;
                    else
                    continue;
                    else
                    continue;
                    else
                    continue;
                else
                    continue;
                else
                continue;
                else
                continue;
                else
                continue;
            else
                continue;
            else if(p[pixel[5]] < c_b)
            if(p[pixel[4]] < c_b)
                if(p[pixel[6]] < c_b)
                if(p[pixel[7]] < c_b)
                if(p[pixel[8]] < c_b)
                if(p[pixel[9]] < c_b)
                    if(p[pixel[10]] < c_b)
                    if(p[pixel[11]] < c_b)
                    if(p[pixel[12]] < c_b)
                    if(p[pixel[3]] < c_b)
                        if(p[pixel[2]] < c_b)
                        {}
                        else
                        if(p[pixel[13]] < c_b)
                        if(p[pixel[14]] < c_b)
                        {}
                        else
                        continue;
                        else
                        continue;
                    else
                        if(p[pixel[13]] < c_b)
                        if(p[pixel[14]] < c_b)
                        if(p[pixel[15]] < c_b)
                        {}
                        else
                        continue;
                        else
                        continue;
                        else
                        continue;
                    else
                    continue;
                    else
                    continue;
                    else
                    continue;
                else
                    continue;
                else
                continue;
                else
                continue;
                else
                continue;
            else
                continue;
            else
            continue;
            else
            if(p[pixel[5]] > cb)
            if(p[pixel[6]] > cb)
                if(p[pixel[7]] > cb)
                if(p[pixel[8]] > cb)
                if(p[pixel[9]] > cb)
                if(p[pixel[10]] > cb)
                    if(p[pixel[11]] > cb)
                    if(p[pixel[12]] > cb)
                    if(p[pixel[13]] > cb)
                    if(p[pixel[14]] > cb)
                        if(p[pixel[15]] > cb)
                        {}
                        else
                        if(p[pixel[3]] > cb)
                        if(p[pixel[4]] > cb)
                        {}
                        else
                        continue;
                        else
                        continue;
                    else
                        if(p[pixel[2]] > cb)
                        if(p[pixel[3]] > cb)
                        if(p[pixel[4]] > cb)
                        {}
                        else
                        continue;
                        else
                        continue;
                        else
                        continue;
                    else
                    continue;
                    else
                    continue;
                    else
                    continue;
                else
                    continue;
                else
                continue;
                else
                continue;
                else
                continue;
            else
                continue;
            else if(p[pixel[5]] < c_b)
            if(p[pixel[4]] < c_b)
                if(p[pixel[6]] < c_b)
                if(p[pixel[7]] < c_b)
                if(p[pixel[8]] < c_b)
                if(p[pixel[9]] < c_b)
                    if(p[pixel[10]] < c_b)
                    if(p[pixel[11]] < c_b)
                    if(p[pixel[12]] < c_b)
                    if(p[pixel[13]] < c_b)
                        if(p[pixel[3]] < c_b)
                        if(p[pixel[2]] < c_b)
                        {}
                        else
                        if(p[pixel[14]] < c_b)
                        {}
                        else
                        continue;
                        else
                        if(p[pixel[14]] < c_b)
                        if(p[pixel[15]] < c_b)
                        {}
                        else
                        continue;
                        else
                        continue;
                    else
                        continue;
                    else
                    continue;
                    else
                    continue;
                    else
                    continue;
                else
                    continue;
                else
                continue;
                else
                continue;
                else
                continue;
            else
                continue;
            else
            continue;
            else if(p[pixel[0]] < c_b)
            if(p[pixel[1]] > cb)
            if(p[pixel[5]] > cb)
            if(p[pixel[4]] > cb)
                if(p[pixel[6]] > cb)
                if(p[pixel[7]] > cb)
                if(p[pixel[8]] > cb)
                if(p[pixel[9]] > cb)
                    if(p[pixel[10]] > cb)
                    if(p[pixel[11]] > cb)
                    if(p[pixel[12]] > cb)
                    if(p[pixel[3]] > cb)
                        if(p[pixel[2]] > cb)
                        {}
                        else
                        if(p[pixel[13]] > cb)
                        if(p[pixel[14]] > cb)
                        {}
                        else
                        continue;
                        else
                        continue;
                    else
                        if(p[pixel[13]] > cb)
                        if(p[pixel[14]] > cb)
                        if(p[pixel[15]] > cb)
                        {}
                        else
                        continue;
                        else
                        continue;
                        else
                        continue;
                    else
                    continue;
                    else
                    continue;
                    else
                    continue;
                else
                    continue;
                else
                continue;
                else
                continue;
                else
                continue;
            else
                continue;
            else if(p[pixel[5]] < c_b)
            if(p[pixel[6]] < c_b)
                if(p[pixel[7]] < c_b)
                if(p[pixel[8]] < c_b)
                if(p[pixel[9]] < c_b)
                if(p[pixel[10]] < c_b)
                    if(p[pixel[11]] < c_b)
                    if(p[pixel[12]] < c_b)
                    if(p[pixel[13]] < c_b)
                    if(p[pixel[14]] < c_b)
                        if(p[pixel[15]] < c_b)
                        {}
                        else
                        if(p[pixel[3]] < c_b)
                        if(p[pixel[4]] < c_b)
                        {}
                        else
                        continue;
                        else
                        continue;
                    else
                        if(p[pixel[2]] < c_b)
                        if(p[pixel[3]] < c_b)
                        if(p[pixel[4]] < c_b)
                        {}
                        else
                        continue;
                        else
                        continue;
                        else
                        continue;
                    else
                    continue;
                    else
                    continue;
                    else
                    continue;
                else
                    continue;
                else
                continue;
                else
                continue;
                else
                continue;
            else
                continue;
            else
            continue;
            else if(p[pixel[1]] < c_b)
            if(p[pixel[2]] > cb)
            if(p[pixel[6]] > cb)
                if(p[pixel[4]] > cb)
                if(p[pixel[5]] > cb)
                if(p[pixel[7]] > cb)
                if(p[pixel[8]] > cb)
                    if(p[pixel[9]] > cb)
                    if(p[pixel[10]] > cb)
                    if(p[pixel[11]] > cb)
                    if(p[pixel[12]] > cb)
                        if(p[pixel[13]] > cb)
                        if(p[pixel[3]] > cb)
                        {}
                        else
                        if(p[pixel[14]] > cb)
                        if(p[pixel[15]] > cb)
                            {}
                        else
                            continue;
                        else
                        continue;
                        else
                        continue;
                    else
                        continue;
                    else
                    continue;
                    else
                    continue;
                    else
                    continue;
                else
                    continue;
                else
                continue;
                else
                continue;
                else
                continue;
            else if(p[pixel[6]] < c_b)
                if(p[pixel[7]] < c_b)
                if(p[pixel[8]] < c_b)
                if(p[pixel[9]] < c_b)
                if(p[pixel[10]] < c_b)
                    if(p[pixel[11]] < c_b)
                    if(p[pixel[12]] < c_b)
                    if(p[pixel[13]] < c_b)
                    if(p[pixel[14]] < c_b)
                        if(p[pixel[15]] < c_b)
                        {}
                        else
                        if(p[pixel[3]] < c_b)
                        if(p[pixel[4]] < c_b)
                        if(p[pixel[5]] < c_b)
                            {}
                        else
                            continue;
                        else
                        continue;
                        else
                        continue;
                    else
                        continue;
                    else
                    continue;
                    else
                    continue;
                    else
                    continue;
                else
                    continue;
                else
                continue;
                else
                continue;
                else
                continue;
            else
                continue;
            else if(p[pixel[2]] < c_b)
            if(p[pixel[3]] > cb)
                if(p[pixel[15]] < c_b)
                if(p[pixel[7]] > cb)
                if(p[pixel[4]] > cb)
                if(p[pixel[5]] > cb)
                    if(p[pixel[6]] > cb)
                    if(p[pixel[8]] > cb)
                    if(p[pixel[9]] > cb)
                    if(p[pixel[10]] > cb)
                        if(p[pixel[11]] > cb)
                        if(p[pixel[12]] > cb)
                        if(p[pixel[13]] > cb)
                        if(p[pixel[14]] > cb)
                            {}
                        else
                            continue;
                        else
                        continue;
                        else
                        continue;
                        else
                        continue;
                    else
                        continue;
                    else
                    continue;
                    else
                    continue;
                    else
                    continue;
                else
                    continue;
                else
                continue;
                else if(p[pixel[7]] < c_b)
                if(p[pixel[8]] < c_b)
                if(p[pixel[9]] < c_b)
                    if(p[pixel[10]] < c_b)
                    if(p[pixel[11]] < c_b)
                    if(p[pixel[12]] < c_b)
                    if(p[pixel[13]] < c_b)
                        if(p[pixel[14]] < c_b)
                        {}
                        else
                        continue;
                    else
                        continue;
                    else
                    continue;
                    else
                    continue;
                    else
                    continue;
                else
                    continue;
                else
                continue;
                else
                continue;
                else
                if(p[pixel[4]] > cb)
                if(p[pixel[5]] > cb)
                if(p[pixel[6]] > cb)
                    if(p[pixel[7]] > cb)
                    if(p[pixel[8]] > cb)
                    if(p[pixel[9]] > cb)
                    if(p[pixel[10]] > cb)
                        if(p[pixel[11]] > cb)
                        if(p[pixel[12]] > cb)
                        if(p[pixel[13]] > cb)
                        if(p[pixel[14]] > cb)
                            {}
                        else
                            continue;
                        else
                        continue;
                        else
                        continue;
                        else
                        continue;
                    else
                        continue;
                    else
                    continue;
                    else
                    continue;
                    else
                    continue;
                else
                    continue;
                else
                continue;
                else
                continue;
            else if(p[pixel[3]] < c_b)
                if(p[pixel[4]] > cb)
                if(p[pixel[8]] > cb)
                if(p[pixel[5]] > cb)
                if(p[pixel[6]] > cb)
                    if(p[pixel[7]] > cb)
                    if(p[pixel[9]] > cb)
                    if(p[pixel[10]] > cb)
                    if(p[pixel[11]] > cb)
                        if(p[pixel[12]] > cb)
                        if(p[pixel[13]] > cb)
                        if(p[pixel[14]] > cb)
                        if(p[pixel[15]] > cb)
                            {}
                        else
                            continue;
                        else
                        continue;
                        else
                        continue;
                        else
                        continue;
                    else
                        continue;
                    else
                    continue;
                    else
                    continue;
                    else
                    continue;
                else
                    continue;
                else
                continue;
                else if(p[pixel[8]] < c_b)
                if(p[pixel[9]] < c_b)
                if(p[pixel[10]] < c_b)
                    if(p[pixel[11]] < c_b)
                    if(p[pixel[12]] < c_b)
                    if(p[pixel[13]] < c_b)
                    if(p[pixel[14]] < c_b)
                        if(p[pixel[15]] < c_b)
                        {}
                        else
                        continue;
                    else
                        continue;
                    else
                    continue;
                    else
                    continue;
                    else
                    continue;
                else
                    continue;
                else
                continue;
                else
                continue;
                else if(p[pixel[4]] < c_b)
                if(p[pixel[5]] < c_b)
                if(p[pixel[6]] < c_b)
                if(p[pixel[7]] < c_b)
                    if(p[pixel[8]] < c_b)
                    if(p[pixel[9]] < c_b)
                    if(p[pixel[10]] < c_b)
                    if(p[pixel[11]] < c_b)
                        {}
                    else
                        if(p[pixel[15]] < c_b)
                        {}
                        else
                        continue;
                    else
                    if(p[pixel[14]] < c_b)
                        if(p[pixel[15]] < c_b)
                        {}
                        else
                        continue;
                    else
                        continue;
                    else
                    if(p[pixel[13]] < c_b)
                    if(p[pixel[14]] < c_b)
                        if(p[pixel[15]] < c_b)
                        {}
                        else
                        continue;
                    else
                        continue;
                    else
                    continue;
                    else
                    if(p[pixel[12]] < c_b)
                    if(p[pixel[13]] < c_b)
                    if(p[pixel[14]] < c_b)
                        if(p[pixel[15]] < c_b)
                        {}
                        else
                        continue;
                    else
                        continue;
                    else
                    continue;
                    else
                    continue;
                else
                    if(p[pixel[11]] < c_b)
                    if(p[pixel[12]] < c_b)
                    if(p[pixel[13]] < c_b)
                    if(p[pixel[14]] < c_b)
                        if(p[pixel[15]] < c_b)
                        {}
                        else
                        continue;
                    else
                        continue;
                    else
                    continue;
                    else
                    continue;
                    else
                    continue;
                else
                if(p[pixel[10]] < c_b)
                    if(p[pixel[11]] < c_b)
                    if(p[pixel[12]] < c_b)
                    if(p[pixel[13]] < c_b)
                    if(p[pixel[14]] < c_b)
                        if(p[pixel[15]] < c_b)
                        {}
                        else
                        continue;
                    else
                        continue;
                    else
                    continue;
                    else
                    continue;
                    else
                    continue;
                else
                    continue;
                else
                if(p[pixel[9]] < c_b)
                if(p[pixel[10]] < c_b)
                    if(p[pixel[11]] < c_b)
                    if(p[pixel[12]] < c_b)
                    if(p[pixel[13]] < c_b)
                    if(p[pixel[14]] < c_b)
                        if(p[pixel[15]] < c_b)
                        {}
                        else
                        continue;
                    else
                        continue;
                    else
                    continue;
                    else
                    continue;
                    else
                    continue;
                else
                    continue;
                else
                continue;
                else
                if(p[pixel[8]] < c_b)
                if(p[pixel[9]] < c_b)
                if(p[pixel[10]] < c_b)
                    if(p[pixel[11]] < c_b)
                    if(p[pixel[12]] < c_b)
                    if(p[pixel[13]] < c_b)
                    if(p[pixel[14]] < c_b)
                        if(p[pixel[15]] < c_b)
                        {}
                        else
                        continue;
                    else
                        continue;
                    else
                    continue;
                    else
                    continue;
                    else
                    continue;
                else
                    continue;
                else
                continue;
                else
                continue;
            else
                if(p[pixel[7]] > cb)
                if(p[pixel[4]] > cb)
                if(p[pixel[5]] > cb)
                if(p[pixel[6]] > cb)
                    if(p[pixel[8]] > cb)
                    if(p[pixel[9]] > cb)
                    if(p[pixel[10]] > cb)
                    if(p[pixel[11]] > cb)
                        if(p[pixel[12]] > cb)
                        if(p[pixel[13]] > cb)
                        if(p[pixel[14]] > cb)
                        if(p[pixel[15]] > cb)
                            {}
                        else
                            continue;
                        else
                        continue;
                        else
                        continue;
                        else
                        continue;
                    else
                        continue;
                    else
                    continue;
                    else
                    continue;
                    else
                    continue;
                else
                    continue;
                else
                continue;
                else
                continue;
                else if(p[pixel[7]] < c_b)
                if(p[pixel[8]] < c_b)
                if(p[pixel[9]] < c_b)
                if(p[pixel[10]] < c_b)
                    if(p[pixel[11]] < c_b)
                    if(p[pixel[12]] < c_b)
                    if(p[pixel[13]] < c_b)
                    if(p[pixel[14]] < c_b)
                        if(p[pixel[15]] < c_b)
                        {}
                        else
                        continue;
                    else
                        continue;
                    else
                    continue;
                    else
                    continue;
                    else
                    continue;
                else
                    continue;
                else
                continue;
                else
                continue;
                else
                continue;
            else
            if(p[pixel[6]] > cb)
                if(p[pixel[4]] > cb)
                if(p[pixel[5]] > cb)
                if(p[pixel[7]] > cb)
                if(p[pixel[8]] > cb)
                    if(p[pixel[9]] > cb)
                    if(p[pixel[10]] > cb)
                    if(p[pixel[11]] > cb)
                    if(p[pixel[12]] > cb)
                        if(p[pixel[13]] > cb)
                        if(p[pixel[14]] > cb)
                        if(p[pixel[3]] > cb)
                        {}
                        else
                        if(p[pixel[15]] > cb)
                            {}
                        else
                            continue;
                        else
                        continue;
                        else
                        continue;
                    else
                        continue;
                    else
                    continue;
                    else
                    continue;
                    else
                    continue;
                else
                    continue;
                else
                continue;
                else
                continue;
                else
                continue;
            else if(p[pixel[6]] < c_b)
                if(p[pixel[7]] < c_b)
                if(p[pixel[8]] < c_b)
                if(p[pixel[9]] < c_b)
                if(p[pixel[10]] < c_b)
                    if(p[pixel[11]] < c_b)
                    if(p[pixel[12]] < c_b)
                    if(p[pixel[13]] < c_b)
                    if(p[pixel[14]] < c_b)
                        if(p[pixel[15]] < c_b)
                        {}
                        else
                        if(p[pixel[3]] < c_b)
                        if(p[pixel[4]] < c_b)
                        if(p[pixel[5]] < c_b)
                            {}
                        else
                            continue;
                        else
                        continue;
                        else
                        continue;
                    else
                        continue;
                    else
                    continue;
                    else
                    continue;
                    else
                    continue;
                else
                    continue;
                else
                continue;
                else
                continue;
                else
                continue;
            else
                continue;
            else
            if(p[pixel[5]] > cb)
            if(p[pixel[4]] > cb)
                if(p[pixel[6]] > cb)
                if(p[pixel[7]] > cb)
                if(p[pixel[8]] > cb)
                if(p[pixel[9]] > cb)
                    if(p[pixel[10]] > cb)
                    if(p[pixel[11]] > cb)
                    if(p[pixel[12]] > cb)
                    if(p[pixel[13]] > cb)
                        if(p[pixel[3]] > cb)
                        if(p[pixel[2]] > cb)
                        {}
                        else
                        if(p[pixel[14]] > cb)
                        {}
                        else
                        continue;
                        else
                        if(p[pixel[14]] > cb)
                        if(p[pixel[15]] > cb)
                        {}
                        else
                        continue;
                        else
                        continue;
                    else
                        continue;
                    else
                    continue;
                    else
                    continue;
                    else
                    continue;
                else
                    continue;
                else
                continue;
                else
                continue;
                else
                continue;
            else
                continue;
            else if(p[pixel[5]] < c_b)
            if(p[pixel[6]] < c_b)
                if(p[pixel[7]] < c_b)
                if(p[pixel[8]] < c_b)
                if(p[pixel[9]] < c_b)
                if(p[pixel[10]] < c_b)
                    if(p[pixel[11]] < c_b)
                    if(p[pixel[12]] < c_b)
                    if(p[pixel[13]] < c_b)
                    if(p[pixel[14]] < c_b)
                        if(p[pixel[15]] < c_b)
                        {}
                        else
                        if(p[pixel[3]] < c_b)
                        if(p[pixel[4]] < c_b)
                        {}
                        else
                        continue;
                        else
                        continue;
                    else
                        if(p[pixel[2]] < c_b)
                        if(p[pixel[3]] < c_b)
                        if(p[pixel[4]] < c_b)
                        {}
                        else
                        continue;
                        else
                        continue;
                        else
                        continue;
                    else
                    continue;
                    else
                    continue;
                    else
                    continue;
                else
                    continue;
                else
                continue;
                else
                continue;
                else
                continue;
            else
                continue;
            else
            continue;
            else
            if(p[pixel[4]] > cb)
            if(p[pixel[5]] > cb)
            if(p[pixel[6]] > cb)
                if(p[pixel[7]] > cb)
                if(p[pixel[8]] > cb)
                if(p[pixel[9]] > cb)
                if(p[pixel[10]] > cb)
                    if(p[pixel[11]] > cb)
                    if(p[pixel[12]] > cb)
                    if(p[pixel[3]] > cb)
                    if(p[pixel[2]] > cb)
                        if(p[pixel[1]] > cb)
                        {}
                        else
                        if(p[pixel[13]] > cb)
                        {}
                        else
                        continue;
                    else
                        if(p[pixel[13]] > cb)
                        if(p[pixel[14]] > cb)
                        {}
                        else
                        continue;
                        else
                        continue;
                    else
                    if(p[pixel[13]] > cb)
                        if(p[pixel[14]] > cb)
                        if(p[pixel[15]] > cb)
                        {}
                        else
                        continue;
                        else
                        continue;
                    else
                        continue;
                    else
                    continue;
                    else
                    continue;
                else
                    continue;
                else
                continue;
                else
                continue;
                else
                continue;
            else
                continue;
            else
            continue;
            else if(p[pixel[4]] < c_b)
            if(p[pixel[5]] < c_b)
            if(p[pixel[6]] < c_b)
                if(p[pixel[7]] < c_b)
                if(p[pixel[8]] < c_b)
                if(p[pixel[9]] < c_b)
                if(p[pixel[10]] < c_b)
                    if(p[pixel[11]] < c_b)
                    if(p[pixel[12]] < c_b)
                    if(p[pixel[3]] < c_b)
                    if(p[pixel[2]] < c_b)
                        if(p[pixel[1]] < c_b)
                        {}
                        else
                        if(p[pixel[13]] < c_b)
                        {}
                        else
                        continue;
                    else
                        if(p[pixel[13]] < c_b)
                        if(p[pixel[14]] < c_b)
                        {}
                        else
                        continue;
                        else
                        continue;
                    else
                    if(p[pixel[13]] < c_b)
                        if(p[pixel[14]] < c_b)
                        if(p[pixel[15]] < c_b)
                        {}
                        else
                        continue;
                        else
                        continue;
                    else
                        continue;
                    else
                    continue;
                    else
                    continue;
                else
                    continue;
                else
                continue;
                else
                continue;
                else
                continue;
            else
                continue;
            else
            continue;
            else
            continue;
                if(num_corners == rsize)
                {
                    rsize*=2;
                    ret_corners = (xy*)realloc(ret_corners, sizeof(xy)*rsize);
                }

                ret_corners[num_corners].x = x;
                ret_corners[num_corners].y = y;
                num_corners++;
            }
        
        *ret_num_corners = num_corners;
        return ret_corners;

    }

    #define Compare(X, Y) ((X)>=(Y))

    xy* nonmax_suppression(const xy* corners, const int* scores, int num_corners, int* ret_num_nonmax)
    {
        int num_nonmax=0;
        int last_row;
        int* row_start;
        int i, j;
        xy* ret_nonmax;
        const int sz = (int)num_corners; 

        /*Point above points (roughly) to the pixel above the one of interest, if there
        is a feature there.*/
        int point_above = 0;
        int point_below = 0;

        
        if(num_corners < 1)
        {
            *ret_num_nonmax = 0;
            return 0;
        }

        ret_nonmax = (xy*)malloc(num_corners * sizeof(xy));

        /* Find where each row begins
        (the corners are output in raster scan order). A beginning of -1 signifies
        that there are no corners on that row. */
        last_row = corners[num_corners-1].y;
        row_start = (int*)malloc((last_row+1)*sizeof(int));

        for(i=0; i < last_row+1; i++)
            row_start[i] = -1;
        
        {
            int prev_row = -1;
            for(i=0; i< num_corners; i++)
                if(corners[i].y != prev_row)
                {
                    row_start[corners[i].y] = i;
                    prev_row = corners[i].y;
                }
        }
        
        
        
        for(i=0; i < sz; i++)
        {
            int score = scores[i];
            xy pos = corners[i];
                
            /*Check left */
            if(i > 0)
                if(corners[i-1].x == pos.x-1 && corners[i-1].y == pos.y && Compare(scores[i-1], score))
                    continue;
                
            /*Check right*/
            if(i < (sz - 1))
                if(corners[i+1].x == pos.x+1 && corners[i+1].y == pos.y && Compare(scores[i+1], score))
                    continue;
                
            /*Check above (if there is a valid row above)*/
            if(pos.y != 0 && row_start[pos.y - 1] != -1) 
            {
                /*Make sure that current point_above is one
                row above.*/
                if(corners[point_above].y < pos.y - 1)
                    point_above = row_start[pos.y-1];
                
                /*Make point_above point to the first of the pixels above the current point,
                if it exists.*/
                for(; corners[point_above].y < pos.y && corners[point_above].x < pos.x - 1; point_above++)
                {}
                
                
                for(j=point_above; corners[j].y < pos.y && corners[j].x <= pos.x + 1; j++)
                {
                    int x = corners[j].x;
                    if( (x == pos.x - 1 || x ==pos.x || x == pos.x+1) && Compare(scores[j], score))
                        goto cont;
                }
                
            }
                
            /*Check below (if there is anything below)*/
            if(pos.y != last_row && row_start[pos.y + 1] != -1 && point_below < sz) /*Nothing below*/
            {
                if(corners[point_below].y < pos.y + 1)
                    point_below = row_start[pos.y+1];
                
                /* Make point below point to one of the pixels belowthe current point, if it
                exists.*/
                for(; point_below < sz && corners[point_below].y == pos.y+1 && corners[point_below].x < pos.x - 1; point_below++)
                {}

                for(j=point_below; j < sz && corners[j].y == pos.y+1 && corners[j].x <= pos.x + 1; j++)
                {
                    int x = corners[j].x;
                    if( (x == pos.x - 1 || x ==pos.x || x == pos.x+1) && Compare(scores[j],score))
                        goto cont;
                }
            }
            
            ret_nonmax[num_nonmax++] = corners[i];
            cont:
                ;
        }

        free(row_start);
        *ret_num_nonmax = num_nonmax;
        return ret_nonmax;
    }

    xy* fast(const byte* im, int xsize, int ysize, int stride, int b, int* ret_num_corners)
    {
        xy* corners;
        int num_corners;
        int* scores;
        static xy* nonmax;

        corners = fast12_detect(im, xsize, ysize, stride, b, &num_corners);
        scores = fast12_score(im, stride, corners, num_corners, b);
        nonmax = nonmax_suppression(corners, scores, num_corners, ret_num_corners);

        free(corners);
        free(scores);

        return nonmax;
    }


}