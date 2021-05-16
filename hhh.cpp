// hhh.cpp: implementation of the hhh class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "灯.h"
#include "hhh.h"
#include "Windows.h"
#include<iostream>
using namespace std;

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define VID 0x04d2
#define PID 0x162e

typedef unsigned __int8 uint8_t;
typedef unsigned __int16 uint16_t;
typedef unsigned __int32 uint32_t;
typedef unsigned __int64 uint64_t;


extern "C" {

// This file is in the Windows DDK available from Microsoft.
#include "hidsdi.h"

#include <setupapi.h>

}


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

hhh::hhh()
{

}

hhh::~hhh()
{

}

BOOL hhh::find_device()
{
    BOOL isFind = false;
	GUID hid_guid;
	HDEVINFO device_info;
	BOOL isGetDeviceInterfaces = false;
	BOOL isGetDeviceInterfacesDetail = false;
	uint32_t deviceInde = 0;
	SP_DEVICE_INTERFACE_DATA device_interface_data;
	DWORD requiredSize = 0;
	PSP_DEVICE_INTERFACE_DETAIL_DATA p_device_interface_detail_data;
	BOOL isGetAttributes = false;
	HANDLE fileHandle;
	HIDD_ATTRIBUTES hid_attribute;

	HidD_GetHidGuid(&hid_guid);
	//show_guid(&hid_guid);

	device_info=SetupDiGetClassDevs(&hid_guid,NULL,NULL,DIGCF_INTERFACEDEVICE | DIGCF_PRESENT);
	do
	{ 
	device_interface_data.cbSize = sizeof(SP_DEVICE_INTERFACE_DATA);
	isGetDeviceInterfaces = SetupDiEnumDeviceInterfaces(device_info, NULL, &hid_guid,
	deviceInde,&device_interface_data);

	deviceInde++;
	if (isGetDeviceInterfaces) {
    cout << "GetDeviceInterfaces success" << endl;

	 /* 获取 RequiredSize*/
	SetupDiGetDeviceInterfaceDetail(
		device_info,
		&device_interface_data,
		NULL,
		0,
		&requiredSize,
		NULL);
	cout << "requiredSize:" << requiredSize<<endl;
	}
	p_device_interface_detail_data =(PSP_DEVICE_INTERFACE_DETAIL_DATA)malloc(requiredSize);
	p_device_interface_detail_data->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);
	isGetDeviceInterfacesDetail = SetupDiGetDeviceInterfaceDetail(
		device_info,
		&device_interface_data,
		p_device_interface_detail_data,
		requiredSize,
		NULL,
		NULL) ;
	if (isGetDeviceInterfacesDetail)
	{
		cout << "GetDeviceInterfacesDetail success" << endl;
	

	fileHandle = CreateFile(
		p_device_interface_detail_data->DevicePath,
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	if (fileHandle == INVALID_HANDLE_VALUE)
	{
		cout << "CreateFile ERROR" << endl;
	 }
	else
	{
		cout << "CreateFile success" << endl;
		isGetAttributes = HidD_GetAttributes(
			fileHandle,
			&hid_attribute);
		if (isGetAttributes) {
			cout << "PID:0x" << hex << hid_attribute.ProductID << endl;
			cout << "VID:0x" << hex << hid_attribute.VendorID << endl;
			if (hid_attribute.ProductID == USHORT(PID) && hid_attribute.VendorID== USHORT(VID))
			{
				//cout << "找到设备" << endl;
				userHidFileHandle = fileHandle;
				return true;
			}
		}


	 }

     }
	} while (isGetDeviceInterfaces);


return isFind;
}

