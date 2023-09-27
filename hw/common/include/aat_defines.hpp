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
//#define NUM_SYMBOL (1024)
//#define NUM_preRisk (1024) // for orderEntry
//#define NUM_DIM_HT (4) // for dimension hashtable memHandler
#define NUM_preRisk (1024) // for orderEntry
#define NUM_DIM_HT (2) // for dimension hashtable memHandler
#define banlistNb (512)


#define testOuchActive 0 //to compile HW must set 0 for tb set 1

#define PRICE_EXPONENT (0.00001)
#define START_TRADING (34200000000) // 09:30:00 in microseconds since midnight (9.5*60*60*1000000)
#define END_TRADING (57600000000)   // 16:00:00 in microseconds since midnight (16*60*60*1000000)

#define NUM_LEVEL (10)
#define LEVEL_UNSPECIFIED (-1)
#define NUM_TEST_SAMPLE (300)

enum ORDERBOOK_ACTIONCODES
{
    ORDERBOOK_NEW = 'N',
    ORDERBOOK_CHANGE = 'C',
    ORDERBOOK_DELETE = 'D',
};

enum ORDER_SIDES
{
    ORDER_BID = 'B',
    ORDER_ASK = 'A'
};

enum PRICINGENGINE_STRATEGIES
{
    STRATEGY_NONE = 0,
    STRATEGY_PEG = 1,
    STRATEGY_LIMIT = 2
};

enum ORDERENTRY_OPCODES
{
    ORDERENTRY_ADD = 0,
    ORDERENTRY_MODIFY,
    ORDERENTRY_DELETE
};

enum TCP_TXSTATUS_CODES
{
    TXSTATUS_SUCCESS = 0,
    TXSTATUS_CLOSED,
    TXSTATUS_OUTOFSPACE
};

enum TriggerEnum
{
	None = 0,
	Up100 = 1,
	AskMiss = 2,
	Down100 = 3,
	BidMiss = 4
};




#endif
