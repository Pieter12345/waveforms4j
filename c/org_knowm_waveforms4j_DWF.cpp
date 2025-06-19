#include <jni.h>
#include "org_knowm_waveforms4j_DWF.h"
#include "dwf.h"
#include "stdint.h"

HDWF hdwf;

#define byte uint8_t

/************************************************************
*                                                           *
*                      Device                               *
*                                                           *
*************************************************************/


JNIEXPORT jboolean JNICALL Java_org_knowm_waveforms4j_DWF_FDwfDeviceOpen
  (JNIEnv * env, jobject obj){
  

    //printf("Open automatically the first available device\n");
    if(!FDwfDeviceOpen(-1, &hdwf)) {
        char szError[512] = {0};
        FDwfGetLastErrorMsg(szError);
        printf("Device open failed: \n\t%s", szError);
        return 0;
    }
    return 1;
  }
  
JNIEXPORT jboolean JNICALL Java_org_knowm_waveforms4j_DWF_FDwfDeviceCloseAll
  (JNIEnv * env, jobject obj){
  
    return FDwfDeviceCloseAll();
  }

JNIEXPORT jstring JNICALL Java_org_knowm_waveforms4j_DWF_FDwfGetLastErrorMsg
  (JNIEnv * env, jobject obj){

    char szError[512] = {0};
    FDwfGetLastErrorMsg(szError);
    printf("Error Message: \n\t%s", szError);
    return (*env).NewStringUTF(szError);
  }

JNIEXPORT jboolean JNICALL Java_org_knowm_waveforms4j_DWF_FDwfDeviceAutoConfigureSet
  (JNIEnv * env, jobject obj, jboolean autoConfigure){

    return FDwfDeviceAutoConfigureSet(hdwf, autoConfigure);
  }

/************************************************************
*                                                           *
*                      Digital I/O                          *
*                                                           *
*************************************************************/


JNIEXPORT jboolean JNICALL Java_org_knowm_waveforms4j_DWF_FDwfDigitalIOReset
  (JNIEnv * env, jobject obj){
  
    return FDwfDigitalIOReset(hdwf);
  }

JNIEXPORT jboolean JNICALL Java_org_knowm_waveforms4j_DWF_FDwfDigitalIOStatus
  (JNIEnv * env, jobject obj){
  
    return FDwfDigitalIOStatus(hdwf);
  }  
  
JNIEXPORT jint JNICALL Java_org_knowm_waveforms4j_DWF_FDwfDigitalIOInputStatus
  (JNIEnv * env, jobject obj){
  
    unsigned int ioStates;
  
    FDwfDigitalIOInputStatus(hdwf, &ioStates);
    
    return ioStates;
  }
  
JNIEXPORT jboolean JNICALL Java_org_knowm_waveforms4j_DWF_FDwfDigitalIOOutputEnableSet
  (JNIEnv * env, jobject obj, jint outputEnableMask){
  
    return FDwfDigitalIOOutputEnableSet(hdwf, outputEnableMask);
  }
  
JNIEXPORT jboolean JNICALL Java_org_knowm_waveforms4j_DWF_FDwfDigitalIOOutputSet
  (JNIEnv * env, jobject obj, jint outputSetMask){
  
    return FDwfDigitalIOOutputSet(hdwf, outputSetMask);
  }

JNIEXPORT jboolean JNICALL Java_org_knowm_waveforms4j_DWF_FDwfDigitalIOConfigure
  (JNIEnv * env, jobject obj){

    return FDwfDigitalIOConfigure(hdwf);
  }

/************************************************************
*                                                           *
*                  Digital Pattern Out                      *
*                                                           *
*************************************************************/


JNIEXPORT jdouble JNICALL Java_org_knowm_waveforms4j_DWF_FDwfDigitalOutInternalClockInfo
  (JNIEnv * env, jobject obj){
  
    double hzSys;
    
    FDwfDigitalOutInternalClockInfo(hdwf, &hzSys);
    printf("hzSys\t%lf\n", hzSys);
    
    return hzSys;
  }

JNIEXPORT jboolean JNICALL Java_org_knowm_waveforms4j_DWF_FDwfDigitalOutEnableSet
  (JNIEnv * env, jobject obj, jint idxChannel, jboolean enable){
  
    return FDwfDigitalOutEnableSet(hdwf, idxChannel, enable);
  }

