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

#include "aat_defines.hpp"
#include "aat_interfaces.hpp"

void mmInterface::orderBookOperationPack(orderBookOperation_t *src,
										 orderBookOperationPack_t *dest)
{
#pragma HLS INLINE

	dest->data.range(223, 160) = src->timestamp;
	dest->data.range(159, 152) = src->opCode;
	dest->data.range(151, 144) = src->symbolIndex;
	dest->data.range(143, 112) = src->orderId;
	dest->data.range(111, 80) = src->orderCount;
	dest->data.range(79, 48) = src->quantity;
	dest->data.range(47, 16) = src->price;
	dest->data.range(15, 8) = src->direction;
	dest->data.range(7, 0) = src->level;

	return;
}

void mmInterface::orderBookOperationUnpack(orderBookOperationPack_t *src,
										   orderBookOperation_t *dest)
{
#pragma HLS INLINE

	dest->timestamp = src->data.range(223, 160);
	dest->opCode = src->data.range(159, 152);
	dest->symbolIndex = src->data.range(151, 144);
	dest->orderId = src->data.range(143, 112);
	dest->orderCount = src->data.range(111, 80);
	dest->quantity = src->data.range(79, 48);
	dest->price = src->data.range(47, 16);
	dest->direction = src->data.range(15, 8);
	dest->level = src->data.range(7, 0);

	return;
}

void mmInterface::orderBookResponsePack(orderBookResponse_t *src,
										orderBookResponsePack_t *dest)
{
#pragma HLS INLINE

	dest->data.range(1023, 968) = src->timestamp;
	dest->data.range(967, 960) = src->symbolIndex;
	dest->data.range(959, 800) = src->bidCount;
	dest->data.range(799, 640) = src->bidPrice;
	dest->data.range(639, 480) = src->bidQuantity;
	dest->data.range(479, 320) = src->askCount;
	dest->data.range(319, 160) = src->askPrice;
	dest->data.range(159, 0) = src->askQuantity;

	return;
}

void mmInterface::orderBookResponseUnpack(orderBookResponsePack_t *src,
										  orderBookResponse_t *dest)
{
#pragma HLS INLINE

	dest->timestamp = src->data.range(1023, 968);
	dest->symbolIndex = src->data.range(967, 960);
	dest->bidCount = src->data.range(959, 800);
	dest->bidPrice = src->data.range(799, 640);
	dest->bidQuantity = src->data.range(639, 480);
	dest->askCount = src->data.range(479, 320);
	dest->askPrice = src->data.range(319, 160);
	dest->askQuantity = src->data.range(159, 0);

	return;
}

void mmInterface::orderEntryEncodePack(orderEntryOperationEncode_t *src, txMsgPack_t *dest)
{
#pragma HLS INLINE

	dest->data.range(1351, 1336) = src->symbolIndex; //	symbolIndex	 <	16	>
	dest->data.range(1335, 1328) = src->lgNdMSB;	 //	lgNdMSB	 <	8	>
	dest->data.range(1327, 1320) = src->lgNdLSB;	 //	lgNdLSB	 <	8	>
	dest->data.range(1319, 1312) = src->seqUnq;		 //	seqUnq	 <	8	>
	dest->data.range(1311, 1304) = src->msgType;	 //	msgType	 <	8	>
	dest->data.range(1303, 1192) = src->extOrdToken; //	extOrdToken	 <	112	>
	dest->data.range(1191, 1080) = src->repOrdToken; //	repOrdToken	 <	112	>
	dest->data.range(1079, 1048) = src->ordBookID;	 //	*ordBookID	 <	32	>
	dest->data.range(1047, 1040) = src->side;		 //	side	 <	8	>
	dest->data.range(1039, 976) = src->qty;			 //	qty	 <	64	>
	dest->data.range(975, 944) = src->price;		 //	price	 <	32	>
	dest->data.range(943, 936) = src->timeInFc;		 //	timeInFc	 <	8	>
	dest->data.range(935, 928) = src->opCl;			 //	opCl	 <	8	>
	dest->data.range(927, 848) = src->account;		 //	account	 <	80	>
	dest->data.range(847, 840) = src->invTy;		 //	invTy	 <	8	>
	dest->data.range(839, 720) = src->custInfo;		 //	custInfo	 <	120	>
	dest->data.range(719, 464) = src->exInfo;		 //	exInfo	 <	256	>
	dest->data.range(463, 400) = src->disQty;		 //	disQty	 <	64	>
	dest->data.range(399, 320) = src->ordInfo;		 //	ordInfo	 <	80	>
	dest->data.range(319, 288) = src->crosKey;		 //	crosKey	 <	32	>
	dest->data.range(287, 280) = src->ordTyp;		 //	ordTyp	 <	8	>
	dest->data.range(279, 272) = src->trigTy;		 //	trigTy	 <	8	>
	dest->data.range(271, 264) = src->trigPcTy;		 //	trigPcTy	 <	8	>
	dest->data.range(263, 232) = src->trigOrdBoID;	 //	trigOrdBoID	 <	32	>
	dest->data.range(231, 200) = src->trigPc;		 //	trigPc	 <	32	>
	dest->data.range(199, 168) = src->trigSesTyID;	 //	trigSesTyID	 <	32	>
	dest->data.range(167, 136) = src->valTdata;		 //	valTdata	 <	32	>
	dest->data.range(135, 72) = src->dealID;		 //	dealID	 <	64	>
	dest->data.range(71, 8) = src->ordID;			 //	ordID	 <	64	>
	dest->data.range(7, 0) = src->NVDR;				 //	NVDR	 <	8	>

	return;
}

void mmInterface::orderEntryEncodeUnpack(txMsgPack_t *src, orderEntryOperationEncode_t *dest)
{
#pragma HLS INLINE

	dest->symbolIndex = src->data.range(1351, 1336); //		symbolIndex	 <	16	>
	dest->lgNdMSB = src->data.range(1335, 1328);	 //		lgNdMSB	 <	8	>
	dest->lgNdLSB = src->data.range(1327, 1320);	 //		lgNdLSB	 <	8	>
	dest->seqUnq = src->data.range(1319, 1312);		 //		seqUnq	 <	8	>
	dest->msgType = src->data.range(1311, 1304);	 //		msgType	 <	8	>
	dest->extOrdToken = src->data.range(1303, 1192); //		extOrdToken	 <	112	>
	dest->repOrdToken = src->data.range(1191, 1080); //		repOrdToken	 <	112	>
	dest->ordBookID = src->data.range(1079, 1048);	 //		*ordBookID	 <	32	>
	dest->side = src->data.range(1047, 1040);		 //		side	 <	8	>
	dest->qty = src->data.range(1039, 976);			 //		qty	 <	64	>
	dest->price = src->data.range(975, 944);		 //		price	 <	32	>
	dest->timeInFc = src->data.range(943, 936);		 //		timeInFc	 <	8	>
	dest->opCl = src->data.range(935, 928);			 //		opCl	 <	8	>
	dest->account = src->data.range(927, 848);		 //		account	 <	80	>
	dest->invTy = src->data.range(847, 840);		 //		invTy	 <	8	>
	dest->custInfo = src->data.range(839, 720);		 //		custInfo	 <	120	>
	dest->exInfo = src->data.range(719, 464);		 //		exInfo	 <	256	>
	dest->disQty = src->data.range(463, 400);		 //		disQty	 <	64	>
	dest->ordInfo = src->data.range(399, 320);		 //		ordInfo	 <	80	>
	dest->crosKey = src->data.range(319, 288);		 //		crosKey	 <	32	>
	dest->ordTyp = src->data.range(287, 280);		 //		ordTyp	 <	8	>
	dest->trigTy = src->data.range(279, 272);		 //		trigTy	 <	8	>
	dest->trigPcTy = src->data.range(271, 264);		 //		trigPcTy	 <	8	>
	dest->trigOrdBoID = src->data.range(263, 232);	 //		trigOrdBoID	 <	32	>
	dest->trigPc = src->data.range(231, 200);		 //		trigPc	 <	32	>
	dest->trigSesTyID = src->data.range(199, 168);	 //		trigSesTyID	 <	32	>
	dest->valTdata = src->data.range(167, 136);		 //		valTdata	 <	32	>
	dest->dealID = src->data.range(135, 72);		 //		dealID	 <	64	>
	dest->ordID = src->data.range(71, 8);			 //		ordID	 <	64	>
	dest->NVDR = src->data.range(7, 0);				 //		NVDR	 <	8	>

	return;
}

//void mmInterface::orderEntryEncodePack(orderEntryOperationEncode_t *src, txReject_t *dest)
//{
//#pragma HLS INLINE
//
//	dest->range(1351, 1336) = src->symbolIndex; //	symbolIndex	 <	16	>
//	dest->range(1335, 1328) = src->lgNdMSB;	 //	lgNdMSB	 <	8	>
//	dest->range(1327, 1320) = src->lgNdLSB;	 //	lgNdLSB	 <	8	>
//	dest->range(1319, 1312) = src->seqUnq;		 //	seqUnq	 <	8	>
//	dest->range(1311, 1304) = src->msgType;	 //	msgType	 <	8	>
//	dest->range(1303, 1192) = src->extOrdToken; //	extOrdToken	 <	112	>
//	dest->range(1191, 1080) = src->repOrdToken; //	repOrdToken	 <	112	>
//	dest->range(1079, 1048) = src->ordBookID;	 //	*ordBookID	 <	32	>
//	dest->range(1047, 1040) = src->side;		 //	side	 <	8	>
//	dest->range(1039, 976) = src->qty;			 //	qty	 <	64	>
//	dest->range(975, 944) = src->price;		 //	price	 <	32	>
//	dest->range(943, 936) = src->timeInFc;		 //	timeInFc	 <	8	>
//	dest->range(935, 928) = src->opCl;			 //	opCl	 <	8	>
//	dest->range(927, 848) = src->account;		 //	account	 <	80	>
//	dest->range(847, 840) = src->invTy;		 //	invTy	 <	8	>
//	dest->range(839, 720) = src->custInfo;		 //	custInfo	 <	120	>
//	dest->range(719, 464) = src->exInfo;		 //	exInfo	 <	256	>
//	dest->range(463, 400) = src->disQty;		 //	disQty	 <	64	>
//	dest->range(399, 320) = src->ordInfo;		 //	ordInfo	 <	80	>
//	dest->range(319, 288) = src->crosKey;		 //	crosKey	 <	32	>
//	dest->range(287, 280) = src->ordTyp;		 //	ordTyp	 <	8	>
//	dest->range(279, 272) = src->trigTy;		 //	trigTy	 <	8	>
//	dest->range(271, 264) = src->trigPcTy;		 //	trigPcTy	 <	8	>
//	dest->range(263, 232) = src->trigOrdBoID;	 //	trigOrdBoID	 <	32	>
//	dest->range(231, 200) = src->trigPc;		 //	trigPc	 <	32	>
//	dest->range(199, 168) = src->trigSesTyID;	 //	trigSesTyID	 <	32	>
//	dest->range(167, 136) = src->valTdata;		 //	valTdata	 <	32	>
//	dest->range(135, 72) = src->dealID;		 //	dealID	 <	64	>
//	dest->range(71, 8) = src->ordID;			 //	ordID	 <	64	>
//	dest->range(7, 0) = src->NVDR;				 //	NVDR	 <	8	>
//
//	return;
//}

void mmInterface::orderEntryOperationPack(orderEntryOperation_t *src, orderEntryOperationPack_t *dest)
{ // from OrderBook to OrderEntry
#pragma HLS INLINE

	dest->data.range(		959	,	952	)= src->	seqUnq	;//	seqUnq	 <	8	>
	dest->data.range(		951	,	944	)= src->	msgType	;//	msgType	 <	8	>
	dest->data.range(		943	,	936	)= src->	NVDR	;//	NVDR	 <	8	>
	dest->data.range(		935	,	928	)= src->	side	;//	side	 <	8	>
	dest->data.range(		927	,	920	)= src->	timeInFc	;//	timeInFc	 <	8	>
	dest->data.range(		919	,	912	)= src->	opCl	;//	opCl	 <	8	>
	dest->data.range(		911	,	904	)= src->	ordTyp	;//	ordTyp	 <	8	>
	dest->data.range(		903	,	896	)= src->	trigTy	;//	trigTy	 <	8	>
	dest->data.range(		895	,	888	)= src->	trigPcTy	;//	trigPcTy	 <	8	>
	dest->data.range(		887	,	872	)= src->	symbolIndex	;//	symbolIndex	 <	16	>
	dest->data.range(		871	,	840	)= src->	ordBookID	;//	ordBookID	 <	32	>
	dest->data.range(		839	,	808	)= src->	price	;//	price	 <	32	>
	dest->data.range(		807	,	776	)= src->	trigOrdBoID	;//	trigOrdBoID	 <	32	>
	dest->data.range(		775	,	744	)= src->	trigPc	;//	trigPc	 <	32	>
	dest->data.range(		743	,	712	)= src->	trigSesTyID	;//	trigSesTyID	 <	32	>
	dest->data.range(		711	,	680	)= src->	valTdata	;//	valTdata	 <	32	>
	dest->data.range(		679	,	616	)= src->	qty	;//	qty	 <	64	>
	dest->data.range(		615	,	552	)= src->	disQty	;//	disQty	 <	64	>
	dest->data.range(		551	,	488	)= src->	dealID	;//	dealID	 <	64	>
	dest->data.range(		487	,	424	)= src->	ordID	;//	ordID	 <	64	>
	dest->data.range(		423	,	344	)= byteReverse<80>(src->ordInfo)	;//	ordInfo	 <	80	>
	dest->data.range(		343	,	232	)= byteReverse<112>(src->extOrdToken)	;//	extOrdToken	 <	112	>
	dest->data.range(		231	,	120	)= byteReverse<112>(src->repOrdToken) ;//	repOrdToken	 <	112	>
	dest->data.range(		119	,	0	)= byteReverse<120>(src->custInfo);	;//	custInfo	 <	120	>
	dest->data.range(		423	,	344	)= byteReverse<80>(src->ordInfo)	;//	ordInfo	 <	80	>
	dest->data.range(		343	,	232	)= byteReverse<112>(src->extOrdToken)	;//	extOrdToken	 <	112	>
	dest->data.range(		231	,	120	)= byteReverse<112>(src->repOrdToken) ;//	repOrdToken	 <	112	>
	dest->data.range(		119	,	0	)= byteReverse<120>(src->custInfo);	;//	custInfo	 <	120	>
	return;
}