void hhh::zongkaiguan()
{
    isReadFile = false;
	isWriteFile = false;
	numberOfBytesWrite = 66;
	writebuf[0] = 0;
	writebuf[62] = 0;
	writebuf[63] = 0;
	writebuf[64] = 0;
	if(!find_device()){
		AfxMessageBox("未找到设备");
		return;
	}

	if(!m_lightrun)
	{
		 for (uint8_t i = 2; i < 62; i++)
					writebuf[i] = 255;
			uint8_t n = 5;
			while (n--) {
				writebuf[1] = n;
				/*for (uint8_t i = 2; i < 62; i++)
					writebuf[i] = 255;*/

				isWriteFile = WriteFile(userHidFileHandle, writebuf, 65, &numberOfBytesWrite, NULL);
				Sleep(10);
			}
			m_lightrun=true;
			m_lightrunnei=true;
			m_lightrunwai=true;
			m_lightrunzhong=true;		
	}
	else if(m_lightrun){
	 uint8_t n = 5;
	 for (uint8_t i = 2; i < 62; i++)
				writebuf[i] = 0;
			while (n--) {
				writebuf[1] = n;
				/*for (uint8_t i = 2; i < 62; i++)
					writebuf[i] = 0;*/
				isWriteFile = WriteFile(userHidFileHandle, writebuf, 65, &numberOfBytesWrite, NULL);
				Sleep(10);
			}
			
			m_lightrun=false;
			m_lightrunnei=false;
			m_lightrunwai=false;
			m_lightrunzhong=false;
	}
}

void hhh::neikaiguan()
{
    isReadFile = false;
	isWriteFile = false;
	numberOfBytesWrite = 66;
	writebuf[0] = 0;
	writebuf[62] = 0;
	writebuf[63] = 0;
	writebuf[64] = 0;
	if(!find_device()){
		AfxMessageBox("未找到设备");
		return;
	}
	if(!m_lightrunnei)
	{
			uint8_t n = 5;
			for (uint8_t i = 2; i < 62; i+=6)
					writebuf[i]=255,writebuf[i+1] =255;
			while (n--) {
				writebuf[1] = n;
				/*for (uint8_t i = 2; i < 62; i+=6)
					writebuf[i]=255,writebuf[i+1] =255;*/

				isWriteFile = WriteFile(userHidFileHandle, writebuf, 65, &numberOfBytesWrite, NULL);
				Sleep(10);
			}
			m_lightrun=true;
			m_lightrunnei=true;		
	}
	else if(m_lightrunnei){
	 uint8_t n = 5;
	 for (uint8_t i = 2; i < 62; i+=6)
					writebuf[i] = 0,writebuf[i+1] = 0;
			while (n--) {
				writebuf[1] = n;
				/*for (uint8_t i = 2; i < 62; i+=6)
					writebuf[i] = 0,writebuf[i+1] = 0;*/

				isWriteFile = WriteFile(userHidFileHandle, writebuf, 65, &numberOfBytesWrite, NULL);
				Sleep(10);
			}
			m_lightrunnei=false;
			if(!m_lightrunnei&&!m_lightrunzhong&&!m_lightrunwai)
			m_lightrun=false;
	}
}

void hhh::zhongkaiguan()
{
	isReadFile = false;
	isWriteFile = false;
	numberOfBytesWrite = 66;
	writebuf[0] = 0;
	writebuf[62] = 0;
	writebuf[63] = 0;
	writebuf[64] = 0;
	if(!find_device()){
		AfxMessageBox("未找到设备");
		return;
	}
	if(!m_lightrunzhong)
	{
			uint8_t n = 5;
			for (uint8_t i = 4; i < 62; i+=6)
					writebuf[i]=255,writebuf[i+1] =255;
			while (n--) {
				writebuf[1] = n;
			   	/*for (uint8_t i = 4; i < 62; i+=6)
					writebuf[i]=255,writebuf[i+1] =255;*/

				isWriteFile = WriteFile(userHidFileHandle, writebuf, 65, &numberOfBytesWrite, NULL);
				Sleep(10);
			}
			
			m_lightrunzhong=true;
			m_lightrun=true;
	}
	else if(m_lightrunzhong){
	 uint8_t n = 5;
	 for (uint8_t i = 4; i < 62; i+=6)
					writebuf[i] = 0,writebuf[i+1] = 0;
			while (n--) {
				writebuf[1] = n;
				/*for (uint8_t i = 4; i < 62; i+=6)
					writebuf[i] = 0,writebuf[i+1] = 0;*/

				isWriteFile = WriteFile(userHidFileHandle, writebuf, 65, &numberOfBytesWrite, NULL);
				Sleep(10);
			}
			
			m_lightrunzhong=false;
			if(!m_lightrunnei&&!m_lightrunzhong&&!m_lightrunwai)
			m_lightrun=false;
	}

}