JNIEXPORT jboolean JNICALL Java_org_knowm_waveforms4j_DWF_FDwfDigitalOutTypeSet
  (JNIEnv * env, jobject obj, jint idxChannel, jint dwfDigitalOutType) {
    return FDwfDigitalOutTypeSet(hdwf, idxChannel, dwfDigitalOutType);
  }

JNIEXPORT jboolean JNICALL Java_org_knowm_waveforms4j_DWF_FDwfDigitalOutDividerSet
  (JNIEnv * env, jobject obj, jint idxChannel, jint divider){
    return FDwfDigitalOutDividerSet(hdwf, idxChannel, divider);
  }

JNIEXPORT jboolean JNICALL Java_org_knowm_waveforms4j_DWF_FDwfDigitalOutCounterSet
  (JNIEnv * env, jobject obj, jint idxChannel, jint low, jint high){
  
    return FDwfDigitalOutCounterSet(hdwf, idxChannel, low, high);
  }
  
JNIEXPORT jboolean JNICALL Java_org_knowm_waveforms4j_DWF_FDwfDigitalOutCounterInitSet
  (JNIEnv * env, jobject obj, jint idxChannel, jboolean high, jint dividerValue){
  
  return FDwfDigitalOutCounterInitSet(hdwf, idxChannel, high, dividerValue);
  }

JNIEXPORT jboolean JNICALL Java_org_knowm_waveforms4j_DWF_FDwfDigitalOutConfigure
  (JNIEnv * env, jobject obj, jboolean start){
  
    return FDwfDigitalOutConfigure(hdwf, start);
  }

JNIEXPORT jboolean JNICALL Java_org_knowm_waveforms4j_DWF_FDwfDigitalOutDataSet
  (JNIEnv * env, jobject obj, jint idxChannel, jbyteArray rgdData, jint size) {

    jsize len = env->GetArrayLength(rgdData);
    jbyte *body = env->GetByteArrayElements(rgdData, 0);
    byte *input = new byte[len];
    int i = 0;
    for (i = 0; i < len; i++) {
      input[i] = body[i];
    }
    return FDwfDigitalOutDataSet(hdwf, idxChannel, input, size);
  }

JNIEXPORT jboolean JNICALL Java_org_knowm_waveforms4j_DWF_FDwfDigitalOutRunSet
  (JNIEnv * env, jobject obj, jdouble secRun) {
    return FDwfDigitalOutRunSet(hdwf, secRun);
  }

JNIEXPORT jboolean JNICALL Java_org_knowm_waveforms4j_DWF_FDwfDigitalOutRepeatSet
  (JNIEnv * env, jobject obj, jint cRepeat) {
    return FDwfDigitalOutRepeatSet(hdwf, cRepeat);
  }

JNIEXPORT jbyte JNICALL Java_org_knowm_waveforms4j_DWF_FDwfDigitalOutStatus
  (JNIEnv * env, jobject obj) {
    DwfState dwfState;
    FDwfDigitalOutStatus(hdwf, &dwfState);
    return dwfState;
  }

JNIEXPORT jboolean JNICALL Java_org_knowm_waveforms4j_DWF_FDwfDigitalOutReset
  (JNIEnv * env, jobject obj){
  
    return FDwfDigitalOutReset(hdwf);
  }


/************************************************************
*                                                           *
*                      Digital In                           *
*                                                           *
*************************************************************/

JNIEXPORT jboolean JNICALL Java_org_knowm_waveforms4j_DWF_FDwfDigitalInReset
  (JNIEnv * env, jobject obj) {
    return FDwfDigitalInReset(hdwf);
  }

JNIEXPORT jboolean JNICALL Java_org_knowm_waveforms4j_DWF_FDwfDigitalInConfigure
  (JNIEnv * env, jobject obj, jboolean fReconfigure, jboolean fStart) {
    return FDwfDigitalInConfigure(hdwf, fReconfigure, fStart);
  }

JNIEXPORT jbyte JNICALL Java_org_knowm_waveforms4j_DWF_FDwfDigitalInStatus
  (JNIEnv * env, jobject obj, jboolean fReadData) {
    byte sts;
    FDwfDigitalInStatus(hdwf, fReadData, &sts);
    return sts;
  }

