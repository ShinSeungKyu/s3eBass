#include "Game.h"
#include "s3eBass.h"
#include "s3eLibrary.h"

void play(const char* path)
{
	DWORD chan,act,time,level;
	BOOL ismod;
	QWORD pos;
	int a;
    
	printf("Simple console mode BASS example : MOD/MPx/OGG/WAV player\n"
           "---------------------------------------------------------\n");
    
	// check the correct BASS was loaded
	if (HIWORD(s3eBASS_GetVersion())!=BASSVERSION) {
		printf("An incorrect version of BASS was loaded");
		return;
	}
    
  
	// try streaming the file/url
	if ((chan=s3eBASS_StreamCreateFile(FALSE,path,0,0,BASS_SAMPLE_LOOP))
		|| (chan=s3eBASS_StreamCreateURL(path,0,BASS_SAMPLE_LOOP,0,0))) {
		pos=s3eBASS_ChannelGetLength(chan,BASS_POS_BYTE);
        pos = 0;
		if (s3eBASS_StreamGetFilePosition(chan,BASS_FILEPOS_DOWNLOAD)!=-1) {
			// streaming from the internet
			if (pos!=-1)
#ifdef _WIN32
				printf("streaming internet file [%I64u bytes]",pos);
#else
            printf("streaming internet file [%llu bytes]",pos);
#endif
			else
				printf("streaming internet file");
		} else
#ifdef _WIN32
			printf("streaming file [%I64u bytes]",pos);
#else
        printf("streaming file [%llu bytes]",pos);
#endif
		ismod=FALSE;
	} else {
		// try loading the MOD (with looping, sensitive ramping, and calculate the duration)
		if (!(chan=s3eBASS_MusicLoad(FALSE,path,0,0,BASS_SAMPLE_LOOP|BASS_MUSIC_RAMPS|BASS_MUSIC_PRESCAN,1)))
			// not a MOD either
			//Error("Can't play the file");
		{ // count channels
			float dummy;
			for (a=0;s3eBASS_ChannelGetAttribute(chan,BASS_ATTRIB_MUSIC_VOL_CHAN+a,&dummy);a++);
		}
        
		printf("playing MOD music \"%s\" [%u chans, %u orders]",
               s3eBASS_ChannelGetTags(chan,BASS_TAG_MUSIC_NAME),a,(DWORD)s3eBASS_ChannelGetLength(chan,BASS_POS_MUSIC_ORDER));
         
		pos=s3eBASS_ChannelGetLength(chan,BASS_POS_BYTE);
		ismod=TRUE;
	}
    
	// display the time length
	if (pos!=-1) {
		time=(DWORD)s3eBASS_ChannelBytes2Seconds(chan,pos);
		printf(" %u:%02u\n",time/60,time%60);
	} else // no time length available
		printf("\n");
    
	s3eBASS_ChannelPlay(chan,FALSE);
    
	while (act=s3eBASS_ChannelIsActive(chan)) {
		// display some stuff and wait a bit
		level=s3eBASS_ChannelGetLevel(chan);
		pos=s3eBASS_ChannelGetPosition(chan,BASS_POS_BYTE);
		time=s3eBASS_ChannelBytes2Seconds(chan,pos);
#ifdef _WIN32
		//printf("pos %09I64u",pos);
#else
		//printf("pos %09llu",pos);
#endif
		if (ismod) {
			pos=s3eBASS_ChannelGetPosition(chan,BASS_POS_MUSIC_ORDER);
			//printf(" (%03u:%03u)",LOWORD(pos),HIWORD(pos));
		}
		//printf(" - %u:%02u - L ",time/60,time%60);
		if (act==BASS_ACTIVE_STALLED) { // playback has stalled
			//printf("-- buffering : %05u --",(DWORD)s3eBASS_StreamGetFilePosition(chan,BASS_FILEPOS_BUFFER));
		} else {
			//for (a=27204;a>200;a=a*2/3) putchar(LOWORD(level)>=a?'*':'-');
			//putchar(' ');
			//for (a=210;a<32768;a=a*3/2) putchar(HIWORD(level)>=a?'*':'-');
		}
		//printf(" R - cpu %.2f%%  \r",s3eBASS_GetCPU());
		//fflush(stdout);
	}
	printf("                                                                             \r");
    
	// wind the frequency down...
	s3eBASS_ChannelSlideAttribute(chan,BASS_ATTRIB_FREQ,1000,500);
	// ...and fade-out to avoid a "click"
	s3eBASS_ChannelSlideAttribute(chan,BASS_ATTRIB_VOL,-1,200);
	// wait for slide to finish
	//while (s3eBASS_ChannelIsSliding(chan,0)) Sleep(1);
}

int main() {
    PFGAME_MAIN_INIT
    char buffer[1000];
    /*
    s3eFileGetFileString("lib/libbass.so", S3E_FILE_REAL_PATH, buffer, 1000);

    PfTrace("AAAA %d", s3eLibraryOpen(buffer));
    PfTrace("BBBB %d", s3eLibraryOpen("/data/data/com.mycompany.testbass/lib/libbass.so"));
    */
    
    PFGAME_MAIN_BEGIN
    if(!s3eBASS_Init(-1, 44100, 0, 0, NULL))
    {
        PfInfo("Couldn't Init Bass");
    }
    s3eBASS_Start();
    
    //GAME->LoadAllScenes();
    //GAME->SwitchToLastScene();
    
    /*
     HSTREAM sound = BASS_StreamCreateFile(FALSE, "/Users/yjpark/pettyfun/libs/PfEditor/data/audio/shoot.wav", 0, 0, BASS_SAMPLE_LOOP);
     if (sound != 0) {
     BASS_ChannelPlay(sound, true);
     }
     */
    //play("/Users/yjpark/pettyfun/libs/TestBass/data/audio/jammin_jagger.mod");
    
    if (true) {
        if (s3eFileGetFileString("rom://audio/theday.xm", S3E_FILE_REAL_PATH, buffer, 1000) == NULL) {
            printf("ERROR getting realpath: %d, %s", s3eFileGetError(), s3eFileGetErrorString());
        }
        printf("AAAAA rom://audio/theday.xm -> %s\n", buffer);
        //play(buffer);
        play("file:///android_asset/audio/theday.xm");
    } else {
        //android's get file string is not working now, using abs path for testing for now.
        play("/sdcard/temp/theday.xm");
    }
    
    PFGAME_MAIN_END
    s3eBASS_Stop();
    s3eBASS_Free();
}