void mmInterface::orderEntryOperationUnpack(orderEntryOperationPack_t *src, orderEntryOperation_t *dest)
{
#pragma HLS INLINE

	dest->	seqUnq	= src->data.range(	959	,	952	);//		seqUnq	 <	8	>
	dest->	msgType	= src->data.range(	951	,	944	);//		msgType	 <	8	>
	dest->	NVDR	= src->data.range(	943	,	936	);//		NVDR	 <	8	>
	dest->	side	= src->data.range(	935	,	928	);//		side	 <	8	>
	dest->	timeInFc	= src->data.range(	927	,	920	);//		timeInFc	 <	8	>
	dest->	opCl	= src->data.range(	919	,	912	);//		opCl	 <	8	>
	dest->	ordTyp	= src->data.range(	911	,	904	);//		ordTyp	 <	8	>
	dest->	trigTy	= src->data.range(	903	,	896	);//		trigTy	 <	8	>
	dest->	trigPcTy	= src->data.range(	895	,	888	);//		trigPcTy	 <	8	>
	dest->	symbolIndex	= src->data.range(	887	,	872	);//		symbolIndex	 <	16	>
	dest->	ordBookID	= src->data.range(	871	,	840	);//		ordBookID	 <	32	>
	dest->	price	= src->data.range(	839	,	808	);//		price	 <	32	>
	dest->	trigOrdBoID	= src->data.range(	807	,	776	);//		trigOrdBoID	 <	32	>
	dest->	trigPc	= src->data.range(	775	,	744	);//		trigPc	 <	32	>
	dest->	trigSesTyID	= src->data.range(	743	,	712	);//		trigSesTyID	 <	32	>
	dest->	valTdata	= src->data.range(	711	,	680	);//		valTdata	 <	32	>
	dest->	qty	= src->data.range(	679	,	616	);//		qty	 <	64	>
	dest->	disQty	= src->data.range(	615	,	552	);//		disQty	 <	64	>
	dest->	dealID	= src->data.range(	551	,	488	);//		dealID	 <	64	>
	dest->	ordID	= src->data.range(	487	,	424	);//		ordID	 <	64	>
	dest->	ordInfo	= byteReverse<80>(src->data.range(	423	,	344	));//		ordInfo	 <	80	>
	dest->	extOrdToken	= byteReverse<112>(src->data.range(	343	,	232	));//		extOrdToken	 <	112	>
	dest->	repOrdToken	= byteReverse<112>(src->data.range(	231	,	120	));//		repOrdToken	 <	112	>
	dest->	custInfo	= byteReverse<120>(src->data.range(	119	,	0	));//		custInfo	 <	120	>

	return;
}


void mmInterface::orderEntryOperationFIFOPack(orderEntryOperationFIFO_t *src, orderEntryOperationPackFIFO_t *dest)
{ // from OrderBook to OrderEntry
#pragma HLS INLINE

	dest->range(		959	,	952	)= src->	seqUnq	;//	seqUnq	 <	8	>
	dest->range(		951	,	944	)= src->	msgType	;//	msgType	 <	8	>
	dest->range(		943	,	936	)= src->	NVDR	;//	NVDR	 <	8	>
	dest->range(		935	,	928	)= src->	side	;//	side	 <	8	>
	dest->range(		927	,	920	)= src->	timeInFc	;//	timeInFc	 <	8	>
	dest->range(		919	,	912	)= src->	opCl	;//	opCl	 <	8	>
	dest->range(		911	,	904	)= src->	ordTyp	;//	ordTyp	 <	8	>
	dest->range(		903	,	896	)= src->	trigTy	;//	trigTy	 <	8	>
	dest->range(		895	,	888	)= src->	trigPcTy	;//	trigPcTy	 <	8	>
	dest->range(		887	,	872	)= src->	symbolIndex	;//	symbolIndex	 <	16	>
	dest->range(		871	,	840	)= src->	ordBookID	;//	ordBookID	 <	32	>
	dest->range(		839	,	808	)= src->	price	;//	price	 <	32	>
	dest->range(		807	,	776	)= src->	trigOrdBoID	;//	trigOrdBoID	 <	32	>
	dest->range(		775	,	744	)= src->	trigPc	;//	trigPc	 <	32	>
	dest->range(		743	,	712	)= src->	trigSesTyID	;//	trigSesTyID	 <	32	>
	dest->range(		711	,	680	)= src->	valTdata	;//	valTdata	 <	32	>
	dest->range(		679	,	616	)= src->	qty	;//	qty	 <	64	>
	dest->range(		615	,	552	)= src->	disQty	;//	disQty	 <	64	>
	dest->range(		551	,	488	)= src->	dealID	;//	dealID	 <	64	>
	dest->range(		487	,	424	)= src->	ordID	;//	ordID	 <	64	>
	dest->range(		423	,	344	)= byteReverse<80>(src->ordInfo)	;//	ordInfo	 <	80	>
	dest->range(		343	,	232	)= byteReverse<112>(src->extOrdToken)	;//	extOrdToken	 <	112	>
	dest->range(		231	,	120	)= byteReverse<112>(src->repOrdToken) ;//	repOrdToken	 <	112	>
	dest->range(		113	,	0	)= byteReverse<120>(src->custInfo);	;//	custInfo	 <	120	>
	return;
}

void mmInterface::orderEntryOperationFIFOUnpack(orderEntryOperationPackFIFO_t *src, orderEntryOperationFIFO_t *dest)
{
#pragma HLS INLINE

	dest->seqUnq		= src->range(	959	,	952	);//		seqUnq	 <	8	>
	dest->msgType		= src->range(	951	,	944	);//		msgType	 <	8	>
	dest->NVDR			= src->range(	943	,	936	);//		NVDR	 <	8	>
	dest->side			= src->range(	935	,	928	);//		side	 <	8	>
	dest->timeInFc		= src->range(	927	,	920	);//		timeInFc	 <	8	>
	dest->opCl			= src->range(	919	,	912	);//		opCl	 <	8	>
	dest->ordTyp		= src->range(	911	,	904	);//		ordTyp	 <	8	>
	dest->trigTy		= src->range(	903	,	896	);//		trigTy	 <	8	>
	dest->trigPcTy		= src->range(	895	,	888	);//		trigPcTy	 <	8	>
	dest->symbolIndex	= src->range(	887	,	872	);//		symbolIndex	 <	16	>
	dest->ordBookID		= src->range(	871	,	840	);//		ordBookID	 <	32	>
	dest->price			= src->range(	839	,	808	);//		price	 <	32	>
	dest->trigOrdBoID	= src->range(	807	,	776	);//		trigOrdBoID	 <	32	>
	dest->trigPc		= src->range(	775	,	744	);//		trigPc	 <	32	>
	dest->trigSesTyID	= src->range(	743	,	712	);//		trigSesTyID	 <	32	>
	dest->valTdata		= src->range(	711	,	680	);//		valTdata	 <	32	>
	dest->qty			= src->range(	679	,	616	);//		qty	 <	64	>
	dest->disQty		= src->range(	615	,	552	);//		disQty	 <	64	>
	dest->dealID		= src->range(	551	,	488	);//		dealID	 <	64	>
	dest->ordID			= src->range(	487	,	424	);//		ordID	 <	64	>
	dest->ordInfo		= src->range(	423	,	344	);//		ordInfo	 <	80	>
	dest->extOrdToken	= src->range(	343	,	232	);//		extOrdToken	 <	112	>
	dest->repOrdToken	= src->range(	231	,	120	);//		repOrdToken	 <	112	>
	dest->custInfo		= src->range(	119	,	0	);//		custInfo	 <	120	>

	return;
}

void mmInterface::orderEntryOperationEncodePack(orderEntryOperationEncode_t *src, orderEntryOperationEncodePack_t *dest)
{ // between kernel orderEntry
#pragma HLS INLINE

	dest->range(		1423	,	1416	)= src->	sideOrderInfo	;//	sideOrderInfo	<	8	>
	dest->range(		1415	,	1408	)= src->	lgNdMSB	;//	lgNdMSB	<	8	>
	dest->range(		1407	,	1400	)= src->	lgNdLSB	;//	lgNdLSB	 <	8	>
	dest->range(		1399	,	1392	)= src->	seqUnq	;//	seqUnq	 <	8	>
	dest->range(		1391	,	1384	)= src->	msgType	;//	msgType	 <	8	>
	dest->range(		1383	,	1376	)= src->	side	;//	side	<	8	>
	dest->range(		1375	,	1368	)= src->	timeInFc	;//	timeInFc	 <	8	>
	dest->range(		1367	,	1360	)= src->	opCl	;//	opCl	 <	8	>
	dest->range(		1359	,	1352	)= src->	invTy	;//	invTy	 <	8	>
	dest->range(		1351	,	1344	)= src->	ordTyp	;//	ordTyp	 <	8	>
	dest->range(		1343	,	1336	)= src->	trigTy	;//	trigTy	 <	8	>
	dest->range(		1335	,	1328	)= src->	trigPcTy	;//	trigPcTy	 <	8	>
	dest->range(		1327	,	1320	)= src->	NVDR	;//	NVDR	<	8	>
	dest->range(		1319	,	1304	)= src->	symbolIndex	;//	symbolIndex	 <	16	>
	dest->range(		1303	,	1272	)= src->	ordBookID	;//	ordBookID	 <	32	>
	dest->range(		1271	,	1240	)= src->	price	;//	price	 <	32	>
	dest->range(		1239	,	1208	)= src->	crosKey	;//	crosKey	<	32	>
	dest->range(		1207	,	1176	)= src->	trigOrdBoID	;//	trigOrdBoID	 <	32	>
	dest->range(		1175	,	1144	)= src->	trigPc	;//	trigPc	 <	32	>
	dest->range(		1143	,	1112	)= src->	trigSesTyID	;//	trigSesTyID	 <	32	>
	dest->range(		1111	,	1080	)= src->	valTdata	;//	valTdata	 <	32	>
	dest->range(		1079	,	1016	)= src->	outStandingOrderInfo	;//	outStandingOrderInfo	<	64
	dest->range(		1015	,	952	)= src->	qty	;//	qty	 <	64	>
	dest->range(		951	,	888	)= src->	disQty	;//	disQty	 <	64	>
	dest->range(		887	,	824	)= src->	dealID	;//	dealID	 <	64	>
	dest->range(		823	,	760	)= src->	ordID	;//	ordID	 <	64	>
	dest->range(		759	,	680	)= src->	ordInfo	;//	ordInfo	 <	80	>
	dest->range(		679	,	600	)= src->	account	;//	account	<	80	>
	dest->range(		599	,	488	)= src->	extOrdToken	;//	extOrdToken	 <	112	>
	dest->range(		487	,	376	)= src->	repOrdToken	;//	repOrdToken	 <	112	>
	dest->range(		375	,	256	)= src->	custInfo	;//	custInfo	 <	120	>
	dest->range(		255	,	0	)= src->	exInfo	;//	exInfo	 <	256	>
	return;
}

void mmInterface::orderEntryOperationEncodeUnpack(orderEntryOperationEncodePack_t *src, orderEntryOperationEncode_t *dest)
{
#pragma HLS INLINE

	dest->	sideOrderInfo	= src->range(	1423	,	1416	);//		sideOrderInfo	 <	8	>
	dest->	lgNdMSB	= src->range(	1415	,	1408	);//		lgNdMSB	 <	8	>
	dest->	lgNdLSB	= src->range(	1407	,	1400	);//		lgNdLSB	 <	8	>
	dest->	seqUnq	= src->range(	1399	,	1392	);//		seqUnq	 <	8	>
	dest->	msgType	= src->range(	1391	,	1384	);//		msgType	 <	8	>
	dest->	side	= src->range(	1383	,	1376	);//		side	 <	8	>
	dest->	timeInFc	= src->range(	1375	,	1368	);//		timeInFc	 <	8	>
	dest->	opCl	= src->range(	1367	,	1360	);//		opCl	 <	8	>
	dest->	invTy	= src->range(	1359	,	1352	);//		invTy	 <	8	>
	dest->	ordTyp	= src->range(	1351	,	1344	);//		ordTyp	 <	8	>
	dest->	trigTy	= src->range(	1343	,	1336	);//		trigTy	 <	8	>
	dest->	trigPcTy	= src->range(	1335	,	1328	);//		trigPcTy	 <	8	>
	dest->	NVDR	= src->range(	1327	,	1320	);//		NVDR	 <	8	>
	dest->	symbolIndex	= src->range(	1319	,	1304	);//		symbolIndex	 <	16	>
	dest->	ordBookID	= src->range(	1303	,	1272	);//		ordBookID	 <	32	>
	dest->	price	= src->range(	1271	,	1240	);//		price	 <	32	>
	dest->	crosKey	= src->range(	1239	,	1208	);//		crosKey	 <	32	>
	dest->	trigOrdBoID	= src->range(	1207	,	1176	);//		trigOrdBoID	 <	32	>
	dest->	trigPc	= src->range(	1175	,	1144	);//		trigPc	 <	32	>
	dest->	trigSesTyID	= src->range(	1143	,	1112	);//		trigSesTyID	 <	32	>
	dest->	valTdata	= src->range(	1111	,	1080	);//		valTdata	 <	32	>
	dest->	outStandingOrderInfo	= src->range(	1079	,	1016	);//		outStandingOrderInfo	 <	64	>
	dest->	qty	= src->range(	1015	,	952	);//		qty	 <	64	>
	dest->	disQty	= src->range(	951	,	888	);//		disQty	 <	64	>
	dest->	dealID	= src->range(	887	,	824	);//		dealID	 <	64	>
	dest->	ordID	= src->range(	823	,	760	);//		ordID	 <	64	>
	dest->	ordInfo	= src->range(	759	,	680	);//		ordInfo	 <	80	>
	dest->	account	= src->range(	679	,	600	);//		account	 <	80	>
	dest->	extOrdToken	= src->range(	599	,	488	);//		extOrdToken	 <	112	>
	dest->	repOrdToken	= src->range(	487	,	376	);//		repOrdToken	 <	112	>
	dest->	custInfo	= src->range(	375	,	256	);//		custInfo	 <	120	>
	dest->	exInfo	= src->range(	255	,	0	);//		exInfo	 <	256	>

	return;
}