JNIEXPORT jbyteArray JNICALL Java_org_knowm_waveforms4j_DWF_FDwfDigitalInStatusData
  (JNIEnv * env, jobject obj, jint countOfDataBytes) {
    jbyte* rgdSamples = new jbyte[countOfDataBytes];
    FDwfDigitalInStatusData(hdwf, rgdSamples, countOfDataBytes);

    jbyteArray jvalues = env->NewByteArray(countOfDataBytes);
    env->SetByteArrayRegion(jvalues, 0, countOfDataBytes, rgdSamples); 
    return jvalues;
  }

JNIEXPORT jdouble JNICALL Java_org_knowm_waveforms4j_DWF_FDwfDigitalInInternalClockInfo
  (JNIEnv * env, jobject obj) {
    double phzFreq;
    FDwfDigitalInInternalClockInfo(hdwf, &phzFreq);
    return phzFreq;
  }

JNIEXPORT jint JNICALL Java_org_knowm_waveforms4j_DWF_FDwfDigitalInDividerInfo
  (JNIEnv * env, jobject obj) {
    unsigned int pdivMax;
    FDwfDigitalInDividerInfo(hdwf, &pdivMax);
    return pdivMax;
  }

JNIEXPORT jboolean JNICALL Java_org_knowm_waveforms4j_DWF_FDwfDigitalInDividerSet
  (JNIEnv * env, jobject obj, jint div) {
    return FDwfDigitalInDividerSet(hdwf, div);
  }

JNIEXPORT jboolean JNICALL Java_org_knowm_waveforms4j_DWF_FDwfDigitalInSampleFormatSet
  (JNIEnv * env, jobject obj, jint nBits) {
    return FDwfDigitalInSampleFormatSet(hdwf, nBits);
  }

JNIEXPORT jboolean JNICALL Java_org_knowm_waveforms4j_DWF_FDwfDigitalInBufferSizeSet
  (JNIEnv * env, jobject obj, jint nSize) {
    return FDwfDigitalInBufferSizeSet(hdwf, nSize);
  }

JNIEXPORT jboolean JNICALL Java_org_knowm_waveforms4j_DWF_FDwfDigitalInTriggerSourceSet
  (JNIEnv * env, jobject obj, jbyte trigsrc) {
    return FDwfDigitalInTriggerSourceSet(hdwf, trigsrc);
  }

JNIEXPORT jboolean JNICALL Java_org_knowm_waveforms4j_DWF_FDwfDigitalInTriggerPositionSet
  (JNIEnv * env, jobject obj, jint cSamplesAfterTrigger) {
    return FDwfDigitalInTriggerPositionSet(hdwf, cSamplesAfterTrigger);
  }

JNIEXPORT jboolean JNICALL Java_org_knowm_waveforms4j_DWF_FDwfDigitalInAcquisitionModeSet
  (JNIEnv * env, jobject obj, jint acqmode) {
    return FDwfDigitalInAcquisitionModeSet(hdwf, acqmode);
  }
JNIEXPORT jboolean JNICALL Java_org_knowm_waveforms4j_DWF_FDwfDigitalInTriggerSet
  (JNIEnv * env, jobject obj, jint fsLevelLow, jint fsLevelHigh, jint fsEdgeRise, jint fsEdgeFall) {
    return FDwfDigitalInTriggerSet(hdwf, fsLevelLow, fsLevelHigh, fsEdgeRise, fsEdgeFall);
  }

JNIEXPORT jboolean JNICALL Java_org_knowm_waveforms4j_DWF_FDwfDigitalInTriggerResetSet
  (JNIEnv * env, jobject obj, jint fsLevelLow, jint fsLevelHigh, jint fsEdgeRise, jint fsEdgeFall) {
    return FDwfDigitalInTriggerResetSet(hdwf, fsLevelLow, fsLevelHigh, fsEdgeRise, fsEdgeFall);
  }

JNIEXPORT jboolean JNICALL Java_org_knowm_waveforms4j_DWF_FDwfDigitalInTriggerCountSet
  (JNIEnv * env, jobject obj, jint cCount, jint fRestart) {
    return FDwfDigitalInTriggerCountSet(hdwf, cCount, fRestart);
  }

