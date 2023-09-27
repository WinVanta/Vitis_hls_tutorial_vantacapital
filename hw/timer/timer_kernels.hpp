

#ifndef TIMER_KERNELS_H
#define TIMER_KERNELS_H

#include "timer.hpp"

extern "C" void timerTop (timerCtrl_t &ctrl,
						  timerStatus_t &status,
						  timerInputPack_t &mem_rd,
						  timerInputPack_t &mem_wr,
						  ap_uint32_t &rxEvent,
						  hls::stream<timerInputPackStream_t> &timerInputStreamPack,
						  hls::stream<timerOutputPackStream_t> &timerOutputStreamPack,
						  hls::stream<clockTickGeneratorEvent_t> &eventStream);

#endif