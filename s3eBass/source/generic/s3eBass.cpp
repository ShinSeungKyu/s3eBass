/*
Generic implementation of the s3eBass extension.
This file should perform any platform-indepedentent functionality
(e.g. error checking) before calling platform-dependent implementations.
*/

/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */

#include "s3eTypes.h"
#include "s3eBass.h"

s3eResult s3eBassInit()
{
    //Add any generic initialisation code here
    return S3E_RESULT_SUCCESS;
}

void s3eBassTerminate()
{
}

BOOL s3eBASS_SetConfig(DWORD option, DWORD value)
{
	return BASS_SetConfig(option, value);
}

DWORD s3eBASS_GetConfig(DWORD option)
{
	return BASS_GetConfig(option);
}

BOOL s3eBASS_SetConfigPtr(DWORD option, void *value)
{
	return BASS_SetConfigPtr(option, value);
}

void *s3eBASS_GetConfigPtr(DWORD option)
{
	return BASS_GetConfigPtr(option);
}

DWORD s3eBASS_GetVersion()
{
	return BASS_GetVersion();
}

int s3eBASS_ErrorGetCode()
{
	return BASS_ErrorGetCode();
}

BOOL s3eBASS_GetDeviceInfo(DWORD device, BASS_DEVICEINFO *info)
{
	return BASS_GetDeviceInfo(device, info);
}

BOOL s3eBASS_Init(int device, DWORD freq, DWORD flags, void *win, void *dsguid)
{
	return BASS_Init(device, freq, flags, win, dsguid);
}

BOOL s3eBASS_SetDevice(DWORD device)
{
	return BASS_SetDevice(device);
}

DWORD s3eBASS_GetDevice()
{
	return BASS_GetDevice();
}

BOOL s3eBASS_Free()
{
	return BASS_Free();
}

BOOL s3eBASS_GetInfo(BASS_INFO *info)
{
	return BASS_GetInfo(info);
}

BOOL s3eBASS_Update(DWORD length)
{
	return BASS_Update(length);
}

float s3eBASS_GetCPU()
{
	return BASS_GetCPU();
}

BOOL s3eBASS_Start()
{
	return BASS_Start();
}

BOOL s3eBASS_Stop()
{
	return BASS_Stop();
}

BOOL s3eBASS_Pause()
{
	return BASS_Pause();
}

BOOL s3eBASS_SetVolume(float volume)
{
	return BASS_SetVolume(volume);
}

float s3eBASS_GetVolume()
{
	return BASS_GetVolume();
}

HPLUGIN s3eBASS_PluginLoad(const char *file, DWORD flags)
{
	return BASS_PluginLoad(file, flags);
}

BOOL s3eBASS_PluginFree(HPLUGIN handle)
{
	return BASS_PluginFree(handle);
}

const BASS_PLUGININFO *s3eBASS_PluginGetInfo(HPLUGIN handle)
{
	return BASS_PluginGetInfo(handle);
}

BOOL s3eBASS_Set3DFactors(float distf, float rollf, float doppf)
{
	return BASS_Set3DFactors(distf, rollf, doppf);
}

BOOL s3eBASS_Get3DFactors(float *distf, float *rollf, float *doppf)
{
	return BASS_Get3DFactors(distf, rollf, doppf);
}

BOOL s3eBASS_Set3DPosition(const BASS_3DVECTOR *pos, const BASS_3DVECTOR *vel, const BASS_3DVECTOR *front, const BASS_3DVECTOR *top)
{
	return BASS_Set3DPosition(pos, vel, front, top);
}

BOOL s3eBASS_Get3DPosition(BASS_3DVECTOR *pos, BASS_3DVECTOR *vel, BASS_3DVECTOR *front, BASS_3DVECTOR *top)
{
	return BASS_Get3DPosition(pos, vel, front, top);
}

void s3eBASS_Apply3D()
{
	s3eBASS_Apply3D();
}

HMUSIC s3eBASS_MusicLoad(BOOL mem, const void *file, QWORD offset, DWORD length, DWORD flags, DWORD freq)
{
	return BASS_MusicLoad(mem, file, offset, length, flags, freq);
}

BOOL s3eBASS_MusicFree(HMUSIC handle)
{
	return BASS_MusicFree(handle);
}

HSAMPLE s3eBASS_SampleLoad(BOOL mem, const void *file, QWORD offset, DWORD length, DWORD max, DWORD flags)
{
	return BASS_SampleLoad(mem, file, offset, length, max, flags);
}

HSAMPLE s3eBASS_SampleCreate(DWORD length, DWORD freq, DWORD chans, DWORD max, DWORD flags)
{
	return BASS_SampleCreate(length, freq, chans, max, flags);
}

BOOL s3eBASS_SampleFree(HSAMPLE handle)
{
	return BASS_SampleFree(handle);
}

BOOL s3eBASS_SampleSetData(HSAMPLE handle, const void *buffer)
{
	return BASS_SampleSetData(handle, buffer);
}

BOOL s3eBASS_SampleGetData(HSAMPLE handle, void *buffer)
{
	return BASS_SampleGetData(handle, buffer);
}

