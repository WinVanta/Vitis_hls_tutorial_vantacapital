#ifndef TIMER_H
#define TIMER_H

#include "hls_stream.h"
#include "ap_int.h"
#include "aat_defines.hpp"
#include "aat_interfaces.hpp"

#define MEM_REG_RD (1 << 0)
#define MEM_REG_WR (1 << 1)

typedef struct timerCtrl_t
{
    ap_uint32_t control;
    ap_uint32_t index;


} timerCtrl_t;

typedef struct timerStatus_t
{
    ap_uint32_t rxStream;
    ap_uint32_t txStream;

} timerStatus_t;

typedef struct timerInputPack_t
{
    ap_uint8_t msgType;
    ap_uint16_t index;
    ap_uint8_t side;
    ap_int32_t bid0;
    ap_int32_t bid1;
    ap_int32_t ask0;
    ap_int32_t ask1;
    ap_uint64_t vBid0;
    ap_uint64_t vBid1;
    ap_uint64_t vAsk0;
    ap_uint64_t vAsk1;

} timerInputPack_t;

typedef struct timerOutputPack_t
{
    ap_uint8_t msgType;
    ap_uint16_t index;
    ap_uint8_t side;
    ap_int32_t bidTrigger;
    ap_int32_t askTrigger;
    ap_uint64_t vBidTrigger;
    ap_uint64_t vAskTrigger;

} timerOutputPack_t;

typedef ap_axiu<512, 0, 0, 0> timerInputPackStream_t;
typedef ap_axiu<256, 0, 0, 0> timerOutputPackStream_t;


class timer
{
public:
    void timerInputPack(timerInputPack_t *src, timerInputPackStream_t *dest);
    void timerInputUnPack(timerInputPackStream_t *src, timerInputPack_t *dest);

    void timerOutPack (timerOutputPack_t*src, timerOutputPackStream_t *dest);
    void timerOutUnPack (timerOutputPackStream_t *src,timerOutputPack_t *dest );

    void checkTimer(timerCtrl_t &ctrl,
                    timerStatus_t &status,
                    timerInputPack_t &mem_rd,
                    timerInputPack_t &mem_wr,
                    hls::stream<ap_uint32_t> &currentMs,
                    hls::stream<timerInputPackStream_t> &timerInputStreamPack,
                    hls::stream<timerOutputPackStream_t> &timerOutputStreamPack);

    void eventHandler(ap_uint32_t &rxEvent,
                      hls::stream<clockTickGeneratorEvent_t> &eventStream,
                      hls::stream<ap_uint32_t> &currentMs);
};

#endif