void mmInterface::ouchMsgUnpack(ouchMsgPack_t *src, ouchMsg_t *dest)
{
#pragma HLS INLINE

	dest->lgNdMSB = src->data.range(1215, 1208);	 //		lgNdMSB	 <	8	>
	dest->lgNdLSB = src->data.range(1207, 1200);	 //		lgNdLSB	 <	8	>
	dest->seqUnq = src->data.range(1199, 1192);		 //		SeqUnq	 <	8	>
	dest->msgType = src->data.range(1191, 1184);	 //		msgType	 <	8	>
	dest->timeSp = src->data.range(1183, 1120);		 //		timeSp	 <	64	>
	dest->extOrdToken = src->data.range(1119, 1008); //		extOrdToken	 <	112	>
	dest->ordBookID = src->data.range(1007, 976);	 //		*ordBookID	 <	32	>
	dest->side = src->data.range(975, 968);			 //		side	 <	8	>
	dest->ordID = src->data.range(967, 904);		 //		ordID	 <	64	>
	dest->qty = src->data.range(903, 840);			 //		qty	 <	64	>
	dest->price = src->data.range(839, 808);		 //		price	 <	32	>
	dest->timeInFc = src->data.range(807, 800);		 //		timeInFc	 <	8	>
	dest->opCl = src->data.range(799, 792);			 //		opCl	 <	8	>
	dest->account = src->data.range(791, 712);		 //		account	 <	80	>
	dest->ordSte = src->data.range(711, 704);		 //		ordSte	 <	8	>
	dest->custInfo = src->data.range(703, 584);		 //		custInfo	 <	120	>
	dest->exInfo = src->data.range(583, 328);		 //		exInfo	 <	256	>
	dest->disQty = src->data.range(327, 264);		 //		disQty	 <	64	>
	dest->ordInfo = src->data.range(263, 184);		 //		ordInfo	 <	80	>
	dest->crosKey = src->data.range(183, 152);		 //		crosKey	 <	32	>
	dest->ordTyp = src->data.range(151, 144);		 //		ordTyp	 <	8	>
	dest->trigTy = src->data.range(143, 136);		 //		TrigTy	 <	8	>
	dest->trigPcTy = src->data.range(135, 128);		 //		TrigPcTy	 <	8	>
	dest->trigOrdBoID = src->data.range(127, 96);	 //		TrigOrdBoID	 <	32	>
	dest->trigPc = src->data.range(95, 64);			 //		TrigPc	 <	32	>
	dest->trigSesTyID = src->data.range(63, 32);	 //		TrigSesTyID	 <	32	>
	dest->valTdata = src->data.range(31, 0);		 //		ValTdata	 <	32	>
	return;
}

void mmInterface::priceLimitOrdEntryMessageUnpack(nasdaqInternalPack_t *src, priceLimitOrdMessage_t *dest)
{
#pragma HLS INLINE

	dest->symbolIndex = src->data.range(1015, 1000); //		symbolIndex	 <	16	>
	dest->orderBookId = src->data.range(871, 840);	 //		orderBookId	 <	32	>
	dest->upperLimit = src->data.range(839, 808);	 //		upperLimit	 <	32	>
	dest->lowerLimit = src->data.range(807, 776);	 //		lowerLimit	 <	32	>
	dest->decimalInPrice = src->data.range(303, 288);


	return;
}

void mmInterface::priceLimitOrdEntryMessagePack(priceLimitOrdMessage_t *src, nasdaqInternalPack_t *dest)
{
#pragma HLS INLINE

	dest->data.range(127, 112) = src->symbolIndex; //		symbolIndex	 <	16	>
	dest->data.range(111, 80) = src->orderBookId;	 //		orderBookId	 <	32	>
	dest->data.range(79, 48) = src->upperLimit;	 //		upperLimit	 <	32	>
	dest->data.range(47, 16) = src->lowerLimit;	 //		lowerLimit	 <	32	>
	dest->data.range(15, 0) = src->decimalInPrice;

	return;
}

void mmInterface::tickerMsgOrdEntryUnpack(nasdaqInternalPack_t *src, tickerMsgOrderEntryMessage_t *dest)
{
#pragma HLS INLINE

	dest->symbolIndex = src->data.range(1015, 1000);  					//		symbolIndex	 <	16	>
	dest->orderBookId = src->data.range(871, 840);  					//		orderBookId	 <	32	>
	dest->price = src->data.range(767, 736);  					//		price	 <	32	>
	dest->decimalInPrice = src->data.range(303, 288);

	return;
}


void mmInterface::txMsgUnPackToTxData(orderEntryOperationEncode_t *src, txData messageTemplate[32],
									  ap_uint<8> *templateL,
									  ap_uint<8> *keep, ap_uint<16> *messageTempSum, ap_uint<16> *txLength)
{
// #pragma HLS PIPELINE  style=flp
#pragma HLS INLINE
	orderEntryOperation_t operationEncode;
	ap_uint<32> checkSumTmp = 0;
	switch (src->msgType)
	{
	case 'O':
	{
		messageTemplate[0].range(63, 56) = src->lgNdMSB.range(7, 0);
		messageTemplate[0].range(55, 48) = src->lgNdLSB.range(7, 0);
		messageTemplate[0].range(47, 40) = src->seqUnq.range(7, 0);
		messageTemplate[0].range(39, 32) = src->msgType.range(7, 0);
		messageTemplate[0].range(31, 0) = src->extOrdToken.range(111, 80);
		messageTemplate[1].range(63, 0) = src->extOrdToken.range(79, 16);
		messageTemplate[2].range(63, 48) = src->extOrdToken.range(15, 0);
		messageTemplate[2].range(47, 16) = src->ordBookID.range(31, 0);
		messageTemplate[2].range(15, 8) = src->side.range(7, 0);
		messageTemplate[2].range(7, 0) = src->qty.range(63, 56);
		messageTemplate[3].range(63, 8) = src->qty.range(55, 0);
		messageTemplate[3].range(7, 0) = src->price.range(31, 24);
		messageTemplate[4].range(63, 40) = src->price.range(23, 0);
		messageTemplate[4].range(39, 32) = src->timeInFc.range(7, 0);
		messageTemplate[4].range(31, 24) = src->opCl.range(7, 0);
		messageTemplate[4].range(23, 0) = src->account.range(79, 56);
		messageTemplate[5].range(63, 8) = src->account.range(55, 0);
		messageTemplate[5].range(7, 0) = src->custInfo.range(119, 112);
		messageTemplate[6].range(63, 0) = src->custInfo.range(111, 48);
		messageTemplate[7].range(63, 16) = src->custInfo.range(47, 0);
		messageTemplate[7].range(15, 0) = src->exInfo.range(255, 240);
		messageTemplate[8].range(63, 0) = src->exInfo.range(239, 176);
		messageTemplate[9].range(63, 0) = src->exInfo.range(175, 112);
		messageTemplate[10].range(63, 0) = src->exInfo.range(111, 48);
		messageTemplate[11].range(63, 16) = src->exInfo.range(47, 0);
		messageTemplate[11].range(15, 0) = src->disQty.range(63, 48);
		messageTemplate[12].range(63, 16) = src->disQty.range(47, 0);
		messageTemplate[12].range(15, 0) = src->ordInfo.range(79, 64);
		messageTemplate[13].range(63, 0) = src->ordInfo.range(63, 0);
		messageTemplate[14].range(63, 32) = src->crosKey.range(31, 0);
		messageTemplate[14].range(31, 24) = src->ordTyp.range(7, 0);
		messageTemplate[14].range(23, 16) = src->trigTy.range(7, 0);
		messageTemplate[14].range(15, 8) = src->trigPcTy.range(7, 0);
		messageTemplate[14].range(7, 0) = src->trigOrdBoID.range(31, 24);
		messageTemplate[15].range(63, 40) = src->trigOrdBoID.range(23, 0);
		messageTemplate[15].range(39, 8) = src->trigPc.range(31, 0);
		messageTemplate[15].range(7, 0) = src->trigSesTyID.range(31, 24);
		messageTemplate[16].range(63, 40) = src->trigSesTyID.range(23, 0);
		messageTemplate[16].range(39, 8) = src->valTdata.range(31, 0);
		messageTemplate[16].range(7, 0) = 0;
		*templateL = 17;
		*keep = 0x7F; // for message O;
		*txLength = 135;
		for (int i = 0; i < 17; i++)
		{
#pragma HLS UNROLL
			checkSumTmp += messageTemplate[i].range(15, 0) + messageTemplate[i].range(31, 16) + messageTemplate[i].range(47, 32) + messageTemplate[i].range(63, 48);
		}
		*messageTempSum = checkSumTmp.range(31, 16) + checkSumTmp.range(15, 0);
		break;
	}
	case 'U':
	{
		messageTemplate[0].range(63, 56) = src->lgNdMSB.range(7, 0);
		messageTemplate[0].range(55, 48) = src->lgNdLSB.range(7, 0);
		messageTemplate[0].range(47, 40) = src->seqUnq.range(7, 0);
		messageTemplate[0].range(39, 32) = src->msgType.range(7, 0);
		messageTemplate[0].range(31, 0) = src->extOrdToken.range(111, 80);
		messageTemplate[1].range(63, 0) = src->extOrdToken.range(79, 16);
		messageTemplate[2].range(63, 48) = src->extOrdToken.range(15, 0);
		messageTemplate[2].range(47, 0) = src->repOrdToken.range(111, 64);
		messageTemplate[3].range(63, 0) = src->repOrdToken.range(63, 0);
		messageTemplate[4].range(63, 0) = src->qty.range(63, 0);
		messageTemplate[5].range(63, 32) = src->price.range(31, 0);
		messageTemplate[5].range(31, 24) = src->timeInFc.range(7, 0);
		messageTemplate[5].range(23, 16) = src->opCl.range(7, 0);
		messageTemplate[5].range(15, 0) = src->account.range(79, 64);
		messageTemplate[6].range(63, 0) = src->account.range(63, 0);
		messageTemplate[7].range(63, 0) = src->custInfo.range(119, 56);
		messageTemplate[8].range(63, 8) = src->custInfo.range(55, 0);
		messageTemplate[8].range(7, 0) = src->exInfo.range(255, 248);
		messageTemplate[9].range(63, 0) = src->exInfo.range(247, 184);
		messageTemplate[10].range(63, 0) = src->exInfo.range(183, 120);
		messageTemplate[11].range(63, 0) = src->exInfo.range(119, 56);
		messageTemplate[12].range(63, 8) = src->exInfo.range(55, 0);
		messageTemplate[12].range(7, 0) = src->disQty.range(63, 56);
		messageTemplate[13].range(63, 8) = src->disQty.range(55, 0);
		messageTemplate[13].range(7, 0) = src->ordInfo.range(79, 72);
		messageTemplate[14].range(63, 0) = src->ordInfo.range(71, 8);
		messageTemplate[15].range(63, 56) = src->ordInfo.range(7, 0);
		messageTemplate[15].range(55, 24) = src->crosKey.range(31, 0);
		messageTemplate[15].range(23, 0) = src->valTdata.range(31, 8);
		messageTemplate[16].range(63, 56) = src->valTdata.range(7, 0);
		messageTemplate[16].range(55, 0) = 0;
		*templateL = 17;
		*keep = 0x1F; // for message U;
		*txLength = 129;
		for (int i = 0; i < 17; i++)
		{
#pragma HLS UNROLL
			checkSumTmp += messageTemplate[i].range(15, 0) + messageTemplate[i].range(31, 16) + messageTemplate[i].range(47, 32) + messageTemplate[i].range(63, 48);
		}
		*messageTempSum = checkSumTmp.range(31, 16) + checkSumTmp.range(15, 0);
		break;
	}

	case 'X':
	{
		messageTemplate[0].range(63, 56) = src->lgNdMSB.range(7, 0);
		messageTemplate[0].range(55, 48) = src->lgNdLSB.range(7, 0);
		messageTemplate[0].range(47, 40) = src->seqUnq.range(7, 0);
		messageTemplate[0].range(39, 32) = src->msgType.range(7, 0);
		messageTemplate[0].range(31, 0) = src->extOrdToken.range(111, 80);
		messageTemplate[1].range(63, 0) = src->extOrdToken.range(79, 16);
		messageTemplate[2].range(63, 48) = src->extOrdToken.range(15, 0);
		messageTemplate[2].range(47, 0) = 0;
		*templateL = 3;
		*keep = 0x2F; // for message X;
		*txLength = 18;
		for (int i = 0; i < 3; i++)
		{
#pragma HLS UNROLL
			checkSumTmp += messageTemplate[i].range(15, 0) + messageTemplate[i].range(31, 16) + messageTemplate[i].range(47, 32) + messageTemplate[i].range(63, 48);
		}
		*messageTempSum = checkSumTmp.range(31, 16) + checkSumTmp.range(15, 0);
		break;
	}

	case 'Y':
	{
		messageTemplate[0].range(63, 56) = src->lgNdMSB.range(7, 0);
		messageTemplate[0].range(55, 48) = src->lgNdLSB.range(7, 0);
		messageTemplate[0].range(47, 40) = src->seqUnq.range(7, 0);
		messageTemplate[0].range(39, 32) = src->msgType.range(7, 0);
		messageTemplate[0].range(31, 0) = src->ordBookID.range(31, 0);
		messageTemplate[1].range(63, 56) = src->side.range(7, 0);
		messageTemplate[1].range(55, 0) = src->qty.range(63, 8);
		messageTemplate[2].range(63, 56) = src->qty.range(7, 0);
		messageTemplate[2].range(55, 0) = 0;
		*templateL = 3;
		*keep = 0x1F; // for message Y;
		*txLength = 17;
		for (int i = 0; i < 3; i++)
		{
#pragma HLS UNROLL
			checkSumTmp += messageTemplate[i].range(15, 0) + messageTemplate[i].range(31, 16) + messageTemplate[i].range(47, 32) + messageTemplate[i].range(63, 48);
		}
		*messageTempSum = checkSumTmp.range(31, 16) + checkSumTmp.range(15, 0);
		break;
	}
	case 'Z':
	{
		messageTemplate[0].range(63, 56) = src->lgNdMSB.range(7, 0);
		messageTemplate[0].range(55, 48) = src->lgNdLSB.range(7, 0);
		messageTemplate[0].range(47, 40) = src->seqUnq.range(7, 0);
		messageTemplate[0].range(39, 32) = src->msgType.range(7, 0);
		messageTemplate[0].range(31, 0) = src->extOrdToken.range(111, 80);
		messageTemplate[1].range(63, 0) = src->extOrdToken.range(79, 16);
		messageTemplate[2].range(63, 48) = src->extOrdToken.range(15, 0);
		messageTemplate[2].range(47, 16) = src->ordBookID.range(31, 0);
		messageTemplate[2].range(15, 0) = src->dealID.range(63, 48);
		messageTemplate[3].range(63, 16) = src->dealID.range(47, 0);
		messageTemplate[3].range(15, 0) = src->ordID.range(63, 48);
		messageTemplate[4].range(63, 16) = src->ordID.range(47, 0);
		messageTemplate[4].range(15, 0) = src->account.range(79, 64);
		messageTemplate[5].range(63, 0) = src->account.range(63, 0);
		messageTemplate[6].range(63, 56) = src->invTy.range(7, 0);
		messageTemplate[6].range(55, 48) = src->NVDR.range(7, 0);
		messageTemplate[6].range(47, 0) = 0;
		*templateL = 7;
		*keep = 0x1F; // for message Z;
		*txLength = 50;
		for (int i = 0; i < 7; i++)
		{
#pragma HLS UNROLL
			checkSumTmp += messageTemplate[i].range(15, 0) + messageTemplate[i].range(31, 16) + messageTemplate[i].range(47, 32) + messageTemplate[i].range(63, 48);
		}
		*messageTempSum = checkSumTmp.range(31, 16) + checkSumTmp.range(15, 0);
		break;
	}
	}
	return;
}

