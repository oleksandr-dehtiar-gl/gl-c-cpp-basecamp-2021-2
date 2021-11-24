#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <QtWidgets>
#include <QMediaPlayer>

#include "../playlist/playlistgui.hpp"
#include "../mediadata/mediadata.hpp"

namespace mediaplayer {
	
	enum RepMode { NOREP, REPALL, REP1 };
	
	class PlayerGui : public QWidget {
		Q_OBJECT
	public:
		PlayerGui(QWidget *parent = nullptr);
	private:
		std::shared_ptr<MediaFile> mCurrPlayFile;
		QMediaPlayer *mpMediaPlayer = nullptr;
		PlaylistGui *mpPlaylist = nullptr;
		RepMode mRepMode = RepMode::NOREP;
	private:
		// Control play buttons
		QPushButton *mPlayButton;
		QPushButton *mStopButton;
		QPushButton *mSeekForwardButton;
		QPushButton *mSeekBackwordButton;
		QPushButton *mRepModeButton;
		// Control volume
		QPushButton *mVolumeMute;
		QSlider *mVolumeSlider;
		// Buttons library and playlist
		QPushButton *mPlaylistButton;
		QPushButton *mLibraryButton;
		// Sliders progress player
		QLabel *mTime;
		QLabel *mRestTime;
		QSlider *mProgress;
	private:
		void connections();
		QString msecsToString(qint64);
		bool play();
	signals:
		void playCurrentFile();
		void changePlaylistRepeat(bool);
	private slots:
		void openPlaylist();
		void getFileForPlay(std::shared_ptr<MediaFile> file);
		void getFile(std::shared_ptr<MediaFile> file);
		void slotPlay();
		void slotStop();
		void slotSetMediaPosition(int n);
		void slotSetSliderPosition(qint64);
		void slotSetDuration(qint64 n);
		void slotSetMute();
		void changeMediaStatus(QMediaPlayer::MediaStatus status);
		void slotChangeRepMode();
	};
	
}

#endif // PLAYER_HPP