void hhh::waikaiguan()
{
    isReadFile = false;
	isWriteFile = false;
	numberOfBytesWrite = 66;
	writebuf[0] = 0;
	writebuf[62] = 0;
	writebuf[63] = 0;
	writebuf[64] = 0;
	if(!find_device()){
		AfxMessageBox("未找到设备");
		return;
	}
	if(!m_lightrunwai)
	{
			uint8_t n = 5;
			for (uint8_t i = 6; i < 62; i+=6)
					writebuf[i]=255,writebuf[i+1] =255;
			while (n--) {
				writebuf[1] = n;
				/*for (uint8_t i = 6; i < 62; i+=6)
					writebuf[i]=255,writebuf[i+1] =255;*/

				isWriteFile = WriteFile(userHidFileHandle, writebuf, 65, &numberOfBytesWrite, NULL);
				Sleep(10);
			}
			
			m_lightrunwai=true;	
			m_lightrun=true;
	}
	else if(m_lightrunwai){
	 uint8_t n = 5;
	 for (uint8_t i = 6; i < 62; i+=6)
		writebuf[i] = 0,writebuf[i+1] = 0;
			while (n--) {
				writebuf[1] = n;
				/*for (uint8_t i = 6; i < 62; i+=6)
					writebuf[i] = 0,writebuf[i+1] = 0;*/

				isWriteFile = WriteFile(userHidFileHandle, writebuf, 65, &numberOfBytesWrite, NULL);
				Sleep(10);
			}
			
		m_lightrunwai=false;
			if(!m_lightrunnei&&!m_lightrunzhong&&!m_lightrunwai)
			m_lightrun=false;
	}
}

void hhh::updatalight(int lightvalue,int type)
{
	
	uint8_t n = 5;
	
	if(type==1){/*
		if(m_lightjiaorun){
			uint8_t m = 0;
		while (n--) {
				writebuf[1] = n;
				for (uint8_t i = 2; i < 62; i+=2){
				if(lightflag[++m]!=0||lightflag[++m]!=0){
				if(lightvalue<=255)
					writebuf[i]=lightvalue,writebuf[i+1]=0;
				else
                    writebuf[i]=255,writebuf[i+1]=lightvalue-255;
				}
				}
				isWriteFile = WriteFile(userHidFileHandle, writebuf, 65, &numberOfBytesWrite, NULL);
				Sleep(10);
			}
		return;
		}*/
			while (n--) {
				writebuf[1] = n;
				for (uint8_t i = 2; i < 62; i+=2){
				if(writebuf[i]!=0||writebuf[i+1]!=0){
				if(lightvalue<=255)
					writebuf[i]=lightvalue,writebuf[i+1]=0;
				else
                    writebuf[i]=255,writebuf[i+1]=lightvalue-255;
				}
				}
				isWriteFile = WriteFile(userHidFileHandle, writebuf, 65, &numberOfBytesWrite, NULL);
				Sleep(10);
			}
	}
	else if(type==2){/*
		if(m_lightjiaorun){
			uint8_t m = 0;
		while (n--) {
				writebuf[1] = n;
				for (uint8_t i = 2; i < 62; i+=2){
				if(lightflag[++m]!=0||lightflag[++m]!=0){
				if(lightvalue<=255)
					writebuf[i]=lightvalue,writebuf[i+1]=0;
				else
                    writebuf[i]=255,writebuf[i+1]=lightvalue-255;
				}
				}
				isWriteFile = WriteFile(userHidFileHandle, writebuf, 65, &numberOfBytesWrite, NULL);
				Sleep(10);
			}
		return;
		}*/
			while (n--) {
				writebuf[1] = n;
				for (uint8_t i = 2; i < 62; i+=4){
				if(writebuf[i]!=0||writebuf[i+1]!=0){
				if(lightvalue<=255)
					writebuf[i]=lightvalue,writebuf[i+1]=0;
				else
                    writebuf[i]=255,writebuf[i+1]=lightvalue-255;
				}
				}
				isWriteFile = WriteFile(userHidFileHandle, writebuf, 65, &numberOfBytesWrite, NULL);
				Sleep(15);
			}
	}
    else if(type==3){/*
		if(m_lightjiaorun){
			uint8_t m = 0;
		while (n--) {
				writebuf[1] = n;
				for (uint8_t i = 2; i < 62; i+=2){
				if(lightflag[++m]!=0||lightflag[++m]!=0){
				if(lightvalue<=255)
					writebuf[i]=lightvalue,writebuf[i+1]=0;
				else
                    writebuf[i]=255,writebuf[i+1]=lightvalue-255;
				}
				}
				isWriteFile = WriteFile(userHidFileHandle, writebuf, 65, &numberOfBytesWrite, NULL);
				Sleep(10);
			}
		return;
		}*/
			while (n--) {
				writebuf[1] = n;
				for (uint8_t i = 4; i < 62; i+=4){
				if(writebuf[i]!=0||writebuf[i+1]!=0){
				if(lightvalue<=255)
					writebuf[i]=lightvalue,writebuf[i+1]=0;
				else
                    writebuf[i]=255,writebuf[i+1]=lightvalue-255;
				}
				}
				isWriteFile = WriteFile(userHidFileHandle, writebuf, 65, &numberOfBytesWrite, NULL);
				Sleep(10);
				
		}
	}
}