void mmInterface::rdPriceLimit(priceLimitOrdMessage_t *src, priceLimitOrdSymbolIndex_t dest[NUM_SYMBOL])
{
#pragma HLS PIPELINE style = flp
	//	static ap_uint<32> lowerData = 0;
	//	static ap_uint<32> upperData = 0;

	dest[src->symbolIndex].decimalInPrice = src->decimalInPrice;
	dest[src->symbolIndex].orderBookId = src->orderBookId;

	if (src->lowerLimit.bit(31) == 1) // minimum is 0.01 but need to check decimal in price if decimalInPrice =5 => 10^5 = 0.01 * 100000 = 1000
	{
		switch (src->decimalInPrice)
		{

			case 2:
			{
				dest[src->symbolIndex].lowerLimit = 1;		 // 0.01 x 10^2 = 1 use normally
				dest[src->symbolIndex].upperLimit = 7483600; // max 74,836 * 10^2 =  7,483,600 use normally
				break;
			}
			case 3:
			{
				dest[src->symbolIndex].lowerLimit = 10;		  // 0.01 x 10^3 = 10
				dest[src->symbolIndex].upperLimit = 47483000; // max 47,483 * 10^3 =  47,483,000
				break;
			}
			case 4:
			{
				dest[src->symbolIndex].lowerLimit = 100;	   // 0.01 x 10^4 = 100
				dest[src->symbolIndex].upperLimit = 147480000; // max 14,748 * 10^4 =  147,480,000
				break;
			}
			case 5:
			{
				dest[src->symbolIndex].lowerLimit = 1000;		// 0.01 x 10^5 = 1000 use normally
				dest[src->symbolIndex].upperLimit = 2147400000; // max 2,147,483,648 => 21474 * 10^5 = 2,147,400,000 use normally
				break;
			}

			default:
			{
				dest[src->symbolIndex].lowerLimit = 2147483647;
				dest[src->symbolIndex].upperLimit = 1000;
				break;
			}
		}
	}
	else
	{
		dest[src->symbolIndex].lowerLimit = src->lowerLimit;
		dest[src->symbolIndex].upperLimit = src->upperLimit;
	}

	return;
}

void mmInterface::rxBuffOuchUnpack(ap_uint<64> src[32], ouchMsg_t *dest)
{
#pragma HLS INLINE
	dest->msgType = src[0].range(39, 32);
	if (dest->msgType == 'A')
	{
		dest->lgNdMSB = src[0].range(63, 56);
		dest->lgNdLSB = src[0].range(55, 48);
		dest->seqUnq = src[0].range(47, 40);
		dest->msgType = src[0].range(39, 32);
		dest->timeSp.range(63, 32) = src[0].range(31, 0);
		dest->timeSp.range(31, 0) = src[1].range(63, 32);
		dest->extOrdToken.range(111, 80) = src[1].range(31, 0);
		dest->extOrdToken.range(79, 16) = src[2].range(63, 0);
		dest->extOrdToken.range(15, 0) = src[3].range(63, 48);
		dest->ordBookID.range(31, 0) = src[3].range(47, 16);
		dest->side.range(7, 0) = src[3].range(15, 8);
		dest->ordID.range(63, 56) = src[3].range(7, 0);
		dest->ordID.range(55, 0) = src[4].range(63, 8);
		dest->qty.range(63, 56) = src[4].range(7, 0);
		dest->qty.range(55, 0) = src[5].range(63, 8);
		dest->price.range(31, 24) = src[5].range(7, 0);
		dest->price.range(23, 0) = src[6].range(63, 40);
		dest->timeInFc.range(7, 0) = src[6].range(39, 32);
		dest->opCl.range(7, 0) = src[6].range(31, 24);
		dest->account.range(79, 56) = src[6].range(23, 0);
		dest->account.range(55, 0) = src[7].range(63, 8);
		dest->ordSte.range(7, 0) = src[7].range(7, 0);
		dest->custInfo.range(119, 56) = src[8].range(63, 0);
		dest->custInfo.range(55, 0) = src[9].range(63, 8);
		dest->exInfo.range(255, 248) = src[9].range(7, 0);
		dest->exInfo.range(247, 184) = src[10].range(63, 0);
		dest->exInfo.range(183, 120) = src[11].range(63, 0);
		dest->exInfo.range(119, 56) = src[12].range(63, 0);
		dest->exInfo.range(55, 0) = src[13].range(63, 8);
		dest->disQty.range(63, 56) = src[13].range(7, 0);
		dest->disQty.range(55, 0) = src[14].range(63, 8);
		dest->ordInfo.range(79, 72) = src[14].range(7, 0);
		dest->ordInfo.range(71, 8) = src[15].range(63, 0);
		dest->ordInfo.range(7, 0) = src[16].range(63, 56);
		dest->crosKey.range(31, 0) = src[16].range(55, 24);
		dest->ordTyp.range(7, 0) = src[16].range(23, 16);
		dest->trigTy.range(7, 0) = src[16].range(15, 8);
		dest->trigPcTy.range(7, 0) = src[16].range(7, 0);
		dest->trigOrdBoID.range(31, 0) = src[17].range(63, 32);
		dest->trigPc.range(31, 0) = src[17].range(31, 0);
		dest->trigSesTyID.range(31, 0) = src[18].range(63, 32);
		dest->trigSesTyID.range(31, 0) = src[18].range(31, 0);
	}

	else if (dest->msgType == 'U')
	{
		dest->lgNdMSB.range(7, 0) = src[0].range(63, 56);
		dest->lgNdLSB.range(7, 0) = src[0].range(55, 48);
		dest->seqUnq.range(7, 0) = src[0].range(47, 40);
		dest->msgType.range(7, 0) = src[0].range(39, 32);
		dest->timeSp.range(63, 32) = src[0].range(31, 0);
		dest->timeSp.range(31, 0) = src[1].range(63, 32);
		dest->repOrdTokenID.range(111, 80) = src[1].range(31, 0);
		dest->repOrdTokenID.range(79, 16) = src[2].range(63, 0);
		dest->repOrdTokenID.range(15, 0) = src[3].range(63, 48);
		dest->extOrdToken.range(111, 64) = src[3].range(47, 0);
		dest->extOrdToken.range(63, 0) = src[4].range(63, 0);
		dest->ordBookID.range(31, 0) = src[5].range(63, 32);
		dest->side.range(7, 0) = src[5].range(31, 24);
		dest->ordID.range(63, 40) = src[5].range(23, 0);
		dest->ordID.range(39, 0) = src[6].range(63, 24);
		dest->qty.range(63, 40) = src[6].range(23, 0);
		dest->qty.range(39, 0) = src[7].range(63, 24);
		dest->price.range(31, 8) = src[7].range(23, 0);
		dest->price.range(7, 0) = src[8].range(63, 56);
		dest->timeInFc.range(7, 0) = src[8].range(55, 48);
		dest->opCl.range(7, 0) = src[8].range(47, 40);
		dest->account.range(79, 40) = src[8].range(39, 0);
		dest->account.range(39, 0) = src[9].range(63, 24);
		dest->ordSte.range(7, 0) = src[9].range(23, 16);
		dest->custInfo.range(119, 104) = src[9].range(15, 0);
		dest->custInfo.range(103, 40) = src[10].range(63, 0);
		dest->custInfo.range(39, 0) = src[11].range(63, 24);
		dest->exInfo.range(255, 232) = src[11].range(23, 0);
		dest->exInfo.range(231, 168) = src[12].range(63, 0);
		dest->exInfo.range(167, 104) = src[13].range(63, 0);
		dest->exInfo.range(103, 40) = src[14].range(63, 0);
		dest->exInfo.range(39, 0) = src[15].range(63, 24);
		dest->disQty.range(63, 40) = src[15].range(23, 0);
		dest->disQty.range(39, 0) = src[16].range(63, 24);
		dest->ordInfo.range(79, 56) = src[16].range(23, 0);
		dest->ordInfo.range(55, 0) = src[17].range(63, 8);
		dest->crosKey.range(31, 24) = src[17].range(7, 0);
		dest->crosKey.range(23, 0) = src[18].range(63, 40);
		dest->ordTyp.range(7, 0) = src[18].range(39, 32);
		dest->trigTy.range(7, 0) = src[18].range(31, 24);
		dest->trigPcTy.range(7, 0) = src[18].range(23, 16);
		dest->trigOrdBoID.range(31, 16) = src[18].range(15, 0);
		dest->trigOrdBoID.range(15, 0) = src[19].range(63, 48);
		dest->trigPc.range(31, 0) = src[19].range(47, 16);
		dest->trigSesTyID.range(31, 16) = src[19].range(15, 0);
		dest->trigSesTyID.range(15, 0) = src[20].range(63, 48);
		dest->valTdata.range(31, 0) = src[20].range(47, 16);
	}
	else if (dest->msgType == 'C')
	{
		dest->lgNdMSB.range(7, 0) = src[0].range(63, 56);
		dest->lgNdLSB.range(7, 0) = src[0].range(55, 48);
		dest->seqUnq.range(7, 0) = src[0].range(47, 40);
		dest->timeSp.range(63, 32) = src[0].range(31, 0);
		dest->timeSp.range(31, 0) = src[1].range(63, 32);
		dest->extOrdToken.range(111, 80) = src[1].range(31, 0);
		dest->extOrdToken.range(79, 16) = src[2].range(63, 0);
		dest->extOrdToken.range(15, 0) = src[3].range(63, 48);
		dest->ordBookID.range(31, 0) = src[3].range(47, 16);
		dest->side.range(7, 0) = src[3].range(15, 8);
		dest->ordID.range(63, 56) = src[3].range(7, 0);
		dest->ordID.range(55, 0) = src[4].range(63, 8);
		dest->reason.range(7, 0) = src[4].range(7, 0);
	}
	else if (dest->msgType == 'J')
	{
		dest->lgNdMSB = src[0].range(63, 56);
		dest->lgNdLSB = src[0].range(55, 48);
		dest->seqUnq = src[0].range(47, 40);
		dest->msgType = src[0].range(39, 32);
		dest->timeSp.range(63, 32) = src[0].range(31, 0);
		dest->timeSp.range(31, 0) = src[1].range(63, 32);
		dest->extOrdToken.range(111, 80) = src[1].range(31, 0);
		dest->extOrdToken.range(79, 16) = src[2].range(63, 0);
		dest->extOrdToken.range(15, 0) = src[3].range(63, 48);
		dest->rejCode.range(31, 0) = src[3].range(47, 16);
	}
	else if (dest->msgType == 'E')
	{
		dest->lgNdMSB = src[0].range(63, 56);
		dest->lgNdLSB = src[0].range(55, 48);
		dest->seqUnq = src[0].range(47, 40);
		dest->msgType = src[0].range(39, 32);
		dest->timeSp.range(63, 32) = src[0].range(31, 0);
		dest->timeSp.range(31, 0) = src[1].range(63, 32);
		dest->extOrdToken.range(111, 80) = src[1].range(31, 0);
		dest->extOrdToken.range(79, 16) = src[2].range(63, 0);
		dest->extOrdToken.range(15, 0) = src[3].range(63, 48);
		dest->ordBookID.range(31, 0) = src[3].range(47, 16);
		dest->trdQty.range(63, 48) = src[3].range(15, 0);
		dest->trdQty.range(47, 0) = src[4].range(63, 16);
		dest->trdPrice.range(31, 16) = src[4].range(15, 0);
		dest->trdPrice.range(15, 0) = src[5].range(63, 48);
		dest->matchID.range(63, 16) = src[5].range(47, 0);
		dest->matchID.range(15, 0) = src[6].range(63, 48);
		dest->cmboGrpID.range(31, 0) = src[6].range(47, 16);
		dest->dealSrc.range(7, 0) = src[6].range(15, 8);
		dest->side.range(7, 0) = src[6].range(7, 0);
	}
	return;
}

