#include "timer_kernels.hpp"
#include "timer.hpp"
#include <iostream>
#include <stack>
#include <stdio.h>
#include <stdlib.h>

#define MEM_REG_RD (1 << 0)
#define MEM_REG_WR (1 << 1)

int main()
{ 
	timer intf;
	timerCtrl_t ctrl;
  timerStatus_t status;
  timerInputPack_t mem_rd;
  timerInputPack_t mem_wr;
  ap_uint32_t rxEvent;
  hls::stream<timerInputPackStream_t> timerInputStreamPack;
	hls::stream<timerOutputPackStream_t> timerOutputStreamPack;
	hls::stream<clockTickGeneratorEvent_t> eventStream;

	static clockTickGeneratorEvent_t tickEvent;
	static timerInputPack_t dataPrepare;
	timerInputPackStream_t timerInPackStream;
	timerOutputPackStream_t timerOutPackStream;
	timerOutputPack_t output;
	std::cout << "Hello_tb" << std::endl;
	ctrl.control = 0; // have to initialize control at beginning

	for (int i = 0; i < 50; i++)
		{
			//call top lvl for each loop
			timerTop(ctrl,status,mem_rd,mem_wr,rxEvent,timerInputStreamPack,timerOutputStreamPack,eventStream);

			if ((i%20) == 0 )// call ever every 20th for event (0,20,40,60,80 etc ...)
			{
					if (i != 0)
						{
							tickEvent.data = 1;
							eventStream.write(tickEvent);
							printf("tickEvent i = %d \n",i);
						}
			}
			if (i == 0)
				{
					ctrl.control = 0 ;
				}
			if (i == 5)
				{
					dataPrepare.index = 1;
					dataPrepare.msgType = 'o';
					dataPrepare.ask0 = 100;
					dataPrepare.ask1 = 101;
					dataPrepare.bid0 = 99;
					dataPrepare.bid1 = 98;
					dataPrepare.vAsk0 = 20000;
					dataPrepare.vAsk1 = 40000;
					dataPrepare.vBid0 = 30000;
					dataPrepare.vBid1 = 50000;
					dataPrepare.side = 'B';
					intf.timerInputPack(&dataPrepare, &timerInPackStream);
					timerInputStreamPack.write(timerInPackStream);
				}
			else if (i == 15)
				{
					dataPrepare.index = 2;
					dataPrepare.msgType = 'o';
					dataPrepare.ask0 = 100 + i;
					dataPrepare.ask1 = 101 + i;
					dataPrepare.bid0 = 99 + i;
					dataPrepare.bid1 = 98 + i;
					dataPrepare.vAsk0 = 20000 + (i*1000);
					dataPrepare.vAsk1 = 40000 + (i*1000);
					dataPrepare.vBid0 = 30000 + (i*1000);
					dataPrepare.vBid1 = 50000 + (i*1000);
					dataPrepare.side = 'B';
					intf.timerInputPack(&dataPrepare, &timerInPackStream);
					timerInputStreamPack.write(timerInPackStream);
				}
			else if (i == 25)
				{
					dataPrepare.index = 3;
					dataPrepare.msgType = 'o';
					dataPrepare.ask0 = 100 + i;
					dataPrepare.ask1 = 101 + i;
					dataPrepare.bid0 = 99 + i;
					dataPrepare.bid1 = 98 + i;
					dataPrepare.vAsk0 = 20000 + (i*1000);
					dataPrepare.vAsk1 = 40000 + (i*1000);
					dataPrepare.vBid0 = 30000 + (i*1000);
					dataPrepare.vBid1 = 50000 + (i*1000);
					dataPrepare.side = 'B';
					intf.timerInputPack(&dataPrepare, &timerInPackStream);
					timerInputStreamPack.write(timerInPackStream);
				}
			else if (i == 35)
				{
					dataPrepare.index = 4;
					dataPrepare.msgType = 'o';
					dataPrepare.ask0 = 100 + i;
					dataPrepare.ask1 = 101 + i;
					dataPrepare.bid0 = 99 + i;
					dataPrepare.bid1 = 98 + i;
					dataPrepare.vAsk0 = 20000 + (i * 1000);
					dataPrepare.vAsk1 = 40000 + (i * 1000);
					dataPrepare.vBid0 = 30000 + (i * 1000);
					dataPrepare.vBid1 = 50000 + (i * 1000);
					dataPrepare.side = 'B';
					intf.timerInputPack (&dataPrepare,&timerInPackStream);
					timerInputStreamPack.write (timerInPackStream);
				}

			// if (!timerOutputStreamPack.empty())
			// 	{
			// 		timerOutPackStream = timerOutputStreamPack.read();
			// 		intf.timerOutUnPack(&timerOutPackStream, &output);
			// 		printf("index =%d |msgType =%s |side =%s |bidTg =%d |askTg =%d |vAskTg =%d |vBidTg =%d  \n",
			// 		output.index,output.msgType,output.side,output.bidTrigger,output.askTrigger,
			// 		output.vAskTrigger,output.vBidTrigger);

			// 	}
		}

	printf("status timer rxStream = %d | txStream = %d | rxEvent = %d \n",status.rxStream,status.txStream,rxEvent);
}

