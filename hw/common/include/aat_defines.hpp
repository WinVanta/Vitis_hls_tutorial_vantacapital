/*
 * Copyright 2021 Xilinx, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef AAT_DEFINES_H
#define AAT_DEFINES_H

#ifndef __SYNTHESIS__
#define _K_DEBUG_EN 1
#endif

#if _KDEBUG_EN == 1
#define KDEBUG(msg)                    \
    do                                 \
    {                                  \
        std::cout << msg << std::endl; \
    } while (0);
#else
#define KDEBUG(msg)
#endif

 #define NUM_SYMBOL (512)







#endif