void mmInterface::banlistUnpack(ap_uint<4096> *banList1, ap_uint<4096> *banList2, ap_uint<32> *ordBookID, bool *banlistBool)
{
//#pragma HLS PIPELINE style=flp
//#pragma HLS INLINE
	bool banlistDet = false;

	if (banList1->range(4095, 4064) == *ordBookID ||
		banList1->range(4063, 4032) == *ordBookID ||
		banList1->range(4031, 4000) == *ordBookID ||
		banList1->range(3999, 3968) == *ordBookID ||
		banList1->range(3967, 3936) == *ordBookID ||
		banList1->range(3935, 3904) == *ordBookID ||
		banList1->range(3903, 3872) == *ordBookID ||
		banList1->range(3871, 3840) == *ordBookID ||
		banList1->range(3839, 3808) == *ordBookID ||
		banList1->range(3807, 3776) == *ordBookID ||
		banList1->range(3775, 3744) == *ordBookID ||
		banList1->range(3743, 3712) == *ordBookID ||
		banList1->range(3711, 3680) == *ordBookID ||
		banList1->range(3679, 3648) == *ordBookID ||
		banList1->range(3647, 3616) == *ordBookID ||
		banList1->range(3615, 3584) == *ordBookID ||
		banList1->range(3583, 3552) == *ordBookID ||
		banList1->range(3551, 3520) == *ordBookID ||
		banList1->range(3519, 3488) == *ordBookID ||
		banList1->range(3487, 3456) == *ordBookID ||
		banList1->range(3455, 3424) == *ordBookID ||
		banList1->range(3423, 3392) == *ordBookID ||
		banList1->range(3391, 3360) == *ordBookID ||
		banList1->range(3359, 3328) == *ordBookID ||
		banList1->range(3327, 3296) == *ordBookID ||
		banList1->range(3295, 3264) == *ordBookID ||
		banList1->range(3263, 3232) == *ordBookID ||
		banList1->range(3231, 3200) == *ordBookID ||
		banList1->range(3199, 3168) == *ordBookID ||
		banList1->range(3167, 3136) == *ordBookID ||
		banList1->range(3135, 3104) == *ordBookID ||
		banList1->range(3103, 3072) == *ordBookID ||
		banList1->range(3071, 3040) == *ordBookID ||
		banList1->range(3039, 3008) == *ordBookID ||
		banList1->range(3007, 2976) == *ordBookID ||
		banList1->range(2975, 2944) == *ordBookID ||
		banList1->range(2943, 2912) == *ordBookID ||
		banList1->range(2911, 2880) == *ordBookID ||
		banList1->range(2879, 2848) == *ordBookID ||
		banList1->range(2847, 2816) == *ordBookID ||
		banList1->range(2815, 2784) == *ordBookID ||
		banList1->range(2783, 2752) == *ordBookID ||
		banList1->range(2751, 2720) == *ordBookID ||
		banList1->range(2719, 2688) == *ordBookID ||
		banList1->range(2687, 2656) == *ordBookID ||
		banList1->range(2655, 2624) == *ordBookID ||
		banList1->range(2623, 2592) == *ordBookID ||
		banList1->range(2591, 2560) == *ordBookID ||
		banList1->range(2559, 2528) == *ordBookID ||
		banList1->range(2527, 2496) == *ordBookID ||
		banList1->range(2495, 2464) == *ordBookID ||
		banList1->range(2463, 2432) == *ordBookID ||
		banList1->range(2431, 2400) == *ordBookID ||
		banList1->range(2399, 2368) == *ordBookID ||
		banList1->range(2367, 2336) == *ordBookID ||
		banList1->range(2335, 2304) == *ordBookID ||
		banList1->range(2303, 2272) == *ordBookID ||
		banList1->range(2271, 2240) == *ordBookID ||
		banList1->range(2239, 2208) == *ordBookID ||
		banList1->range(2207, 2176) == *ordBookID ||
		banList1->range(2175, 2144) == *ordBookID ||
		banList1->range(2143, 2112) == *ordBookID ||
		banList1->range(2111, 2080) == *ordBookID ||
		banList1->range(2079, 2048) == *ordBookID ||
		banList1->range(2047, 2016) == *ordBookID ||
		banList1->range(2015, 1984) == *ordBookID ||
		banList1->range(1983, 1952) == *ordBookID ||
		banList1->range(1951, 1920) == *ordBookID ||
		banList1->range(1919, 1888) == *ordBookID ||
		banList1->range(1887, 1856) == *ordBookID ||
		banList1->range(1855, 1824) == *ordBookID ||
		banList1->range(1823, 1792) == *ordBookID ||
		banList1->range(1791, 1760) == *ordBookID ||
		banList1->range(1759, 1728) == *ordBookID ||
		banList1->range(1727, 1696) == *ordBookID ||
		banList1->range(1695, 1664) == *ordBookID ||
		banList1->range(1663, 1632) == *ordBookID ||
		banList1->range(1631, 1600) == *ordBookID ||
		banList1->range(1599, 1568) == *ordBookID ||
		banList1->range(1567, 1536) == *ordBookID ||
		banList1->range(1535, 1504) == *ordBookID ||
		banList1->range(1503, 1472) == *ordBookID ||
		banList1->range(1471, 1440) == *ordBookID ||
		banList1->range(1439, 1408) == *ordBookID ||
		banList1->range(1407, 1376) == *ordBookID ||
		banList1->range(1375, 1344) == *ordBookID ||
		banList1->range(1343, 1312) == *ordBookID ||
		banList1->range(1311, 1280) == *ordBookID ||
		banList1->range(1279, 1248) == *ordBookID ||
		banList1->range(1247, 1216) == *ordBookID ||
		banList1->range(1215, 1184) == *ordBookID ||
		banList1->range(1183, 1152) == *ordBookID ||
		banList1->range(1151, 1120) == *ordBookID ||
		banList1->range(1119, 1088) == *ordBookID ||
		banList1->range(1087, 1056) == *ordBookID ||
		banList1->range(1055, 1024) == *ordBookID ||
		banList1->range(1023, 992) == *ordBookID ||
		banList1->range(991, 960) == *ordBookID ||
		banList1->range(959, 928) == *ordBookID ||
		banList1->range(927, 896) == *ordBookID ||
		banList1->range(895, 864) == *ordBookID ||
		banList1->range(863, 832) == *ordBookID ||
		banList1->range(831, 800) == *ordBookID ||
		banList1->range(799, 768) == *ordBookID ||
		banList1->range(767, 736) == *ordBookID ||
		banList1->range(735, 704) == *ordBookID ||
		banList1->range(703, 672) == *ordBookID ||
		banList1->range(671, 640) == *ordBookID ||
		banList1->range(639, 608) == *ordBookID ||
		banList1->range(607, 576) == *ordBookID ||
		banList1->range(575, 544) == *ordBookID ||
		banList1->range(543, 512) == *ordBookID ||
		banList1->range(511, 480) == *ordBookID ||
		banList1->range(479, 448) == *ordBookID ||
		banList1->range(447, 416) == *ordBookID ||
		banList1->range(415, 384) == *ordBookID ||
		banList1->range(383, 352) == *ordBookID ||
		banList1->range(351, 320) == *ordBookID ||
		banList1->range(319, 288) == *ordBookID ||
		banList1->range(287, 256) == *ordBookID ||
		banList1->range(255, 224) == *ordBookID ||
		banList1->range(223, 192) == *ordBookID ||
		banList1->range(191, 160) == *ordBookID ||
		banList1->range(159, 128) == *ordBookID ||
		banList1->range(127, 96) == *ordBookID ||
		banList1->range(95, 64) == *ordBookID ||
		banList1->range(63, 32) == *ordBookID ||
		banList1->range(31, 0) == *ordBookID ||
		banList2->range(4095, 4064) == *ordBookID ||
		banList2->range(4063, 4032) == *ordBookID ||
		banList2->range(4031, 4000) == *ordBookID ||
		banList2->range(3999, 3968) == *ordBookID ||
		banList2->range(3967, 3936) == *ordBookID ||
		banList2->range(3935, 3904) == *ordBookID ||
		banList2->range(3903, 3872) == *ordBookID ||
		banList2->range(3871, 3840) == *ordBookID ||
		banList2->range(3839, 3808) == *ordBookID ||
		banList2->range(3807, 3776) == *ordBookID ||
		banList2->range(3775, 3744) == *ordBookID ||
		banList2->range(3743, 3712) == *ordBookID ||
		banList2->range(3711, 3680) == *ordBookID ||
		banList2->range(3679, 3648) == *ordBookID ||
		banList2->range(3647, 3616) == *ordBookID ||
		banList2->range(3615, 3584) == *ordBookID ||
		banList2->range(3583, 3552) == *ordBookID ||
		banList2->range(3551, 3520) == *ordBookID ||
		banList2->range(3519, 3488) == *ordBookID ||
		banList2->range(3487, 3456) == *ordBookID ||
		banList2->range(3455, 3424) == *ordBookID ||
		banList2->range(3423, 3392) == *ordBookID ||
		banList2->range(3391, 3360) == *ordBookID ||
		banList2->range(3359, 3328) == *ordBookID ||
		banList2->range(3327, 3296) == *ordBookID ||
		banList2->range(3295, 3264) == *ordBookID ||
		banList2->range(3263, 3232) == *ordBookID ||
		banList2->range(3231, 3200) == *ordBookID ||
		banList2->range(3199, 3168) == *ordBookID ||
		banList2->range(3167, 3136) == *ordBookID ||
		banList2->range(3135, 3104) == *ordBookID ||
		banList2->range(3103, 3072) == *ordBookID ||
		banList2->range(3071, 3040) == *ordBookID ||
		banList2->range(3039, 3008) == *ordBookID ||
		banList2->range(3007, 2976) == *ordBookID ||
		banList2->range(2975, 2944) == *ordBookID ||
		banList2->range(2943, 2912) == *ordBookID ||
		banList2->range(2911, 2880) == *ordBookID ||
		banList2->range(2879, 2848) == *ordBookID ||
		banList2->range(2847, 2816) == *ordBookID ||
		banList2->range(2815, 2784) == *ordBookID ||
		banList2->range(2783, 2752) == *ordBookID ||
		banList2->range(2751, 2720) == *ordBookID ||
		banList2->range(2719, 2688) == *ordBookID ||
		banList2->range(2687, 2656) == *ordBookID ||
		banList2->range(2655, 2624) == *ordBookID ||
		banList2->range(2623, 2592) == *ordBookID ||
		banList2->range(2591, 2560) == *ordBookID ||
		banList2->range(2559, 2528) == *ordBookID ||
		banList2->range(2527, 2496) == *ordBookID ||
		banList2->range(2495, 2464) == *ordBookID ||
		banList2->range(2463, 2432) == *ordBookID ||
		banList2->range(2431, 2400) == *ordBookID ||
		banList2->range(2399, 2368) == *ordBookID ||
		banList2->range(2367, 2336) == *ordBookID ||
		banList2->range(2335, 2304) == *ordBookID ||
		banList2->range(2303, 2272) == *ordBookID ||
		banList2->range(2271, 2240) == *ordBookID ||
		banList2->range(2239, 2208) == *ordBookID ||
		banList2->range(2207, 2176) == *ordBookID ||
		banList2->range(2175, 2144) == *ordBookID ||
		banList2->range(2143, 2112) == *ordBookID ||
		banList2->range(2111, 2080) == *ordBookID ||
		banList2->range(2079, 2048) == *ordBookID ||
		banList2->range(2047, 2016) == *ordBookID ||
		banList2->range(2015, 1984) == *ordBookID ||
		banList2->range(1983, 1952) == *ordBookID ||
		banList2->range(1951, 1920) == *ordBookID ||
		banList2->range(1919, 1888) == *ordBookID ||
		banList2->range(1887, 1856) == *ordBookID ||
		banList2->range(1855, 1824) == *ordBookID ||
		banList2->range(1823, 1792) == *ordBookID ||
		banList2->range(1791, 1760) == *ordBookID ||
		banList2->range(1759, 1728) == *ordBookID ||
		banList2->range(1727, 1696) == *ordBookID ||
		banList2->range(1695, 1664) == *ordBookID ||
		banList2->range(1663, 1632) == *ordBookID ||
		banList2->range(1631, 1600) == *ordBookID ||
		banList2->range(1599, 1568) == *ordBookID ||
		banList2->range(1567, 1536) == *ordBookID ||
		banList2->range(1535, 1504) == *ordBookID ||
		banList2->range(1503, 1472) == *ordBookID ||
		banList2->range(1471, 1440) == *ordBookID ||
		banList2->range(1439, 1408) == *ordBookID ||
		banList2->range(1407, 1376) == *ordBookID ||
		banList2->range(1375, 1344) == *ordBookID ||
		banList2->range(1343, 1312) == *ordBookID ||
		banList2->range(1311, 1280) == *ordBookID ||
		banList2->range(1279, 1248) == *ordBookID ||
		banList2->range(1247, 1216) == *ordBookID ||
		banList2->range(1215, 1184) == *ordBookID ||
		banList2->range(1183, 1152) == *ordBookID ||
		banList2->range(1151, 1120) == *ordBookID ||
		banList2->range(1119, 1088) == *ordBookID ||
		banList2->range(1087, 1056) == *ordBookID ||
		banList2->range(1055, 1024) == *ordBookID ||
		banList2->range(1023, 992) == *ordBookID ||
		banList2->range(991, 960) == *ordBookID ||
		banList2->range(959, 928) == *ordBookID ||
		banList2->range(927, 896) == *ordBookID ||
		banList2->range(895, 864) == *ordBookID ||
		banList2->range(863, 832) == *ordBookID ||
		banList2->range(831, 800) == *ordBookID ||
		banList2->range(799, 768) == *ordBookID ||
		banList2->range(767, 736) == *ordBookID ||
		banList2->range(735, 704) == *ordBookID ||
		banList2->range(703, 672) == *ordBookID ||
		banList2->range(671, 640) == *ordBookID ||
		banList2->range(639, 608) == *ordBookID ||
		banList2->range(607, 576) == *ordBookID ||
		banList2->range(575, 544) == *ordBookID ||
		banList2->range(543, 512) == *ordBookID ||
		banList2->range(511, 480) == *ordBookID ||
		banList2->range(479, 448) == *ordBookID ||
		banList2->range(447, 416) == *ordBookID ||
		banList2->range(415, 384) == *ordBookID ||
		banList2->range(383, 352) == *ordBookID ||
		banList2->range(351, 320) == *ordBookID ||
		banList2->range(319, 288) == *ordBookID ||
		banList2->range(287, 256) == *ordBookID ||
		banList2->range(255, 224) == *ordBookID ||
		banList2->range(223, 192) == *ordBookID ||
		banList2->range(191, 160) == *ordBookID ||
		banList2->range(159, 128) == *ordBookID ||
		banList2->range(127, 96) == *ordBookID ||
		banList2->range(95, 64) == *ordBookID ||
		banList2->range(63, 32) == *ordBookID ||
		banList2->range(31, 0) == *ordBookID)

	{
		banlistDet = true;
	}
	else
	{
		banlistDet = false;
	}
	*banlistBool = banlistDet;
	return;
}

void mmInterface::orderCheckPack(orderCheckPack_t *dest, orderCheck_t *src)
{
#pragma HLS INLINE

	dest->range (495,488) = src->msgType;//	msgType	 <	8	>
	dest->range (487,480) = src->side;//	side	 <	8	>
	dest->range (479,448) = src->price;//	price	 <	32	>
	dest->range (447,416) = src->ordBookID;//	ordBookID	 <	32	>
	dest->range (415,352) = src->dealID;//	dealID	 <	64	>
	dest->range (351,288) = src->ordID;//	ordID	 <	64	>
	dest->range (287,224) = src->qty;//	qty	 <	64	>
	dest->range (223,112) = src->extOrdToken;//	extOrdToken	 <	112	>
	dest->range (111,0) = src->repOrdToken;//	repOrdToken	 <	112	>

	return;
}

void mmInterface::orderCheckUnPack(orderCheck_t *dest, orderCheckPack_t *src)
{
#pragma HLS INLINE
	dest->msgType = src->range (495,488);//		msgType	 <	8	>
	dest->side = src->range (487,480);//		side	 <	8	>
	dest->price = src->range (479,448);//		price	 <	32	>
	dest->ordBookID = src->range (447,416);//		ordBookID	 <	32	>
	dest->dealID = src->range (415,352);//		dealID	 <	64	>
	dest->ordID = src->range (351,288);//		ordID	 <	64	>
	dest->qty = src->range (287,224);//		qty	 <	64	>
	dest->extOrdToken = src->range (223,112);//		extOrdToken	 <	112	>
	dest->repOrdToken = src->range (111,0);//		repOrdToken	 <	112	>
	return;
}

void mmInterface::rxBuffPack(ap_uint<64> src[32], ouchMsgProcess_t *dest)
{
#pragma HLS INLINE

	dest->data.range(2047, 1984) = src[31];
	dest->data.range(1983, 1920) = src[30];
	dest->data.range(1919, 1856) = src[29];
	dest->data.range(1855, 1792) = src[28];
	dest->data.range(1791, 1728) = src[27];
	dest->data.range(1727, 1664) = src[26];
	dest->data.range(1663, 1600) = src[25];
	dest->data.range(1599, 1536) = src[24];
	dest->data.range(1535, 1472) = src[23];
	dest->data.range(1471, 1408) = src[22];
	dest->data.range(1407, 1344) = src[21];
	dest->data.range(1343, 1280) = src[20];
	dest->data.range(1279, 1216) = src[19];
	dest->data.range(1215, 1152) = src[18];
	dest->data.range(1151, 1088) = src[17];
	dest->data.range(1087, 1024) = src[16];
	dest->data.range(1023, 960) = src[15];
	dest->data.range(959, 896) = src[14];
	dest->data.range(895, 832) = src[13];
	dest->data.range(831, 768) = src[12];
	dest->data.range(767, 704) = src[11];
	dest->data.range(703, 640) = src[10];
	dest->data.range(639, 576) = src[9];
	dest->data.range(575, 512) = src[8];
	dest->data.range(511, 448) = src[7];
	dest->data.range(447, 384) = src[6];
	dest->data.range(383, 320) = src[5];
	dest->data.range(319, 256) = src[4];
	dest->data.range(255, 192) = src[3];
	dest->data.range(191, 128) = src[2];
	dest->data.range(127, 64) = src[1];
	dest->data.range(63, 0) = src[0];
	return;
}

