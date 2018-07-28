#include "CMusic.h"

string CMusic::ALIAS_NAME = "MEDIA_MP3";

CMusic::CMusic()
{
	isOpen = false;
	setMediaName("Suprise.mp3");

	status_cmd = "status " + ALIAS_NAME + " mode";
	play_cmd = "PLAY " + ALIAS_NAME + " FROM 0";
	close_cmd = "CLOSE " + ALIAS_NAME;
}

CMusic::CMusic(string mediaName)
{
	isOpen = false;
	setMediaName(mediaName);

	status_cmd = "status " + ALIAS_NAME + " mode";
	play_cmd = "PLAY " + ALIAS_NAME + " FROM 0";
	close_cmd = "CLOSE " + ALIAS_NAME;
}

//发送信息给MCI  
bool CMusic::SendMciCmd(string cmd)
{  
	if(!mciSendString(cmd.c_str(), NULL, 0, 0))
	{
		return true;  
	}
	return false;  
}  

//从MCI获取信息  
string CMusic::GetMciStatus(string cmd)
{  
	char message[20];  
	mciSendString(cmd.c_str(), message,20,0);
	string str(message);  
	return str;  
}  

void CMusic::ClosePlayer()
{
	if (isOpen)
	{
		SendMciCmd(close_cmd);
		isOpen = false;
	}
}


void CMusic::OpenMediaFile()
{
	ClosePlayer();

	SendMciCmd(open_cmd);

	isOpen = true;

}


void CMusic::PlayMediaFile()
{
	if(isOpen)
	{
		SendMciCmd(play_cmd);
	}
}


void CMusic::Play()
{
	OpenMediaFile();
	PlayMediaFile();
}

void CMusic::Stop()
{
	ClosePlayer();
}
void CMusic::setMediaName(string mediaName) {
	this->mediaName = mediaName;

	open_cmd = "OPEN " + mediaName + " TYPE MPEGVideo ALIAS " + ALIAS_NAME;
	
}


bool CMusic::isStopped()
{
	string result="";
	result=GetMciStatus(status_cmd);  //获取音乐状态  
	if(result == "stopped")  
	{
		return true;
	}
	return false;
} 
