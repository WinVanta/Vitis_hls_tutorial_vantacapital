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

#ifndef AAT_INTERFACES_H
#define AAT_INTERFACES_H
#define AP_INT_MAX_W (4096)
#define MEM_FULL_INDEX (0xFFFFFFFF)

#include <hls_stream.h>
#include <ap_int.h>
#include <ap_shift_reg.h>
#include "ap_axi_sdata.h"
#include "hls_stream.h"

#ifndef __SYNTHESIS__
#define _LH_DEBUG_EN 1
#endif

#if _LH_DEBUG_EN == 1
#define LH_DBG(msg)                    \
	do                                 \
	{                                  \
		std::cout << msg << std::endl; \
	} while (0);
#define ENDL() std::cout << std::endl;
#define CDEBUG_(msg) std::cout << #msg << " : " << msg << " ";
#define HDEBUG_(msg) std::cout << #msg << " : " << std::hex << msg << std::dec << " ";
#define XDEBUG_(msg) std::cout << #msg << " data : " << std::hex << msg.data << std::dec << " keep: " << msg.keep << " last: " << msg.last << " ";
#define CDEBUG(msg) std::cout << #msg << " : " << msg << std::endl;
#define HDEBUG(msg) std::cout << #msg << " : " << std::hex << msg << std::dec << std::endl;
#define XDEBUG(msg) std::cout << #msg << " data : " << std::hex << msg.data << std::dec << " keep: " << msg.keep << " last: " << msg.last << std::endl;

#define STRDEBUG(x, w)                        \
	std::cout << #x << " :";                  \
	for (int _ = 0; _ < w; _ += 8)            \
	{                                         \
		std::cout << (char)x.range(_ + 7, _); \
	}                                         \
	std::cout << "|" << std::endl;

#define SIZEDEBUG(stream)                        \
	if (stream.size() != 0)                      \
	{                                            \
		std::cout << #stream << " " << stream.size() << std::endl; \
	}

#else
#define LH_DBG(msg)
#define ENDL()
#define CDEBUG_(msg)
#define HDEBUG_(msg)
#define XDEBUG_(msg)
#define CDEBUG(msg)
#define HDEBUG(msg)
#define XDEBUG(msg)
#define DATAOUT(x)
#define STRDEBUG(x, w)
#define SIZEDEBUG(stream)
#endif

template <int T>
ap_uint<T> bitReverse(ap_uint<T> inputData)
{
#pragma HLS INLINE

	ap_uint<T> reversed;
	for (int i = 0; i < T; i += 1)
	{
#pragma HLS UNROLL
		reversed.range((T - 1) - i, (T - 1) - i) = inputData.range(i, i);
	}

	return reversed;
}

template <int T>
ap_uint<T> byteReverse(ap_uint<T> inputData)
{
#pragma HLS INLINE

	ap_uint<T> reversed;
	for (int i = 0; i < T; i += 8)
	{
#pragma HLS UNROLL
		reversed.range((T - 1) - i, T - 8 - i) = inputData.range(i + 7, i);
	}

	return reversed;
}

typedef ap_uint<1> ap_uint1_t;
typedef ap_uint<8> ap_uint8_t;
typedef ap_uint<16> ap_uint16_t;
typedef ap_uint<32> ap_uint32_t;
typedef ap_uint<64> ap_uint64_t;
typedef ap_uint<256> ap_uint256_t;
typedef ap_int<8> ap_int8_t;
typedef ap_int<32> ap_int32_t;
typedef ap_int<64> ap_int64_t;

typedef ap_uint<112> ap_uint112_t;

typedef struct nasdaqInternalPack_t
{
	ap_uint<1024> data;
} nasdaqInternalPack_t;

typedef struct stateMessage_t
{
	const ap_uint<160> CLOSE_D = ap_uint<160>			("434c4f53455f4420202020202020202020202020",16);
	const ap_uint<160> PREOPEN1_E = ap_uint<160>		("5052452d4f50454e315f45202020202020202020",16);
	const ap_uint<160> PREOPEN_E = ap_uint<160> 		("5052452d4f50454e5f4520202020202020202020",16);
	const ap_uint<160> OPEN1_E = ap_uint<160>			("4f50454e315f4520202020202020202020202020",16);
	const ap_uint<160> OPEN_E = ap_uint<160>			("4f50454e5f452020202020202020202020202020",16);
	const ap_uint<160> INTERMISSION_E = ap_uint<160>	("494e5445524d495353494f4e5f45202020202020",16);
	const ap_uint<160> PREOPEN2_E = ap_uint<160>		("5052452d4f50454e325f45202020202020202020",16);
	const ap_uint<160> OPEN2_E = ap_uint<160>			("4f50454e325f4520202020202020202020202020",16);
	const ap_uint<160> PRECLOSE_E = ap_uint<160>		("5052452d434c4f53455f45202020202020202020",16);
	const ap_uint<160> OFFHOUR_E = ap_uint<160>			("4f46462d484f55525f4520202020202020202020",16);
	const ap_uint<160> MARKETCLOSE_E = ap_uint<160>		("4d41524b4554434c4f53455f4520202020202020",16);
	const ap_uint<160> HALT_E = ap_uint<160>			("48414c545f452020202020202020202020202020",16);
	const ap_uint<160> SUSPEND_E = ap_uint<160>			("53555350454e445f452020202020202020202020",16);
	const ap_uint<160> FULLHALT_E = ap_uint<160>		("46554c4c48414c545f4520202020202020202020",16);
}	stateMessage_t;

typedef struct OuchOrderAccepted_t
{ /// message Type: 'A'      Total Length: 848
	ap_uint8_t messageType;
	ap_uint16_t symbolIndex;
	ap_uint8_t reserve;
	ap_uint8_t protocol;
	ap_uint8_t connNum;
	ap_uint8_t splitId;
	ap_uint32_t sequenceNumber;
	ap_uint64_t timeStamp;
	ap_uint112_t orderToken; /// char[14]
	ap_uint64_t orderTokenLong;
	ap_uint32_t orderBookId;
	ap_uint8_t side;
	ap_uint64_t orderId;
	ap_uint64_t quantity;
	ap_int32_t price;
	ap_uint8_t timeInForce;
	ap_uint8_t openClose;
	ap_uint<80> clientAccount; /// char[10]
	ap_uint8_t orderState;
	ap_uint<120> customerInfo; /// char[15]
	// ap_uint256_t exchangeInfo;   /// char[32] /// NOT USED
	ap_uint64_t displayQuantity;
	ap_uint<80> orderInfo; /// char[10]
	ap_int32_t crossingKey;
	ap_uint8_t orderType;
	ap_uint8_t triggerType;
	// ap_uint8_t triggerPriceType; // NOT USED
	// ap_uint32_t triggerOrderBookId; // NOT USED
	// ap_uint32_t triggerPrice; // NOT USED
	// ap_uint32_t triggerSessionTypeId; // NOT USED
	ap_uint32_t validTillData;
} OuchOrderAccepted_t;

typedef struct OuchOrderRejected_t
{ /// message Type: 'J'      Total Length: 232
	ap_uint8_t messageType;
	ap_uint16_t symbolIndex;
	ap_uint8_t reserve;
	ap_uint8_t protocol;
	ap_uint8_t connNum;
	ap_uint8_t splitId;
	ap_uint32_t sequenceNumber;
	ap_uint64_t timeStamp;
	ap_uint112_t orderToken; /// char[14]
	ap_uint64_t orderTokenLong;
	ap_int32_t rejectCode;
} OuchOrderRejected_t;

typedef struct OuchOrderCanceled_t
{ /// message Type: 'C'      Total Length: 312
	ap_uint8_t messageType;
	ap_uint16_t symbolIndex;
	ap_uint8_t reserve;
	ap_uint8_t protocol;
	ap_uint8_t connNum;
	ap_uint8_t splitId;
	ap_uint32_t sequenceNumber;
	ap_uint64_t timeStamp;
	ap_uint112_t orderToken; /// char[14]
	ap_uint64_t orderTokenLong;
	ap_uint32_t orderBookId;
	ap_uint8_t side;
	ap_uint64_t orderId;
	ap_uint8_t reason;
} OuchOrderCanceled_t;

typedef struct OuchOrderReplaced_t
{ /// message Type: 'U'      Total Length: 1024
	ap_uint8_t messageType;
	ap_uint16_t symbolIndex;
	ap_uint8_t reserve;
	ap_uint8_t protocol;
	ap_uint8_t connNum;
	ap_uint8_t splitId;
	ap_uint32_t sequenceNumber;
	ap_uint64_t timeStamp;
	ap_uint112_t replacementOrderToken; /// char[14]
	ap_uint64_t replacementOrderTokenLong;
	ap_uint112_t previousOrderToken; /// char[14]
	ap_uint64_t previousOrderTokenLong;
	ap_uint32_t orderBookId;
	ap_uint8_t side;
	ap_uint64_t orderId;
	ap_uint64_t quantity;
	ap_int32_t price;
	ap_uint8_t timeInForce;
	ap_uint8_t openClose;
	ap_uint<80> clientAccount;
	ap_uint8_t orderState;
	ap_uint<120> customerInfo; /// char[15]
	// ap_uint256_t exchangeInfo;    /// char[32]    // NOT USED
	ap_uint8_t triggerType;
	ap_uint64_t displayQuantity;
	ap_uint<80> orderInfo; /// char[10]
	ap_int32_t crossingKey;
	ap_uint8_t orderType;
	// ap_uint8_t triggerPriceType; // NOT USED
	// ap_uint32_t triggerOrderBookId;   // NOT USED
	// ap_uint32_t triggerPrice;   // NOT USED
	// ap_uint32_t triggerSessionTypeId;   // NOT USED
	ap_uint32_t validTillData;
	ap_uint64_t tradedQuantity;
} OuchOrderReplaced_t;

typedef struct OuchOrderExecuted_t
{ /// message Type: 'E'      Total Length: 400
	ap_uint8_t messageType;
	ap_uint16_t symbolIndex;
	ap_uint8_t reserve;
	ap_uint8_t protocol;
	ap_uint8_t connNum;
	ap_uint8_t splitId;
	ap_uint32_t sequenceNumber;
	ap_uint64_t timeStamp;
	ap_uint112_t orderToken; /// char[14]
	ap_uint64_t orderTokenLong;
	ap_uint32_t orderBookId;
	ap_uint64_t tradedQuantity;
	ap_int32_t tradedPrice;
	ap_uint64_t matchId;
	ap_uint32_t comboGroupId;
	ap_uint8_t dealSource;
	ap_uint8_t side;
} OuchOrderExecuted_t;

typedef struct ItchIndexPrice_t
{ /// message Type: 'J'
	ap_uint8_t messageType;
	ap_uint16_t symbolIndex;
	ap_uint8_t reserve;
	ap_uint8_t protocol;
	ap_uint8_t connNum;
	ap_uint8_t splitId;
	ap_uint32_t sequenceNumber;
	ap_uint32_t second;
	ap_uint32_t nanos;
	ap_uint32_t orderBookId;
	ap_uint64_t value;
	ap_uint64_t highValue;
	ap_uint64_t lowValue;
	ap_uint64_t openValue;
	ap_uint64_t tradedVolume;
	ap_uint64_t tradedValue;
	ap_uint64_t change;
	ap_uint32_t changePercent;
	ap_uint64_t previousClose;
	ap_uint64_t close;

} ItchIndexPrice_t;

typedef struct ItchSecondsMessage_t
{ /// message Type: 'T'
	ap_uint8_t messageType;
	ap_uint16_t symbolIndex;
	ap_uint8_t reserve;
	ap_uint8_t protocol;
	ap_uint8_t connNum;
	ap_uint8_t splitId;
	ap_uint32_t sequenceNumber;
	ap_uint32_t second;

} ItchSecondsMessage_t;

typedef struct ItchMarketByPriceMessage_t
{
	ap_uint8_t messageType;
	ap_uint16_t symbolIndex;
	ap_uint8_t reserve;
	ap_uint8_t protocol;
	ap_uint8_t connNum;
	ap_uint8_t splitId;
	ap_uint32_t sequenceNumber;
	ap_uint32_t second;
	ap_uint32_t nanos;
	ap_uint32_t orderBookId;
	ap_uint8_t maximumLevel;
	ap_uint8_t levelUpdateAction;
	ap_uint8_t side;
	ap_uint8_t level;
	ap_int32_t price;
	ap_uint64_t quantity;
	ap_uint<4> numberOfDeletes;
	ap_uint<4> hasRemaining;
} ItchMarketByPriceMessage_t;

typedef struct ItchPriceLimitMessage_t
{ /// message Type: 'l'
	ap_uint8_t messageType;
	ap_uint16_t symbolIndex;
	ap_uint8_t reserve;
	ap_uint8_t protocol;
	ap_uint8_t connNum;
	ap_uint8_t splitId;
	ap_uint32_t sequenceNumber;
	ap_uint32_t second;
	ap_uint32_t nanos;
	ap_uint32_t orderBookId;
	ap_int32_t upperLimit;
	ap_int32_t lowerLimit;

} ItchPriceLimitMessage_t;

typedef struct ItchTickSizeTableMessage_t
{ /// message Type: 'L'
	ap_uint8_t messageType;
	ap_uint16_t symbolIndex;
	ap_uint8_t reserve;
	ap_uint8_t protocol;
	ap_uint8_t connNum;
	ap_uint8_t splitId;
	ap_uint32_t sequenceNumber;
	ap_uint32_t second;
	ap_uint32_t nanos;
	ap_uint32_t orderBookId;
	ap_int64_t tickSize;
	ap_int32_t priceFrom;
	ap_int32_t priceTo;

} ItchTickSizeTableMessage_t;

typedef struct priceLimitOrdMessage_t
{
	ap_uint16_t symbolIndex;
	ap_uint16_t decimalInPrice;
	ap_uint32_t orderBookId;
	ap_int32_t upperLimit;
	ap_int32_t lowerLimit;

} priceLimitOrdMessage_t;

typedef struct priceLimitOrdSymbolIndex_t
{
	ap_uint32_t orderBookId;
	ap_int32_t upperLimit;
	ap_int32_t lowerLimit;
	ap_uint16_t decimalInPrice;

} priceLimitOrdSymbolIndex_t;

typedef struct tickerMsgOrderEntryMessage_t
{
	ap_uint16_t symbolIndex;
	ap_uint16_t decimalInPrice;
	ap_uint32_t price;
	ap_uint32_t orderBookId;
} tickerMsgOrderEntryMessage_t;

typedef struct ItchOrderBookStateMessage_t
{ /// message Type: 'O'
	ap_uint8_t messageType;
	ap_uint16_t symbolIndex;
	ap_uint8_t reserve;
	ap_uint8_t protocol;
	ap_uint8_t connNum;
	ap_uint8_t splitId;
	ap_uint32_t sequenceNumber;
	ap_uint32_t second;
	ap_uint32_t nanos;
	ap_uint32_t orderBookId;
	ap_uint<160> stateName; /// char[20]

} ItchOrderBookStateMessage_t;

typedef struct ItchHaltInformationMessage_t
{ /// message Type: 'l'
	ap_uint8_t messageType;
	ap_uint16_t symbolIndex;
	ap_uint8_t reserve;
	ap_uint8_t protocol;
	ap_uint8_t connNum;
	ap_uint8_t splitId;
	ap_uint32_t sequenceNumber;
	ap_uint32_t second;
	ap_uint32_t nanos;
	ap_uint32_t orderBookId;
	ap_uint<160> instrumentState; /// char[20]

} ItchHaltInformationMessage_t;

typedef struct ItchTradeTickerMessage_t
{ /// message Type: 'i'
	ap_uint8_t messageType;
	ap_uint16_t symbolIndex;
	ap_uint8_t reserve;
	ap_uint8_t protocol;
	ap_uint8_t connNum;
	ap_uint8_t splitId;
	ap_uint32_t sequenceNumber;
	ap_uint32_t second;
	ap_uint32_t nanos;
	ap_uint32_t orderBookId;
	ap_uint64_t dealId;
	ap_uint8_t dealSource;
	ap_int32_t price;
	ap_uint64_t quantity;
	ap_uint64_t dealDateTime;
	ap_uint8_t action;
	ap_uint8_t aggressor; //// B = Bid, A = Ask
	ap_uint16_t tradeReportCode;

} ItchTradeTickerMessage_t;

typedef struct peTradeTickerMsg_t //for princing engine onTradeEvent @by Win
{
	ap_uint8_t messageType;
	ap_uint16_t symbolIndex;
	ap_uint32_t sequenceNumber;
	ap_uint32_t second;
	ap_uint32_t nanos;
	ap_uint32_t orderBookId;
	ap_uint64_t dealId;
	ap_int32_t price;
	ap_uint64_t quantity;
	ap_uint64_t dealDateTime;
	ap_uint8_t aggressor; //// B = Bid, A = Ask
	ap_uint32_t lastOrderStateSecond;
	ap_uint32_t lastLimitOrderBookSecond;
	ap_uint32_t lastLimitOrderBookNanos;
	ap_uint8_t tradableCalByStateMsg;
	ap_uint32_t currentMs;
	ap_uint32_t Ul;
	ap_uint32_t Dw;
	ap_uint32_t isCall;
	ap_uint8_t trigger;
	ap_int32_t triggerPrice;


}peTradeTickerMsg_t;

