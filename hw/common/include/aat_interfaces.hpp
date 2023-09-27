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

typedef ap_axiu<8, 0, 0, 0> clockTickGeneratorEvent_t;



class mmInterface
{
public:

private:
};

#endif