void mmInterface::rxBuffUnPack(ouchMsgProcess_t *src, ap_uint<64> dest[32])
{
#pragma HLS INLINE

	dest[31] = src->data.range(2047, 1984);
	dest[30] = src->data.range(1983, 1920);
	dest[29] = src->data.range(1919, 1856);
	dest[28] = src->data.range(1855, 1792);
	dest[27] = src->data.range(1791, 1728);
	dest[26] = src->data.range(1727, 1664);
	dest[25] = src->data.range(1663, 1600);
	dest[24] = src->data.range(1599, 1536);
	dest[23] = src->data.range(1535, 1472);
	dest[22] = src->data.range(1471, 1408);
	dest[21] = src->data.range(1407, 1344);
	dest[20] = src->data.range(1343, 1280);
	dest[19] = src->data.range(1279, 1216);
	dest[18] = src->data.range(1215, 1152);
	dest[17] = src->data.range(1151, 1088);
	dest[16] = src->data.range(1087, 1024);
	dest[15] = src->data.range(1023, 960);
	dest[14] = src->data.range(959, 896);
	dest[13] = src->data.range(895, 832);
	dest[12] = src->data.range(831, 768);
	dest[11] = src->data.range(767, 704);
	dest[10] = src->data.range(703, 640);
	dest[9] = src->data.range(639, 576);
	dest[8] = src->data.range(575, 512);
	dest[7] = src->data.range(511, 448);
	dest[6] = src->data.range(447, 384);
	dest[5] = src->data.range(383, 320);
	dest[4] = src->data.range(319, 256);
	dest[3] = src->data.range(255, 192);
	dest[2] = src->data.range(191, 128);
	dest[1] = src->data.range(127, 64);
	dest[0] = src->data.range(63, 0);
	return;
}

void mmInterface::ipTuplePack(ipTuple_t *src,
							  ipTuplePack_t *dest)
{
#pragma HLS INLINE

	dest->data.range(47, 32) = src->port;
	dest->data.range(31, 0) = src->address;

	return;
}

void mmInterface::udpMetaPack(ipUdpMeta_t *src,
							  ipUdpMetaPack_t *dest)
{
#pragma HLS INLINE

	dest->data.range(128, 128) = src->validSum;
	dest->data.range(127, 112) = src->subSum;
	dest->data.range(111, 96) = src->length;
	dest->data.range(95, 80) = src->dstPort;
	dest->data.range(79, 48) = src->dstAddress;
	dest->data.range(47, 32) = src->srcPort;
	dest->data.range(31, 0) = src->srcAddress;

	return;
}

void mmInterface::udpMetaUnpack(ipUdpMetaPack_t *src,
								ipUdpMeta_t *dest)
{
#pragma HLS INLINE

	dest->validSum = src->data.range(128, 128);
	dest->subSum = src->data.range(127, 112);
	dest->length = src->data.range(111, 96);
	dest->dstPort = src->data.range(95, 80);
	dest->dstAddress = src->data.range(79, 48);
	dest->srcPort = src->data.range(47, 32);
	dest->srcAddress = src->data.range(31, 0);

	return;
}

void mmInterface::ipTcpReadRequestPack(ipTcpReadRequest_t *src,
									   ipTcpReadRequestPack_t *dest)
{
#pragma HLS INLINE

	dest->data.range(31, 16) = src->length;
	dest->data.range(15, 0) = src->sessionID;

	return;
}

void mmInterface::ipTcpTxMetaPack(ipTcpTxMeta_t *src,
								  ipTcpTxMetaPack_t *dest)
{
#pragma HLS INLINE

	dest->data.range(48, 48) = src->validSum;
	dest->data.range(47, 32) = src->subSum;
	dest->data.range(31, 16) = src->length;
	dest->data.range(15, 0) = src->sessionID;

	return;
}

void mmInterface::ipTcpNotificationUnpack(ipTcpNotificationPack_t *src,
										  ipTcpNotification_t *dest)
{
#pragma HLS INLINE

	dest->rsvd = src->data.range(103, 96);
	dest->opened = src->data.range(95, 88);
	dest->closed = src->data.range(87, 80);
	dest->dstPort = src->data.range(79, 64);
	dest->ipAddress = src->data.range(63, 32);
	dest->length = src->data.range(31, 16);
	dest->sessionID = src->data.range(15, 0);

	return;
}

void mmInterface::ipTcpConnectionStatusUnpack(ipTcpConnectionStatusPack_t *src,
											  ipTcpConnectionStatus_t *dest)
{
#pragma HLS INLINE

	dest->success = src->data.range(23, 16);
	dest->sessionID = src->data.range(15, 0);

	return;
}

void mmInterface::ipTcpTxStatusStreamUnpack(ipTcpTxStatusPack_t *src,
											ipTcpTxStatus_t *dest)
{
#pragma HLS INLINE

	dest->error = src->data.range(63, 62);
	dest->space = src->data.range(61, 32);
	dest->length = src->data.range(31, 16);
	dest->sessionID = src->data.range(15, 0);

	return;
}

void mmInterface::ipTcpTxMetaUnpack(ipTcpTxMetaPack_t *src, ipTcpTxMeta_t *dest)
{
#pragma HLS INLINE

	dest->validSum = src->data.range(48, 48);
	dest->subSum = src->data.range(47, 32);
	dest->length = src->data.range(31, 16);
	dest->sessionID = src->data.range(15, 0);
}

void mmInterface::ipTcpNotificationPack(ipTcpNotification_t *src,
										ipTcpNotificationPack_t *dest)
{
	dest->data.range(103, 96) = src->rsvd;
	dest->data.range(95, 88) = src->opened;
	dest->data.range(87, 80) = src->closed;
	dest->data.range(79, 64) = src->dstPort;
	dest->data.range(63, 32) = src->ipAddress;
	dest->data.range(31, 16) = src->length;
	dest->data.range(15, 0) = src->sessionID;
}

void mmInterface::ipTcpConnectionStatusPack(ipTcpConnectionStatus_t *src, ipTcpConnectionStatusPack_t *dest)
{
#pragma HLS INLINE

	dest->data.range(23, 16) = src->success;
	dest->data.range(15, 0) = src->sessionID;

	return;
}

void mmInterface::ipTcpTxStatusStreamPack(ipTcpTxStatus_t *src, ipTcpTxStatusPack_t *dest)
{
#pragma HLS INLINE
	dest->data.range(63, 62) = src->error;
	dest->data.range(61, 32) = src->space;
	dest->data.range(31, 16) = src->length;
	dest->data.range(15, 0) = src->sessionID;

	return;
}
void mmInterface::positionInfoPack(positionInfo_t *src, positionInfoPack_t *dest)
{
#pragma HLS INLINE
	dest->range (191,176) = src->decimalInPrice;//	decimalInPrice	 <	16	>
	dest->range (175,160) = src->symbolIndex;//	symbolIndex	 <	16	>
	dest->range (159,128) = src->orderBookId;//	orderBookId	 <	32	>
	dest->range (127,64) = src->position;//	position	 <	64	>
	dest->range (63,0) = src->sellableVolume;//	sellableVolume	 <	64	>
	return;
}

void mmInterface::positionInfoUnpack(positionInfoPack_t *src, positionInfo_t *dest)
{
#pragma HLS INLINE
	dest->decimalInPrice = src->range (191,176);//		decimalInPrice	 <	16	>
	dest->symbolIndex = src->range (175,160);//		symbolIndex	 <	16	>
	dest->orderBookId = src->range (159,128);//		orderBookId	 <	32	>
	dest->position = src->range (127,64);//		position	 <	64	>
	dest->sellableVolume = src->range (63,0);//		sellableVolume	 <	64	>
	return;
}

void mmInterface::orderInfoPack(orderInfo_t *src, orderInfoPack_t *dest)
{
#pragma HLS INLINE
	dest->range (503,496) = src->side;//	side	 <	8	>
	dest->range (495,480) = src->symbolIndex;//	symbolIndex	 <	16	>
	dest->range (479,464) = src->decimalInPrice;//	decimalInPrice	 <	16	>
	dest->range (463,432) = src->price;//	price	 <	32	>
	dest->range (431,368) = src->lastOrderEventTimeStamp;//	lastOrderEventTimeStamp	 <	64	>
	dest->range (367,304) = src->creditUsed;//	creditUsed	 <	64	>
	dest->range (303,240) = src->creditUsedMatch;//	creditUsedMatch	 <	64	>
	dest->range (239,176) = src->outstandingVolume;//	outstandingVolume	 <	64	>
	dest->range (175,112) = src->orgVolume;//	orgVolume	 <	64	>
	dest->range (111,0) = src->tokenTrack;//	tokenTrack	 <	112	>
}

void mmInterface::orderInfoUnPack(orderInfoPack_t *src, orderInfo_t *dest)
{
#pragma HLS INLINE
	dest->side = src->range (503,496);//		side	 <	8	>
	dest->symbolIndex = src->range (495,480);//		symbolIndex	 <	16	>
	dest->decimalInPrice = src->range (479,464);//		decimalInPrice	 <	16	>
	dest->price = src->range (463,432);//		price	 <	32	>
	dest->lastOrderEventTimeStamp = src->range (431,368);//		lastOrderEventTimeStamp	 <	64	>
	dest->creditUsed = src->range (367,304);//		creditUsed	 <	64	>
	dest->creditUsedMatch = src->range (303,240);//		creditUsedMatch	 <	64	>
	dest->outstandingVolume = src->range (239,176);//		outstandingVolume	 <	64	>
	dest->orgVolume = src->range (175,112);//		orgVolume	 <	64	>
	dest->tokenTrack = src->range (111,0);//		tokenTrack	 <	112	>
}

void mmInterface::tokenMapPack(tokenMap_t *src, tokenMapPack_t *dest)
{
#pragma HLS INLINE
	dest->range(239,224) = src->symbolIndex;
	dest->range(223,112) = src->origineToken;
	dest->range(111, 0) = src->replaceToken;
}

void mmInterface::tokenMapUnpack(tokenMapPack_t *src, tokenMap_t *dest)
{
#pragma HLS INLINE
	dest->symbolIndex = src->range(239, 224);
	dest->origineToken = src->range(223,112);
	dest->replaceToken = src->range(111, 0);
}


void mmInterface::itchMetaPack(itchMeta_t *src,itchMetaPack_t *dest)
{
#pragma HLS INLINE

	dest->data.range(63, 32) = src->seqNumber;
	dest->data.range(23, 16) = src->type;
	dest->data.range(15, 8) = src->connNum;
	dest->data.range(7, 0) = src->splitID;
}

void mmInterface::itchMetaUnPack(itchMetaPack_t *src,itchMeta_t *dest)
{
#pragma HLS INLINE
	dest->seqNumber = src->data.range(63, 32);
	dest->type = src->data.range(23, 16);
	dest->connNum = src->data.range(15, 8);
	dest->splitID = src->data.range(7, 0);
}

void mmInterface::sessionMapPack(sessionMap_t *src,sessionMapPack_t *dest)
{
#pragma HLS INLINE

	dest->data.range(31, 24) = src->type;
	dest->data.range(23, 16) = src->connNum;
	dest->data.range(15, 0) = src->sessionID;
}

void mmInterface::sessionMapUnPack(sessionMapPack_t *src,sessionMap_t *dest)
{
#pragma HLS INLINE
	dest->type = src->data.range(31, 24);
	dest->connNum = src->data.range(23, 16);
	dest->sessionID = src->data.range(15, 0);
}

void mmInterface::cuHbResetPack(cuHbReset_t *src,cuHbResetPack_t *dest)
{
#pragma HLS INLINE

	dest->data.range(15, 8) = src->connNum;
	dest->data.range(7, 0) = src->type;
}

void mmInterface::cuHbResetUnPack(cuHbResetPack_t *src,cuHbReset_t *dest)
{
#pragma HLS INLINE
	dest->connNum = src->data.range(15, 8);
	dest->type = src->data.range(7, 0);
}

void mmInterface::seqCounterPack(seqCounter_t *src,seqCounterPack_t *dest)
{
#pragma HLS INLINE

	dest->data.range(63, 56) = src->type;
	dest->data.range(55, 48) = src->connNum;
	dest->data.range(47, 32) = src->sessionID;
	dest->data.range(31, 0) = src->seqNum;
}

void mmInterface::seqCounterUnPack(seqCounterPack_t *src,seqCounter_t *dest)
{
#pragma HLS INLINE
	dest->type = src->data.range(63, 56);
	dest->connNum = src->data.range(55, 48);
	dest->sessionID = src->data.range(47, 32);
	dest->seqNum = src->data.range(31, 0);
}

void mmInterface::seqNumberMapPack(seqNumberMap_t *src,seqNumberMapPack_t *dest)
{
#pragma HLS INLINE

	dest->data.range(63, 48) = src->connNum;
	dest->data.range(47, 16) = src->seqNum;
}

void mmInterface::seqNumberMapUnPack(seqNumberMapPack_t *src,seqNumberMap_t *dest)
{
#pragma HLS INLINE
	dest->connNum = src->data.range(63, 48);
	dest->seqNum = src->data.range(47, 16);
}


void mmInterface::memOperationPack(orderEntryMemOperation_t*src, memOperationPack_t*dest)
{
#pragma HLS PIPELINE
	dest->data.range(1015,1008) = src->opCode;
	dest->data.range(1007,1000) = src->statement;
	dest->data.range(999,984) = src->positionInfo.decimalInPrice;
	dest->data.range(983,968) = src->positionInfo.symbolIndex;
	dest->data.range(967,936) = src->positionInfo.orderBookId;
	dest->data.range(935,872) = src->positionInfo.position;
	dest->data.range(871,808) = src->positionInfo.sellableVolume;
	dest->data.range(807,744) = src->creditLmt.creditLimit;
	dest->data.range(743,736) = src->orderInfo.side;
	dest->data.range(735,720) = src->orderInfo.symbolIndex;
	dest->data.range(719,704) = src->orderInfo.decimalInPrice;
	dest->data.range(703,672) = src->orderInfo.price;
	dest->data.range(671,608) = src->orderInfo.lastOrderEventTimeStamp;
	dest->data.range(607,544) = src->orderInfo.creditUsed;
	dest->data.range(543,480) = src->orderInfo.creditUsedMatch;
	dest->data.range(479,416) = src->orderInfo.outstandingVolume;
	dest->data.range(415,352) = src->orderInfo.orgVolume;
	dest->data.range(351,240) = src->orderInfo.tokenTrack;
	dest->data.range(239,224) = src->token.symbolIndex;
	dest->data.range(223,112) = src->token.replaceToken;
	dest->data.range(111, 0) = src->token.origineToken;

}