BOOL s3eBASS_SampleGetInfo(HSAMPLE handle, BASS_SAMPLE *info)
{
	return BASS_SampleGetInfo(handle, info);
}

BOOL s3eBASS_SampleSetInfo(HSAMPLE handle, const BASS_SAMPLE *info)
{
	return BASS_SampleSetInfo(handle, info);
}

HCHANNEL s3eBASS_SampleGetChannel(HSAMPLE handle, BOOL onlynew)
{
	return BASS_SampleGetChannel(handle, onlynew);
}

DWORD s3eBASS_SampleGetChannels(HSAMPLE handle, HCHANNEL *channels)
{
	return BASS_SampleGetChannels(handle, channels);
}

BOOL s3eBASS_SampleStop(HSAMPLE handle)
{
	return BASS_SampleStop(handle);
}

HSTREAM s3eBASS_StreamCreate(DWORD freq, DWORD chans, DWORD flags, STREAMPROC *proc, void *user)
{
	return BASS_StreamCreate(freq, chans, flags, proc, user);
}

HSTREAM s3eBASS_StreamCreateFile(BOOL mem, const void *file, QWORD offset, QWORD length, DWORD flags)
{
	return BASS_StreamCreateFile(mem, file, offset, length, flags);
}

HSTREAM s3eBASS_StreamCreateURL(const char *url, DWORD offset, DWORD flags, DOWNLOADPROC *proc, void *user)
{
	return BASS_StreamCreateURL(url, offset, flags, proc, user);
}

HSTREAM s3eBASS_StreamCreateFileUser(DWORD system, DWORD flags, const BASS_FILEPROCS *proc, void *user)
{
	return BASS_StreamCreateFileUser(system, flags, proc, user);
}

BOOL s3eBASS_StreamFree(HSTREAM handle)
{
	return BASS_StreamFree(handle);
}

QWORD s3eBASS_StreamGetFilePosition(HSTREAM handle, DWORD mode)
{
	return BASS_StreamGetFilePosition(handle, mode);
}

DWORD s3eBASS_StreamPutData(HSTREAM handle, const void *buffer, DWORD length)
{
	return BASS_StreamPutData(handle, buffer, length);
}

DWORD s3eBASS_StreamPutFileData(HSTREAM handle, const void *buffer, DWORD length)
{
	return BASS_StreamPutFileData(handle, buffer, length);
}

BOOL s3eBASS_RecordGetDeviceInfo(DWORD device, BASS_DEVICEINFO *info)
{
	return BASS_RecordGetDeviceInfo(device, info);
}

BOOL s3eBASS_RecordInit(int device)
{
	return BASS_RecordInit(device);
}

BOOL s3eBASS_RecordSetDevice(DWORD device)
{
	return BASS_RecordSetDevice(device);
}

DWORD s3eBASS_RecordGetDevice()
{
	return BASS_RecordGetDevice();
}

BOOL s3eBASS_RecordFree()
{
	return BASS_RecordFree();
}

BOOL s3eBASS_RecordGetInfo(BASS_RECORDINFO *info)
{
	return BASS_RecordGetInfo(info);
}

const char *s3eBASS_RecordGetInputName(int input)
{
	return BASS_RecordGetInputName(input);
}

BOOL s3eBASS_RecordSetInput(int input, DWORD flags, float volume)
{
	return BASS_RecordSetInput(input, flags, volume);
}

DWORD s3eBASS_RecordGetInput(int input, float *volume)
{
	return BASS_RecordGetInput(input, volume);
}

HRECORD s3eBASS_RecordStart(DWORD freq, DWORD chans, DWORD flags, RECORDPROC *proc, void *user)
{
	return BASS_RecordStart(freq, chans, flags, proc, user);
}

double s3eBASS_ChannelBytes2Seconds(DWORD handle, QWORD pos)
{
	return BASS_ChannelBytes2Seconds(handle, pos);
}

QWORD s3eBASS_ChannelSeconds2Bytes(DWORD handle, double pos)
{
	return BASS_ChannelSeconds2Bytes(handle, pos);
}

DWORD s3eBASS_ChannelGetDevice(DWORD handle)
{
	return BASS_ChannelGetDevice(handle);
}

BOOL s3eBASS_ChannelSetDevice(DWORD handle, DWORD device)
{
	return BASS_ChannelSetDevice(handle, device);
}

DWORD s3eBASS_ChannelIsActive(DWORD handle)
{
	return BASS_ChannelIsActive(handle);
}

BOOL s3eBASS_ChannelGetInfo(DWORD handle, BASS_CHANNELINFO *info)
{
	return BASS_ChannelGetInfo(handle, info);
}

const char *s3eBASS_ChannelGetTags(DWORD handle, DWORD tags)
{
	return BASS_ChannelGetTags(handle, tags);
}

DWORD s3eBASS_ChannelFlags(DWORD handle, DWORD flags, DWORD mask)
{
	return BASS_ChannelFlags(handle, flags, mask);
}

