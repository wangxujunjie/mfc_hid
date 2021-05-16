// hhh.h: interface for the hhh class.
//
//////////////////////////////////////////////////////////////////////
typedef unsigned __int8 uint8_t;
typedef unsigned __int16 uint16_t;
typedef unsigned __int32 uint32_t;
typedef unsigned __int64 uint64_t;

#if !defined(AFX_HHH_H__3486B372_5117_46EF_910D_44CACC96F02B__INCLUDED_)
#define AFX_HHH_H__3486B372_5117_46EF_910D_44CACC96F02B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class hhh  
{
public:
	BOOL m_lightjiaorun;
	void guandeng();
	void updatejiaodu(int start,int end,int value);
	void updatalight(int lightvalue,int type);
	BOOL m_lightrunwai;
	BOOL m_lightrunzhong;
	BOOL m_lightrunnei;
	void waikaiguan();
	void zhongkaiguan();
	BOOL m_lightrun;
	void neikaiguan();
	DWORD numberOfBytesWrite;
	BOOL isWriteFile;
	BOOL isReadFile;
	uint8_t writebuf[65];
	uint8_t lightflag[241];
	void zongkaiguan();
	HANDLE userHidFileHandle;
	BOOL find_device();
	hhh();
	virtual ~hhh();

};

#endif // !defined(AFX_HHH_H__3486B372_5117_46EF_910D_44CACC96F02B__INCLUDED_)
