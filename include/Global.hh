// Global.hh --- 
// 
// Description: 
// Author: Hongyi Wu(吴鸿毅)
// Email: wuhongyi@qq.com 
// Created: 五 11月 25 21:05:40 2016 (+0800)
// Last-Updated: 日 12月  4 12:23:47 2016 (+0800)
//           By: Hongyi Wu(吴鸿毅)
//     Update #: 21
// URL: http://wuhongyi.cn 

#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include <CAENDigitizer.h>
#include <CAENDigitizerType.h>

#include <cmath>
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#define MAX_CHANNEL 16

// Set a bit in a 32-bit unsigned integer.
unsigned int SetBit_32(unsigned short bit,unsigned int value);//将value第bit位设为1

// Clear a bit in a 32-bit unsigned integer.
unsigned int ClrBit_32(unsigned short bit,unsigned int value);//将value第bit位设为0

// Test a bit in a 32-bit unsigned integer.
unsigned int TstBit_32(unsigned short bit,unsigned int value );//获得value第bit位数值

// 十进制转二进制
// d 十进制数
// bstr 二进制字符串
// return 出错返回-1，成功返回字符串长度
int Decimal2Binary(uint32_t d, char *bstr);


typedef struct {
  CAEN_DGTZ_BoardInfo_t* boardInfo;
  
  CAEN_DGTZ_ConnectionType linkType;
  int linkNum;
  int conetNode;
  int baseAddress;
  int boardHandle;
  
} Digitizer;


// typedef struct {
//   int M;
//   int m;
//   int k;
//   int ftd;
//   int a;
//   int b;
//   int thr;
//   int nsbl;
//   int nspk;
//   int pkho;
//   int tpet;
//   int otrej;
//   int trgho;
//   int twwdt;
//   int trgwin;
//   float dgain;
// } DppParams;



enum ButtonIDs
  {
    CONNECTBUTTON,
    DELETEBUTTON,
    COMPLETEBUTTON,
    ADJUSTPARBUTTON,
    STARTSTOPBUTTON,
    WRITEDATABUTTON,
    ONLINECHECKBUTTON,
    PRINTREGISTERSBUTTON
  };

enum NumberEntryIDs
  {
    RUNNUMBER,
    RECORDLENGTH
  };


#endif /* _GLOBAL_H_ */

// 
// Global.hh ends here
