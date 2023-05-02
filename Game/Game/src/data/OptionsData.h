#pragma once
#include "../utils/Singleton.h"

class OptionsData : public Singleton<OptionsData> {
	friend Singleton<OptionsData>;

private:

	int music;
	int sfx;
	int fullWindow;
	int peripheral;

	OptionsData() : music(4), sfx(4), fullWindow(0), peripheral(0) {}

public:
	inline int getMusic() { return music; }
	inline void setMusic(int value) { music = value; }
	inline int getSFX() { return sfx; }
	inline void setSFX(int value) { sfx = value; }
	inline int getFullWindow() { return fullWindow; }
	inline void setFullWindow(int value) { fullWindow = value; }
	inline int getPeripheral() { return peripheral; }
	inline void setPeripheral(int value) { peripheral = value; }
};

inline OptionsData& oD() { return *OptionsData::instance(); }