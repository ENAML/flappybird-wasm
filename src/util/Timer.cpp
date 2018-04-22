// #include <mach/mach_time.h>


// #include "util/package.hpp"

// uint32_t Timer::getTimeMS()
// {
//     const int64_t kOneMillion = 1000 * 1000;
//     static mach_timebase_info_data_t s_timebase_info;

//     if (s_timebase_info.denom == 0)
//     {
//         (void) mach_timebase_info(&s_timebase_info);
//     }

//     // mach_absolute_time() returns billionth of seconds,
//     // so divide by one million to get milliseconds
//     return (uint32_t)((mach_absolute_time() * s_timebase_info.numer) / (kOneMillion * s_timebase_info.denom));
// }