JNIEXPORT jboolean JNICALL Java_org_knowm_waveforms4j_DWF_FDwfDigitalInTriggerLengthSet
  (JNIEnv * env, jobject obj, jdouble secMin, jdouble secMax, jint idxSync) {
    return FDwfDigitalInTriggerLengthSet(hdwf, secMin, secMax, idxSync);
  }

JNIEXPORT jboolean JNICALL Java_org_knowm_waveforms4j_DWF_FDwfDigitalInTriggerMatchSet
  (JNIEnv * env, jobject obj, jint iPin, jint fsMask, jint fsValue, jint cBitStuffing) {
    return FDwfDigitalInTriggerMatchSet(hdwf, iPin, fsMask, fsValue, cBitStuffing);
  }

/************************************************************
*                                                           *
*                           I2C                             *
*                                                           *
*************************************************************/

JNIEXPORT jboolean JNICALL Java_org_knowm_waveforms4j_DWF_FDwfDigitalI2cReset
  (JNIEnv * env, jobject obj) {
    return FDwfDigitalI2cReset(hdwf);
  }

JNIEXPORT jint JNICALL Java_org_knowm_waveforms4j_DWF_FDwfDigitalI2cClear
  (JNIEnv *, jobject) {
    int pfFree = 0;
    FDwfDigitalI2cClear(hdwf, &pfFree);
    return pfFree;
  }

JNIEXPORT jboolean JNICALL Java_org_knowm_waveforms4j_DWF_FDwfDigitalI2cRateSet
  (JNIEnv * env, jobject obj, jdouble hz) {
    return FDwfDigitalI2cRateSet(hdwf, hz);
  }

JNIEXPORT jboolean JNICALL Java_org_knowm_waveforms4j_DWF_FDwfDigitalI2cSclSet
  (JNIEnv * env, jobject obj, jint idxChannel) {
    return FDwfDigitalI2cSclSet(hdwf, idxChannel);
  }

JNIEXPORT jboolean JNICALL Java_org_knowm_waveforms4j_DWF_FDwfDigitalI2cSdaSet
  (JNIEnv * env, jobject obj, jint idxChannel) {
    return FDwfDigitalI2cSdaSet(hdwf, idxChannel);
  }

JNIEXPORT jint JNICALL Java_org_knowm_waveforms4j_DWF_FDwfDigitalI2cWriteRead
  (JNIEnv * env, jobject obj, jbyte adr8bits, jbyteArray rgbTx, jint cTx, jbyteArray rgbRx, jint cRx) {
    int pNak = -1;
    jbyte* rgbTxBody = env->GetByteArrayElements(rgbTx, 0);
    jbyte* rgbRxBody = env->GetByteArrayElements(rgbRx, 0);
    FDwfDigitalI2cWriteRead(hdwf, adr8bits, (unsigned char*) rgbTxBody, cTx, (unsigned char*) rgbRxBody, cRx, &pNak);
	env->ReleaseByteArrayElements(rgbRx, rgbRxBody, 0);
    return pNak;
  }

JNIEXPORT jint JNICALL Java_org_knowm_waveforms4j_DWF_FDwfDigitalI2cRead
  (JNIEnv * env, jobject obj, jbyte adr8bits, jbyteArray rgbRx, jint cRx) {
    int pNak = -1;
    jbyte* rgbRxBody = env->GetByteArrayElements(rgbRx, 0);
    FDwfDigitalI2cRead(hdwf, adr8bits, (unsigned char*) rgbRxBody, cRx, &pNak);
	env->ReleaseByteArrayElements(rgbRx, rgbRxBody, 0);
    return pNak;
  }

JNIEXPORT jint JNICALL Java_org_knowm_waveforms4j_DWF_FDwfDigitalI2cWrite
  (JNIEnv * env, jobject obj, jbyte adr8bits, jbyteArray rgbTx, jint cTx) {
    int pNak = -1;
    jbyte* rgbTxBody = env->GetByteArrayElements(rgbTx, 0);
    FDwfDigitalI2cWrite(hdwf, adr8bits, (unsigned char*) rgbTxBody, cTx, &pNak);
    return pNak;
  }

/************************************************************
*                                                           *
*                      Analog In                            *
*                                                           *
*************************************************************/

JNIEXPORT jint JNICALL Java_org_knowm_waveforms4j_DWF_FDwfAnalogOutTriggerSourceInfo
  (JNIEnv * env, jobject obj, jint idxChannel){
  
    int pfstrigsrc;  
  
    FDwfAnalogOutTriggerSourceInfo(hdwf, idxChannel, &pfstrigsrc);
  
    return pfstrigsrc;
  }

