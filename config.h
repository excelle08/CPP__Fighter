#ifndef CONFIG_Hs
#define CONFIG_Hs

#include <iostream>
using std::string;

#define WINDOW_WIDTH 480
#define WINDOW_HEIGHT 800

namespace TextureLib {
	static string background = "resources/images/background.png";
	static string shuttle = "resources/images/plane.png";
	static string enemy = "resources/images/enemy.png";
	static string bomb = "resources/images/bomb.png";
	static string bonusLife = "resources/images/bonus1.png";
};

namespace AudioLib {
	static string bgm = "resources/audios/bgm.ogg";
	static string bang = "resources/audios/bang.ogg";
	static string damage = "resources/audios/bomb-04.ogg";
	static string upgrade = "resources/audios/upgrade.wav";
};

namespace FontLib {
	static string arial = "resources/fonts/arial.ttf";
};

namespace Config {
	static int pointsPerEnemy = 20;
};


#endif // CONFIG_Hs