typedef struct peLmtOrdBookMsg_t //for princing engine onMarket by lvl event @by Win
{
	ap_uint8_t messageType;
	ap_uint16_t symbolIndex;
	ap_uint32_t sequenceNumber;
	ap_uint32_t second;
	ap_uint32_t nanos;
	ap_uint32_t orderBookId;
	ap_int32_t askPrice0;
	ap_int32_t askPrice1;
	ap_int32_t bidPrice0;
	ap_int32_t bidPrice1;
	ap_uint64_t askVol0;
	ap_uint64_t askVol1;
	ap_uint64_t bidVol0;
	ap_uint64_t bidVol1;
	ap_uint32_t lastOrderStateSecond;
	ap_uint32_t currentMs;
	ap_uint8_t trigger;
	ap_int32_t triggerPrice;
	ap_uint32_t Ul;
	ap_uint32_t Dw;
	ap_uint32_t isCall;

}peLmtOrdBookMsg_t;


typedef struct peLmtOrdBookTime_t //for princing engine onMarket by lvl event @by Win
{
	ap_uint32_t second;
	ap_uint32_t nanos;

}peLmtOrdBookTime_t;


typedef struct ItchLimitOrderBookMessage_t
{ /// message Type: 'o'
	ap_uint8_t messageType;
	ap_uint16_t symbolIndex;
	ap_uint8_t reserve;
	ap_uint8_t protocol;
	ap_uint8_t connNum;
	ap_uint8_t splitId;
	ap_uint32_t sequenceNumber;
	ap_uint32_t second;
	ap_uint32_t nanos;
	ap_uint32_t orderBookId;
	ap_int<128> bidPrice;
	ap_uint256_t bidQuantity;
	ap_int<128> askPrice;
	ap_uint256_t askQuantity;
} ItchLimitOrderBookMessage_t;

typedef struct ItchIndexPriceMessage_t
{ /// message Type: 'J'
	ap_uint8_t messageType;
	ap_uint16_t symbolIndex;
	ap_uint8_t reserve;
	ap_uint8_t protocol;
	ap_uint8_t connNum;
	ap_uint8_t splitId;
	ap_uint32_t sequenceNumber;
	ap_uint32_t second;
	ap_uint32_t nanos;
	ap_uint32_t orderBookId;
	ap_int64_t value;
	ap_int64_t highValue;
	ap_int64_t lowValue;
	ap_int64_t openValue;
	ap_uint64_t tradedVolume;
	ap_uint64_t tradedValue;
	ap_int64_t change;
	ap_int32_t changePercent;
	ap_int64_t previousClose;
	ap_int64_t close;
	ap_uint64_t timeStamp;
} ItchIndexPriceMessage_t;

typedef struct ItchEquilibriumPriceMessage_t
{ /// message Type: 'Z'
	ap_uint8_t messageType;
	ap_uint16_t symbolIndex;
	ap_uint8_t reserve;
	ap_uint8_t protocol;
	ap_uint8_t connNum;
	ap_uint8_t splitId;
	ap_uint32_t sequenceNumber;
	ap_uint32_t second;
	ap_uint32_t nanos;
	ap_uint32_t orderBookId;
	ap_uint64_t bidQuantity;
	ap_uint64_t askQuantity;
	ap_int32_t equilibriumPrice;
} ItchEquilibriumPriceMessage_t;

typedef struct ItchMarketStatisticMessage_t
{ /// message Type: 'g'
	ap_uint8_t messageType;
	ap_uint16_t symbolIndex;
	ap_uint8_t reserve;
	ap_uint8_t protocol;
	ap_uint8_t connNum;
	ap_uint8_t splitId;
	ap_uint32_t sequenceNumber;
	ap_uint32_t second;
	ap_uint32_t nanos;
	ap_uint<96> marketStatsId;
	ap_uint<24> currency;
	ap_uint64_t marketStatsTime;
	ap_uint32_t totalTrade;
	ap_uint64_t totalQuantity;
	ap_uint64_t totalValue;
	ap_uint64_t upQuantity;
	ap_uint64_t downQuantity;
	ap_uint64_t noChangeVolume;
	ap_uint32_t upShares;
	ap_uint32_t downShares;
	ap_uint32_t noChangeShares;
} ItchMarketStatisticMessage_t;

typedef struct ItchiNAVMessage_t
{ /// message Type: 'f'
	ap_uint8_t messageType;
	ap_uint16_t symbolIndex;
	ap_uint8_t reserve;
	ap_uint8_t protocol;
	ap_uint8_t connNum;
	ap_uint8_t splitId;
	ap_uint32_t sequenceNumber;
	ap_uint32_t second;
	ap_uint32_t nanos;
	ap_uint32_t orderBookId;
	ap_uint32_t iNAV;
	ap_uint32_t change;
	ap_uint32_t percentChange;
	ap_uint64_t timeStamp;
} ItchiNAVMessage_t;

typedef struct ItchTradeStatisticMessage_t
{ /// message Type: 'I'
	ap_uint8_t messageType;
	ap_uint16_t symbolIndex;
	ap_uint8_t reserve;
	ap_uint8_t protocol;
	ap_uint8_t connNum;
	ap_uint8_t splitId;
	ap_uint32_t sequenceNumber;
	ap_uint32_t second;
	ap_uint32_t nanos;
	ap_uint32_t orderBookId;
	ap_uint32_t openPrice;
	ap_uint32_t highPrice;
	ap_uint32_t lowPrice;
	ap_uint32_t lastPrice;
	ap_uint32_t lastAuctionPrice;
	ap_uint64_t turnoverQuantity;
	ap_uint64_t reportedTurnoverQuantity;
	ap_uint64_t turnoverValue;
	ap_uint64_t reportedTurnoverValue;
	ap_uint32_t averagePrice;
	ap_uint64_t totalNumberOfTrades;
} ItchTradeStatisticMessage_t;

typedef struct ItchOrderBookDirectoryMessage_t
{ /// message Type: 'R'
	ap_uint8_t messageType;
	ap_uint16_t symbolIndex;
	ap_uint32_t nanos;
	ap_uint32_t orderBookId;
	ap_uint256_t symbol;		  /// char[32]
	ap_uint256_t longName;		  /// char[32]
	ap_uint<96> isin;			  /// char[12]
	ap_uint<24> financialProduct; /// char[3]
	ap_uint<24> tradingCurrency;  /// char[3]
	ap_uint16_t decimalInPrice;
	ap_uint16_t decimalInNominalValue;
	ap_uint32_t roundLotSize;
	ap_uint64_t nominalValue;
	ap_uint8_t numberOfLegs;
	ap_uint<48> underlyingName; /// char[6]
	ap_uint32_t underlying;
	ap_uint32_t underlyingOrderBookId;
	ap_int32_t strikePrice;
	ap_uint32_t expirationDate;
	ap_uint16_t decimalsInStrikePrice;
	ap_uint8_t optionType;
	ap_uint8_t exchangeCode;
	ap_uint8_t marketCode;
	ap_int64_t priceQuotationFactor;
	ap_uint256_t corporateActionCode; /// char[32]
	ap_uint256_t notificationSign;	  /// char[32]
	ap_uint256_t otherSign;			  /// char[32]
	ap_uint8_t allowNVDR;
	ap_uint8_t allowShortSell;
	ap_uint8_t allowShortSellOnNVDR;
	ap_int64_t parValue;
	ap_uint32_t FirstTradingDate;
	ap_uint32_t FirstTradingTime;
	ap_uint32_t LastTradingDate;
	ap_uint32_t LastTradingTime;
	ap_uint256_t marketSegment; /// char[32]
	ap_uint8_t physicalDelivery;
	ap_int32_t contractSize;
	ap_uint32_t sectorCode;		 /// char[4]
	ap_uint256_t originatesFrom; /// char[32]
	ap_uint8_t status;
	ap_uint16_t modifier;
	ap_uint32_t notationDate;
	ap_uint16_t decimalsInContractSize;
} ItchOrderBookDirectoryMessage_t;

typedef struct ItchOtherMessage_t
{ /// message Type: 'Z'
	ap_uint8_t messageType;
	ap_uint16_t symbolIndex;
	ap_uint8_t reserve;
	ap_uint8_t protocol;
	ap_uint8_t connNum;
	ap_uint8_t splitId;
	ap_uint32_t sequenceNumber;
	ap_uint32_t second;
	ap_uint32_t nanos;
	ap_uint256_t word;
} ItchOtherMessage_t;

typedef struct ItchOrderBookDirectoryCompact_t
{ /// message Type: 'R'
	ap_uint8_t messageType;
	ap_uint16_t symbolIndex;
	ap_uint8_t reserve;
	ap_uint8_t protocol;
	ap_uint8_t connNum;
	ap_uint8_t splitId;
	ap_uint32_t sequenceNumber;
	ap_uint32_t second;
	ap_uint32_t nanos;
	ap_uint32_t orderBookId;
	ap_uint256_t symbol;		  /// char[32]
	ap_uint256_t longName;		  /// char[32]
	ap_uint<24> financialProduct; /// char[3]
	ap_uint16_t decimalInPrice;
	ap_uint32_t roundLotSize;
	ap_uint8_t marketCode;
	ap_uint<72> corporateActionCode;
	ap_uint<72> notificationSign;
	ap_uint<72> otherSign;
	ap_uint8_t allowNVDR;
	ap_uint8_t allowShortSell;
	ap_uint8_t allowShortSellOnNVDR;
} ItchOrderBookDirectoryCompact_t;

typedef struct ItchGlimpseEndMessage_t
{ /// message Type: 'R'
	ap_uint8_t messageType;
	ap_uint16_t symbolIndex;
	ap_uint8_t reserve;
	ap_uint8_t protocol;
	ap_uint8_t connNum;
	ap_uint8_t splitId;
	ap_uint32_t sequenceNumber;
	ap_uint32_t second;
	ap_uint32_t nanos;
	ap_uint<160> glimpseEnd;
} ItchGlimpseEndMessage_t;

typedef struct orderBookOperation_t
{
	ap_uint64_t timestamp;
	ap_uint8_t opCode;
	ap_uint8_t symbolIndex;
	ap_uint32_t orderId;
	ap_uint32_t orderCount;
	ap_uint32_t quantity;
	ap_uint32_t price;
	ap_uint8_t direction;
	ap_int8_t level;
} orderBookOperation_t;

// TODO: 56b timestamp to pack within 1024b total, review if 64b required
typedef struct orderBookResponse_t
{
	ap_uint<56> timestamp;
	ap_uint8_t symbolIndex;
	ap_uint<160> bidCount;
	ap_uint<160> bidPrice;
	ap_uint<160> bidQuantity;
	ap_uint<160> askCount;
	ap_uint<160> askPrice;
	ap_uint<160> askQuantity;
} orderBookResponse_t;

typedef struct orderBookResponseVerify_t
{
	ap_uint8_t symbolIndex;
	ap_uint32_t bidCount[NUM_LEVEL];
	ap_uint32_t bidPrice[NUM_LEVEL];
	ap_uint32_t bidQuantity[NUM_LEVEL];
	ap_uint32_t askCount[NUM_LEVEL];
	ap_uint32_t askPrice[NUM_LEVEL];
	ap_uint32_t askQuantity[NUM_LEVEL];
} orderBookResponseVerify_t;

typedef struct ouchMsg_t // Win OrderEntry
{
	ap_uint8_t lgNdMSB;
	ap_uint8_t lgNdLSB;
	ap_uint8_t seqUnq;
	ap_uint8_t msgType;
	ap_uint64_t timeSp;
	ap_uint<112> extOrdToken;
	ap_uint<112> repOrdTokenID;
	ap_uint32_t ordBookID;
	ap_uint8_t side;
	ap_uint64_t ordID;
	ap_uint64_t qty;
	ap_uint32_t price;
	ap_uint8_t timeInFc;
	ap_uint8_t opCl;
	ap_uint<80> account;
	ap_uint8_t ordSte;
	ap_uint<120> custInfo;
	ap_uint<256> exInfo;
	ap_uint64_t disQty;
	ap_uint<80> ordInfo;
	ap_uint32_t crosKey;
	ap_uint8_t ordTyp;
	ap_uint8_t trigTy;
	ap_uint8_t trigPcTy;
	ap_uint32_t trigOrdBoID;
	ap_uint32_t trigPc;
	ap_uint32_t trigSesTyID;
	ap_uint32_t valTdata;
	ap_uint8_t reason;
	ap_uint32_t rejCode;
	ap_uint64_t trdQty;
	ap_uint32_t trdPrice;
	ap_uint64_t matchID;
	ap_uint32_t cmboGrpID;
	ap_uint8_t dealSrc;
} ouchMsgA_t;

typedef struct orderEntryOperation_t // send from OrderBook to OrderEntry
{
	ap_uint<8> seqUnq;
	ap_uint<8> msgType;
	ap_uint<8> NVDR;
	ap_uint<8> side;
	ap_uint<8> timeInFc;
	ap_uint<8> opCl;
	ap_uint<8> ordTyp;
	ap_uint<8> trigTy;
	ap_uint<8> trigPcTy;
	ap_uint<16> symbolIndex;
	ap_uint<32> ordBookID;
	ap_uint<32> price;
	ap_uint<32> trigOrdBoID;
	ap_uint<32> trigPc;
	ap_uint<32> trigSesTyID;
	ap_uint<32> valTdata;
	ap_uint<64> qty;
	ap_uint<64> disQty;
	ap_uint<64> dealID;
	ap_uint<64> ordID;
	ap_uint<80> ordInfo;
	ap_uint<112> extOrdToken;
	ap_uint<112> repOrdToken;
	ap_uint<120> custInfo;

} orderEntryOperation_t;

typedef struct orderEntryOperationFIFO_t // send from OrderBook to OrderEntry
{
	ap_uint<8> seqUnq;
	ap_uint<8> msgType;
	ap_uint<8> NVDR;
	ap_uint<8> side;
	ap_uint<8> timeInFc;
	ap_uint<8> opCl;
	ap_uint<8> ordTyp;
	ap_uint<8> trigTy;
	ap_uint<8> trigPcTy;
	ap_uint<16> symbolIndex;
	ap_uint<32> ordBookID;
	ap_uint<32> price;
	ap_uint<32> trigOrdBoID;
	ap_uint<32> trigPc;
	ap_uint<32> trigSesTyID;
	ap_uint<32> valTdata;
	ap_uint<64> qty;
	ap_uint<64> disQty;
	ap_uint<64> dealID;
	ap_uint<64> ordID;
	ap_uint<80> ordInfo;
	ap_uint<112> extOrdToken;
	ap_uint<112> repOrdToken;
	ap_uint<120> custInfo;

} orderEntryOperationFIFO_t;

typedef struct orderEntryOperationEncode_t // send from OrderEntry to CU
{
	ap_uint8_t sideOrderInfo;  // attach price order Info for Replace Volume check
	ap_uint8_t lgNdMSB;
	ap_uint8_t lgNdLSB;
	ap_uint8_t seqUnq;
	ap_uint8_t msgType;
	ap_uint8_t side;
	ap_uint8_t timeInFc;
	ap_uint8_t opCl;
	ap_uint8_t invTy;
	ap_uint8_t ordTyp;
	ap_uint8_t trigTy;
	ap_uint8_t trigPcTy;
	ap_uint8_t NVDR;
	ap_uint16_t symbolIndex;
	ap_uint32_t ordBookID;
	ap_uint32_t price;
	ap_uint32_t crosKey;
	ap_uint32_t trigOrdBoID;
	ap_uint32_t trigPc;
	ap_uint32_t trigSesTyID;
	ap_uint32_t valTdata;
	ap_uint64_t outStandingOrderInfo; // attach price order Info for Replace Volume check
	ap_uint64_t qty;
	ap_uint64_t disQty;
	ap_uint64_t dealID;
	ap_uint64_t ordID;
	ap_uint<80> ordInfo;
	ap_uint<80> account;
	ap_uint<112> extOrdToken;
	ap_uint<112> repOrdToken;
	ap_uint<120> custInfo;
	ap_uint<256> exInfo;
	ap_int8_t rejectCode = 0;
	ap_int32_t rejectInt1 = 0;
	ap_int32_t rejectInt2 = 0;
	ap_int64_t rejectLong = 0;
	ap_uint<160> reject160b = 0;

} orderEntryOperationEncode_t;

typedef struct orderCheck_t
{
		ap_uint<8> msgType;
		ap_uint<8> side;
		ap_uint<32> price;
		ap_uint<32> ordBookID;
		ap_uint<64> dealID;
		ap_uint<64> ordID;
		ap_uint<64> qty;
		ap_uint<112> extOrdToken;
		ap_uint<112> repOrdToken;

} orderCheck_t;

typedef struct creditLimit_t
{
	ap_int<64> creditLimit;

} creditLimit_t;

typedef struct positionInfo_t
{
	ap_uint<16> decimalInPrice;
	ap_uint<16> symbolIndex ;
	ap_uint<32> orderBookId ;
	ap_int<64> position ;
	ap_uint<64> sellableVolume ;
} positionInfo_t;

typedef struct orderInfo_t
{
	ap_uint<8> side;
	ap_uint<16> symbolIndex;
	ap_uint<16> decimalInPrice;
	ap_int<32>  price;
	ap_uint<64> lastOrderEventTimeStamp;
	ap_uint<64> creditUsed;
	ap_uint<64> creditUsedMatch;
	ap_uint<64> outstandingVolume;
	ap_uint<64> orgVolume;
	ap_uint<112> tokenTrack;
} orderInfo_t;

