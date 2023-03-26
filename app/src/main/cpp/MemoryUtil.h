//
// Created by Sivin on 2023-03-26.
//

#ifndef LEARNNDK_MEMORYUTIL_H
#define LEARNNDK_MEMORYUTIL_H
#include <cstdint>
struct MemInfo{
    uint64_t system_totalram;
    uint64_t system_availableram;
    uint64_t system_freeram;
    uint64_t self_useram;
} ;

int get_system_meminfo(MemInfo *pInfo);

#endif //LEARNNDK_MEMORYUTIL_H