JNIEXPORT jboolean JNICALL Java_org_knowm_waveforms4j_DWF_FDwfAnalogInChannelEnableSet
  (JNIEnv * env, jobject obj, jint idxChannel, jboolean enable){
  
    return FDwfAnalogInChannelEnableSet(hdwf, idxChannel, enable);
  }
  
JNIEXPORT jboolean JNICALL Java_org_knowm_waveforms4j_DWF_FDwfAnalogInChannelRangeSet
  (JNIEnv * env, jobject obj, jint idxChannel, jdouble voltsRange){
  
    return FDwfAnalogInChannelRangeSet(hdwf, idxChannel, voltsRange);
  }

JNIEXPORT jboolean JNICALL Java_org_knowm_waveforms4j_DWF_FDwfAnalogInFrequencySet
  (JNIEnv * env, jobject obj, jdouble hzFrequency){
  
    return FDwfAnalogInFrequencySet(hdwf, hzFrequency);
  }
  
JNIEXPORT jint JNICALL Java_org_knowm_waveforms4j_DWF_FDwfAnalogInBufferSizeMax
  (JNIEnv * env, jobject obj){
  
    int cSamples;
    FDwfAnalogInBufferSizeInfo(hdwf, NULL, &cSamples);  
    return cSamples;
  }
  
JNIEXPORT jboolean JNICALL Java_org_knowm_waveforms4j_DWF_FDwfAnalogInBufferSizeSet
  (JNIEnv * env, jobject obj, jint size){
  
    return FDwfAnalogInBufferSizeSet(hdwf, size);  
  }  

JNIEXPORT jbyte JNICALL Java_org_knowm_waveforms4j_DWF_FDwfAnalogInStatus
  (JNIEnv * env, jobject obj, jboolean readData){

    DwfState dwfState;
    FDwfAnalogInStatus(hdwf, readData, &dwfState);
    return dwfState;
  }
  
JNIEXPORT jint JNICALL Java_org_knowm_waveforms4j_DWF_FDwfAnalogInStatusSamplesValid
  (JNIEnv * env, jobject obj){
  
    int pcSamplesValid;  
  
    FDwfAnalogInStatusSamplesValid(hdwf, &pcSamplesValid);
  
    return pcSamplesValid;
  }




JNIEXPORT jdoubleArray JNICALL Java_org_knowm_waveforms4j_DWF_FDwfAnalogInTriggerPositionInfo
  (JNIEnv * env, jobject obj){

  double psecMin;
  double psecMax;
  double pnSteps;

  FDwfAnalogInTriggerPositionInfo(hdwf, &psecMin, &psecMax, &pnSteps);

  jdoubleArray jvalues = env->NewDoubleArray(3);
  jdouble outCArray[] = {psecMin, psecMax, pnSteps};
  env->SetDoubleArrayRegion(jvalues, 0, 3, outCArray);
  return jvalues;
  }




JNIEXPORT jboolean JNICALL Java_org_knowm_waveforms4j_DWF_FDwfAnalogInTriggerPositionSet
  (JNIEnv * env, jobject obj, jdouble secPosition){

    return FDwfAnalogInTriggerPositionSet(hdwf, secPosition);
  }













  
JNIEXPORT jdoubleArray JNICALL Java_org_knowm_waveforms4j_DWF_FDwfAnalogInStatusData
  (JNIEnv * env, jobject obj, jint idxChannel, jint size){
  
    double* rgdSamples = new double[size];
    FDwfAnalogInStatusData(hdwf, idxChannel, rgdSamples, size);
    
    jdoubleArray jvalues = env->NewDoubleArray(size);
    env->SetDoubleArrayRegion(jvalues, 0, size, rgdSamples); 
    return jvalues;
  } 
  
JNIEXPORT jboolean JNICALL Java_org_knowm_waveforms4j_DWF_FDwfAnalogInConfigure
  (JNIEnv * env, jobject obj, jboolean reconfigure, jboolean start){
  
    return FDwfAnalogInConfigure(hdwf, reconfigure, start);
  }
  