typedef struct lastOrderTimeStamp_t
{
	ap_uint<64> lastOrderEventTimeStamp;
	ap_uint<112> tokenTrack;
} lastOrderTimeStamp_t;

typedef struct tokenMap_t
{
	ap_uint<16> symbolIndex;
	ap_uint<112> origineToken; // use for prev token
	ap_uint<112> replaceToken;
} tokenMap_t;

typedef struct orderEntryMemOperation_t
{
	ap_uint<8> opCode;
	ap_uint<8> statement;
	positionInfo_t positionInfo;
	creditLimit_t creditLmt;
	orderInfo_t orderInfo;
	tokenMap_t token;

} orderEntryMemOperation_t;


typedef struct ipTuple_t
{
	ap_uint32_t address;
	ap_uint16_t port;
} ipTuple_t;

typedef struct ipUdpMeta_t
{
	ap_uint32_t srcAddress;
	ap_uint16_t srcPort;
	ap_uint32_t dstAddress;
	ap_uint16_t dstPort;
	ap_uint16_t length;
	ap_uint16_t subSum;
	ap_uint<1> validSum;
} ipUdpMeta_t;

typedef struct ipTcpReadRequest_t
{
	ap_uint16_t sessionID;
	ap_uint16_t length;
} ipTcpReadRequest_t;

typedef struct ipTcpTxMeta_t
{
	ap_uint16_t sessionID;
	ap_uint16_t length;
	ap_uint16_t subSum;
	ap_uint<1> validSum;
} ipTcpTxMeta_t;

typedef struct ipTcpNotification_t
{
	ap_uint16_t sessionID;
	ap_uint16_t length;
	ap_uint32_t ipAddress;
	ap_uint16_t dstPort;
	ap_uint8_t closed;
	ap_uint8_t opened;
	ap_uint8_t rsvd;
} ipTcpNotification_t;

typedef struct ipTcpConnectionStatus_t
{
	ap_uint16_t sessionID;
	ap_uint8_t success;
} ipTcpConnectionStatus_t;

typedef struct ipTcpTxStatus_t
{
	ap_uint16_t sessionID;
	ap_uint16_t length;
	ap_uint<30> space;
	ap_uint<2> error;
} ipTcpTxStatus_t;

typedef struct itchMeta_t
{
	ap_uint32_t seqNumber;
	ap_uint8_t type;
	ap_uint8_t connNum;
	ap_uint8_t splitID;
} itchMeta_t;

typedef struct sessionMap
{
    enum type
    {
        GLIMPSE,
        ORDER,
        MD,
        SIZE
    };

    ap_uint8_t type;
    ap_uint8_t connNum;
    ap_uint16_t sessionID;

} sessionMap_t;

typedef struct cuHbReset
{
    ap_uint8_t connNum;
    ap_uint8_t type;
} cuHbReset_t;

typedef struct seqCounter
{
    ap_uint8_t type;
    ap_uint8_t connNum;
    ap_uint16_t sessionID;
    ap_uint32_t seqNum;
} seqCounter_t;

static void copySeqCounter(seqCounter_t *src, seqCounter_t *dest)
{
#pragma HLS INLINE
    dest->type = src->type;
    dest->connNum = src->connNum;
    dest->sessionID = src->sessionID;
    dest->seqNum = src->seqNum;
}

typedef struct seqNumberMap
{
    ap_uint16_t connNum;
    ap_uint32_t seqNum;
} seqNumberMap_t;


typedef struct dwExecute_t
{
	ap_uint16_t symbolIndex = 0;
	ap_uint32_t orderbookId = 0;
	ap_uint32_t sequenceNumber = 0;
	ap_uint32_t currentMillis = 0;
	ap_uint8_t isCall = 0;
	ap_uint8_t side = 0;
	ap_int32_t triggerPrice = 0;
	ap_int32_t price = 0;
	ap_uint64_t qtyInput = 0;
	ap_int32_t bid0 = 0;
	ap_int32_t bid1 = 0;
	ap_int32_t ask0 = 0;
	ap_int32_t ask1 = 0;
	ap_uint8_t valid = 0;
	
} dwExecute_t;

typedef struct dwPositionUpdate_t
{
	ap_uint16_t symbolIndex = 0;
	ap_uint32_t orderbookId = 0;
	ap_int32_t currentPosition_update = 0;
	ap_int32_t realizedPosition_update = 0;
	ap_int32_t openSellPosition_update = 0;
	
} dwPositionUpdate_t;



template <unsigned W>
struct axiu
{
	ap_uint<W> data;
	ap_uint<W / 8> keep;
	ap_uint<W / 8> strb;
	ap_uint<1> last;

	axiu() {}

	axiu(ap_uint<W> iData, ap_uint<W / 8> iKeep, ap_uint<W / 8> iStrb, ap_uint<1> iLast)
		: data(iData), keep(iKeep), strb(iStrb), last(iLast) {}

	inline axiu(const ap_axiu<W, 0, 0, 0> &axiw)
		: axiu(axiw.data, axiw.keep, axiw.strb, axiw.last) {}

	inline axiu(const qdma_axis<W, 0, 0, 0> &qdmaw)
		: axiu(qdmaw.data, qdmaw.keep, -1, qdmaw.last) {}

	template <typename T>
	T pack(void) const
	{
#pragma HLS INLINE
		T axiw;
		axiw.data = data;
		axiw.keep = keep;
		axiw.strb = strb;
		axiw.last = last;
		return axiw;
	}

	operator ap_axiu<W, 0, 0, 0>() const
	{
#pragma HLS INLINE
		return pack<ap_axiu<W, 0, 0, 0>>();
	}

	operator qdma_axis<W, 0, 0, 0>() const
	{
#pragma HLS INLINE
		return pack<qdma_axis<W, 0, 0, 0>>();
	}
};

template <unsigned W>
struct axis
{
	ap_int<W> data;
	ap_uint<W / 8> keep;
	ap_uint<W / 8> strb;
	ap_uint<1> last;

	axis() {}

	axis(ap_int<W> iData, ap_uint<W / 8> iKeep, ap_uint<W / 8> iStrb, ap_uint<1> iLast)
		: data(iData), keep(iKeep), strb(iStrb), last(iLast) {}

	inline axis(const ap_axis<W, 0, 0, 0> &axiw)
		: axis(axiw.data, axiw.keep, axiw.strb, axiw.last) {}

	inline axis(const qdma_axis<W, 0, 0, 0> &qdmaw)
		: axis(qdmaw.data, qdmaw.keep, -1, qdmaw.last) {}

	template <typename T>
	T pack(void) const
	{
#pragma HLS INLINE
		T axiw;
		axiw.data = data;
		axiw.keep = keep;
		axiw.strb = strb;
		axiw.last = last;
		return axiw;
	}

	operator ap_axis<W, 0, 0, 0>() const
	{
#pragma HLS INLINE
		return pack<ap_axis<W, 0, 0, 0>>();
	}

	operator qdma_axis<W, 0, 0, 0>() const
	{
#pragma HLS INLINE
		return pack<qdma_axis<W, 0, 0, 0>>();
	}
};





// packed data structures
typedef ap_uint8_t templateId_t;
typedef ap_uint8_t protocol_t;
typedef ap_uint16_t msgLength_t;
typedef ap_uint32_t securityId_t;
typedef ap_axiu<1024, 0, 0, 0> nasdaqMessagePack_t;
typedef ap_axiu<256, 0, 0, 0> nasdaqSmallMessagePack_t;

typedef ap_axiu<224, 0, 0, 0> orderBookOperationPack_t;	 // to be deleted ?
typedef ap_axiu<1024, 0, 0, 0> orderBookResponsePack_t;	 // to be deleted ?

typedef ap_axiu<2048, 0, 0, 0> orderEntryMessagePack_t;	 // Win orderEntry
typedef ap_axiu<8, 0, 0, 0> clockTickGeneratorEvent_t;

typedef ap_axiu<960,0,0,0> orderEntryOperationPack_t; // Win orderEntry
typedef ap_uint<960> orderEntryOperationPackFIFO_t; // Win orderEntry

typedef ap_uint<1424> orderEntryOperationEncodePack_t; //orderEntry

// for Win Nasdaq
typedef ap_uint64_t txData;
typedef ap_axiu<1352, 0, 0, 0> txMsgPack_t;
typedef ap_uint<2048> txReject_t;
typedef ap_axiu<2048, 0, 0, 0> txRejectPack_t;
typedef axiu<112> token_t;
typedef axiu<8> posToken_t;
typedef ap_axiu<2048, 0, 0, 0> ouchMsgPack_t;
typedef ap_uint32_t timerEvent_t;
typedef ap_axiu<8, 0, 0, 0> statusCuManager_t;
typedef ap_uint<512> orderCheckPack_t;
typedef ap_uint<512> orderInfoPack_t;
typedef ap_uint<256> positionInfoPack_t;
typedef ap_uint<256> tokenMapPack_t;

typedef ap_axiu<2048, 0, 0, 0> ouchMsgProcess_t; // Win orderEntry Test
//memHandler

typedef ap_axiu<1024,0,0,0 > nasdaqExternPack_t;
typedef ap_axiu<1024,0,0,0 > memOperationPack_t;
typedef ap_axiu<256,0,0,0 > positionInfoAxiPack_t;
typedef ap_axis<64,0,0,0> creditLimitAxi_t;
typedef ap_axiu<512,0,0,0> orderInfoAxiPack_t;

//pricingEngine
typedef ap_axiu<1024,0,0,0> peTradeTickerMsgPack_t;
typedef ap_axiu<1024,0,0,0> peLmtOrdBookMsgPack_t;
typedef ap_axiu<512,0,0,0> dwExecutePack_t;
typedef ap_axiu<256,0,0,0> dwPositionUpdatePack_t;

// network facing packed data structures
typedef ap_uint16_t ipTcpListenPort_t;
typedef ap_uint16_t ipTcpRxMeta_t;
typedef ap_uint16_t ipTcpCloseConnection_t;
typedef axiu<64> axiWord_t;
typedef axiu<256> ipUdpMetaPack_t;
typedef ap_axiu<64, 0, 0, 0> sequenceNumberPack_t;
typedef ap_axiu<64, 0, 0, 0> axiWordExt_t;
typedef ap_axiu<256, 0, 0, 0> ipUdpMetaPackExt_t;
typedef ap_axiu<64, 0, 0, 0> ipTuplePack_t;
typedef ap_axiu<16, 0, 0, 0> ipTcpListenPortPack_t;
typedef ap_axiu<1, 0, 0, 0> ipTcpListenStatusPack_t;
typedef ap_axiu<128, 0, 0, 0> ipTcpNotificationPack_t;
typedef ap_axiu<32, 0, 0, 0> ipTcpReadRequestPack_t;
typedef ap_axiu<16, 0, 0, 0> ipTcpRxMetaPack_t;
typedef ap_axiu<64, 0, 0, 0> ipTcpRxDataPack_t;
typedef ap_axiu<32, 0, 0, 0> ipTcpConnectionStatusPack_t;
typedef ap_axiu<16, 0, 0, 0> ipTcpCloseConnectionPack_t;
typedef ap_axiu<64, 0, 0, 0> ipTcpTxMetaPack_t;
typedef ap_axiu<64, 0, 0, 0> ipTcpTxDataPack_t;
typedef ap_axiu<64, 0, 0, 0> ipTcpTxStatusPack_t;
typedef ap_axiu<64, 0, 0, 0> itchMetaPack_t;
typedef ap_axiu<32, 0, 0, 0> sessionMapPack_t;
typedef ap_axiu<16, 0, 0, 0> cuHbResetPack_t;
typedef ap_axiu<64, 0, 0, 0> seqCounterPack_t;
typedef ap_axiu<64, 0, 0, 0> seqNumberMapPack_t;

typedef ap_axiu<64, 0, 0, 0> dataMoverPack_t;

typedef struct decodeWord_t
{
    axiWord_t axiWord;
    ap_uint1_t incomplete;
    ap_uint8_t line;
} decodeWord_t;

static void copyDecodeWord(decodeWord_t *src, decodeWord_t *dest)
{
#pragma HLS INLINE
    dest->axiWord.data = src->axiWord.data;
    dest->axiWord.keep = src->axiWord.keep;
    dest->axiWord.last = src->axiWord.last;
    dest->line = src->incomplete;
    dest->incomplete = src->incomplete;
}

class mmInterface
{
public:
	// TODO: these pack/unpack functions could be moved to the typedefs and use
	//       the constructor functionality of C++, this would remove the need
	//       for a lot of the *Stream and *StreamPack bloat

	template <typename T>
	void ouchOrderAcceptedPack(OuchOrderAccepted_t *src, T *dest);

	template <typename T>
	void ouchOrderAcceptedUnpack(T *src, OuchOrderAccepted_t *dest);

	template <typename T>
	void ouchOrderRejectedPack(OuchOrderRejected_t *src, T *dest);

	template <typename T>
	void ouchOrderRejectedUnpack(T *src, OuchOrderRejected_t *dest);

	template <typename T>
	void ouchOrderCanceledPack(OuchOrderCanceled_t *src, T *dest);

	template <typename T>
	void ouchOrderCanceledUnpack(T *src, OuchOrderCanceled_t *dest);

	template <typename T>
	void ouchOrderReplacedPack(OuchOrderReplaced_t *src, T *dest);

	template <typename T>
	void ouchOrderReplacedUnpack(T *src, OuchOrderReplaced_t *dest);

	template <typename T>
	void ouchOrderExecutedPack(OuchOrderExecuted_t *src, T *dest);

	template <typename T>
	void ouchOrderExecutedUnpack(T *src, OuchOrderExecuted_t *dest);

	template <typename T>
	void itchMarketByPricePack(ItchMarketByPriceMessage_t *src, T *dest);

	template <typename T>
	void itchMarketByPriceUnpack(T *src, ItchMarketByPriceMessage_t *dest);

	template <typename T>
	void itchTickSizeTableMessagePack(ItchTickSizeTableMessage_t *src, T *dest);

	template <typename T>
	void itchTickSizeTableMessageUnpack(T *src, ItchTickSizeTableMessage_t *dest);

	template <typename T>
	void itchPriceLimitMessagePack(ItchPriceLimitMessage_t *src, T *dest);

	template <typename T>
	void itchPriceLimitMessageUnpack(T *src, ItchPriceLimitMessage_t *dest);

	template <typename T>
	void itchOrderBookStateMessagePack(ItchOrderBookStateMessage_t *src, T *dest);

	template <typename T>
	void itchOrderBookStateMessageUnpack(T *src, ItchOrderBookStateMessage_t *dest);

	template <typename T>
	void itchHaltInformationMessagePack(ItchHaltInformationMessage_t *src, T *dest);

	template <typename T>
	void itchhHaltInformationMessageUnpack(T *src, ItchHaltInformationMessage_t *dest);

	template <typename T>
	void itchTradeTickerMessagePack(ItchTradeTickerMessage_t *src, T *dest);

	template <typename T>
	void itchTradeTickerMessageUnpack(T *src, ItchTradeTickerMessage_t *dest);

	template <typename T>
	void itchLimitOrderBookPack(ItchLimitOrderBookMessage_t *src, T *dest);

	template <typename T>
	void itchLimitOrderBookUnpack(T *src, ItchLimitOrderBookMessage_t *dest);

	template <typename T>
	void itchIndexPriceMessagePack(ItchIndexPriceMessage_t *src, T *dest);

	template <typename T>
	void itchIndexPriceMessageUnpack(T *src, ItchIndexPriceMessage_t *dest);

	template <typename T>
	void itchEquilibriumPriceMessagePack(ItchEquilibriumPriceMessage_t *src, T *dest);

	template <typename T>
	void itchEquilibriumPriceMessageUnpack(T *src, ItchEquilibriumPriceMessage_t *dest);

	template <typename T>
	void itchMarketStatisticMessagePack(ItchMarketStatisticMessage_t *src, T *dest);

	template <typename T>
	void itchMarketStatisticMessageUnpack(T *src, ItchMarketStatisticMessage_t *dest);

	template <typename T>
	void itchiNAVMessagePack(ItchiNAVMessage_t *src, T *dest);

	template <typename T>
	void itchiNAVMessageUnpack(T *src, ItchiNAVMessage_t *dest);	

	template <typename T>
	void itchTradeStatisticMessagePack(ItchTradeStatisticMessage_t *src, T *dest);

	template <typename T>
	void itchTradeStatisticMessageUnpack(T *src, ItchTradeStatisticMessage_t *dest);
	
	template <typename T>
	void itchOrderBookDirectoryCompactPack(ItchOrderBookDirectoryCompact_t *src, T *dest);

	template <typename T>
	void itchOrderBookDirectoryCompactUnpack(T *src, ItchOrderBookDirectoryCompact_t *dest);

	template <typename T>
	void itchGlimpseEndMessagePack(ItchGlimpseEndMessage_t *src, T *dest);

	template <typename T>
	void itchGlimpseEndMessageUnpack(T *src, ItchGlimpseEndMessage_t *dest);

	template <typename T>
	void itchOtherMessagePack(ItchOtherMessage_t *src, T *dest);

	template <typename T>
	void itchOtherMessageUnpack(T *src, ItchOtherMessage_t *dest);

