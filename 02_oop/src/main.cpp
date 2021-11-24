#include "mediaplayer/player/playergui.hpp"

int main(int argc, char** argv) {

	QApplication app(argc, argv);

	mediaplayer::PlayerGui pl;
	pl.show();

	return app.exec();
}
