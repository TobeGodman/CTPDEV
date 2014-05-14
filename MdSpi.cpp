#include "MdSpi.h"
#include <iostream>
#include<string>
#include<cstring>
using namespace std;

// USER_API����
extern CThostFtdcMdApi* pUserApi;

// ���ò���
extern char FRONT_ADDR[];
extern TThostFtdcBrokerIDType BROKER_ID;
extern TThostFtdcInvestorIDType INVESTOR_ID;
extern TThostFtdcPasswordType PASSWORD;
extern char* ppInstrumentID[];
extern int iInstrumentID;

// ������
extern int iRequestID;

void CMdSpi::OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID,
		bool bIsLast)
{
	cerr << "--->>> " << __FUNCTION__ << endl;
	IsErrorRspInfo(pRspInfo);
}

void CMdSpi::OnFrontDisconnected(int nReason)
{
	cerr << "--->>> " << __FUNCTION__ << endl;
	cerr << "--->>> Reason = " << nReason << endl;
}

void CMdSpi::OnHeartBeatWarning(int nTimeLapse)
{
	cerr << "--->>> " << __FUNCTION__ << endl;
	cerr << "--->>> nTimerLapse = " << nTimeLapse << endl;
}

void CMdSpi::OnFrontConnected()
{
	cerr << "--->>> " << __FUNCTION__ << endl;
	///�û���¼����
	ReqUserLogin();
}

void CMdSpi::ReqUserLogin()
{
	CThostFtdcReqUserLoginField req;
	memset(&req, 0, sizeof(req));
	strcpy(req.BrokerID, BROKER_ID);
	strcpy(req.UserID, INVESTOR_ID);
	strcpy(req.Password, PASSWORD);
	int iResult = pUserApi->ReqUserLogin(&req, ++iRequestID);
	cerr << "--->>> send user login request: "
			<< ((iResult == 0) ? "successed" : "failed") << endl;
}

void CMdSpi::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin,
		CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	cerr << "--->>> " << __FUNCTION__ << endl;
	if (bIsLast && !IsErrorRspInfo(pRspInfo))
	{
		///��ȡ��ǰ������
		cerr << "--->>>get trading date = " << pUserApi->GetTradingDay()
				<< endl;
		// ����������
		SubscribeMarketData();
	}
}

void CMdSpi::SubscribeMarketData()
{
	int iResult = pUserApi->SubscribeMarketData(ppInstrumentID, iInstrumentID);
	cerr << "--->>> send hangqing dingyue: "
			<< ((iResult == 0) ? "successed" : "failed") << endl;
}

void CMdSpi::OnRspSubMarketData(
		CThostFtdcSpecificInstrumentField *pSpecificInstrument,
		CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	cerr << __FUNCTION__ << endl;
}

void CMdSpi::OnRspUnSubMarketData(
		CThostFtdcSpecificInstrumentField *pSpecificInstrument,
		CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	cerr << __FUNCTION__ << endl;
}

void CMdSpi::OnRtnDepthMarketData(
		CThostFtdcDepthMarketDataField *pDepthMarketData)
{
	//cerr << __FUNCTION__ << endl;
	cout << pDepthMarketData->InstrumentID << "   "
			<< pDepthMarketData->LastPrice << endl;
}

bool CMdSpi::IsErrorRspInfo(CThostFtdcRspInfoField *pRspInfo)
{
	// ���ErrorID != 0, ˵���յ��˴������Ӧ
	bool bResult = ((pRspInfo) && (pRspInfo->ErrorID != 0));
	if (bResult)
		cerr << "--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg="
				<< pRspInfo->ErrorMsg << endl;
	return bResult;
}