	template <typename T>
	void itchSecondsMessagePack(ItchSecondsMessage_t *src, T *dest);

	template <typename T>
	void itchSecondsMessageUnpack(T *src, ItchSecondsMessage_t *dest);

	void orderBookOperationPack(orderBookOperation_t *src,
								orderBookOperationPack_t *dest);

	void orderBookOperationUnpack(orderBookOperationPack_t *src,
								  orderBookOperation_t *dest);

	void orderBookResponsePack(orderBookResponse_t *src,
							   orderBookResponsePack_t *dest);

	void orderBookResponseUnpack(orderBookResponsePack_t *src,
								 orderBookResponse_t *dest);

	void orderEntryEncodePack(orderEntryOperationEncode_t *src, txMsgPack_t *dest);
	void orderEntryEncodePack(orderEntryOperationEncode_t *src, txReject_t *dest);

	void orderEntryEncodeUnpack(txMsgPack_t *src, orderEntryOperationEncode_t *dest);

	void orderEntryOperationPack(orderEntryOperation_t *src,
								 orderEntryOperationPack_t *dest);

	void orderEntryOperationUnpack(orderEntryOperationPack_t *src,
								   orderEntryOperation_t *dest);

	void orderEntryOperationFIFOPack(orderEntryOperationFIFO_t *src, orderEntryOperationPackFIFO_t *dest);

	void orderEntryOperationFIFOUnpack(orderEntryOperationPackFIFO_t *src, orderEntryOperationFIFO_t *dest);

	void orderEntryOperationEncodePack(orderEntryOperationEncode_t *src,
																		 orderEntryOperationEncodePack_t *dest);

	void orderEntryOperationEncodeUnpack(orderEntryOperationEncodePack_t *src,
																			 orderEntryOperationEncode_t *dest);




	void ouchMsgUnpack(ouchMsgPack_t *src, ouchMsg_t *dest); // Win test OrderEntry

	void priceLimitOrdEntryMessageUnpack(nasdaqInternalPack_t *src, priceLimitOrdMessage_t *dest);

	void priceLimitOrdEntryMessagePack(priceLimitOrdMessage_t *src, nasdaqInternalPack_t *dest);

	void tickerMsgOrdEntryUnpack(nasdaqInternalPack_t *src, tickerMsgOrderEntryMessage_t *dest);

	void rxBuffOuchUnpack(ap_uint<64> src[32], ouchMsg_t *dest); // Win test OrdereEntry

	void txMsgUnPackToTxData(orderEntryOperationEncode_t *src, txData messageTemplate[32], // Win test OrdereEntry
							 ap_uint<8> *templateL,
							 ap_uint<8> *keep, ap_uint<16> *messageTempSum,
							 ap_uint<16> *txLength);

	void banlistUnpack(ap_uint<4096> *banList1, ap_uint<4096> *banList2, ap_uint<32> *ordBookID, bool *banlistBool);

	void rdPriceLimit(priceLimitOrdMessage_t *src, priceLimitOrdSymbolIndex_t dest[NUM_SYMBOL]);

	void rxBuffPack(ap_uint<64> src[32], ouchMsgProcess_t *dest);

	void rxBuffUnPack(ouchMsgProcess_t *src, ap_uint<64> dest[32]);

	void orderCheckPack(orderCheckPack_t *dest, orderCheck_t *src);

	void orderCheckUnPack(orderCheck_t *dest, orderCheckPack_t *src);

	void ipTuplePack(ipTuple_t *src,
					 ipTuplePack_t *dest);

	void udpMetaPack(ipUdpMeta_t *src,
					 ipUdpMetaPack_t *dest);

	void udpMetaUnpack(ipUdpMetaPack_t *src,
					   ipUdpMeta_t *dest);

	void ipTcpReadRequestPack(ipTcpReadRequest_t *src,
							  ipTcpReadRequestPack_t *dest);

	void ipTcpTxMetaPack(ipTcpTxMeta_t *src,
						 ipTcpTxMetaPack_t *dest);

	void ipTcpNotificationUnpack(ipTcpNotificationPack_t *src,
								 ipTcpNotification_t *dest);

	void ipTcpConnectionStatusUnpack(ipTcpConnectionStatusPack_t *src,
									 ipTcpConnectionStatus_t *dest);

	void ipTcpTxStatusStreamUnpack(ipTcpTxStatusPack_t *src,
								   ipTcpTxStatus_t *dest);

	void ipTcpTxMetaUnpack(ipTcpTxMetaPack_t *src,
						   ipTcpTxMeta_t *dest);

	void ipTcpNotificationPack(ipTcpNotification_t *src,
							   ipTcpNotificationPack_t *dest);

	void ipTcpConnectionStatusPack(ipTcpConnectionStatus_t *src,
								   ipTcpConnectionStatusPack_t *dest);

	void ipTcpTxStatusStreamPack(ipTcpTxStatus_t *src,
								 ipTcpTxStatusPack_t *dest);

	void positionInfoPack(positionInfo_t *src,
						  positionInfoPack_t *dest);

	void positionInfoUnpack(positionInfoPack_t *src,
							positionInfo_t *dest);

	void tokenMapPack(tokenMap_t *src, tokenMapPack_t *dest);

	void tokenMapUnpack(tokenMapPack_t *src, tokenMap_t *dest);

	void orderInfoPack(orderInfo_t *src, orderInfoPack_t *dest);

	void orderInfoUnPack(orderInfoPack_t *src, orderInfo_t *dest);

	void itchMetaPack(itchMeta_t *src,itchMetaPack_t *dest);
	void itchMetaUnPack(itchMetaPack_t *src,itchMeta_t *dest);

	void sessionMapPack(sessionMap_t *src,sessionMapPack_t *dest);
	void sessionMapUnPack(sessionMapPack_t *src, sessionMap_t *dest);	
	void cuHbResetPack(cuHbReset_t *src,cuHbResetPack_t *dest);
	void cuHbResetUnPack(cuHbResetPack_t *src, cuHbReset_t *dest);	
	void seqCounterPack(seqCounter_t *src, seqCounterPack_t *dest);
	void seqCounterUnPack(seqCounterPack_t *src, seqCounter_t *dest);	
	void seqNumberMapPack(seqNumberMap_t *src, seqNumberMapPack_t *dest);
	void seqNumberMapUnPack(seqNumberMapPack_t *src, seqNumberMap_t *dest);

	void memOperationPack(orderEntryMemOperation_t*src, memOperationPack_t*dest);
	void memOperationUnPack(memOperationPack_t*src ,orderEntryMemOperation_t*dest );
	void positionInfoAxiPack(positionInfo_t *src, positionInfoAxiPack_t *dest);
	void positionInfoAxiUnpack(positionInfoAxiPack_t *src, positionInfo_t *dest);
	void orderInfoAxiPack(orderInfo_t *src, orderInfoAxiPack_t *dest);
	void orderInfoAxiUnPack(orderInfoAxiPack_t *src, orderInfo_t *dest);
	void peTradeTickerMsgPack (peTradeTickerMsg_t *src, peTradeTickerMsgPack_t *dest );
	void peTradeTickerMsgUnPack (peTradeTickerMsgPack_t *src, peTradeTickerMsg_t *dest );
	void peLmtOrdBookMsgPack (peLmtOrdBookMsg_t *src, peLmtOrdBookMsgPack_t *dest );
	void peLmtOrdBookMsgUnPack (peLmtOrdBookMsgPack_t *src, peLmtOrdBookMsg_t *dest);

	void dwExecutePack(dwExecute_t *src, dwExecutePack_t *dest);
	void dwExecuteUnPack(dwExecutePack_t *src, dwExecute_t *dest);
	void dwPositionUpdatePack(dwPositionUpdate_t *src, dwPositionUpdatePack_t *dest);
	void dwPositionUpdateUnPack(dwPositionUpdatePack_t *src, dwPositionUpdate_t *dest);

	ap_uint<32> hashTableMod (ap_uint<112> &token, ap_uint<32> &size);
	ap_uint<16> ansciiDateToInt (ap_uint<72> &token);
	ap_uint<32> ansciiToInt (ap_uint<8> &data);
	ap_uint<32> ansciiNumToInt (ap_uint<40> & alphaNum);
	orderInfo_t searchOrderInfoHT(ap_uint<112> &token, ap_uint<32> &index, ap_uint<32> &dim
				  									 , orderInfoPack_t orderInfoMapPack[NUM_preRisk][NUM_DIM_HT],bool &foundRD);

	void insertNewOrderInfoHT(orderInfo_t &newOrderInfo,orderInfoPack_t orderInfoMapPack[NUM_preRisk][NUM_DIM_HT], bool &full);

	tokenMap_t searchRepFdOrgTokenMap(ap_uint<112> &token, ap_uint<32> &index, ap_uint<32> &dim
															,tokenMapPack_t repFdOrgMapPack[NUM_preRisk][NUM_DIM_HT], bool &foundRD);
	//searchOrgTokenRepMap
	tokenMap_t searchOrgFdRepTokenMap(ap_uint<112> &token, ap_uint<32> &index, ap_uint<32> &dim
							,tokenMapPack_t orgFdRepMapPack[NUM_preRisk][NUM_DIM_HT], bool &foundRD);

	void insertOrgFdRepTokenMap(tokenMap_t &tokenMap,tokenMapPack_t repFdOrgMapPack[NUM_preRisk][NUM_DIM_HT], bool &full);
	void insertRepFdOrgTokenMap(tokenMap_t &tokenMap,tokenMapPack_t orgFdRepMapPack[NUM_preRisk][NUM_DIM_HT], bool &full);
//	void shiftTest (ap_uint<80> RangeL1,ap_uint<80> RangeL2, ap_uint<32> shift);

private:
};

template <typename T>
void mmInterface::ouchOrderAcceptedPack(OuchOrderAccepted_t *src, T *dest)
{
#pragma HLS INLINE
	dest->data.range(1023, 1016) = src->messageType;  				//	messageType	 <	8	>
	dest->data.range(1015, 1000) = src->symbolIndex;  				//	symbolIndex	 <	16	>
	dest->data.range(999, 992) = src->reserve;  					//	reserve	 <	8	>
	dest->data.range(991, 984) = src->protocol;  					//	protocol	 <	8	>
	dest->data.range(983, 976) = src->connNum;  					//	connNum	 <	8	>
	dest->data.range(975, 968) = src->splitId;  					//	splitId	 <	8	>
	dest->data.range(967, 936) = src->sequenceNumber;  				//	sequenceNumber	 <	32	>
	dest->data.range(935, 872) = src->timeStamp;  					//	timeStamp	 <	64	>
	dest->data.range(871, 760) = byteReverse<112>(src->orderToken);  					//	orderToken	 <	112	>
	dest->data.range(759, 728) = src->orderBookId;  				//	orderBookId	 <	32	>
	dest->data.range(727, 720) = src->side;  						//	side	 <	8	>
	dest->data.range(719, 656) = src->orderId;  					//	orderId	 <	64	>
	dest->data.range(655, 592) = src->quantity;  					//	quantity	 <	64	>
	dest->data.range(591, 560) = src->price;  						//	price	 <	32	>
	dest->data.range(559, 552) = src->timeInForce;  				//	timeInForce	 <	8	>
	dest->data.range(551, 544) = src->openClose;  					//	openClose	 <	8	>
	dest->data.range(543, 464) = byteReverse<80>(src->clientAccount);  				//	clientAccount	 <	80	>
	dest->data.range(463, 456) = src->orderState;  					//	orderState	 <	8	>
	dest->data.range(455, 336) = byteReverse<120>(src->customerInfo);  				//	customerInfo	 <	120	>
	dest->data.range(335, 272) = src->displayQuantity;  			//	displayQuantity	 <	64	>
	dest->data.range(271, 192) = byteReverse<80>(src->orderInfo);  					//	orderInfo	 <	80	>
	dest->data.range(191, 160) = src->crossingKey;  				//	crossingKey	 <	32	>
	dest->data.range(159, 152) = src->orderType;  					//	orderType	 <	8	>
	dest->data.range(151, 144) = src->triggerType;  				//	triggerType	 <	8	>
	dest->data.range(143, 112) = src->validTillData;  				//	validTillData	 <	32	>
}
template <typename T>
void mmInterface::ouchOrderAcceptedUnpack(T *src, OuchOrderAccepted_t *dest)
{
#pragma HLS INLINE
	dest->messageType = src->data.range(1023, 1016);  				//		messageType	 <	8	>
	dest->symbolIndex = src->data.range(1015, 1000);  				//		symbolIndex	 <	16	>
	dest->reserve = src->data.range(999, 992);  				 	//		reserve	 <	8	>
	dest->protocol = src->data.range(991, 984);  				 	//		protocol	 <	8	>
	dest->connNum = src->data.range(983, 976);  				 	//		connNum	 <	8	>
	dest->splitId = src->data.range(975, 968);  				 	//		splitId	 <	8	>
	dest->sequenceNumber = src->data.range(967, 936);  				//		sequenceNumber	 <	32	>
	dest->timeStamp = src->data.range(935, 872);  					//		timeStamp	 <	64	>
	dest->orderToken = byteReverse<112>(src->data.range(871, 760));  					//		orderToken	 <	112	>
	dest->orderBookId = src->data.range(759, 728);  				//		orderBookId	 <	32	>
	dest->side = src->data.range(727, 720);  						//		side	 <	8	>
	dest->orderId = src->data.range(719, 656);  					//		orderId	 <	64	>
	dest->quantity = src->data.range(655, 592);  					//		quantity	 <	64	>
	dest->price = src->data.range(591, 560);  						//		price	 <	32	>
	dest->timeInForce = src->data.range(559, 552);  				//		timeInForce	 <	8	>
	dest->openClose = src->data.range(551, 544);  					//		openClose	 <	8	>
	dest->clientAccount = byteReverse<80>(src->data.range(543, 464));  				//		clientAccount	 <	80	>
	dest->orderState = src->data.range(463, 456);  					//		orderState	 <	8	>
	dest->customerInfo = byteReverse<120>(src->data.range(455, 336));  				//		customerInfo	 <	120	>
	dest->displayQuantity = src->data.range(335, 272);  			//		displayQuantity	 <	64	>
	dest->orderInfo = byteReverse<80>(src->data.range(271, 192));  					//		orderInfo	 <	80	>
	dest->crossingKey = src->data.range(191, 160);  				//		crossingKey	 <	32	>
	dest->orderType = src->data.range(159, 152);  					//		orderType	 <	8	>
	dest->triggerType = src->data.range(151, 144);  				//		triggerType	 <	8	>
	dest->validTillData = src->data.range(143, 112);  				//		validTillData	 <	32	>
}

template <typename T>
void mmInterface::ouchOrderRejectedPack(OuchOrderRejected_t *src, T *dest)
{
#pragma HLS INLINE
	dest->data.range(1023, 1016) = src->messageType;  				//	messageType	 <	8	>
	dest->data.range(1015, 1000) = src->symbolIndex;  				//	symbolIndex	 <	16	>
	dest->data.range(999, 992) = src->reserve;  					//	reserve	 <	8	>
	dest->data.range(991, 984) = src->protocol;  					//	protocol	 <	8	>
	dest->data.range(983, 976) = src->connNum;  					//	connNum	 <	8	>
	dest->data.range(975, 968) = src->splitId;  					//	splitId	 <	8	>
	dest->data.range(967, 936) = src->sequenceNumber;  				//	sequenceNumber	 <	32	>
	dest->data.range(935, 872) = src->timeStamp;  					//	timeStamp	 <	64	>
	dest->data.range(871, 760) = byteReverse<112>(src->orderToken);  					//	orderToken	 <	112	>
	dest->data.range(759, 728) = src->rejectCode;  					//	rejectCode	 <	32	>
}

template <typename T>
void mmInterface::ouchOrderRejectedUnpack(T *src, OuchOrderRejected_t *dest)
{
#pragma HLS INLINE
	dest->messageType = src->data.range(1023, 1016);  				//		messageType	 <	8	>
	dest->symbolIndex = src->data.range(1015, 1000);  				//		symbolIndex	 <	16	>
	dest->reserve = src->data.range(999, 992);  					//		reserve	 <	8	>
	dest->protocol = src->data.range(991, 984);  					//		protocol	 <	8	>
	dest->connNum = src->data.range(983, 976);  					//		connNum	 <	8	>
	dest->splitId = src->data.range(975, 968);  					//		splitId	 <	8	>
	dest->sequenceNumber = src->data.range(967, 936);  				//		sequenceNumber	 <	32	>
	dest->timeStamp = src->data.range(935, 872);  					//		timeStamp	 <	64	>
	dest->orderToken = byteReverse<112>(src->data.range(871, 760));  					//		orderToken	 <	112	>
	dest->rejectCode = src->data.range(759, 728);  					//		rejectCode	 <	32	>
}

