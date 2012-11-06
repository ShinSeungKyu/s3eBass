/*
java implementation of the s3eBass extension.

Add android-specific functionality here.

These functions are called via JNI from native code.
*/
/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */
import com.ideaworks3d.marmalade.LoaderAPI;

class s3eBass
{
    public void s3eBASS_SetConfig()
    {
        
    }
    public void s3eBASS_GetConfig()
    {
        
    }
    public void s3eBASS_SetConfigPtr()
    {
        
    }
    public void s3eBASS_GetConfigPtr()
    {
        
    }
    public void s3eBASS_GetVersion()
    {
        
    }
    public int s3eBASS_ErrorGetCode()
    {
        return 0;
    }
    public void s3eBASS_GetDeviceInfo()
    {
        
    }
    public void s3eBASS_Init(int device)
    {
        
    }
    public void s3eBASS_SetDevice()
    {
        
    }
    public void s3eBASS_GetDevice()
    {
        
    }
    public void s3eBASS_Free()
    {
        
    }
    public void s3eBASS_GetInfo()
    {
        
    }
    public void s3eBASS_Update()
    {
        
    }
    public float s3eBASS_GetCPU()
    {
        return 0;   
    }
    public void s3eBASS_Start()
    {
        
    }
    public void s3eBASS_Stop()
    {
        
    }
    public void s3eBASS_Pause()
    {
        
    }
    public void s3eBASS_SetVolume()
    {
        
    }
    public float s3eBASS_GetVolume()
    {
        return 0;
    }
    public void s3eBASS_PluginLoad()
    {
        
    }
    public void s3eBASS_PluginFree()
    {
        
    }
    public void s3eBASS_PluginGetInfo()
    {
        
    }
    public void s3eBASS_Set3DFactors()
    {
        
    }
    public void s3eBASS_Get3DFactors()
    {
        
    }
    public void s3eBASS_Set3DPosition()
    {
        
    }
    public void s3eBASS_Get3DPosition()
    {
        
    }
    public void s3eBASS_Apply3D()
    {
        
    }
    public void s3eBASS_MusicLoad()
    {
        
    }
    public void s3eBASS_MusicFree()
    {
        
    }
    public void s3eBASS_SampleLoad()
    {
        
    }
    public void s3eBASS_SampleCreate()
    {
        
    }
    public void s3eBASS_SampleFree()
    {
        
    }
    public void s3eBASS_SampleSetData()
    {
        
    }
    public void s3eBASS_SampleGetData()
    {
        
    }
    public void s3eBASS_SampleGetInfo()
    {
        
    }
    public void s3eBASS_SampleSetInfo()
    {
        
    }
    public void s3eBASS_SampleGetChannel()
    {
        
    }
    public void s3eBASS_SampleGetChannels()
    {
        
    }
    public void s3eBASS_SampleStop()
    {
        
    }
    public void s3eBASS_StreamCreate()
    {
        
    }
    public void s3eBASS_StreamCreateFile()
    {
        
    }
    public void s3eBASS_StreamCreateURL()
    {
        
    }
    public void s3eBASS_StreamCreateFileUser()
    {
        
    }
    public void s3eBASS_StreamFree()
    {
        
    }
    public void s3eBASS_StreamGetFilePosition()
    {
        
    }
    public void s3eBASS_StreamPutData()
    {
        
    }
    public void s3eBASS_StreamPutFileData()
    {
        
    }
    public void s3eBASS_RecordGetDeviceInfo()
    {
        
    }
    public void s3eBASS_RecordInit(int device)
    {
        
    }
    public void s3eBASS_RecordSetDevice()
    {
        
    }
    public void s3eBASS_RecordGetDevice()
    {
        
    }
    public void s3eBASS_RecordFree()
    {
        
    }
    public void s3eBASS_RecordGetInfo()
    {
        
    }
    public void s3eBASS_RecordGetInputName(int input)
    {
        
    }
    public void s3eBASS_RecordSetInput(int input)
    {
        
    }
    public void s3eBASS_RecordGetInput(int input)
    {
        
    }
    public void s3eBASS_RecordStart()
    {
        
    }
    public double s3eBASS_ChannelBytes2Seconds()
    {
        return 0;   
    }
    public void s3eBASS_ChannelSeconds2Bytes()
    {
        
    }
    public void s3eBASS_ChannelGetDevice()
    {
        
    }
    public void s3eBASS_ChannelSetDevice()
    {
        
    }
    public void s3eBASS_ChannelIsActive()
    {
        
    }
    public void s3eBASS_ChannelGetInfo()
    {
        
    }
    public void s3eBASS_ChannelGetTags()
    {
        
    }
    public void s3eBASS_ChannelFlags()
    {
        
    }
    public void s3eBASS_ChannelUpdate()
    {
        
    }
    public void s3eBASS_ChannelLock()
    {
        
    }
    public void s3eBASS_ChannelPlay()
    {
        
    }
    public void s3eBASS_ChannelStop()
    {
        
    }
    public void s3eBASS_ChannelPause()
    {
        
    }
    public void s3eBASS_ChannelSetAttribute()
    {
        
    }
    public void s3eBASS_ChannelGetAttribute()
    {
        
    }
    public void s3eBASS_ChannelSlideAttribute()
    {
        
    }
    public void s3eBASS_ChannelIsSliding()
    {
        
    }
    public void s3eBASS_ChannelSet3DAttributes(int mode, int iangle, int oangle)
    {
        
    }
    public void s3eBASS_ChannelGet3DAttributes()
    {
        
    }
    public void s3eBASS_ChannelSet3DPosition()
    {
        
    }
    public void s3eBASS_ChannelGet3DPosition()
    {
        
    }
    public void s3eBASS_ChannelGetLength()
    {
        
    }
    public void s3eBASS_ChannelSetPosition()
    {
        
    }
    public void s3eBASS_ChannelGetPosition()
    {
        
    }
    public void s3eBASS_ChannelGetLevel()
    {
        
    }
    public void s3eBASS_ChannelGetData()
    {
        
    }
    public void s3eBASS_ChannelSetSync()
    {
        
    }
    public void s3eBASS_ChannelRemoveSync()
    {
        
    }
    public void s3eBASS_ChannelSetDSP(int priority)
    {
        
    }
    public void s3eBASS_ChannelRemoveDSP()
    {
        
    }
    public void s3eBASS_ChannelSetLink()
    {
        
    }
    public void s3eBASS_ChannelRemoveLink()
    {
        
    }
    public void s3eBASS_ChannelSetFX(int priority)
    {
        
    }
    public void s3eBASS_ChannelRemoveFX()
    {
        
    }
    public void s3eBASS_FXSetParameters()
    {
        
    }
    public void s3eBASS_FXGetParameters()
    {
        
    }
    public void s3eBASS_FXReset()
    {
        
    }
}
