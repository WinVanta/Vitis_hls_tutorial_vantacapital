
#include "timer.hpp"
#include <iostream>

void timer::timerInputPack(timerInputPack_t *src, timerInputPackStream_t *dest)
{
#pragma HLS INLINE
    dest->data.range(415, 408) = src->msgType; //	msgType	 <	8	>
    dest->data.range(407, 392) = src->index;   //	index	 <	16	>
    dest->data.range(391, 384) = src->side;    //	side	 <	8	>
    dest->data.range(383, 352) = src->bid0;    //	bid0	 <	32	>
    dest->data.range(351, 320) = src->bid1;    //	bid1	 <	32	>
    dest->data.range(319, 288) = src->ask0;    //	ask0	 <	32	>
    dest->data.range(287, 256) = src->ask1;    //	ask1	 <	32	>
    dest->data.range(255, 192) = src->vBid0;   //	vBid0	 <	64	>
    dest->data.range(191, 128) = src->vBid1;   //	vBid1	 <	64	>
    dest->data.range(127, 64) = src->vAsk0;    //	vAsk0	 <	64	>
    dest->data.range(63, 0) = src->vAsk1;      //	vAsk1	 <	64	>
    return;
}

void timer::timerInputUnPack(timerInputPackStream_t *src, timerInputPack_t *dest)
{
    #pragma HLS INLINE

    dest->msgType = src->data.range(415, 408); //		msgType	 <	8	>
    dest->index = src->data.range(407, 392);   //		index	 <	16	>
    dest->side = src->data.range(391, 384);    //		side	 <	8	>
    dest->bid0 = src->data.range(383, 352);    //		bid0	 <	32	>
    dest->bid1 = src->data.range(351, 320);    //		bid1	 <	32	>
    dest->ask0 = src->data.range(319, 288);    //		ask0	 <	32	>
    dest->ask1 = src->data.range(287, 256);    //		ask1	 <	32	>
    dest->vBid0 = src->data.range(255, 192);   //		vBid0	 <	64	>
    dest->vBid1 = src->data.range(191, 128);   //		vBid1	 <	64	>
    dest->vAsk0 = src->data.range(127, 64);    //		vAsk0	 <	64	>
    dest->vAsk1 = src->data.range(63, 0);      //		vAsk1	 <	64	>
    return;

}


void timer::timerOutPack (timerOutputPack_t*src, timerOutputPackStream_t *dest)
{
    #pragma HLS INLINE

    dest->data.range(		223	,	216	)= src->	msgType	;//	msgType	 <	8	>
    dest->data.range(		215	,	200	)= src->	index	;//	index	 <	16	>
    dest->data.range(		199	,	192	)= src->	side	;//	side	 <	8	>
    dest->data.range(		191	,	160	)= src->	bidTrigger	;//	bidTrigger	 <	32	>
    dest->data.range(		159	,	128	)= src->	askTrigger	;//	askTrigger	 <	32	>
    dest->data.range(		127	,	64	)= src->	vBidTrigger	;//	vBidTrigger	 <	64	>
    dest->data.range(		63	,	0	)= src->	vAskTrigger	;//	vAskTrigger	 <	64	>
    return;

}

void timer::timerOutUnPack (timerOutputPackStream_t *src,timerOutputPack_t *dest )
{    
    #pragma HLS INLINE

    dest->	msgType	= src->data.range(	223	,	216	);//		msgType	 <	8	>
    dest->	index	= src->data.range(	215	,	200	);//		index	 <	16	>
    dest->	side	= src->data.range(	199	,	192	);//		side	 <	8	>
    dest->	bidTrigger	= src->data.range(	191	,	160	);//		bidTrigger	 <	32	>
    dest->	askTrigger	= src->data.range(	159	,	128	);//		askTrigger	 <	32	>
    dest->	vBidTrigger	= src->data.range(	127	,	64	);//		vBidTrigger	 <	64	>
    dest->	vAskTrigger	= src->data.range(	63	,	0	);//		vAskTrigger	 <	64	>
    return;

}