BOOL s3eBASS_ChannelUpdate(DWORD handle, DWORD length)
{
	return BASS_ChannelUpdate(handle, length);
}

BOOL s3eBASS_ChannelLock(DWORD handle, BOOL lock)
{
	return BASS_ChannelLock(handle, lock);
}

BOOL s3eBASS_ChannelPlay(DWORD handle, BOOL restart)
{
	return BASS_ChannelPlay(handle, restart);
}

BOOL s3eBASS_ChannelStop(DWORD handle)
{
	return BASS_ChannelStop(handle);
}

BOOL s3eBASS_ChannelPause(DWORD handle)
{
	return BASS_ChannelPause(handle);
}

BOOL s3eBASS_ChannelSetAttribute(DWORD handle, DWORD attrib, float value)
{
	return BASS_ChannelSetAttribute(handle, attrib, value);
}

BOOL s3eBASS_ChannelGetAttribute(DWORD handle, DWORD attrib, float *value)
{
	return BASS_ChannelGetAttribute(handle, attrib, value);
}

BOOL s3eBASS_ChannelSlideAttribute(DWORD handle, DWORD attrib, float value, DWORD time)
{
	return BASS_ChannelSlideAttribute(handle, attrib, value, time);
}

BOOL s3eBASS_ChannelIsSliding(DWORD handle, DWORD attrib)
{
	return BASS_ChannelIsSliding(handle, attrib);
}

BOOL s3eBASS_ChannelSet3DAttributes(DWORD handle, int mode, float min, float max, int iangle, int oangle, float outvol)
{
	return BASS_ChannelSet3DAttributes(handle, mode, min, max, iangle, oangle, outvol);
}

BOOL s3eBASS_ChannelGet3DAttributes(DWORD handle, DWORD *mode, float *min, float *max, DWORD *iangle, DWORD *oangle, float *outvol)
{
	return BASS_ChannelGet3DAttributes(handle, mode, min, max, iangle, oangle, outvol);
}

BOOL s3eBASS_ChannelSet3DPosition(DWORD handle, const BASS_3DVECTOR *pos, const BASS_3DVECTOR *orient, const BASS_3DVECTOR *vel)
{
	return BASS_ChannelSet3DPosition(handle, pos, orient, vel);
}

BOOL s3eBASS_ChannelGet3DPosition(DWORD handle, BASS_3DVECTOR *pos, BASS_3DVECTOR *orient, BASS_3DVECTOR *vel)
{
	return BASS_ChannelGet3DPosition(handle, pos, orient, vel);
}

QWORD s3eBASS_ChannelGetLength(DWORD handle, DWORD mode)
{
	return BASS_ChannelGetLength(handle, mode);
}

BOOL s3eBASS_ChannelSetPosition(DWORD handle, QWORD pos, DWORD mode)
{
	return BASS_ChannelSetPosition(handle, pos, mode);
}

QWORD s3eBASS_ChannelGetPosition(DWORD handle, DWORD mode)
{
	return BASS_ChannelGetPosition(handle, mode);
}

DWORD s3eBASS_ChannelGetLevel(DWORD handle)
{
	return BASS_ChannelGetLevel(handle);
}

DWORD s3eBASS_ChannelGetData(DWORD handle, void *buffer, DWORD length)
{
	return BASS_ChannelGetData(handle, buffer, length);
}

HSYNC s3eBASS_ChannelSetSync(DWORD handle, DWORD type, QWORD param, SYNCPROC *proc, void *user)
{
	return BASS_ChannelSetSync(handle, type, param, proc, user);
}

BOOL s3eBASS_ChannelRemoveSync(DWORD handle, HSYNC sync)
{
	return BASS_ChannelRemoveSync(handle, sync);
}

HDSP s3eBASS_ChannelSetDSP(DWORD handle, DSPPROC *proc, void *user, int priority)
{
	return BASS_ChannelSetDSP(handle, proc, user, priority);
}

BOOL s3eBASS_ChannelRemoveDSP(DWORD handle, HDSP dsp)
{
	return BASS_ChannelRemoveDSP(handle, dsp);
}

BOOL s3eBASS_ChannelSetLink(DWORD handle, DWORD chan)
{
	return BASS_ChannelSetLink(handle, chan);
}

BOOL s3eBASS_ChannelRemoveLink(DWORD handle, DWORD chan)
{
	return BASS_ChannelRemoveLink(handle, chan);
}

HFX s3eBASS_ChannelSetFX(DWORD handle, DWORD type, int priority)
{
	return BASS_ChannelSetFX(handle, type, priority);
}

BOOL s3eBASS_ChannelRemoveFX(DWORD handle, HFX fx)
{
	return BASS_ChannelRemoveFX(handle, fx);
}

BOOL s3eBASS_FXSetParameters(HFX handle, const void *params)
{
	return BASS_FXSetParameters(handle, params);
}

BOOL s3eBASS_FXGetParameters(HFX handle, void *params)
{
	return BASS_FXGetParameters(handle, params);
}

BOOL s3eBASS_FXReset(HFX handle)
{
	return BASS_FXReset(handle);
}