void mmInterface::memOperationUnPack(memOperationPack_t*src ,orderEntryMemOperation_t*dest )
{
#pragma HLS PIPELINE
	dest->opCode = src->data.range(1015,1008);
	dest->statement = src->data.range(1007,1000);
	dest->positionInfo.decimalInPrice = src->data.range (999,984);
	dest->positionInfo.symbolIndex = src->data.range (983,968);
	dest->positionInfo.orderBookId = src->data.range (967,936);
	dest->positionInfo.position = src->data.range (935,872);
	dest->positionInfo.sellableVolume = src->data.range (871,808);
	dest->creditLmt.creditLimit = src->data.range (807,744);
	dest->orderInfo.side = src->data.range (743,736);
	dest->orderInfo.symbolIndex = src->data.range (735,720);
	dest->orderInfo.decimalInPrice = src->data.range (719,704);
	dest->orderInfo.price = src->data.range (703,672);
	dest->orderInfo.lastOrderEventTimeStamp = src->data.range (671,608);
	dest->orderInfo.creditUsed = src->data.range (607,544);
	dest->orderInfo.creditUsedMatch = src->data.range (543,480);
	dest->orderInfo.outstandingVolume = src->data.range (479,416);
	dest->orderInfo.orgVolume = src->data.range (415,352);
	dest->orderInfo.tokenTrack = src->data.range (351,240);
	dest->token.symbolIndex = src->data.range (239,224);
	dest->token.replaceToken = src->data.range (223,112);
	dest->token.origineToken = src->data.range (111, 0);
}


void mmInterface::positionInfoAxiPack(positionInfo_t *src, positionInfoAxiPack_t *dest)
{
#pragma HLS INLINE
	dest->data.range (191,176) = src->decimalInPrice;//	decimalInPrice	 <	16	>
	dest->data.range (175,160) = src->symbolIndex;//	symbolIndex	 <	16	>
	dest->data.range (159,128) = src->orderBookId;//	orderBookId	 <	32	>
	dest->data.range (127,64) = src->position;//	position	 <	64	>
	dest->data.range (63,0) = src->sellableVolume;//	sellableVolume	 <	64	>
	return;
}

void mmInterface::positionInfoAxiUnpack(positionInfoAxiPack_t *src, positionInfo_t *dest)
{
#pragma HLS INLINE
	dest->decimalInPrice = src->data.range (191,176);//		decimalInPrice	 <	16	>
	dest->symbolIndex = src->data.range (175,160);//		symbolIndex	 <	16	>
	dest->orderBookId = src->data.range (159,128);//		orderBookId	 <	32	>
	dest->position = src->data.range (127,64);//		position	 <	64	>
	dest->sellableVolume = src->data.range (63,0);//		sellableVolume	 <	64	>
	return;
}

void mmInterface::orderInfoAxiPack(orderInfo_t *src, orderInfoAxiPack_t *dest)
{
#pragma HLS INLINE
	dest->data.range (503,496) = src->side;//	side	 <	8	>
	dest->data.range (495,480) = src->symbolIndex;//	symbolIndex	 <	16	>
	dest->data.range (479,464) = src->decimalInPrice;//	decimalInPrice	 <	16	>
	dest->data.range (463,432) = src->price;//	price	 <	32	>
	dest->data.range (431,368) = src->lastOrderEventTimeStamp;//	lastOrderEventTimeStamp	 <	64	>
	dest->data.range (367,304) = src->creditUsed;//	creditUsed	 <	64	>
	dest->data.range (303,240) = src->creditUsedMatch;//	creditUsedMatch	 <	64	>
	dest->data.range (239,176) = src->outstandingVolume;//	outstandingVolume	 <	64	>
	dest->data.range (175,112) = src->orgVolume;//	orgVolume	 <	64	>
	dest->data.range (111,0) = src->tokenTrack;//	tokenTrack	 <	112	>
}

void mmInterface::orderInfoAxiUnPack(orderInfoAxiPack_t *src, orderInfo_t *dest)
{
#pragma HLS INLINE
	dest->side = src->data.range (503,496);//		side	 <	8	>
	dest->symbolIndex = src->data.range (495,480);//		symbolIndex	 <	16	>
	dest->decimalInPrice = src->data.range (479,464);//		decimalInPrice	 <	16	>
	dest->price = src->data.range (463,432);//		price	 <	32	>
	dest->lastOrderEventTimeStamp = src->data.range (431,368);//		lastOrderEventTimeStamp	 <	64	>
	dest->creditUsed = src->data.range (367,304);//		creditUsed	 <	64	>
	dest->creditUsedMatch = src->data.range (303,240);//		creditUsedMatch	 <	64	>
	dest->outstandingVolume = src->data.range (239,176);//		outstandingVolume	 <	64	>
	dest->orgVolume = src->data.range (175,112);//		orgVolume	 <	64	>
	dest->tokenTrack = src->data.range (111,0);//		tokenTrack	 <	112	>
}


void mmInterface::dwExecutePack(dwExecute_t *src, dwExecutePack_t *dest)
{
#pragma HLS INLINE
	dest->data.range(	511	,	496	)= src->	symbolIndex	;  //	symbolIndex	 <	16	>
	dest->data.range(	495	,	464	)= src->	orderbookId	;  //	orderbookId	 <	32	>
	dest->data.range(	463	,	432	)= src->	sequenceNumber	;  //	sequenceNumber	 <	32	>
	dest->data.range(	431	,	400	)= src->	currentMillis	;  //	currentMillis	 <	32	>
	dest->data.range(	399	,	392	)= src->	isCall	;  //	isCall	 <	8	>
	dest->data.range(	391	,	384	)= src->	side	;  //	side	 <	8	>
	dest->data.range(	383	,	352	)= src->	triggerPrice	;  //	triggerPrice	 <	32	>
	dest->data.range(	351	,	320	)= src->	price	;  //	price	 <	32	>
	dest->data.range(	319	,	256	)= src->	qtyInput	;  //	qtyInput	 <	64	>
	dest->data.range(	255	,	224	)= src->	bid0	;  //	bid0	 <	32	>
	dest->data.range(	223	,	192	)= src->	bid1	;  //	bid1	 <	32	>
	dest->data.range(	191	,	160	)= src->	ask0	;  //	ask0	 <	32	>
	dest->data.range(	159	,	128	)= src->	ask1	;  //	ask1	 <	32	>
	dest->data.range(	127	,	120	)= src->	valid	;  //	valid	 <	8	>
}

void mmInterface::dwExecuteUnPack(dwExecutePack_t *src, dwExecute_t *dest)
{
#pragma HLS INLINE
	dest->	symbolIndex	= src->data.range(	511	,	496	);  //		symbolIndex	 <	16	>
	dest->	orderbookId	= src->data.range(	495	,	464	);  //		orderbookId	 <	32	>
	dest->	sequenceNumber	= src->data.range(	463	,	432	);  //		sequenceNumber	 <	32	>
	dest->	currentMillis	= src->data.range(	431	,	400	);  //		currentMillis	 <	32	>
	dest->	isCall	= src->data.range(	399	,	392	);  //		isCall	 <	8	>
	dest->	side	= src->data.range(	391	,	384	);  //		side	 <	8	>
	dest->	triggerPrice	= src->data.range(	383	,	352	);  //		triggerPrice	 <	32	>
	dest->	price	= src->data.range(	351	,	320	);  //		price	 <	32	>
	dest->	qtyInput	= src->data.range(	319	,	256	);  //		qtyInput	 <	64	>
	dest->	bid0	= src->data.range(	255	,	224	);  //		bid0	 <	32	>
	dest->	bid1	= src->data.range(	223	,	192	);  //		bid1	 <	32	>
	dest->	ask0	= src->data.range(	191	,	160	);  //		ask0	 <	32	>
	dest->	ask1	= src->data.range(	159	,	128	);  //		ask1	 <	32	>
	dest->	valid	= src->data.range(	127	,	120	);  //		valid	 <	8	>
}

void mmInterface::dwPositionUpdatePack(dwPositionUpdate_t *src, dwPositionUpdatePack_t *dest)
{
#pragma HLS INLINE
	dest->data.range (255,240) = src->symbolIndex;
	dest->data.range (239,208) = src->orderbookId;
	dest->data.range (207,176) = src->currentPosition_update;
	dest->data.range (175,144) = src->realizedPosition_update;
	dest->data.range (143,112) = src->openSellPosition_update;
}

void mmInterface::dwPositionUpdateUnPack(dwPositionUpdatePack_t *src, dwPositionUpdate_t *dest)
{
#pragma HLS INLINE
	dest->symbolIndex = src->data.range (255,240);
	dest->orderbookId = src->data.range (239,208);
	dest->currentPosition_update = src->data.range (207,176);
	dest->realizedPosition_update = src->data.range (175,144);
	dest->openSellPosition_update = src->data.range (143,112);
}



void mmInterface::peTradeTickerMsgPack (peTradeTickerMsg_t *src, peTradeTickerMsgPack_t *dest )
{
#pragma  HLS INLINE
	dest->data.range(	1023	,	1016	)= src->	messageType	;  //	messageType	 <	8	>
	dest->data.range(	1015	,	1000	)= src->	symbolIndex	;  //	symbolIndex	 <	16	>
	dest->data.range(	999	,	968	)= src->	sequenceNumber	;  //	sequenceNumber	 <	32	>
	dest->data.range(	967	,	936	)= src->	second	;  //	second	 <	32	>
	dest->data.range(	935	,	904	)= src->	nanos	;  //	nanos	 <	32	>
	dest->data.range(	903	,	872	)= src->	orderBookId	;  //	orderBookId	 <	32	>
	dest->data.range(	871	,	808	)= src->	dealId	;  //	dealId	 <	64	>
	dest->data.range(	807	,	776	)= src->	price	;  //	price	 <	32	>
	dest->data.range(	775	,	712	)= src->	quantity	;  //	quantity	 <	64	>
	dest->data.range(	711	,	648	)= src->	dealDateTime	;  //	dealDateTime	 <	64	>
	dest->data.range(	647	,	640	)= src->	aggressor	;  //	aggressor	 <	8	>
	dest->data.range(	639	,	608	)= src->	lastOrderStateSecond	;  //	lastOrderStateSecond	 <	32	>
	dest->data.range(	607	,	576	)= src->	lastLimitOrderBookSecond	;  //	lastLimitOrderBookSecond	 <	32	>
	dest->data.range(	575	,	544	)= src->	lastLimitOrderBookNanos	;  //	lastLimitOrderBookNanos	 <	32	>
	dest->data.range(	543	,	536	)= src->	tradableCalByStateMsg	;  //	tradableCalByStateMsg	 <	8	>
	dest->data.range(	535	,	504	)= src->	currentMs	;  //	currentMs	 <	32	>
	dest->data.range(	503	,	472	)= src->	Ul	;  //	Ul	 <	32	>
	dest->data.range(	471	,	440	)= src->	Dw	;  //	Dw	 <	32	>
	dest->data.range(	439	,	408	)= src->	isCall	;  //	isCall	 <	32	>
	dest->data.range(	407	,	400	)= src->	trigger	;  //	trigger	 <	8	>
	dest->data.range(	399	,	368	)= src->	triggerPrice	;  //	triggerPrice	 <	32	>

}

void mmInterface::peTradeTickerMsgUnPack (peTradeTickerMsgPack_t *src, peTradeTickerMsg_t *dest )
{
#pragma  HLS INLINE
	dest->	messageType	= src->data.range(	1023	,	1016	);  //		messageType	 <	8	>
	dest->	symbolIndex	= src->data.range(	1015	,	1000	);  //		symbolIndex	 <	16	>
	dest->	sequenceNumber	= src->data.range(	999	,	968	);  //		sequenceNumber	 <	32	>
	dest->	second	= src->data.range(	967	,	936	);  //		second	 <	32	>
	dest->	nanos	= src->data.range(	935	,	904	);  //		nanos	 <	32	>
	dest->	orderBookId	= src->data.range(	903	,	872	);  //		orderBookId	 <	32	>
	dest->	dealId	= src->data.range(	871	,	808	);  //		dealId	 <	64	>
	dest->	price	= src->data.range(	807	,	776	);  //		price	 <	32	>
	dest->	quantity	= src->data.range(	775	,	712	);  //		quantity	 <	64	>
	dest->	dealDateTime	= src->data.range(	711	,	648	);  //		dealDateTime	 <	64	>
	dest->	aggressor	= src->data.range(	647	,	640	);  //		aggressor	 <	8	>
	dest->	lastOrderStateSecond	= src->data.range(	639	,	608	);  //		lastOrderStateSecond	 <	32	>
	dest->	lastLimitOrderBookSecond	= src->data.range(	607	,	576	);  //		lastLimitOrderBookSecond	 <	32	>
	dest->	lastLimitOrderBookNanos	= src->data.range(	575	,	544	);  //		lastLimitOrderBookNanos	 <	32	>
	dest->	tradableCalByStateMsg	= src->data.range(	543	,	536	);  //		tradableCalByStateMsg	 <	8	>
	dest->	currentMs	= src->data.range(	535	,	504	);  //		currentMs	 <	32	>
	dest->	Ul	= src->data.range(	503	,	472	);  //		Ul	 <	32	>
	dest->	Dw	= src->data.range(	471	,	440	);  //		Dw	 <	32	>
	dest->	isCall	= src->data.range(	439	,	408	);  //		isCall	 <	32	>
	dest->	trigger	= src->data.range(	407	,	400	);  //		trigger	 <	8	>
	dest->	triggerPrice	= src->data.range(	399	,	368	);  //		triggerPrice	 <	32	>
}

void mmInterface::peLmtOrdBookMsgPack (peLmtOrdBookMsg_t *src, peLmtOrdBookMsgPack_t *dest )
{
#pragma HLS INLINE
	dest->data.range(	1023	,	1016	)= src->	messageType	;  //	messageType	 <	8	>
	dest->data.range(	1015	,	1000	)= src->	symbolIndex	;  //	symbolIndex	 <	16	>
	dest->data.range(	999	,	968	)= src->	sequenceNumber	;  //	sequenceNumber	 <	32	>
	dest->data.range(	967	,	936	)= src->	second	;  //	second	 <	32	>
	dest->data.range(	935	,	904	)= src->	nanos	;  //	nanos	 <	32	>
	dest->data.range(	903	,	872	)= src->	orderBookId	;  //	orderBookId	 <	32	>
	dest->data.range(	871	,	840	)= src->	askPrice0	;  //	askPrice0	 <	32	>
	dest->data.range(	839	,	808	)= src->	askPrice1	;  //	askPrice1	 <	32	>
	dest->data.range(	807	,	776	)= src->	bidPrice0	;  //	bidPrice0	 <	32	>
	dest->data.range(	775	,	744	)= src->	bidPrice1	;  //	bidPrice1	 <	32	>
	dest->data.range(	743	,	680	)= src->	askVol0	;  //	askVol0	 <	64	>
	dest->data.range(	679	,	616	)= src->	askVol1	;  //	askVol1	 <	64	>
	dest->data.range(	615	,	552	)= src->	bidVol0	;  //	bidVol0	 <	64	>
	dest->data.range(	551	,	488	)= src->	bidVol1	;  //	bidVol1	 <	64	>
	dest->data.range(	487	,	456	)= src->	lastOrderStateSecond	;  //	lastOrderStateSecond	 <	32	>
	dest->data.range(	455	,	424	)= src->	currentMs	;  //	currentMs	 <	32	>
	dest->data.range(	423	,	416	)= src->	trigger	;  //	trigger	 <	8	>
	dest->data.range(	415	,	384	)= src->	triggerPrice	;  //	triggerPrice	 <	32	>
	dest->data.range(	383	,	352	)= src->	Ul	;  //	Ul	 <	32	>
	dest->data.range(	351	,	320	)= src->	Dw	;  //	Dw	 <	32	>
	dest->data.range(	319	,	288	)= src->	isCall	;  //	isCall	 <	32	>
}