JNIEXPORT jboolean JNICALL Java_org_knowm_waveforms4j_DWF_FDwfAnalogInAcquisitionModeSet
  (JNIEnv * env, jobject obj, jint mode){
  
    return FDwfAnalogInAcquisitionModeSet(hdwf, mode);
  }
  
JNIEXPORT jboolean JNICALL Java_org_knowm_waveforms4j_DWF_FDwfAnalogInTriggerAutoTimeoutSet
  (JNIEnv * env, jobject obj, double secTimeout){
  
    return FDwfAnalogInTriggerAutoTimeoutSet(hdwf, secTimeout);
  }

JNIEXPORT jboolean JNICALL Java_org_knowm_waveforms4j_DWF_FDwfAnalogInTriggerSourceSet
  (JNIEnv * env, jobject obj, jint trigsrc){
  
    return FDwfAnalogInTriggerSourceSet(hdwf, trigsrc);
  }

JNIEXPORT jboolean JNICALL Java_org_knowm_waveforms4j_DWF_FDwfAnalogInTriggerTypeSet
  (JNIEnv * env, jobject obj, jint trigtype){
  
    return FDwfAnalogInTriggerTypeSet(hdwf, trigtype);
  }
    
JNIEXPORT jboolean JNICALL Java_org_knowm_waveforms4j_DWF_FDwfAnalogInTriggerConditionSet
  (JNIEnv * env, jobject obj, jint trigcond){
  
    return FDwfAnalogInTriggerConditionSet(hdwf, trigcond);
  }  

JNIEXPORT jboolean JNICALL Java_org_knowm_waveforms4j_DWF_FDwfAnalogInTriggerChannelSet
  (JNIEnv * env, jobject obj, jint idxChannel){
  
    return FDwfAnalogInTriggerChannelSet(hdwf, idxChannel);
  }
  
JNIEXPORT jboolean JNICALL Java_org_knowm_waveforms4j_DWF_FDwfAnalogInTriggerLevelSet
  (JNIEnv * env, jobject obj, jdouble voltsLevel){
  
    return FDwfAnalogInTriggerLevelSet(hdwf, voltsLevel);
  }
  
/************************************************************
*                                                           *
*                      Analog Out                            *
*                                                           *
*************************************************************/  
  
  
JNIEXPORT jboolean JNICALL Java_org_knowm_waveforms4j_DWF_FDwfAnalogOutNodeEnableSet
  (JNIEnv * env, jobject obj, jint idxChannel, jboolean enable){
  
    return FDwfAnalogOutNodeEnableSet(hdwf, idxChannel, AnalogOutNodeCarrier, enable);
  }
  
JNIEXPORT jboolean JNICALL Java_org_knowm_waveforms4j_DWF_FDwfAnalogOutNodeFunctionSet
  (JNIEnv * env, jobject obj, jint idxChannel, jint func){
  
    return FDwfAnalogOutNodeFunctionSet(hdwf, idxChannel, AnalogOutNodeCarrier, func);
  }  
  
JNIEXPORT jboolean JNICALL Java_org_knowm_waveforms4j_DWF_FDwfAnalogOutNodeFrequencySet
  (JNIEnv * env, jobject obj, jint idxChannel, jdouble hzFrequency){
  
    return FDwfAnalogOutNodeFrequencySet(hdwf, idxChannel, AnalogOutNodeCarrier, hzFrequency);
  }  
  
JNIEXPORT jboolean JNICALL Java_org_knowm_waveforms4j_DWF_FDwfAnalogOutNodeAmplitudeSet
  (JNIEnv * env, jobject obj, jint idxChannel, jdouble amplitude){
  
    return FDwfAnalogOutNodeAmplitudeSet(hdwf, idxChannel, AnalogOutNodeCarrier, amplitude);
  }  
  
JNIEXPORT jboolean JNICALL Java_org_knowm_waveforms4j_DWF_FDwfAnalogOutNodeOffsetSet
  (JNIEnv * env, jobject obj, jint idxChannel, jdouble offset){
  
    return FDwfAnalogOutNodeOffsetSet(hdwf, idxChannel, AnalogOutNodeCarrier, offset);
  }


JNIEXPORT jboolean JNICALL Java_org_knowm_waveforms4j_DWF_FDwfAnalogOutNodeSymmetrySet
  (JNIEnv * env, jobject obj, jint idxChannel, jdouble dutyCycle){

    return FDwfAnalogOutNodeSymmetrySet(hdwf, idxChannel, AnalogOutNodeCarrier, dutyCycle);
  }

    