void timer::checkTimer(timerCtrl_t &ctrl,
                       timerStatus_t &status,
                       timerInputPack_t &mem_rd,
                       timerInputPack_t &mem_wr,
                       hls::stream<ap_uint32_t> &currentMs,
                       hls::stream<timerInputPackStream_t> &timerInputStreamPack,
                       hls::stream<timerOutputPackStream_t> &timerOutputStreamPack)

{
#pragma HLS PIPELINE

		static timer intf;
    static ap_uint32_t currentMsSave;
    static timerInputPack_t memTimer[NUM_SYMBOL];
    timerInputPackStream_t timerInPackStream;
    timerOutputPackStream_t timerOutPackStream;
    static timerInputPack_t timerIn;
    static timerOutputPack_t timerOut;
    static timerStatus_t statusTmp;
    enum stateType
    {
        pull,
		save,
        encode,
        write,
    };
    static stateType state = pull;
    switch (state)
    {
    case pull:
        if(!currentMs.empty())
        {   
            CDEBUG("currentMS arrive")
            currentMsSave = currentMs.read();
            state = encode;
        }
        else if (!timerInputStreamPack.empty())
        {
        		statusTmp.rxStream++;
        		timerInPackStream = timerInputStreamPack.read();
        		intf.timerInputUnPack(&timerInPackStream, &timerIn);
        		printf("stream in index = %d | ask0 =%d \n",timerIn.index,timerIn.ask0);
            state = save;
        }
        else if (ctrl.control & MEM_REG_RD)
        {
        		mem_rd = memTimer[ctrl.index];
        }
        else if (ctrl.control & MEM_REG_WR)
        {
        		memTimer[ctrl.index] = mem_wr;
        }
        break;

    case save:

//    	memTimer[timerIn.index] = timerIn;
    	CDEBUG("save statement")
    	state = pull;

    	break;
    case encode:
        timerOut.msgType = timerIn.msgType;
        timerOut.index = timerIn.index;
        timerOut.side = timerIn.side;
        timerOut.bidTrigger = timerIn.bid0 + currentMsSave;
        timerOut.askTrigger = timerIn.ask0 + currentMsSave;
        timerOut.vBidTrigger = timerIn.vBid0 + timerIn.vBid1;
        timerOut.vAskTrigger = timerIn.vAsk0 + timerIn.vAsk1;
        state = write;
        CDEBUG("encode statement")
        break;
    case write:
		CDEBUG("write statement")
  		statusTmp.txStream++;
        CDEBUG("write cnt ok")

        intf.timerOutPack(&timerOut,&timerOutPackStream);
        CDEBUG("write Pack ok")
        timerOutputStreamPack.write(timerOutPackStream);
        printf("index =%d |msgType =%d |side =%d |bidTg =%d |askTg =%d |vAskTg =%d |vBidTg =%d  \n",
					timerOut.index,timerOut.msgType,timerOut.side,timerOut.bidTrigger,timerOut.askTrigger,
					timerOut.vAskTrigger,timerOut.vBidTrigger);
        state = pull;
        break;
    }
    status = statusTmp;
    return;
}

void timer::eventHandler(ap_uint32_t &rxEvent,
                         hls::stream<clockTickGeneratorEvent_t> &eventStream,
                         hls::stream<ap_uint32_t> &currentMs)
{
    clockTickGeneratorEvent_t tickEvent;
    static ap_uint32_t event;
    enum stateType
    {
        read,
        write,
    };
    static stateType state = read;

    switch (state)
    {
    case read:
        if (!eventStream.empty())
        {
            eventStream.read(tickEvent);
            event++;
            state = write;
        }
        break;

    case write:
        CDEBUG("event write")
        currentMs.write(event);
        state = read;
        break;
    }
    rxEvent = event;
    return;
}