void mmInterface::peLmtOrdBookMsgUnPack (peLmtOrdBookMsgPack_t *src, peLmtOrdBookMsg_t *dest)
{
#pragma HLS INLINE
	dest->	messageType	= src->data.range(	1023	,	1016	);  //		messageType	 <	8	>
	dest->	symbolIndex	= src->data.range(	1015	,	1000	);  //		symbolIndex	 <	16	>
	dest->	sequenceNumber	= src->data.range(	999	,	968	);  //		sequenceNumber	 <	32	>
	dest->	second	= src->data.range(	967	,	936	);  //		second	 <	32	>
	dest->	nanos	= src->data.range(	935	,	904	);  //		nanos	 <	32	>
	dest->	orderBookId	= src->data.range(	903	,	872	);  //		orderBookId	 <	32	>
	dest->	askPrice0	= src->data.range(	871	,	840	);  //		askPrice0	 <	32	>
	dest->	askPrice1	= src->data.range(	839	,	808	);  //		askPrice1	 <	32	>
	dest->	bidPrice0	= src->data.range(	807	,	776	);  //		bidPrice0	 <	32	>
	dest->	bidPrice1	= src->data.range(	775	,	744	);  //		bidPrice1	 <	32	>
	dest->	askVol0	= src->data.range(	743	,	680	);  //		askVol0	 <	64	>
	dest->	askVol1	= src->data.range(	679	,	616	);  //		askVol1	 <	64	>
	dest->	bidVol0	= src->data.range(	615	,	552	);  //		bidVol0	 <	64	>
	dest->	bidVol1	= src->data.range(	551	,	488	);  //		bidVol1	 <	64	>
	dest->	lastOrderStateSecond	= src->data.range(	487	,	456	);  //		lastOrderStateSecond	 <	32	>
	dest->	currentMs	= src->data.range(	455	,	424	);  //		currentMs	 <	32	>
	dest->	trigger	= src->data.range(	423	,	416	);  //		trigger	 <	8	>
	dest->	triggerPrice	= src->data.range(	415	,	384	);  //		triggerPrice	 <	32	>
	dest->	Ul	= src->data.range(	383	,	352	);  //		Ul	 <	32	>
	dest->	Dw	= src->data.range(	351	,	320	);  //		Dw	 <	32	>
	dest->	isCall	= src->data.range(	319	,	288	);  //		isCall	 <	32	>
}



ap_uint<32> mmInterface::hashTableMod (ap_uint<112> &token, ap_uint<32> &size)
{
#pragma HLS INLINE

	mmInterface intf;
	ap_uint<32> index;
	ap_uint<32> joinDateAndNum;
	ap_uint<16> number;
	ap_uint<72> tokenDate;
	ap_uint<40> tokenNum;

	tokenDate.range(71, 0) = token.range(111,40);
	tokenNum.range(39, 0) = token.range(39,0);

	joinDateAndNum = (intf.ansciiDateToInt(tokenDate) * 100000) + 	intf.ansciiNumToInt(tokenNum) ;
	index = joinDateAndNum%size;
	return index;
}

ap_uint<16> mmInterface::ansciiDateToInt (ap_uint<72> &token)
{
#pragma HLS INLINE
	static ap_uint<16> addData;
	addData = token.range(71, 64); // slot 6
	addData += token.range(63, 56); // slot 7
	addData += token.range(55, 48); // slot 8
	addData += token.range(47, 40); // slot 9
	addData += token.range(39, 32); // slot 10
	addData += token.range(31, 24); // slot 11
	addData += token.range(23, 16); // slot 12
	addData += token.range(15, 8); // slot 13
	addData += token.range(7, 0); // slot 14
	return addData;
}

ap_uint<32> mmInterface::ansciiToInt (ap_uint<8> &data)
{
#pragma HLS INLINE

	static ap_uint<32> intData;
	switch(data)
	{
		case '0': intData = 0; break;
		case '1':	intData = 1; break;
		case '2':	intData = 2; break;
		case '3': intData = 3; break;
		case '4': intData = 4; break;
		case '5': intData = 5; break;
		case '6':	intData = 6; break;
		case '7':	intData = 7; break;
		case '8':	intData = 8; break;
		case '9': intData = 9; break;
	}
		return intData;
}

ap_uint<32>mmInterface::ansciiNumToInt (ap_uint<40> & token)
{
#pragma HLS INLINE

	mmInterface intf;
	static ap_uint<32> numData;
	static ap_uint<8> pos4th;
	static ap_uint<8> pos3th;
	static ap_uint<8> pos2th;
	static ap_uint<8> pos1th;
	static ap_uint<8> pos0th;

	pos4th = token.range(39,32);
	pos3th = token.range(31,24);
	pos2th = token.range(23,16);
	pos1th = token.range(15,8);
	pos0th = token.range(7,0);

	numData = intf.ansciiToInt(pos4th) * 10000; //4th position
	numData += intf.ansciiToInt(pos3th) * 1000; // 3th pos
	numData += intf.ansciiToInt(pos2th) * 100; // 2nd pos
	numData += intf.ansciiToInt(pos1th) * 10; // 1st pos
	numData += intf.ansciiToInt(pos0th); // 0 pos

	return numData;

}

orderInfo_t mmInterface::searchOrderInfoHT(ap_uint<112> &token, ap_uint<32> &index, ap_uint<32> &dim
												, orderInfoPack_t orderInfoMapPack[NUM_preRisk][NUM_DIM_HT], bool &foundRD)
{
#pragma HLS PIPELINE

	static orderInfo_t orderInfo;
	static orderInfo_t findOrderInfo;
	mmInterface intf;
	static ap_uint32_t indexHT;
	static ap_uint32_t dimenHT;

	ap_uint32_t size = NUM_preRisk;
	static orderInfoPack_t orderInfoPack;
	bool save = false;
	bool found = false;

	indexHT = intf.hashTableMod(token, size);
LoopSearchOrderInfoHT:
	for (ap_uint<32> i =0 ; i < NUM_DIM_HT ; i ++)
		{
//#pragma HLS UNROLL
			orderInfoPack = orderInfoMapPack[indexHT][i];
			intf.orderInfoUnPack(&orderInfoPack, &orderInfo);

			if(orderInfo.tokenTrack == token && save == false)
				{
					dimenHT = i;
					findOrderInfo = orderInfo;
					save = true;
					found = true;
				}
			else if(save == false)
				{
					findOrderInfo = {0};
					found = false;

					//mem full for this index
				}

		}
	dim = dimenHT;
	index = indexHT;
	foundRD = found;
	return findOrderInfo;

}


void mmInterface::insertNewOrderInfoHT(orderInfo_t &newOrderInfo,orderInfoPack_t orderInfoMapPack[NUM_preRisk][NUM_DIM_HT], bool &full)
{
#pragma HLS DATAFLOW

	static orderInfo_t orderInfo = newOrderInfo;
	static orderInfo_t findOrderInfo;
	mmInterface intf;
	static ap_uint32_t indexHT;
	static ap_uint32_t dimenHT;

	ap_uint32_t size = NUM_preRisk;
	static orderInfoPack_t orderInfoPack;
	bool found = false;
	bool fullStatus = false;


	indexHT = intf.hashTableMod(newOrderInfo.tokenTrack, size);
LoopInsertNewOrderInfoHT:
	for (ap_uint<32> i =0 ; i < NUM_DIM_HT ; i ++)
		{
#pragma HLS PIPELINE

			if (orderInfoMapPack[indexHT][i] == 0 && found == false)
				{
					intf.orderInfoPack(&newOrderInfo, &orderInfoPack);
					orderInfoMapPack[indexHT][i] = orderInfoPack;
					dimenHT = i;
					found = true;
					fullStatus = false;
				}
			else if (orderInfoMapPack[indexHT][i] != 0 && found == false)
				{
					dimenHT = NUM_DIM_HT;
					fullStatus = true;
				}
		}
	full = fullStatus;
	return;

}


tokenMap_t mmInterface::searchRepFdOrgTokenMap(ap_uint<112> &token, ap_uint<32> &index, ap_uint<32> &dim
																					 , tokenMapPack_t repFdOrgTokenMap[NUM_preRisk][NUM_DIM_HT], bool &foundRD)
{
//#pragma HLS PIPELINE

	//use for delete during orderInfo
	static tokenMap_t tokenMap;
	static tokenMap_t findTokenMap;
	mmInterface intf;
	static ap_uint32_t indexHT;
	static ap_uint32_t dimenHT;
	ap_uint32_t size = NUM_preRisk;
	static tokenMapPack_t tokenMapPack;
	bool save = false;
	bool found = false;

	indexHT = intf.hashTableMod(token, size);
LoopSearchReplaceMapHT:
	for (ap_uint<32> i =0 ; i < NUM_DIM_HT ; i ++)
		{
//#pragma HLS PIPELINE

			tokenMapPack = repFdOrgTokenMap[indexHT][i];
			intf.tokenMapUnpack(&tokenMapPack, &tokenMap);
			if(tokenMap.replaceToken == token && save == false)
				{
					dimenHT = i;
					findTokenMap = tokenMap;
					save = true;
					found = true;
				}
			else if(save == false)
				{
					findTokenMap = {0};
					found = false;
					//mem full for this index
				}
		}
	dim = dimenHT;
	index = indexHT;
	foundRD = found;
	return findTokenMap;
}
//searchOrgTokenRepMap
tokenMap_t mmInterface::searchOrgFdRepTokenMap(ap_uint<112> &token, ap_uint<32> &index, ap_uint<32> &dim
						,tokenMapPack_t orgFdRepMapPack[NUM_preRisk][NUM_DIM_HT], bool &foundRD)
{
	// in orderentry memOp.token.origineToken = orderReplace.previousOrderToken
	// in memHandler searchToken = updateReq.token.origineToken
	// orgFdRepMapPack mem for finding original token with previous token
	//	hashTable
	//	replaceToken			OriginalToken
	//	T2								T1
	//	T3								T1
	//	T4								T1
//#pragma HLS PIPELINE

	static tokenMap_t tokenMap;
	static tokenMap_t findTokenMap;
	mmInterface intf;
	static ap_uint32_t indexHT;
	static ap_uint32_t dimenHT;
	ap_uint32_t size = NUM_preRisk;
	static tokenMapPack_t tokenMapPack;
	bool save = false;
	bool found = false;

	indexHT = intf.hashTableMod(token, size);
loopsearchOrgFdRepTokenMap:
	for (ap_uint<32> i =0 ; i < NUM_DIM_HT ; i ++)
		{
//#pragma HLS PIPELINE

			tokenMapPack = orgFdRepMapPack[indexHT][i];
			intf.tokenMapUnpack(&tokenMapPack, &tokenMap);
			if(tokenMap.origineToken == token && save == false)
				{
					dimenHT = i;
					findTokenMap = tokenMap;
					save = true;
					found = true;
				}
			else if(save == false)
				{
					findTokenMap = {0};
					found = false;
					//mem full for this index
				}
		}


	dim = dimenHT;
	index = indexHT;
	foundRD = found;
	return findTokenMap;
}
//insertReplaceMapHT
void mmInterface::insertOrgFdRepTokenMap(tokenMap_t &tokenMap,tokenMapPack_t repFdOrgMapPack[NUM_preRisk][NUM_DIM_HT], bool &full)
{
//#pragma HLS DATAFLOW

	static tokenMap_t findTokenMap;
	mmInterface intf;
	static ap_uint32_t indexHT;
	static ap_uint32_t dimenHT;

	ap_uint32_t size = NUM_preRisk;
	static tokenMapPack_t tokenMapPackData;
	bool found = false;
	bool fullStatus = false;


	indexHT = intf.hashTableMod(tokenMap.origineToken, size);
LoopinsertOrgFdRepTokenMap:
	for (ap_uint<32> i =0 ; i < NUM_DIM_HT ; i ++)
		{
//#pragma HLS PIPELINE

			if (repFdOrgMapPack[indexHT][i] == 0 && found == false)
				{
					intf.tokenMapPack(&tokenMap, &tokenMapPackData);
					repFdOrgMapPack[indexHT][i] = tokenMapPackData;
					dimenHT = i;
					found = true;
					fullStatus = false;
				}
			else if (repFdOrgMapPack[indexHT][i] != 0 && found == false)
				{
					dimenHT = 0xFFFFFFFF;
					fullStatus = true;
				}
		}

	full = fullStatus;

	return;

}
//insertOrgTokenRepMap
void mmInterface::insertRepFdOrgTokenMap(tokenMap_t &tokenMap,tokenMapPack_t orgFdRepMapPack[NUM_preRisk][NUM_DIM_HT], bool &full)
{
//#pragma HLS DATAFLOW

	static tokenMap_t findTokenMap;
	mmInterface intf;
	static ap_uint32_t indexHT;
	static ap_uint32_t dimenHT;
	ap_uint32_t size = NUM_preRisk;
	static tokenMapPack_t tokenMapPackData;
	static tokenMapPack_t read;

	bool found = false;
	bool fullStatus = false;


	indexHT = intf.hashTableMod(tokenMap.replaceToken, size);
LoopinsertOrgFdRepTokenMap:
	for (ap_uint<32> i =0 ; i < NUM_DIM_HT ; i ++)
		{
//#pragma HLS PIPELINE

			if (orgFdRepMapPack[indexHT][i] == 0 && found == false)
				{
					intf.tokenMapPack(&tokenMap, &tokenMapPackData);
					orgFdRepMapPack[indexHT][i] = tokenMapPackData;
					dimenHT = i;
					found = true;
					fullStatus = false;
				}
			else if (orgFdRepMapPack[indexHT][i] != 0 && found == false)
				{
					dimenHT = 0xFFFFFFFF;
					fullStatus = true;
				}
		}
	full = fullStatus;

	return;

}