template <typename T>
void mmInterface::ouchOrderCanceledPack(OuchOrderCanceled_t *src, T *dest)
{
#pragma HLS INLINE
	dest->data.range(1023, 1016) = src->messageType;  				//	messageType	 <	8	>
	dest->data.range(1015, 1000) = src->symbolIndex;  				//	symbolIndex	 <	16	>
	dest->data.range(999, 992) = src->reserve;  					//	reserve	 <	8	>
	dest->data.range(991, 984) = src->protocol;  					//	protocol	 <	8	>
	dest->data.range(983, 976) = src->connNum;  					//	connNum	 <	8	>
	dest->data.range(975, 968) = src->splitId;  					//	splitId	 <	8	>
	dest->data.range(967, 936) = src->sequenceNumber;  				//	sequenceNumber	 <	32	>
	dest->data.range(935, 872) = src->timeStamp;  					//	timeStamp	 <	64	>
	dest->data.range(871, 760) = byteReverse<112>(src->orderToken);  					//	orderToken	 <	112	>
	dest->data.range(759, 728) = src->orderBookId;  				//	orderBookId	 <	32	>
	dest->data.range(727, 720) = src->side;  						//	side	 <	8	>
	dest->data.range(719, 656) = src->orderId;  					//	orderId	 <	64	>
	dest->data.range(655, 648) = src->reason;  						//	reason	 <	8	>
}

template <typename T>
void mmInterface::ouchOrderCanceledUnpack(T *src, OuchOrderCanceled_t *dest)
{
#pragma HLS INLINE
	dest->messageType = src->data.range(1023, 1016);  				//		messageType	 <	8	>
	dest->symbolIndex = src->data.range(1015, 1000);  				//		symbolIndex	 <	16	>
	dest->reserve = src->data.range(999, 992);  					//		reserve	 <	8	>
	dest->protocol = src->data.range(991, 984);  					//		protocol	 <	8	>
	dest->connNum = src->data.range(983, 976);  					//		connNum	 <	8	>
	dest->splitId = src->data.range(975, 968);  					//		splitId	 <	8	>
	dest->sequenceNumber = src->data.range(967, 936);  				//		sequenceNumber	 <	32	>
	dest->timeStamp = src->data.range(935, 872);  					//		timeStamp	 <	64	>
	dest->orderToken = byteReverse<112>(src->data.range(871, 760));  					//		orderToken	 <	112	>
	dest->orderBookId = src->data.range(759, 728);  				//		orderBookId	 <	32	>
	dest->side = src->data.range(727, 720);  						//		side	 <	8	>
	dest->orderId = src->data.range(719, 656);  					//		orderId	 <	64	>
	dest->reason = src->data.range(655, 648);  						//		reason	 <	8	>
}

template <typename T>
void mmInterface::ouchOrderReplacedPack(OuchOrderReplaced_t *src, T *dest)
{
#pragma HLS INLINE
	dest->data.range(1023, 1016) = src->messageType;  				//	messageType	 <	8	>
	dest->data.range(1015, 1000) = src->symbolIndex;  				//	symbolIndex	 <	16	>
	dest->data.range(999, 992) = src->reserve;  					//	reserve	 <	8	>
	dest->data.range(991, 984) = src->protocol;  					//	protocol	 <	8	>
	dest->data.range(983, 976) = src->connNum;  					//	connNum	 <	8	>
	dest->data.range(975, 968) = src->splitId;  					//	splitId	 <	8	>
	dest->data.range(967, 936) = src->sequenceNumber;  				//	sequenceNumber	 <	32	>
	dest->data.range(935, 872) = src->timeStamp;  					//	timeStamp	 <	64	>
	dest->data.range(871, 760) = byteReverse<112>(src->replacementOrderToken);  		//	replacementOrderToken	 <	112	>
	dest->data.range(759, 648) = byteReverse<112>(src->previousOrderToken);  			//	previousOrderToken	 <	112	>
	dest->data.range(647, 616) = src->orderBookId;  				//	orderBookId	 <	32	>
	dest->data.range(615, 608) = src->side;  						//	side	 <	8	>
	dest->data.range(607, 544) = src->orderId;  					//	orderId	 <	64	>
	dest->data.range(543, 480) = src->quantity;  					//	quantity	 <	64	>
	dest->data.range(479, 448) = src->price;  						//	price	 <	32	>
	dest->data.range(447, 440) = src->timeInForce;  				//	timeInForce	 <	8	>
	dest->data.range(439, 432) = src->openClose;  					//	openClose	 <	8	>
	dest->data.range(431, 352) = byteReverse<80>(src->clientAccount);  				//	clientAccount	 <	80	>
	dest->data.range(351, 344) = src->orderState;  					//	orderState	 <	8	>
	dest->data.range(343, 224) = byteReverse<120>(src->customerInfo);  				//	customerInfo	 <	120	>
	dest->data.range(223, 160) = src->displayQuantity;  			//	displayQuantity	 <	64	>
	dest->data.range(159, 80) = byteReverse<80>(src->orderInfo);  					//	orderInfo	 <	80	>
	dest->data.range(79, 48) = src->crossingKey;  					//	crossingKey	 <	32	>
	dest->data.range(47, 40) = src->orderType;  					//	orderType	 <	8	>
	dest->data.range(39, 32) = src->validTillData;  				//	validTillData	 <	8	>
	dest->data.range(31, 0) = src->tradedQuantity;  				//	tradedQuantity	 <	32	>
}

template <typename T>
void mmInterface::ouchOrderReplacedUnpack(T *src, OuchOrderReplaced_t *dest)
{
#pragma HLS INLINE
	dest->messageType = src->data.range(1023, 1016);  				//		messageType	 <	8	>
	dest->symbolIndex = src->data.range(1015, 1000);  				//		symbolIndex	 <	16	>
	dest->reserve = src->data.range(999, 992);  					//		reserve	 <	8	>
	dest->protocol = src->data.range(991, 984);  					//		protocol	 <	8	>
	dest->connNum = src->data.range(983, 976);  					//		connNum	 <	8	>
	dest->splitId = src->data.range(975, 968);  					//		splitId	 <	8	>
	dest->sequenceNumber = src->data.range(967, 936);  				//		sequenceNumber	 <	32	>
	dest->timeStamp = src->data.range(935, 872);  					//		timeStamp	 <	64	>
	dest->replacementOrderToken = byteReverse<112>(src->data.range(871, 760));  		//		replacementOrderToken	 <	112	>
	dest->previousOrderToken = byteReverse<112>(src->data.range(759, 648));  			//		previousOrderToken	 <	112	>
	dest->orderBookId = src->data.range(647, 616);  				//		orderBookId	 <	32	>
	dest->side = src->data.range(615, 608);  						//		side	 <	8	>
	dest->orderId = src->data.range(607, 544);  					//		orderId	 <	64	>
	dest->quantity = src->data.range(543, 480);  					//		quantity	 <	64	>
	dest->price = src->data.range(479, 448);  						//		price	 <	32	>
	dest->timeInForce = src->data.range(447, 440);  				//		timeInForce	 <	8	>
	dest->openClose = src->data.range(439, 432);  					//		openClose	 <	8	>
	dest->clientAccount = byteReverse<80>(src->data.range(431, 352));  				//		clientAccount	 <	80	>
	dest->orderState = src->data.range(351, 344);  					//		orderState	 <	8	>
	dest->customerInfo = byteReverse<120>(src->data.range(343, 224));  				//		customerInfo	 <	120	>
	dest->displayQuantity = src->data.range(223, 160);  			//		displayQuantity	 <	64	>
	dest->orderInfo = byteReverse<80>(src->data.range(159, 80));  					//		orderInfo	 <	80	>
	dest->crossingKey = src->data.range(79, 48);  					//		crossingKey	 <	32	>
	dest->orderType = src->data.range(47, 40);  					//		orderType	 <	8	>
	dest->validTillData = src->data.range(39, 32);  				//		validTillData	 <	8	>
	dest->tradedQuantity = src->data.range(31, 0);  				//		tradedQuantity	 <	32	>
}

template <typename T>
void mmInterface::ouchOrderExecutedPack(OuchOrderExecuted_t *src, T *dest)
{
#pragma HLS INLINE
	dest->data.range(1023, 1016) = src->messageType;  				//	messageType	 <	8	>
	dest->data.range(1015, 1000) = src->symbolIndex;  				//	symbolIndex	 <	16	>
	dest->data.range(999, 992) = src->reserve;  				//	reserve	 <	8	>
	dest->data.range(991, 984) = src->protocol;  				//	protocol	 <	8	>
	dest->data.range(983, 976) = src->connNum;  				//	connNum	 <	8	>
	dest->data.range(975, 968) = src->splitId;  				//	splitId	 <	8	>
	dest->data.range(967, 936) = src->sequenceNumber;  				//	sequenceNumber	 <	32	>
	dest->data.range(935, 872) = src->timeStamp;  				//	timeStamp	 <	64	>
	dest->data.range(871, 760) = byteReverse<112>(src->orderToken);  				//	orderToken	 <	112	>
	dest->data.range(759, 728) = src->orderBookId;  				//	orderBookId	 <	32	>
	dest->data.range(727, 664) = src->tradedQuantity;  				//	tradedQuantity	 <	64	>
	dest->data.range(663, 632) = src->tradedPrice;  				//	tradedPrice	 <	32	>
	dest->data.range(631, 568) = src->matchId;  				//	matchID	 <	64	>
	dest->data.range(567, 536) = src->comboGroupId;  				//	comboGroupID	 <	32	>
	dest->data.range(535, 528) = src->dealSource;  				//	dealSource	 <	8	>
	dest->data.range(527, 520) = src->side;  				//	side	 <	8	>
}

template <typename T>
void mmInterface::ouchOrderExecutedUnpack(T *src, OuchOrderExecuted_t *dest)
{
#pragma HLS INLINE
	dest->messageType = src->data.range(1023, 1016);  						//		messageType	 <	8	>
	dest->symbolIndex = src->data.range(1015, 1000);  						//		symbolIndex	 <	16	>
	dest->reserve = src->data.range(999, 992);  						//		reserve	 <	8	>
	dest->protocol = src->data.range(991, 984);  						//		protocol	 <	8	>
	dest->connNum = src->data.range(983, 976);  						//		connNum	 <	8	>
	dest->splitId = src->data.range(975, 968);  						//		splitId	 <	8	>
	dest->sequenceNumber = src->data.range(967, 936);  						//		sequenceNumber	 <	32	>
	dest->timeStamp = src->data.range(935, 872);  						//		timeStamp	 <	64	>
	dest->orderToken = byteReverse<112>(src->data.range(871, 760));  						//		orderToken	 <	112	>
	dest->orderBookId = src->data.range(759, 728);  						//		orderBookId	 <	32	>
	dest->tradedQuantity = src->data.range(727, 664);  						//		tradedQuantity	 <	64	>
	dest->tradedPrice = src->data.range(663, 632);  						//		tradedPrice	 <	32	>
	dest->matchId = src->data.range(631, 568);  						//		matchID	 <	64	>
	dest->comboGroupId = src->data.range(567, 536);  						//		comboGroupID	 <	32	>
	dest->dealSource = src->data.range(535, 528);  						//		dealSource	 <	8	>
	dest->side = src->data.range(527, 520);  						//		side	 <	8	>
}

template <typename T>
void mmInterface::itchSecondsMessagePack(ItchSecondsMessage_t *src, T *dest)
{
#pragma HLS INLINE

	dest->data.range(1023, 1016)= src->messageType;  					//	messageType	 <	8	>
	dest->data.range(1015, 1000)= src->symbolIndex;  					//	symbolIndex	 <	16	>
	dest->data.range(999, 992)= src->reserve;  					//	reserve	 <	8	>
	dest->data.range(991, 984)= src->protocol;  					//	protocol	 <	8	>
	dest->data.range(983, 976)= src->connNum;  					//	connNum	 <	8	>
	dest->data.range(975, 968)= src->splitId;  					//	splitId	 <	8	>
	dest->data.range(967, 936)= src->sequenceNumber;  					//	sequenceNumber	 <	32	>
	dest->data.range(935, 904)= src->second;  					//	second	 <	32	>

	return;
}

template <typename T>
void mmInterface::itchSecondsMessageUnpack(T *src, ItchSecondsMessage_t *dest)
{
#pragma HLS INLINE

	dest->messageType = src->data.range(1023, 1016);  					//		messageType	 <	8	>
	dest->symbolIndex = src->data.range(1015, 1000);  					//		symbolIndex	 <	16	>
	dest->reserve = src->data.range(999, 992);  					//		reserve	 <	8	>
	dest->protocol = src->data.range(991, 984);  					//		protocol	 <	8	>
	dest->connNum = src->data.range(983, 976);  					//		connNum	 <	8	>
	dest->splitId = src->data.range(975, 968);  					//		splitId	 <	8	>
	dest->sequenceNumber = src->data.range(967, 936);  					//		sequenceNumber	 <	32	>
	dest->second = src->data.range(935, 904);  					//		second	 <	32	>

	return;
}

template <typename T>
void mmInterface::itchMarketByPricePack(ItchMarketByPriceMessage_t *src, T *dest)
{
#pragma HLS INLINE

	dest->data.range(1023, 1016) = 'b';  					//	messageType	 <	8	>
	dest->data.range(1015, 1000) = src->symbolIndex;  					//	symbolIndex	 <	16	>
	dest->data.range(999, 992) = src->reserve;  					//	reserve	 <	8	>
	dest->data.range(991, 984) = src->protocol;  					//	protocol	 <	8	>
	dest->data.range(983, 976) = src->connNum;  					//	connNum	 <	8	>
	dest->data.range(975, 968) = src->splitId;  					//	splitId	 <	8	>
	dest->data.range(967, 936) = src->sequenceNumber;  					//	sequenceNumber	 <	32	>
	dest->data.range(935, 904) = src->second;  					//	second	 <	32	>
	dest->data.range(903, 872) = src->nanos;  					//	nanos	 <	32	>
	dest->data.range(871, 840) = src->orderBookId;  					//	orderBookId	 <	32	>
	dest->data.range(839, 832) = src->maximumLevel;  					//	maximumLevel	 <	8	>
	dest->data.range(831, 824) = src->levelUpdateAction;  					//	levelUpdateAction	 <	8	>
	dest->data.range(823, 816) = src->side;  					//	side	 <	8	>
	dest->data.range(815, 808) = src->level;  					//	level	 <	8	>
	dest->data.range(807, 776) = src->price;  					//	price	 <	32	>
	dest->data.range(775, 712) = src->quantity;  					//	quantity	 <	64	>
	dest->data.range(711, 708) = src->numberOfDeletes;  					//	numberOfDeletes	 <	4	>
	dest->data.range(707, 704) = src->hasRemaining;  					//	hasRemaining	 <	4	>

	return;
}

template <typename T>
void mmInterface::itchMarketByPriceUnpack(T *src, ItchMarketByPriceMessage_t *dest)
{
#pragma HLS INLINE

	dest->messageType = src->data.range(1023, 1016);  						//		messageType	 <	8	>
	dest->symbolIndex = src->data.range(1015, 1000);  						//		symbolIndex	 <	16	>
	dest->reserve = src->data.range(999, 992);  						//		reserve	 <	8	>
	dest->protocol = src->data.range(991, 984);  						//		protocol	 <	8	>
	dest->connNum = src->data.range(983, 976);  						//		connNum	 <	8	>
	dest->splitId = src->data.range(975, 968);  						//		splitId	 <	8	>
	dest->sequenceNumber = src->data.range(967, 936);  						//		sequenceNumber	 <	32	>
	dest->second = src->data.range(935, 904);  						//		second	 <	32	>
	dest->nanos = src->data.range(903, 872);  						//		nanos	 <	32	>
	dest->orderBookId = src->data.range(871, 840);  						//		orderBookId	 <	32	>
	dest->maximumLevel = src->data.range(839, 832);  						//		maximumLevel	 <	8	>
	dest->levelUpdateAction = src->data.range(831, 824);  						//		levelUpdateAction	 <	8	>
	dest->side = src->data.range(823, 816);  						//		side	 <	8	>
	dest->level = src->data.range(815, 808);  						//		level	 <	8	>
	dest->price = src->data.range(807, 776);  						//		price	 <	32	>
	dest->quantity = src->data.range(775, 712);  						//		quantity	 <	64	>
	dest->numberOfDeletes = src->data.range(711, 708);  						//		numberOfDeletes	 <	4	>
	dest->hasRemaining = src->data.range(707, 704);  						//		hasRemaining	 <	4	>

	return;
}

template <typename T>
void mmInterface::itchTickSizeTableMessagePack(ItchTickSizeTableMessage_t *src, T *dest)
{
#pragma HLS INLINE

	dest->data.range(1023, 1016) = src->messageType;  						//	messageType	 <	8	>
	dest->data.range(1015, 1000) = src->symbolIndex;  						//	symbolIndex	 <	16	>
	dest->data.range(999, 992) = src->reserve;  						//	reserve	 <	8	>
	dest->data.range(991, 984) = src->protocol;  						//	protocol	 <	8	>
	dest->data.range(983, 976) = src->connNum;  						//	connNum	 <	8	>
	dest->data.range(975, 968) = src->splitId;  						//	splitId	 <	8	>
	dest->data.range(967, 936) = src->sequenceNumber;  						//	sequenceNumber	 <	32	>
	dest->data.range(935, 904) = src->second;  						//	second	 <	32	>
	dest->data.range(903, 872) = src->nanos;  						//	nanos	 <	32	>
	dest->data.range(871, 840) = src->orderBookId;  						//	orderBookId	 <	32	>
	dest->data.range(839, 776) = src->tickSize;  						//	tickSize	 <	64	>
	dest->data.range(775, 744) = src->priceFrom;  						//	priceFrom	 <	32	>
	dest->data.range(743, 712) = src->priceTo;  						//	priceTo	 	<	32	>

	return;
}

