

#include "timer_kernels.hpp"

extern "C" void timerTop ()
{


#pragma HLS INTERFACE ap_ctrl_none port = return



#pragma HLS DATAFLOW

    static timer kernel;


}
