#include "stdafx.h"

SoundManager::SoundManager()
{
	this->cmdType = 0;
	this->currentSong = 0;
	this->songMaxIndex = 0;
	this->songList = new const char*;
}

void SoundManager::AddSong(const char * songDir)
{
	songList[songMaxIndex++] = songDir;
}

void SoundManager::SongStateSet()
{
	char result[128] = "";
	strcat(result, (char*)state[cmdType]);
	strcat(result, (char*)songList[currentSong]);
	mciSendString(result, NULL, 0, NULL);
}

void SoundManager::ChangeCurrentSong(int SongID)
{
	ChangeCurrentState(0);
	SongStateSet();
	currentSong = SongID;
}

void SoundManager::ChangeCurrentState(int StateID)
{
	cmdType = StateID;
}

int SoundManager::GetCurrentSongID() {
	return currentSong;
}

int SoundManager::GetCurrentMaxIndex() {
	return songMaxIndex - 1;
}

void SoundManager::Release()
{
	delete songList;
}

SoundManager::~SoundManager()
{
}