JNIEXPORT jboolean JNICALL Java_org_knowm_waveforms4j_DWF_FDwfAnalogOutConfigure
  (JNIEnv * env, jobject obj, jint idxChannel, jboolean start){
  
    return FDwfAnalogOutConfigure(hdwf, idxChannel, start);
  }

JNIEXPORT jboolean JNICALL Java_org_knowm_waveforms4j_DWF_FDwfAnalogOutRepeatSet
  (JNIEnv * env, jobject obj, jint idxChannel, jint repeat){
  
    return FDwfAnalogOutRepeatSet(hdwf, idxChannel, repeat);
  }

JNIEXPORT jboolean JNICALL Java_org_knowm_waveforms4j_DWF_FDwfAnalogOutRunSet
  (JNIEnv * env, jobject obj, jint idxChannel, jdouble secRun){
  
    return FDwfAnalogOutRunSet(hdwf, idxChannel, secRun);
  }

JNIEXPORT jboolean JNICALL Java_org_knowm_waveforms4j_DWF_FDwfAnalogOutIdleSet
  (JNIEnv * env, jobject obj, jint idxChannel, jint idle){
  
    return FDwfAnalogOutIdleSet(hdwf, idxChannel, idle);
  }

JNIEXPORT jintArray JNICALL Java_org_knowm_waveforms4j_DWF_FDwfAnalogOutNodeDataInfo
  (JNIEnv * env, jobject obj, jint idxChannel){

  int pnSamplesMin;
  int pnSamplesMax;

  FDwfAnalogOutNodeDataInfo(hdwf, idxChannel, AnalogOutNodeCarrier, &pnSamplesMin, &pnSamplesMax);

  //int cValues[2] = {pnSamplesMin, pnSamplesMax};
  jintArray jvalues = env->NewIntArray(2);
  jint outCArray[] = {pnSamplesMin, pnSamplesMax};
  env->SetIntArrayRegion(jvalues, 0, 2, outCArray);
  return jvalues;
  }










JNIEXPORT jboolean JNICALL Java_org_knowm_waveforms4j_DWF_FDwfAnalogOutNodeDataSet
  (JNIEnv * env, jobject obj, jint idxChannel, jdoubleArray rgdData, jint size){

  //double *input = new double[size];
//  env->GetDoubleArrayRegion( rgdData, 0, size, &input[0] );

  double *input = new double[size];
  jsize len = env->GetArrayLength(rgdData);
  jdouble *body = env->GetDoubleArrayElements(rgdData, 0);
  int i = 0;
  for (i=0; i<len; i++) {
     input[i] = body[i];
  }
  return FDwfAnalogOutNodeDataSet(hdwf, idxChannel, AnalogOutNodeCarrier, input, size);

//  double *input = new double[size];
//  env->SetDoubleArrayRegion(input, 0, size, rgdData);

//double rgdSamples[4096];
//for(int i = 0; i < 4096; i++){
// rgdSamples[i] = 2.0*i/4095-1;
// }
//  return FDwfAnalogOutNodeDataSet(hdwf, idxChannel, AnalogOutNodeCarrier, rgdSamples, 4096);
  }










/************************************************************
*                                                           *
*                      Analog I/O                           *
*                                                           *
*************************************************************/  
  
      
JNIEXPORT jboolean JNICALL Java_org_knowm_waveforms4j_DWF_FDwfAnalogIOChannelNodeSet
  (JNIEnv * env, jobject obj, jint idxChannel, jint idxNode, jdouble value){
  
    return FDwfAnalogIOChannelNodeSet(hdwf, idxChannel, idxNode, value);
  }
 
JNIEXPORT jboolean JNICALL Java_org_knowm_waveforms4j_DWF_FDwfAnalogIOEnableSet
  (JNIEnv * env, jobject obj, jboolean masterEnable){
  
    return FDwfAnalogIOEnableSet(hdwf, masterEnable);
  }
  
JNIEXPORT jboolean JNICALL Java_org_knowm_waveforms4j_DWF_FDwfAnalogIOConfigure
  (JNIEnv * env, jobject obj){

  return FDwfAnalogIOConfigure(hdwf);
  }