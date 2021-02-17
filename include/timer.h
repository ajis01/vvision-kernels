#pragma once

#include<iostream>

namespace cpu{
    struct Timer {

        uint64_t start, end;

        uint64_t rdtsc(){
            unsigned int lo,hi;
            __asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
            return ((uint64_t)hi << 32) | lo;
        }

        Timer(){
            start = rdtsc();
        }

        ~Timer(){
            end = rdtsc();
            std::cout << "Cycles completed " << end-start << " cycles" << std::endl;
        }

    };
}