template <typename T>
void mmInterface::itchTickSizeTableMessageUnpack(T *src, ItchTickSizeTableMessage_t *dest)
{
#pragma HLS INLINE

	dest->messageType = src->data.range(1023, 1016);  						//		messageType	 <	8	>
	dest->symbolIndex = src->data.range(1015, 1000);  						//		symbolIndex	 <	16	>
	dest->reserve = src->data.range(999, 992);  						//		reserve	 <	8	>
	dest->protocol = src->data.range(991, 984);  						//		protocol	 <	8	>
	dest->connNum = src->data.range(983, 976);  						//		connNum	 <	8	>
	dest->splitId = src->data.range(975, 968);  						//		splitId	 <	8	>
	dest->sequenceNumber = src->data.range(967, 936);  						//		sequenceNumber	 <	32	>
	dest->second = src->data.range(935, 904);  						//		second	 <	32	>
	dest->nanos = src->data.range(903, 872);  						//		nanos	 <	32	>
	dest->orderBookId = src->data.range(871, 840);  						//		orderBookId	 <	32	>
	dest->tickSize = src->data.range(839, 776);  						//		tickSize	 <	64	>
	dest->priceFrom = src->data.range(775, 744);  						//		priceFrom	 <	32	>
	dest->priceTo = src->data.range(743, 712);  						//		priceTo	 <	32	>

	return;
}

template <typename T>
void mmInterface::itchPriceLimitMessagePack(ItchPriceLimitMessage_t *src, T *dest)
{
#pragma HLS INLINE

	dest->data.range(1023, 1016) = src->messageType;  						//	messageType	 <	8	>
	dest->data.range(1015, 1000) = src->symbolIndex;  						//	symbolIndex	 <	16	>
	dest->data.range(999, 992) = src->reserve;  						//	reserve	 <	8	>
	dest->data.range(991, 984) = src->protocol;  						//	protocol	 <	8	>
	dest->data.range(983, 976) = src->connNum;  						//	connNum	 <	8	>
	dest->data.range(975, 968) = src->splitId;  						//	splitId	 <	8	>
	dest->data.range(967, 936) = src->sequenceNumber;  						//	sequenceNumber	 <	32	>
	dest->data.range(935, 904) = src->second;  						//	second	 <	32	>
	dest->data.range(903, 872) = src->nanos;  						//	nanos	 <	32	>
	dest->data.range(871, 840) = src->orderBookId;  						//	orderBookId	 <	32	>
	dest->data.range(839, 808) = src->upperLimit;  						//	upperLimit	 <	32	>
	dest->data.range(807, 776) = src->lowerLimit;  						//	lowerLimit	 <	32	>

	return;
}

template <typename T>
void mmInterface::itchPriceLimitMessageUnpack(T *src, ItchPriceLimitMessage_t *dest)
{
#pragma HLS INLINE

	dest->messageType = src->data.range(1023, 1016);  						//		messageType	 <	8	>
	dest->symbolIndex = src->data.range(1015, 1000);  						//		symbolIndex	 <	16	>
	dest->reserve = src->data.range(999, 992);  						//		reserve	 <	8	>
	dest->protocol = src->data.range(991, 984);  						//		protocol	 <	8	>
	dest->connNum = src->data.range(983, 976);  						//		connNum	 <	8	>
	dest->splitId = src->data.range(975, 968);  						//		splitId	 <	8	>
	dest->sequenceNumber = src->data.range(967, 936);  						//		sequenceNumber	 <	32	>
	dest->second = src->data.range(935, 904);  						//		second	 <	32	>
	dest->nanos = src->data.range(903, 872);  						//		nanos	 <	32	>
	dest->orderBookId = src->data.range(871, 840);  						//		orderBookId	 <	32	>
	dest->upperLimit = src->data.range(839, 808);  						//		upperLimit	 <	32	>
	dest->lowerLimit = src->data.range(807, 776);  						//		lowerLimit	 <	32	>

	return;
}

template <typename T>
void mmInterface::itchOrderBookStateMessagePack(ItchOrderBookStateMessage_t *src, T *dest)
{
#pragma HLS INLINE

	dest->data.range(1023, 1016) = src->messageType;  					//	messageType	 <	8	>
	dest->data.range(1015, 1000) = src->symbolIndex;  					//	symbolIndex	 <	16	>
	dest->data.range(999, 992) = src->reserve;  					//	reserve	 <	8	>
	dest->data.range(991, 984) = src->protocol;  					//	protocol	 <	8	>
	dest->data.range(983, 976) = src->connNum;  					//	connNum	 <	8	>
	dest->data.range(975, 968) = src->splitId;  					//	splitId	 <	8	>
	dest->data.range(967, 936) = src->sequenceNumber;  					//	sequenceNumber	 <	32	>
	dest->data.range(935, 904) = src->second;  					//	second	 <	32	>
	dest->data.range(903, 872) = src->nanos;  					//	nanos	 <	32	>
	dest->data.range(871, 840) = src->orderBookId;  					//	orderBookId	 <	32	>
	dest->data.range(839, 680) = byteReverse<160>(src->stateName)	;  //	stateName	 <	160	>

	return;
}

template <typename T>
void mmInterface::itchOrderBookStateMessageUnpack(T *src, ItchOrderBookStateMessage_t *dest)
{
#pragma HLS INLINE

	dest->messageType = src->data.range(1023, 1016);  					//		messageType	 <	8	>
	dest->symbolIndex = src->data.range(1015, 1000);  					//		symbolIndex	 <	16	>
	dest->reserve = src->data.range(999, 992);  					//		reserve	 <	8	>
	dest->protocol = src->data.range(991, 984);  					//		protocol	 <	8	>
	dest->connNum = src->data.range(983, 976);  					//		connNum	 <	8	>
	dest->splitId = src->data.range(975, 968);  					//		splitId	 <	8	>
	dest->sequenceNumber = src->data.range(967, 936);  					//		sequenceNumber	 <	32	>
	dest->second = src->data.range(935, 904);  					//		second	 <	32	>
	dest->nanos = src->data.range(903, 872);  					//		nanos	 <	32	>
	dest->orderBookId = src->data.range(871, 840);  					//		orderBookId	 <	32	>
	dest->stateName = byteReverse<160>(src->data.range(839, 680));  					//		stateName	 <	160	>
	return;
}

template <typename T>
void mmInterface::itchHaltInformationMessagePack(ItchHaltInformationMessage_t *src, T *dest)
{
#pragma HLS INLINE

	dest->data.range(1023, 1016) = src->messageType;  					//	messageType	 <	8	>
	dest->data.range(1015, 1000) = src->symbolIndex;  					//	symbolIndex	 <	16	>
	dest->data.range(999, 992) = src->reserve;  					//	reserve	 <	8	>
	dest->data.range(991, 984) = src->protocol;  					//	protocol	 <	8	>
	dest->data.range(983, 976) = src->connNum;  					//	connNum	 <	8	>
	dest->data.range(975, 968) = src->splitId;  					//	splitId	 <	8	>
	dest->data.range(967, 936) = src->sequenceNumber;  					//	sequenceNumber	 <	32	>
	dest->data.range(935, 904) = src->second;  					//	second	 <	32	>
	dest->data.range(903, 872) = src->nanos;  					//	nanos	 <	32	>
	dest->data.range(871, 840) = src->orderBookId;  					//	orderBookId	 <	32	>
	dest->data.range(839, 680) = byteReverse<160>(src->instrumentState);  					//	stateName	 <	160	>

	return;
}

template <typename T>
void mmInterface::itchhHaltInformationMessageUnpack(T *src, ItchHaltInformationMessage_t *dest)
{
#pragma HLS INLINE

	dest->messageType = src->data.range(1023, 1016);  					//		messageType	 <	8	>
	dest->symbolIndex = src->data.range(1015, 1000);  					//		symbolIndex	 <	16	>
	dest->reserve = src->data.range(999, 992);  					//		reserve	 <	8	>
	dest->protocol = src->data.range(991, 984);  					//		protocol	 <	8	>
	dest->connNum = src->data.range(983, 976);  					//		connNum	 <	8	>
	dest->splitId = src->data.range(975, 968);  					//		splitId	 <	8	>
	dest->sequenceNumber = src->data.range(967, 936);  					//		sequenceNumber	 <	32	>
	dest->second = src->data.range(935, 904);  					//		second	 <	32	>
	dest->nanos = src->data.range(903, 872);  					//		nanos	 <	32	>
	dest->orderBookId = src->data.range(871, 840);  					//		orderBookId	 <	32	>
	dest->instrumentState = byteReverse<160>(src->data.range(839, 680));  					//		stateName	 <	160	>

	return;
}

template <typename T>
void mmInterface::itchTradeTickerMessagePack(ItchTradeTickerMessage_t *src, T *dest)
{
#pragma HLS INLINE

	dest->data.range(1023, 1016) = src->messageType;  					//	messageType	 <	8	>
	dest->data.range(1015, 1000) = src->symbolIndex;  					//	symbolIndex	 <	16	>
	dest->data.range(999, 992) = src->reserve;  					//	reserve	 <	8	>
	dest->data.range(991, 984) = src->protocol;  					//	protocol	 <	8	>
	dest->data.range(983, 976) = src->connNum;  					//	connNum	 <	8	>
	dest->data.range(975, 968) = src->splitId;  					//	splitId	 <	8	>
	dest->data.range(967, 936) = src->sequenceNumber;  					//	sequenceNumber	 <	32	>
	dest->data.range(935, 904) = src->second;  					//	second	 <	32	>
	dest->data.range(903, 872) = src->nanos;  					//	nanos	 <	32	>
	dest->data.range(871, 840) = src->orderBookId;  					//	orderBookId	 <	32	>
	dest->data.range(839, 776) = src->dealId;  					//	dealId	 <	64	>
	dest->data.range(775, 768) = src->dealSource;  					//	dealSource	 <	8	>
	dest->data.range(767, 736) = src->price;  					//	price	 <	32	>
	dest->data.range(735, 672) = src->quantity;  					//	quantity	 <	64	>
	dest->data.range(671, 608) = src->dealDateTime;  					//	dealDateTime	 <	64	>
	dest->data.range(607, 600) = src->action;  					//	action	 <	8	>
	dest->data.range(599, 592) = src->aggressor;  					//	aggressor	 <	8	>
	dest->data.range(591, 576) = src->tradeReportCode;  					//	tradeReportCode	 <	16	>

	return;
}

template <typename T>
void mmInterface::itchTradeTickerMessageUnpack(T *src, ItchTradeTickerMessage_t *dest)
{
#pragma HLS INLINE

	dest->messageType = src->data.range(1023, 1016);  					//		messageType	 <	8	>
	dest->symbolIndex = src->data.range(1015, 1000);  					//		symbolIndex	 <	16	>
	dest->reserve = src->data.range(999, 992);  					//		reserve	 <	8	>
	dest->protocol = src->data.range(991, 984);  					//		protocol	 <	8	>
	dest->connNum = src->data.range(983, 976);  					//		connNum	 <	8	>
	dest->splitId = src->data.range(975, 968);  					//		splitId	 <	8	>
	dest->sequenceNumber = src->data.range(967, 936);  					//		sequenceNumber	 <	32	>
	dest->second = src->data.range(935, 904);  					//		second	 <	32	>
	dest->nanos = src->data.range(903, 872);  					//		nanos	 <	32	>
	dest->orderBookId = src->data.range(871, 840);  					//		orderBookId	 <	32	>
	dest->dealId = src->data.range(839, 776);  					//		dealId	 <	64	>
	dest->dealSource = src->data.range(775, 768);  					//		dealSource	 <	8	>
	dest->price = src->data.range(767, 736);  					//		price	 <	32	>
	dest->quantity = src->data.range(735, 672);  					//		quantity	 <	64	>
	dest->dealDateTime = src->data.range(671, 608);  					//		dealDateTime	 <	64	>
	dest->action = src->data.range(607, 600);  					//		action	 <	8	>
	dest->aggressor = src->data.range(599, 592);  					//		aggressor	 <	8	>
	dest->tradeReportCode = src->data.range(591, 576);  					//		tradeReportCode	 <	16	>

	return;
}

template <typename T>
void mmInterface::itchLimitOrderBookPack(ItchLimitOrderBookMessage_t *src, T *dest)
{
#pragma HLS INLINE

	dest->data.range(1023, 1016) = src->messageType;  					//	messageType	 <	8	>
	dest->data.range(1015, 1000) = src->symbolIndex;  					//	symbolIndex	 <	16	>
	dest->data.range(999, 992) = src->reserve;  					//	reserve	 <	8	>
	dest->data.range(991, 984) = src->protocol;  					//	protocol	 <	8	>
	dest->data.range(983, 976) = src->connNum;  					//	connNum	 <	8	>
	dest->data.range(975, 968) = src->splitId;  					//	splitId	 <	8	>
	dest->data.range(967, 936) = src->sequenceNumber;  					//	sequenceNumber	 <	32	>
	dest->data.range(935, 904) = src->second;  					//	second	 <	32	>
	dest->data.range(903, 872) = src->nanos;  					//	nanos	 <	32	>
	dest->data.range(871, 840) = src->orderBookId;  					//	orderBookId	 <	32	>
	dest->data.range(839, 712) = src->bidPrice;  					//	bidPrice	 <	128	>
	dest->data.range(711, 456) = src->bidQuantity;  					//	bidQuantity	 <	256	>
	dest->data.range(455, 328) = src->askPrice;  					//	askPrice	 <	128	>
	dest->data.range(327, 72) = src->askQuantity;  					//	askQuantity	 <	256	>

	return;
}

template <typename T>
void mmInterface::itchLimitOrderBookUnpack(T *src, ItchLimitOrderBookMessage_t *dest)
{
#pragma HLS INLINE

	dest->messageType = src->data.range(1023, 1016);  						//		messageType	 <	8	>
	dest->symbolIndex = src->data.range(1015, 1000);  						//		symbolIndex	 <	16	>
	dest->reserve = src->data.range(999, 992);  						//		reserve	 <	8	>
	dest->protocol = src->data.range(991, 984);  						//		protocol	 <	8	>
	dest->connNum = src->data.range(983, 976);  						//		connNum	 <	8	>
	dest->splitId = src->data.range(975, 968);  						//		splitId	 <	8	>
	dest->sequenceNumber = src->data.range(967, 936);  						//		sequenceNumber	 <	32	>
	dest->second = src->data.range(935, 904);  						//		second	 <	32	>
	dest->nanos = src->data.range(903, 872);  						//		nanos	 <	32	>
	dest->orderBookId = src->data.range(871, 840);  						//		orderBookId	 <	32	>
	dest->bidPrice = src->data.range(839, 712);  						//		bidPrice	 <	128	>
	dest->bidQuantity = src->data.range(711, 456);  						//		bidQuantity	 <	256	>
	dest->askPrice = src->data.range(455, 328);  						//		askPrice	 <	128	>
	dest->askQuantity = src->data.range(327, 72);  						//		askQuantity	 <	256	>

	return;
}

template <typename T>
void mmInterface::itchIndexPriceMessagePack(ItchIndexPriceMessage_t *src, T *dest)
{
#pragma HLS INLINE
	dest->data.range(1023, 1016) = 'x';  						//	messageType	 <	8	>
	dest->data.range(1015, 1000) = src->symbolIndex;  						//	symbolIndex	 <	16	>
	dest->data.range(999, 992) = src->reserve;  						//	reserve	 <	8	>
	dest->data.range(991, 984) = src->protocol;  						//	protocol	 <	8	>
	dest->data.range(983, 976) = src->connNum;  						//	connNum	 <	8	>
	dest->data.range(975, 968) = src->splitId;  						//	splitId	 <	8	>
	dest->data.range(967, 936) = src->sequenceNumber;  						//	sequenceNumber	 <	32	>
	dest->data.range(935, 904) = src->second;  						//	second	 <	32	>
	dest->data.range(903, 872) = src->nanos;  						//	nanos	 <	32	>
	dest->data.range(871, 840) = src->orderBookId;  						//	orderBookId	 <	32	>
	dest->data.range(839, 776) = src->value;  						//	value	 <	64	>
	dest->data.range(775, 712) = src->highValue;  						//	highValue	 <	64	>
	dest->data.range(711, 648) = src->lowValue;  						//	lowValue	 <	64	>
	dest->data.range(647, 584) = src->openValue;  						//	openValue	 <	64	>
	dest->data.range(583, 520) = src->tradedVolume;  						//	tradedVolume	 <	64	>
	dest->data.range(519, 456) = src->tradedValue;  						//	tradedValue	 <	64	>
	dest->data.range(455, 392) = src->change;  						//	change	 <	64	>
	dest->data.range(391, 360) = src->changePercent;  						//	changePercent	 <	32	>
	dest->data.range(359, 296) = src->previousClose;  						//	previousClose	 <	64	>
	dest->data.range(295, 232) = src->close;  						//	close	 <	64	>

	return;
}

