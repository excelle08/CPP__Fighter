#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "myobject.h"
#include <SFML/Audio.hpp>

class Background : public MyObject {
public:
	Background(string bgPath="resources/images/background.png", string bgmusicPath="resources/audios/bgm.ogg") : MyObject(bgPath, sf::Vector2f(0,0)), __bgmPath(bgmusicPath){}
	~Background(){}
	// Load music and play
	bool loadBackMusic(){
		bool state = bgm.openFromFile(__bgmPath);
		if(state){
			bgm.play();
			return true;
		} else {
			return false;
		}
	}
	// Stop BGM
	void stopBackMusic(){
		bgm.stop();
	}
	// Get BGM loop status
	bool getIfLoop(){
		return bgm.getLoop();
	}
	// Set whether to loop the BGM
	void setLoop(bool stat){
		bgm.setLoop(stat);
	}
	// Get BGM file path
	string getBGMPath(){
		return __bgmPath;
	}
private:
	string __bgmPath;
	sf::Music bgm;
	/* data */
};

#endif // BACKGROUND_H
