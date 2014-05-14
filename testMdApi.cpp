// testTraderApi.cpp : 定义控制台应用程序的入口点。
//

#include "./api/ThostFtdcMdApi.h"
#include "MdSpi.h"
#include<iostream>
using namespace std;
// UserApi对象
CThostFtdcMdApi* pUserApi;

// 配置参数
char FRONT_ADDR[] = "tcp://ctpmn1-front1.citicsf.com:51213";		// 前置地址
TThostFtdcBrokerIDType BROKER_ID = "1017";				// 经纪公司代码
TThostFtdcInvestorIDType INVESTOR_ID = "123456";			// 投资者代码
TThostFtdcPasswordType PASSWORD = "888888";			// 用户密码
char *ppInstrumentID[] =
{ "IF1406" , "IF1405"};			// 行情订阅列表
int iInstrumentID = 2;									// 行情订阅数量

// 请求编号
int iRequestID = 0;

int main()
{
	// 初始化UserApi
	pUserApi = CThostFtdcMdApi::CreateFtdcMdApi();			// 创建UserApi
	CThostFtdcMdSpi* pUserSpi = new CMdSpi();
	pUserApi->RegisterSpi(pUserSpi);						// 注册事件类
	pUserApi->RegisterFront(FRONT_ADDR);					// connect
	pUserApi->Init();

	pUserApi->Join();
//	pUserApi->Release();
	return 0;
}