template <typename T>
void mmInterface::itchIndexPriceMessageUnpack(T *src, ItchIndexPriceMessage_t *dest)
{
#pragma HLS INLINE

	dest->messageType = src->data.range(1023, 1016);  						//		messageType	 <	8	>
	dest->symbolIndex = src->data.range(1015, 1000);  						//		symbolIndex	 <	16	>
	dest->reserve = src->data.range(999, 992);  						//		reserve	 <	8	>
	dest->protocol = src->data.range(991, 984);  						//		protocol	 <	8	>
	dest->connNum = src->data.range(983, 976);  						//		connNum	 <	8	>
	dest->splitId = src->data.range(975, 968);  						//		splitId	 <	8	>
	dest->sequenceNumber = src->data.range(967, 936);  						//		sequenceNumber	 <	32	>
	dest->second = src->data.range(935, 904);  						//		second	 <	32	>
	dest->nanos = src->data.range(903, 872);  						//		nanos	 <	32	>
	dest->orderBookId = src->data.range(871, 840);  						//		orderBookId	 <	32	>
	dest->value = src->data.range(839, 776);  						//		value	 <	64	>
	dest->highValue = src->data.range(775, 712);  						//		highValue	 <	64	>
	dest->lowValue = src->data.range(711, 648);  						//		lowValue	 <	64	>
	dest->openValue = src->data.range(647, 584);  						//		openValue	 <	64	>
	dest->tradedVolume = src->data.range(583, 520);  						//		tradedVolume	 <	64	>
	dest->tradedValue = src->data.range(519, 456);  						//		tradedValue	 <	64	>
	dest->change = src->data.range(455, 392);  						//		change	 <	64	>
	dest->changePercent = src->data.range(391, 360);  						//		changePercent	 <	32	>
	dest->previousClose = src->data.range(359, 296);  						//		previousClose	 <	64	>
	dest->close = src->data.range(295, 232);  						//		close	 <	64	>

	return;
}

template <typename T>
void mmInterface::itchEquilibriumPriceMessagePack(ItchEquilibriumPriceMessage_t *src, T *dest)
{
#pragma HLS INLINE

	dest->data.range(1023, 1016) = src->messageType;  					//	messageType	 <	8	>
	dest->data.range(1015, 1000) = src->symbolIndex;  					//	symbolIndex	 <	16	>
	dest->data.range(999, 992) = src->reserve;  					//	reserve	 <	8	>
	dest->data.range(991, 984) = src->protocol;  					//	protocol	 <	8	>
	dest->data.range(983, 976) = src->connNum;  					//	connNum	 <	8	>
	dest->data.range(975, 968) = src->splitId;  					//	splitId	 <	8	>
	dest->data.range(967, 936) = src->sequenceNumber;  					//	sequenceNumber	 <	32	>
	dest->data.range(935, 904) = src->second;  					//	second	 <	32	>
	dest->data.range(903, 872) = src->nanos;  					//	nanos	 <	32	>
	dest->data.range(871, 840) = src->orderBookId;  					//	orderBookId	 <	32	>
	dest->data.range(839, 776) = src->bidQuantity;  					//	bidQuantity	 <	64	>
	dest->data.range(775, 712) = src->askQuantity;  					//	askQuantity	 <	64	>
	dest->data.range(711, 680) = src->equilibriumPrice;  					//	equilibriumPrice	 <	32	>

	return;
}

template <typename T>
void mmInterface::itchEquilibriumPriceMessageUnpack(T *src, ItchEquilibriumPriceMessage_t *dest)
{
#pragma HLS INLINE

	dest->messageType = src->data.range(1023, 1016);  					//		messageType	 <	8	>
	dest->symbolIndex = src->data.range(1015, 1000);  					//		symbolIndex	 <	16	>
	dest->reserve = src->data.range(999, 992);  					//		reserve	 <	8	>
	dest->protocol = src->data.range(991, 984);  					//		protocol	 <	8	>
	dest->connNum = src->data.range(983, 976);  					//		connNum	 <	8	>
	dest->splitId = src->data.range(975, 968);  					//		splitId	 <	8	>
	dest->sequenceNumber = src->data.range(967, 936);  					//		sequenceNumber	 <	32	>
	dest->second = src->data.range(935, 904);  					//		second	 <	32	>
	dest->nanos = src->data.range(903, 872);  					//		nanos	 <	32	>
	dest->orderBookId = src->data.range(871, 840);  					//		orderBookId	 <	32	>
	dest->bidQuantity = src->data.range(839, 776);  					//		bidQuantity	 <	64	>
	dest->askQuantity = src->data.range(775, 712);  					//		askQuantity	 <	64	>
	dest->equilibriumPrice = src->data.range(711, 680);  					//		equilibriumPrice	 <	32	>

	return;
}

template <typename T>
void mmInterface::itchMarketStatisticMessagePack(ItchMarketStatisticMessage_t *src, T *dest)
{
#pragma HLS INLINE

	dest->data.range(1023, 1016) = src->messageType;  					//	messageType	 <	8	>
	dest->data.range(1015, 1000) = src->symbolIndex;  					//	symbolIndex	 <	16	>
	dest->data.range(999, 992) = src->reserve;  					//	reserve	 <	8	>
	dest->data.range(991, 984) = src->protocol;  					//	protocol	 <	8	>
	dest->data.range(983, 976) = src->connNum;  					//	connNum	 <	8	>
	dest->data.range(975, 968) = src->splitId;  					//	splitId	 <	8	>
	dest->data.range(967, 936) = src->sequenceNumber;  					//	sequenceNumber	 <	32	>
	dest->data.range(935, 904) = src->second;  					//	second	 <	32	>
	dest->data.range(903, 872) = src->nanos;  					//	nanos	 <	32	>
	dest->data.range(871, 776) = byteReverse<96>(src->marketStatsId);  					//	marketStatsId	 <	96	>
	dest->data.range(775, 752) = byteReverse<24>(src->currency);  					//	currency	 <	24	>
	dest->data.range(751, 688) = src->marketStatsTime;  					//	marketStatsTime	 <	64	>
	dest->data.range(687, 656) = src->totalTrade;  					//	totalTrade	 <	32	>
	dest->data.range(655, 592) = src->totalQuantity;  					//	totalQuantity	 <	64	>
	dest->data.range(591, 528) = src->totalValue;  					//	totalValue	 <	64	>
	dest->data.range(527, 464) = src->upQuantity;  					//	upQuantity	 <	64	>
	dest->data.range(463, 400) = src->downQuantity;  					//	downQuantity	 <	64	>
	dest->data.range(399, 336) = src->noChangeVolume;  					//	noChangeVolume	 <	64	>
	dest->data.range(335, 304) = src->upShares;  					//	upShares	 <	32	>
	dest->data.range(303, 272) = src->downShares;  					//	downShares	 <	32	>
	dest->data.range(271, 240) = src->noChangeShares;  					//	noChangeShares	 <	32	>

	return;
}

template <typename T>
void mmInterface::itchMarketStatisticMessageUnpack(T *src, ItchMarketStatisticMessage_t *dest)
{
#pragma HLS INLINE

	dest->messageType = src->data.range(1023, 1016);  						//		messageType	 <	8	>
	dest->symbolIndex = src->data.range(1015, 1000);  						//		symbolIndex	 <	16	>
	dest->reserve = src->data.range(999, 992);  						//		reserve	 <	8	>
	dest->protocol = src->data.range(991, 984);  						//		protocol	 <	8	>
	dest->connNum = src->data.range(983, 976);  						//		connNum	 <	8	>
	dest->splitId = src->data.range(975, 968);  						//		splitId	 <	8	>
	dest->sequenceNumber = src->data.range(967, 936);  						//		sequenceNumber	 <	32	>
	dest->second = src->data.range(935, 904);  						//		second	 <	32	>
	dest->nanos = src->data.range(903, 872);  						//		nanos	 <	32	>
	dest->marketStatsId = byteReverse<96>(src->data.range(871, 776));  						//		marketStatsId	 <	96	>
	dest->currency = byteReverse<24>(src->data.range(775, 752));  						//		currency	 <	24	>
	dest->marketStatsTime = src->data.range(751, 688);  						//		marketStatsTime	 <	64	>
	dest->totalTrade = src->data.range(687, 656);  						//		totalTrade	 <	32	>
	dest->totalQuantity = src->data.range(655, 592);  						//		totalQuantity	 <	64	>
	dest->totalValue = src->data.range(591, 528);  						//		totalValue	 <	64	>
	dest->upQuantity = src->data.range(527, 464);  						//		upQuantity	 <	64	>
	dest->downQuantity = src->data.range(463, 400);  						//		downQuantity	 <	64	>
	dest->noChangeVolume = src->data.range(399, 336);  						//		noChangeVolume	 <	64	>
	dest->upShares = src->data.range(335, 304);  						//		upShares	 <	32	>
	dest->downShares = src->data.range(303, 272);  						//		downShares	 <	32	>
	dest->noChangeShares = src->data.range(271, 240);  						//		noChangeShares	 <	32	>

	return;
}

template <typename T>
void mmInterface::itchiNAVMessagePack(ItchiNAVMessage_t *src, T *dest)
{
#pragma HLS INLINE

	dest->data.range(1023, 1016) = src->messageType;  						//	messageType	 <	8	>
	dest->data.range(1015, 1000) = src->symbolIndex;  						//	symbolIndex	 <	16	>
	dest->data.range(999, 992) = src->reserve;  						//	reserve	 <	8	>
	dest->data.range(991, 984) = src->protocol;  						//	protocol	 <	8	>
	dest->data.range(983, 976) = src->connNum;  						//	connNum	 <	8	>
	dest->data.range(975, 968) = src->splitId;  						//	splitId	 <	8	>
	dest->data.range(967, 936) = src->sequenceNumber;  						//	sequenceNumber	 <	32	>
	dest->data.range(935, 904) = src->second;  						//	second	 <	32	>
	dest->data.range(903, 872) = src->nanos;  						//	nanos	 <	32	>
	dest->data.range(871, 840) = src->orderBookId;  						//	orderBookId	 <	32	>
	dest->data.range(839, 808) = src->iNAV;  						//	iNAV	 <	32	>
	dest->data.range(807, 776) = src->change;  						//	change	 <	32	>
	dest->data.range(775, 744) = src->percentChange;  						//	percentChange	 <	32	>
	dest->data.range(743, 680) = src->timeStamp;  						//	timeStamp	 <	64	>

	return;
}

template <typename T>
void mmInterface::itchiNAVMessageUnpack(T *src, ItchiNAVMessage_t *dest)
{
#pragma HLS INLINE

	dest->messageType = src->data.range(1023, 1016);  						//		messageType	 <	8	>
	dest->symbolIndex = src->data.range(1015, 1000);  						//		symbolIndex	 <	16	>
	dest->reserve = src->data.range(999, 992);  						//		reserve	 <	8	>
	dest->protocol = src->data.range(991, 984);  						//		protocol	 <	8	>
	dest->connNum = src->data.range(983, 976);  						//		connNum	 <	8	>
	dest->splitId = src->data.range(975, 968);  						//		splitId	 <	8	>
	dest->sequenceNumber = src->data.range(967, 936);  						//		sequenceNumber	 <	32	>
	dest->second = src->data.range(935, 904);  						//		second	 <	32	>
	dest->nanos = src->data.range(903, 872);  						//		nanos	 <	32	>
	dest->orderBookId = src->data.range(871, 840);  						//		orderBookId	 <	32	>
	dest->iNAV = src->data.range(839, 808);  						//		iNAV	 <	32	>
	dest->change = src->data.range(807, 776);  						//		change	 <	32	>
	dest->percentChange = src->data.range(775, 744);  						//		percentChange	 <	32	>
	dest->timeStamp = src->data.range(743, 680);  						//		timeStamp	 <	64	>

	return;
}

template <typename T>
void mmInterface::itchTradeStatisticMessagePack(ItchTradeStatisticMessage_t *src, T *dest)
{
#pragma HLS INLINE

	dest->data.range(1023, 1016) = src->messageType;  						//	messageType	 <	8	>
	dest->data.range(1015, 1000) = src->symbolIndex;  						//	symbolIndex	 <	16	>
	dest->data.range(999, 992) = src->reserve;  						//	reserve	 <	8	>
	dest->data.range(991, 984) = src->protocol;  						//	protocol	 <	8	>
	dest->data.range(983, 976) = src->connNum;  						//	connNum	 <	8	>
	dest->data.range(975, 968) = src->splitId;  						//	splitId	 <	8	>
	dest->data.range(967, 936) = src->sequenceNumber;  						//	sequenceNumber	 <	32	>
	dest->data.range(935, 904) = src->second;  						//	second	 <	32	>
	dest->data.range(903, 872) = src->nanos;  						//	nanos	 <	32	>
	dest->data.range(871, 840) = src->orderBookId;  						//	orderBookId	 <	32	>
	dest->data.range(839, 808) = src->openPrice;  						//	openPrice	 <	32	>
	dest->data.range(807, 776) = src->highPrice;  						//	highPrice	 <	32	>
	dest->data.range(775, 744) = src->lowPrice;  						//	lowPrice	 <	32	>
	dest->data.range(743, 712) = src->lastPrice;  						//	lastPrice	 <	32	>
	dest->data.range(711, 680) = src->lastAuctionPrice;  						//	lastAuctionPrice	 <	32	>
	dest->data.range(679, 616) = src->turnoverQuantity;  						//	turnoverQuantity	 <	64	>
	dest->data.range(615, 552) = src->reportedTurnoverQuantity;  						//	reportedTurnoverQuantity	 <	64	>
	dest->data.range(551, 488) = src->turnoverValue;  						//	turnoverValue	 <	64	>
	dest->data.range(487, 424) = src->reportedTurnoverValue;  						//	reportedTurnoverValue	 <	64	>
	dest->data.range(423, 392) = src->averagePrice;  						//	averagePrice	 <	32	>
	dest->data.range(391, 328) = src->totalNumberOfTrades;  						//	totalNumberOfTrades	 <	64	>

	return;
}

template <typename T>
void mmInterface::itchTradeStatisticMessageUnpack(T *src, ItchTradeStatisticMessage_t *dest)
{
#pragma HLS INLINE

	dest->messageType = src->data.range(1023, 1016);  						//		messageType	 <	8	>
	dest->symbolIndex = src->data.range(1015, 1000);  						//		symbolIndex	 <	16	>
	dest->reserve = src->data.range(999, 992);  						//		reserve	 <	8	>
	dest->protocol = src->data.range(991, 984);  						//		protocol	 <	8	>
	dest->connNum = src->data.range(983, 976);  						//		connNum	 <	8	>
	dest->splitId = src->data.range(975, 968);  						//		splitId	 <	8	>
	dest->sequenceNumber = src->data.range(967, 936);  						//		sequenceNumber	 <	32	>
	dest->second = src->data.range(935, 904);  						//		second	 <	32	>
	dest->nanos = src->data.range(903, 872);  						//		nanos	 <	32	>
	dest->orderBookId = src->data.range(871, 840);  						//		orderBookId	 <	32	>
	dest->openPrice = src->data.range(839, 808);  						//		openPrice	 <	32	>
	dest->highPrice = src->data.range(807, 776);  						//		highPrice	 <	32	>
	dest->lowPrice = src->data.range(775, 744);  						//		lowPrice	 <	32	>
	dest->lastPrice = src->data.range(743, 712);  						//		lastPrice	 <	32	>
	dest->lastAuctionPrice = src->data.range(711, 680);  						//		lastAuctionPrice	 <	32	>
	dest->turnoverQuantity = src->data.range(679, 616);  						//		turnoverQuantity	 <	64	>
	dest->reportedTurnoverQuantity = src->data.range(615, 552);  						//		reportedTurnoverQuantity	 <	64	>
	dest->turnoverValue = src->data.range(551, 488);  						//		turnoverValue	 <	64	>
	dest->reportedTurnoverValue = src->data.range(487, 424);  						//		reportedTurnoverValue	 <	64	>
	dest->averagePrice = src->data.range(423, 392);  						//		averagePrice	 <	32	>
	dest->totalNumberOfTrades = src->data.range(391, 328);  						//		totalNumberOfTrades	 <	64	>

	return;
}

template <typename T>
void mmInterface::itchOrderBookDirectoryCompactPack(ItchOrderBookDirectoryCompact_t *src, T *dest)
{
#pragma HLS INLINE

	dest->data.range(1023, 1016) = src->messageType;  						//	messageType	 <	8	>
	dest->data.range(1015, 1000) = src->symbolIndex;  						//	symbolIndex	 <	16	>
	dest->data.range(999, 992) = src->reserve;  						//	reserve	 <	8	>
	dest->data.range(991, 984) = src->protocol;  						//	protocol	 <	8	>
	dest->data.range(983, 976) = src->connNum;  						//	connNum	 <	8	>
	dest->data.range(975, 968) = src->splitId;  						//	splitId	 <	8	>
	dest->data.range(967, 936) = src->sequenceNumber;  						//	sequenceNumber	 <	32	>
	dest->data.range(935, 904) = src->second;  						//	second	 <	32	>
	dest->data.range(903, 872) = src->nanos;  						//	nanos	 <	32	>
	dest->data.range(871, 840) = src->orderBookId;  						//	orderBookId	 <	32	>
	dest->data.range(839, 584) = byteReverse<256>(src->symbol);  						//	symbol	 <	256	>
	dest->data.range(583, 328) = byteReverse<256>(src->longName);  						//	longName	 <	256	>
	dest->data.range(327, 304) = byteReverse<24>(src->financialProduct);  						//	financialProduct	 <	24	>
	dest->data.range(303, 288) = src->decimalInPrice;  						//	decimalInPrice	 <	16	>
	dest->data.range(287, 256) = src->roundLotSize;  						//	roundLotSize	 <	32	>
	dest->data.range(255, 248) = src->marketCode;  						//	marketCode	 <	8	>
	dest->data.range(247, 176) = byteReverse<72>(src->corporateActionCode);  						//	corporateActionCode	 <	72	>
	dest->data.range(175, 104) = byteReverse<72>(src->notificationSign);  						//	notificationSign	 <	72	>
	dest->data.range(103, 32) = byteReverse<72>(src->otherSign);  						//	otherSign	 <	72	>
	dest->data.range(31, 24) = src->allowNVDR;  						//	allowNVDR	 <	8	>
	dest->data.range(23, 16) = src->allowShortSell;  						//	allowShortSell	 <	8	>
	dest->data.range(15, 8) = src->allowShortSellOnNVDR;  						//	allowShortSellOnNVDR	 <	8	>

	return;
}

