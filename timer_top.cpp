

#include "timer_kernels.hpp"

extern "C" void timerTop (timerCtrl_t &ctrl,
						  timerStatus_t &status,
						  timerInputPack_t &mem_rd,
						  timerInputPack_t &mem_wr,
						  ap_uint32_t &rxEvent,
						  hls::stream<timerInputPackStream_t> &timerInputStreamPack,
						  hls::stream<timerOutputPackStream_t> &timerOutputStreamPack,
						  hls::stream<clockTickGeneratorEvent_t> &eventStream)
{

#pragma HLS INTERFACE s_axilite port=ctrl bundle = control
#pragma HLS INTERFACE s_axilite port=status bundle = control
#pragma HLS INTERFACE s_axilite port=mem_rd bundle = control
#pragma HLS INTERFACE s_axilite port=mem_wr bundle = control
#pragma HLS INTERFACE s_axilite port=rxEvent bundle = control

#pragma HLS DISAGGREGATE variable = ctrl
#pragma HLS DISAGGREGATE variable = status
#pragma HLS DISAGGREGATE variable = mem_rd
#pragma HLS DISAGGREGATE variable = mem_wr


#pragma HLS INTERFACE axis register port = timerInputStreamPack
#pragma HLS INTERFACE axis register port = timerOutputStreamPack

#pragma HLS INTERFACE axis register port = eventStream
#pragma HLS INTERFACE ap_ctrl_none port = return

static hls::stream<ap_uint32_t> currentMsFIFO;
#pragma HLS STREAM variable = currentMsFIFO depth = 512



#pragma HLS DATAFLOW

    static timer kernel;

    kernel.checkTimer(ctrl,status,mem_rd,mem_wr,currentMsFIFO,timerInputStreamPack,timerOutputStreamPack);
    kernel.eventHandler(rxEvent,eventStream,currentMsFIFO);

}