void hhh::updatejiaodu(int start, int end,int lv)
{
	int num=40;
	if(lv==0){
    AfxMessageBox("未设置亮度");
	return;
	}
	if(start==end){
	m_lightrun=false;
	m_lightjiaorun=false;
    uint8_t h = 5;
	while(h--){
    writebuf[1] = h;
		for (uint8_t i = 2; i < 62; i+=2){
        writebuf[i]=0,writebuf[i+1]=0;
		}
		isWriteFile = WriteFile(userHidFileHandle, writebuf, 65, &numberOfBytesWrite, NULL);
		Sleep(10);	
	}
     return;
	}
		
    if(start>end)
		swap(start,end);

	int x=start/9,y=end/9;
	m_lightjiaorun=true;
	uint8_t n = 5;
	uint8_t m = 0;
	while(n--){
    writebuf[1] = n;
		for (uint8_t i = 61; i > 1; i-=6){
			if(num<=y&&num>=x){
		writebuf[i]=lv/2,writebuf[i-1]=lv/2;
        writebuf[i-2]=lv/2,writebuf[i-3]=lv/2;
		writebuf[i-4]=lv/2,writebuf[i-5]=lv/2;
		}
		else{
        writebuf[i]=0,writebuf[i-1]=0;
        writebuf[i-2]=0,writebuf[i-3]=0;
		writebuf[i-4]=0,writebuf[i-5]=0;
	}
		num--;
		
	}
		isWriteFile = WriteFile(userHidFileHandle, writebuf, 65, &numberOfBytesWrite, NULL);
		Sleep(10);
		//for(uint8_t j=2;j<62;++j)
			//lightflag[++m]=writebuf[j];
	}
	
}

void hhh::guandeng()
{
    isReadFile = false;
	isWriteFile = false;
	numberOfBytesWrite = 66;
	writebuf[0] = 0;
	writebuf[62] = 0;
	writebuf[63] = 0;
	writebuf[64] = 0;
	for (uint8_t i = 2; i < 62; i++)
		writebuf[i] = 0;
			uint8_t n = 5;
			while (n--) {
				writebuf[1] = n;
				/*for (uint8_t i = 2; i < 62; i++)
					writebuf[i] = 0;*/

				isWriteFile = WriteFile(userHidFileHandle, writebuf, 65, &numberOfBytesWrite, NULL);
				Sleep(10);
		}		
}
