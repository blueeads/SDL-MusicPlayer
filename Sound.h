#pragma once
class SoundManager
{
private:
	int cmdType;
	int currentSong;
	int songMaxIndex;
	const char* state[3] = { "stop ", "play ", "pause " };
	const char** songList;

public:
	SoundManager();
	void AddSong(const char* songDir);
	void SongStateSet();
	void ChangeCurrentSong(int SongID);
	void ChangeCurrentState(int StateID);
	int GetCurrentSongID();
	int GetCurrentMaxIndex();
	void Release();
	~SoundManager();
};

