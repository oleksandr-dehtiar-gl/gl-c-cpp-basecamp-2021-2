#include "mediaplayer/player/playergui.hpp"


int main(int argc, char** argv) {

	QApplication app(argc, argv);
	
	mediaplayer::PlayerGui palayer;
	palayer.show();

	return app.exec();
}

