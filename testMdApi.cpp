// testTraderApi.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "./api/ThostFtdcMdApi.h"
#include "MdSpi.h"
#include<iostream>
using namespace std;
// UserApi����
CThostFtdcMdApi* pUserApi;

// ���ò���
char FRONT_ADDR[] = "tcp://ctpmn1-front1.citicsf.com:51213";		// ǰ�õ�ַ
TThostFtdcBrokerIDType BROKER_ID = "1017";				// ���͹�˾����
TThostFtdcInvestorIDType INVESTOR_ID = "123456";			// Ͷ���ߴ���
TThostFtdcPasswordType PASSWORD = "888888";			// �û�����
char *ppInstrumentID[] =
{ "IF1406" , "IF1405"};			// ���鶩���б�
int iInstrumentID = 2;									// ���鶩������

// ������
int iRequestID = 0;

int main()
{
	// ��ʼ��UserApi
	pUserApi = CThostFtdcMdApi::CreateFtdcMdApi();			// ����UserApi
	CThostFtdcMdSpi* pUserSpi = new CMdSpi();
	pUserApi->RegisterSpi(pUserSpi);						// ע���¼���
	pUserApi->RegisterFront(FRONT_ADDR);					// connect
	pUserApi->Init();

	pUserApi->Join();
//	pUserApi->Release();
	return 0;
}
