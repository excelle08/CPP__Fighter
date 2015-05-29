#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "myobject.h"
#include "config.h"
#include <SFML/Audio.hpp>

class Background : public MyObject {
public:
	Background(string bgPath=TextureLib::background, string bgmusicPath=AudioLib::bgm, string type="Background") : 
		MyObject(bgPath, sf::Vector2f(0,0)), __bgmPath(bgmusicPath){}
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
	// Revive BGM
	void reviveBackMusic(){
		bgm.play();
	}
	// Get BGM loop status
	bool getIfLoop(){
		return bgm.getLoop();
	}
	sf::SoundStream::Status getMusicState(){
		return bgm.getStatus();
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
