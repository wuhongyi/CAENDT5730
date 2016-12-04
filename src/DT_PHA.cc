// DT_PHA.cc --- 
// 
// Description: 
// Author: Hongyi Wu(吴鸿毅)
// Email: wuhongyi@qq.com 
// Created: 六 12月  3 09:58:01 2016 (+0800)
// Last-Updated: 六 12月  3 17:48:21 2016 (+0800)
//           By: Hongyi Wu(吴鸿毅)
//     Update #: 3
// URL: http://wuhongyi.cn 

#include "DT_PHA.hh"

#include <cstdlib>
#include <cstdio>
#include <iostream>
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DT_PHA::DT_PHA(Digitizer* dig,const char *name)
  : Board(dig,name)
{

}

DT_PHA::~DT_PHA()
{
  if(readoutBuffer != NULL)
    {
      CAEN_DGTZ_FreeReadoutBuffer(&readoutBuffer);
      readoutBuffer = NULL;
      CAEN_DGTZ_FreeDPPEvents(handle, (void **)dpppsdevents);
      CAEN_DGTZ_FreeDPPWaveforms(handle,dpppsdwaveforms);
    }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int DT_PHA::ProgramDigitizer()
{
  printf("Program DPP-PHA\n");
  int ret = 0;
  
  // ret |= CAEN_DGTZ_WriteRegister(handle, 0x811C, 0xC003C);// serve per mandare SW trg individuali e per abilitare il ts reset
  // ret |= CAEN_DGTZ_WriteRegister(handle, 0x8000, 0x01000110);// Channel Control Reg (indiv trg, seq readout)
  // ret |= CAEN_DGTZ_WriteRegister(handle, 0x8004, 0x00000004);// Enable indiv trgin

  
  ret |= CAEN_DGTZ_SetDPPAcquisitionMode(handle, par_dppacqmode, par_dppsaveparam);
  
  ret |= CAEN_DGTZ_SetAcquisitionMode(handle, par_acqmode);
  
  ret |= CAEN_DGTZ_SetRecordLength(handle, par_recordlength);
  ret |= CAEN_DGTZ_GetRecordLength(handle, &par_recordlength,0);//总是拿ch=0
  
  ret |= CAEN_DGTZ_SetIOLevel(handle, par_iolevel);

  ret |= CAEN_DGTZ_SetExtTriggerInputMode(handle, par_exttriggerinputmode);

  ret |= CAEN_DGTZ_SetChannelEnableMask(handle, par_enablemask);
  
  ret |= CAEN_DGTZ_SetDPPEventAggregation(handle, par_dppeventaggregationthreshold, par_dppeventaggregationmaxsize);

  ret |= CAEN_DGTZ_SetRunSynchronizationMode(handle, par_runsyncmode);

  
  // ret |= CAEN_DGTZ_SetDPPParameters(handle, 0/*channel*/, &dpppsdParams);

  if ((FamilyCode == CAEN_DGTZ_XX740_FAMILY_CODE) || (FamilyCode == CAEN_DGTZ_XX742_FAMILY_CODE))
    {
      // x740 x742

    }
  else
    {
      if (FamilyCode != CAEN_DGTZ_XX730_FAMILY_CODE && FamilyCode != CAEN_DGTZ_XX725_FAMILY_CODE)
	{
		
	  ret |= CAEN_DGTZ_SetChannelSelfTrigger(handle, par_channelselftrigger, par_enablemask);
	}

      if (FamilyCode == CAEN_DGTZ_XX730_FAMILY_CODE || FamilyCode == CAEN_DGTZ_XX725_FAMILY_CODE)
	{
	  // x725 x730
	  ret |= CAEN_DGTZ_SetChannelSelfTrigger(handle, par_channelselftrigger, par_enablemask);
	}
	      
    }

  // if(ret) printf("-- 1 --");

  if(ret) printf("Warning: errors found while programming the digitizer. ");
  return ret;
}

int DT_PHA::AllocateMemory()
{
  int ret = 0;

  if(readoutBuffer != NULL)
    {
      ret = CAEN_DGTZ_FreeReadoutBuffer(&readoutBuffer);
      readoutBuffer = NULL;
      ret = CAEN_DGTZ_FreeDPPEvents(handle, (void **)dpppsdevents);
      ret = CAEN_DGTZ_FreeDPPWaveforms(handle,dpppsdwaveforms);
    }

 
  ret = CAEN_DGTZ_MallocReadoutBuffer(handle, &readoutBuffer, &bufferSize); // WARNING: This malloc must be done after the digitizer programming
  // std::cout<<"BufferSize: "<<bufferSize<<"  "<<sizeof(readoutBuffer)<<std::endl;
  ret |= CAEN_DGTZ_MallocDPPEvents(handle, (void **)dpppsdevents, &size); 
  // std::cout<<"EventSize: "<<size<<"  "<<sizeof(dpppsdevents)<<std::endl;
  ret |= CAEN_DGTZ_MallocDPPWaveforms(handle, (void **)&dpppsdwaveforms, &size);// Allocate memory for the waveforms 
  // std::cout<<"Waveforms: "<<size<<"  "<<sizeof(dpppsdwaveforms)<<std::endl;
  
  if(ret) printf("Warning: errors malloc space the digitizer. ");
  
  return ret;
}


int DT_PHA::GetEvent()
{
  return CAEN_DGTZ_GetDPPEvents(handle, readoutBuffer, bufferSize, (void**)dppphaevents, NumEvents);
   
}


int DT_PHA::GetWaveform()
{
  for(int ch = 0; ch < Nch; ch++)
    {
      if (!(par_enablemask & (1<<ch)))
	continue;

      for(int ev = 0; ev < NumEvents[ch]; ev++)
	{
	  // Time Tag
	  // dpppsdevents[ch][ev].TimeTag;

	  // Energy
	  
	  

	}// loop on events
    }// loop on channels
}

// 
// DT_PHA.cc ends here