template <typename T>
void mmInterface::itchOrderBookDirectoryCompactUnpack(T *src, ItchOrderBookDirectoryCompact_t *dest)
{
#pragma HLS INLINE

	dest->messageType = src->data.range(1023, 1016);  							//		messageType	 <	8	>
	dest->symbolIndex = src->data.range(1015, 1000);  							//		symbolIndex	 <	16	>
	dest->reserve = src->data.range(999, 992);  							//		reserve	 <	8	>
	dest->protocol = src->data.range(991, 984);  							//		protocol	 <	8	>
	dest->connNum = src->data.range(983, 976);  							//		connNum	 <	8	>
	dest->splitId = src->data.range(975, 968);  							//		splitId	 <	8	>
	dest->sequenceNumber = src->data.range(967, 936);  							//		sequenceNumber	 <	32	>
	dest->second = src->data.range(935, 904);  							//		second	 <	32	>
	dest->nanos = src->data.range(903, 872);  							//		nanos	 <	32	>
	dest->orderBookId = src->data.range(871, 840);  							//		orderBookId	 <	32	>
	dest->symbol = byteReverse<256>(src->data.range(839, 584));  							//		symbol	 <	256	>
	dest->longName = byteReverse<256>(src->data.range(583, 328));  							//		longName	 <	256	>
	dest->financialProduct = byteReverse<24>(src->data.range(327, 304));  							//		financialProduct	 <	24	>
	dest->decimalInPrice = src->data.range(303, 288);  							//		decimalInPrice	 <	16	>
	dest->roundLotSize = src->data.range(287, 256);  							//		roundLotSize	 <	32	>
	dest->marketCode = src->data.range(255, 248);  							//		marketCode	 <	8	>
	dest->corporateActionCode = byteReverse<72>(src->data.range(247, 176));  							//		corporateActionCode	 <	72	>
	dest->notificationSign = byteReverse<72>(src->data.range(175, 104));  							//		notificationSign	 <	72	>
	dest->otherSign = byteReverse<72>(src->data.range(103, 32));  							//		otherSign	 <	72	>
	dest->allowNVDR = src->data.range(31, 24);  							//		allowNVDR	 <	8	>
	dest->allowShortSell = src->data.range(23, 16);  							//		allowShortSell	 <	8	>
	dest->allowShortSellOnNVDR = src->data.range(15, 8);  							//		allowShortSellOnNVDR	 <	8	>

	return;
}

template <typename T>
void mmInterface::itchGlimpseEndMessagePack(ItchGlimpseEndMessage_t *src, T *dest)
{
#pragma HLS INLINE

	dest->data.range(1023, 1016) = src->messageType;  							//	messageType	 <	8	>
	dest->data.range(1015, 1000) = src->symbolIndex;  							//	symbolIndex	 <	16	>
	dest->data.range(999, 992) = src->reserve;  							//	reserve	 <	8	>
	dest->data.range(991, 984) = src->protocol;  							//	protocol	 <	8	>
	dest->data.range(983, 976) = src->connNum;  							//	connNum	 <	8	>
	dest->data.range(975, 968) = src->splitId;  							//	splitId	 <	8	>
	dest->data.range(967, 936) = src->sequenceNumber;  							//	sequenceNumber	 <	32	>
	dest->data.range(935, 904) = src->second;  							//	second	 <	32	>
	dest->data.range(903, 872) = src->nanos;  							//	nanos	 <	32	>
	dest->data.range(871, 712) = src->glimpseEnd;  							//	GlimpseEnd	 <	160	>

	return;
}

template <typename T>
void mmInterface::itchGlimpseEndMessageUnpack(T *src, ItchGlimpseEndMessage_t *dest)
{
#pragma HLS INLINE

	dest->messageType = src->data.range(1023, 1016);  							//		messageType	 <	8	>
	dest->symbolIndex = src->data.range(1015, 1000);  							//		symbolIndex	 <	16	>
	dest->reserve = src->data.range(999, 992);  							//		reserve	 <	8	>
	dest->protocol = src->data.range(991, 984);  							//		protocol	 <	8	>
	dest->connNum = src->data.range(983, 976);  							//		connNum	 <	8	>
	dest->splitId = src->data.range(975, 968);  							//		splitId	 <	8	>
	dest->sequenceNumber = src->data.range(967, 936);  							//		sequenceNumber	 <	32	>
	dest->second = src->data.range(935, 904);  							//		second	 <	32	>
	dest->nanos = src->data.range(903, 872);  							//		nanos	 <	32	>
	dest->glimpseEnd = src->data.range(871, 712);  							//		GlimpseEnd	 <	160	>

	return;
}

template <typename T>
void mmInterface::itchOtherMessagePack(ItchOtherMessage_t *src, T *dest)
{
#pragma HLS INLINE

	dest->data.range(1023, 1016) = src->messageType;  							//	messageType	 <	8	>
	dest->data.range(1015, 1000) = src->symbolIndex;  							//	symbolIndex	 <	16	>
	dest->data.range(999, 992) = src->reserve;  							//	reserve	 <	8	>
	dest->data.range(991, 984) = src->protocol;  							//	protocol	 <	8	>
	dest->data.range(983, 976) = src->connNum;  							//	connNum	 <	8	>
	dest->data.range(975, 968) = src->splitId;  							//	splitId	 <	8	>
	dest->data.range(967, 936) = src->sequenceNumber;  							//	sequenceNumber	 <	32	>
	dest->data.range(935, 904) = src->second;  							//	second	 <	32	>
	dest->data.range(903, 872) = src->nanos;  							//	nanos	 <	32	>
	dest->data.range(871, 616) = src->word;  							//	word	 <	256	>

	return;
}

template <typename T>
void mmInterface::itchOtherMessageUnpack(T *src, ItchOtherMessage_t *dest)
{
#pragma HLS INLINE

	dest->messageType = src->data.range(1023, 1016);  							//		messageType	 <	8	>
	dest->symbolIndex = src->data.range(1015, 1000);  							//		symbolIndex	 <	16	>
	dest->reserve = src->data.range(999, 992);  							//		reserve	 <	8	>
	dest->protocol = src->data.range(991, 984);  							//		protocol	 <	8	>
	dest->connNum = src->data.range(983, 976);  							//		connNum	 <	8	>
	dest->splitId = src->data.range(975, 968);  							//		splitId	 <	8	>
	dest->sequenceNumber = src->data.range(967, 936);  							//		sequenceNumber	 <	32	>
	dest->second = src->data.range(935, 904);  							//		second	 <	32	>
	dest->nanos = src->data.range(903, 872);  							//		nanos	 <	32	>
	dest->word = src->data.range(871, 616);  							//		word	 <	256	>

	return;
}
typedef struct cntOuchMsg_t
{
	ap_uint32_t resp_A_B;
	ap_uint32_t resp_C_B;
	ap_uint32_t resp_U_B;
	ap_uint32_t resp_E_B;
	ap_uint32_t resp_E_S;
	ap_uint32_t resp_A_S;
	ap_uint32_t resp_C_S;
	ap_uint32_t resp_U_S;
	ap_uint32_t rxNasdaqStream;

} cntOuchMsg_t;

typedef struct memoryControl_t
{
	ap_uint32_t control;
	ap_uint32_t index;
	ap_uint32_t dimension;
	ap_int64_t credit;

} memoryControl_t;

typedef struct memoryBlock_t
{
	positionInfoPack_t positionWdBlock;
	positionInfoPack_t positionRdBlock;
	orderInfoPack_t orderInfoRead;
	orderInfoPack_t orderInfoWrite;
	tokenMapPack_t replaceMapRead;
	tokenMapPack_t replaceMapWrite;

} memoryBlock_t;	

typedef struct memStatus_t
{
	ap_int64_t creditStatus;
	ap_int64_t creditLimitOrg;
	ap_uint32_t fetchPositionCount;
	ap_uint32_t updatePositionCount;
	ap_uint32_t fetchCreditCount;
	ap_uint32_t updateCreditCount;
	ap_uint32_t newOrderInfoCount;
	ap_uint32_t fetchOrderInfoCount;
	ap_uint32_t updateOrderInfoCount;
	ap_uint32_t updateReplaceCount;
	ap_uint32_t fetchPositionFound;
	ap_uint32_t updatePositionFound;
	ap_uint32_t newOrderInfoFound;
	ap_uint32_t fetchOrderInfoFound;
	ap_uint32_t updateOrderInfoFound;
	ap_uint32_t updateReplaceFound;

	ap_uint32_t updateReplaceNoFound;
	ap_uint32_t updateReplaceFull;
	ap_uint32_t fetchReplaceFound;
	ap_uint32_t fetchReplaceNoFound;
	ap_uint32_t fetchReplaceCount;

	ap_uint32_t fetchPositionNoFound;
	ap_uint32_t updatePositionNoFound;
	ap_uint32_t updatePositionFull;
	ap_uint32_t newOrderInfoFull;
	ap_uint32_t fetchOrderInfoNoFound;
	ap_uint32_t updateOrderInfoNoFound;
	ap_uint32_t delOrderInfoCount;
	ap_uint32_t delOrderInfoNoFound;

	ap_uint32_t delReplaceMapCount;
	ap_uint32_t delReplaceMapNoFound;

} memStatus_t;

typedef struct sbiCheckControl_t
{
	ap_uint32_t control;
	ap_uint32_t index;

} sbiCheckControl_t;

typedef struct sbiCheckMemBlock_t
{
	ap_uint32_t orderBookID;

} sbiCheckMemBlock_t;

typedef struct tickerReg_t
{
	ap_uint<32> regTickerMsgRxCnt;
	ap_uint<32> regLmtOrdBookMsgRxCnt;
	ap_uint<32> regTickerOpCnt;
	ap_uint<32> regTickerBlCnt;




} tickerReg_t;

typedef struct tickerCheckControl_t
{
	ap_uint32_t control;
	ap_uint32_t index;

} tickerCheckControl_t;


typedef struct tickerMemBlock_t
{
	ap_uint16_t decimalInPrice;
	ap_uint32_t orderBookID;
	ap_uint32_t lastPrice;
	ap_uint32_t plus5percent;
	ap_uint32_t minus5percent;
	ap_int<32> bidPrice0;
	ap_int<32> bidPrice1;
	ap_int<32> askPrice0;
	ap_int<32> askPrice1;
	ap_int<32> upper;
	ap_int<32> lower;

} tickerMemBlock_t;

typedef struct priceLmtCheckCtrl_t
{
	ap_uint32_t control;
	ap_uint32_t index;

}priceLmtCheckCtrl_t;

typedef struct priceLmtMemBlock_t
{
	ap_uint16_t decimalInPrice;
	ap_uint32_t orderBookID;
	ap_int32_t upperLimit;
	ap_int32_t lowerLimit;

} priceLmtMemBlock_t;

typedef struct rejectMemCtrl_t
{
	ap_uint32_t control;
	ap_uint32_t index;

} rejectMemCtrl_t;

typedef struct testBlockMemBlock_t
{
	ap_uint8_t side;
	ap_uint16_t symbolIndex;
	ap_uint32_t orderBookID;
	ap_uint32_t price;
	ap_uint64_t qty;

}testBlockMemBlock_t;

typedef struct memCtrl_t
{
	ap_uint32_t control;
	ap_uint32_t index;
	ap_uint32_t stateMsgRec;
}memCtrl_t;

typedef struct stateMsgMemBlock_t
{
	ap_uint16_t symbolIndex;
	ap_uint32_t orderBookID;
	ap_uint<160> stateName;
	ap_uint1_t tradable;
}stateMsgMemBlock_t;

typedef struct orderBookMemBlock_t
{
	ap_uint16_t symbolIndex;
	ap_int<320> bidPrice;
	ap_uint<640> bidQuantity;
	ap_int<320> askPrice;
	ap_uint<640> askQuantity;
} orderBookMemBlock_t;


typedef struct stateMsgStatus_t
{
	ap_uint32_t inhibitStateMsgStatus;
	ap_uint32_t nasdaqStateMsgCnt;
	ap_uint32_t stateMsgOpCnt;
	ap_uint32_t stateMsgBlCnt;
}stateMsgCnt_t;

typedef struct peCtrl_t
{
	ap_uint32_t control;
	ap_uint32_t index;
	ap_uint32_t currentMsRd;
	ap_uint32_t currentMsWr;

}peCtrl_t;

typedef struct peProcessMemBlock_t
{
	ap_uint32_t orderBookID;
	ap_uint32_t Ul;
	ap_uint32_t Dw;
	ap_uint32_t isCall;

}peProcessMemBlock_t;

typedef struct pePullStatus_t
{
	ap_uint32_t RxCounter;
	ap_uint32_t TxtradeTickerCnt;
	ap_uint32_t TxLmtOrdBookCnt;
	ap_uint32_t TxStateMsgCnt;
	ap_uint32_t regRxEvent;

}pePullStatus_t;

typedef struct peStateMsg_t
{
	ap_uint32_t second;
	ap_uint32_t nanos;
	ap_uint8_t tradable;
}peStateMsg_t;

typedef struct peOnTradeEventCtrl_t
{
	ap_uint32_t control;
	ap_uint32_t index;
	ap_uint32_t filterTimeDiff;
} peOnTradeEventCtrl_t;



typedef struct peStrategyParam_t
{
	ap_uint16_t symbolIndex;
	ap_uint64_t targetTradeAskMiss;
	ap_uint64_t targetTradeUp100;
	ap_uint64_t targetTradeBidMiss;
	ap_uint64_t targetTradeDown100;
	ap_uint1_t Down100Traded;
	ap_uint1_t BidMissTraded;
	ap_uint1_t Up100Traded;
	ap_uint1_t AskMissTraded;
	ap_uint64_t cumuBidTradeValue;
	ap_uint64_t cumuBidTradeVol;
	ap_uint64_t cumuAskTradeValue;
	ap_uint64_t cumuAskTradeVol;
	ap_int32_t ask0;
	ap_int32_t ask1;
	ap_int32_t bid0;
	ap_int32_t bid1;
	ap_uint32_t filterUp100Time;
	ap_uint32_t filterAskMissTime;
	ap_uint32_t filterDown100Time;
	ap_uint32_t filterBidMissTime;
	ap_uint64_t vAsk0;
	ap_uint64_t vBid0;
	ap_uint64_t vAsk1;
	ap_uint64_t vBid1;

}peStrategyParam_t;

typedef struct peOnTradeTickMemBlock_t
{
	ap_uint64_t tradeUp100MinValue =0;
	ap_uint64_t tradeDown100MinValue =0;
	ap_uint64_t tradeUp100MinVolume =0;
	ap_uint64_t tradeDown100MinVolume =0;
	ap_uint64_t tradeAskMissMinVolume =0;
	ap_uint64_t tradeBidMissMinVolume =0;

}peOnTradeTickMemBlock_t;

typedef struct peOnMrkByLvlCtrl_t
{
	ap_uint32_t control;
	ap_uint32_t index;
	ap_uint32_t filterTimeDiff;
}peOnMrkByLvlCtrl_t;

typedef struct peOnMrkByLvlStatus_t
{
	ap_uint32_t savePriceCnt=0;
	ap_uint32_t trigUp100Cnt=0;
	ap_uint32_t trigDown100Cnt=0;
	ap_uint32_t trigAskMissCnt=0;
	ap_uint32_t trigBidMissCnt=0;
	ap_uint32_t txStreamCnt;

} peOnMrkByLvlStatus_t;


typedef struct peOnTradeEventStatus_t
{
	ap_uint32_t rxStream;
	ap_uint32_t trigUp100Cnt;
	ap_uint32_t trigDown100Cnt;
	ap_uint32_t trigAskMissCnt;
	ap_uint32_t trigBidMissCnt;
	ap_uint32_t RxParaCnt;
	ap_uint32_t trigWriteCnt;
}tradeTickerStatus_t;

typedef struct checkTimerScheduler_t
{
	ap_uint32_t openTime;
	ap_uint32_t stopBuyIdle;
	ap_uint32_t idleTimeStart;
	ap_uint32_t idleTimeEnd;
	ap_uint32_t stopBuy;
	ap_uint32_t closeTime;

}checkTimerScheduler_t;

typedef struct regCheckTimerStatus_t
{
	ap_uint32_t rxStreamCnt;
	ap_uint32_t txStreamCnt;
	ap_uint32_t condCnt;

}checkTimerStatus_t;

typedef struct regCheckTimerCond_t
{
	ap_uint32_t regEnumSchedule;

}regCheckTimerCond_t;

typedef struct eventHandStatus_t
{
	ap_uint32_t regRxEvent;
	ap_uint32_t regTxEvent;
	regCheckTimerCond_t condRd;

}eventHandStatus_t;

#endif



