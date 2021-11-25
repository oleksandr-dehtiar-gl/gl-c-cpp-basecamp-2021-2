#include "playergui.hpp"
#include <QVideoWidget>

#include "../mediadata/mediadata.hpp"
#include "../playlist/playlistgui.hpp"
#include "../library/librarygui.hpp"

constexpr int widthPlayilist = 600;
constexpr int heightPlayilist = 500;
constexpr int widthLib = 500;
constexpr int heightLib = 500;
constexpr int defaultVolume = 50;

namespace mediaplayer {
	constexpr char* repNames[] {"NOREP", "REPALL", "REP1"};
	static const char* getRepName(RepMode mode) { return repNames[mode]; }

	PlayerGui::PlayerGui(QWidget *parent) 
		: QWidget(parent)
	{
		auto frameBounder = QFrame::Box | QFrame::Sunken;
		auto frameLineWidth = 1;
		
		mpMediaPlayer = new QMediaPlayer(this);
		mpPlaylist = new PlaylistGui(this);
		mpPlaylist->resize(widthPlayilist, heightPlayilist);
		mpPlaylist->addDirToList(QString(SEARCH_DIRECTORY));
		
		mpLibrary = new LibraryGui(this);
		mpLibrary->resize(widthLib, heightLib);
		
		// video vidget
		QVideoWidget *pVideoWdg = new QVideoWidget;
		pVideoWdg->setMinimumSize(300, 300);
		mpMediaPlayer->setVideoOutput(pVideoWdg);
		
		// progress area
		QHBoxLayout *hProgressPanel = new QHBoxLayout;
		mTime = new QLabel("time");
		mRestTime = new QLabel("resttime");
		mProgress = new QSlider(Qt::Horizontal);
		hProgressPanel->addWidget(mTime);
		hProgressPanel->addWidget(mProgress);
		hProgressPanel->addWidget(mRestTime);
		
		// volume area
		QFrame *borderVolumePanel = new QFrame;
		borderVolumePanel->setFrameStyle(frameBounder);
		borderVolumePanel->setLineWidth(frameLineWidth);
		
		QHBoxLayout *hVolumePanel = new QHBoxLayout(borderVolumePanel);
		mVolumeMute = new QPushButton(borderVolumePanel);
		mVolumeSlider = new QSlider(Qt::Horizontal, borderVolumePanel);
		mVolumeSlider->setMinimumWidth(100);
		mVolumeSlider->setRange(0, 100);
		mpMediaPlayer->setVolume(defaultVolume);
		mVolumeSlider->setValue(defaultVolume);
		
		mVolumeMute->setIcon(style()->standardIcon(QStyle::SP_MediaVolume));
		hVolumePanel->addWidget(mVolumeMute);
		hVolumePanel->addWidget(mVolumeSlider);
		borderVolumePanel->setLayout(hVolumePanel);
		
		// play control area
		QFrame *borderControlPanel = new QFrame;
		borderControlPanel->setFrameStyle(frameBounder);
		borderControlPanel->setLineWidth(frameLineWidth);
		
		QHBoxLayout *hPlayControlePanel = new QHBoxLayout(borderControlPanel);
		mPlayButton = new QPushButton(borderControlPanel);
		mStopButton = new QPushButton(borderControlPanel);
		mSeekForwardButton = new QPushButton(borderControlPanel);
		mSeekBackwordButton = new QPushButton(borderControlPanel);
		mRepModeButton = new QPushButton(getRepName(RepMode::NOREP), borderControlPanel);
		mPlayButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
		mStopButton->setIcon(style()->standardIcon(QStyle::SP_MediaStop));
		mSeekForwardButton->setIcon(style()->standardIcon(QStyle::SP_MediaSeekForward));
		mSeekBackwordButton->setIcon(style()->standardIcon(QStyle::SP_MediaSeekBackward));
		hPlayControlePanel->addWidget(mSeekBackwordButton);
		hPlayControlePanel->addWidget(mPlayButton);
		hPlayControlePanel->addWidget(mStopButton);
		hPlayControlePanel->addWidget(mSeekForwardButton);
		hPlayControlePanel->addWidget(mRepModeButton);
		borderControlPanel->setLayout(hPlayControlePanel);
		
		// Playlists area
		QFrame *borderPlaylistPanel = new QFrame;
		borderPlaylistPanel->setFrameStyle(frameBounder);
		borderPlaylistPanel->setLineWidth(frameLineWidth);
		
		QHBoxLayout *hPlaylistPanel = new QHBoxLayout;
		mPlaylistButton = new QPushButton("PLIST", borderPlaylistPanel);
		mLibraryButton = new QPushButton("LIB", borderPlaylistPanel);
		mPlaylistButton->setIcon(style()->standardIcon(QStyle::SP_FileDialogDetailedView));
		mLibraryButton->setIcon(style()->standardIcon(QStyle::SP_FileDialogDetailedView));
		hPlaylistPanel->addWidget(mPlaylistButton);
		hPlaylistPanel->addWidget(mLibraryButton);
		borderPlaylistPanel->setLayout(hPlaylistPanel);
		
		// Horizontal control panel area
		QHBoxLayout *hControlPanel = new QHBoxLayout;
		hControlPanel->addWidget(borderControlPanel);
		hControlPanel->addWidget(borderVolumePanel);
		hControlPanel->addStretch(1);
		hControlPanel->addWidget(borderPlaylistPanel);

		// Vertical layout
		QVBoxLayout *vertLayout = new QVBoxLayout;
		vertLayout->addWidget(pVideoWdg);
		vertLayout->addStretch(1);
		vertLayout->addLayout(hProgressPanel);
		vertLayout->addLayout(hControlPanel);
		mpShowMedia = new QLabel("File path/name");
		vertLayout->addWidget(mpShowMedia);
		
		// Main bounder box player
		QFrame *playerBounder = new QFrame;
		playerBounder->setFrameStyle(frameBounder);
		playerBounder->setLineWidth(frameLineWidth);
		playerBounder->setLayout(vertLayout);
		 
		QHBoxLayout *mainBox = new QHBoxLayout;
		mainBox->addWidget(playerBounder);
		setLayout(mainBox);
		
		connections();
	}
	
	void PlayerGui::connections() {
		// open new sub windows
		connect(mPlaylistButton, SIGNAL(clicked()), SLOT(openPlaylist()));
		connect(mLibraryButton, SIGNAL(clicked()), SLOT(openLibrary()));
		// control play media
		connect(mVolumeSlider, SIGNAL(valueChanged(int)), mpMediaPlayer, SLOT(setVolume(int)));
		connect(mPlayButton, SIGNAL(clicked()), SLOT(slotPlay()));
		connect(mStopButton, SIGNAL(clicked()), SLOT(slotStop()));
		// progress slider 
		connect(mProgress, SIGNAL(sliderMoved(int)), SLOT(slotSetMediaPosition(int)));
		connect(mpMediaPlayer, SIGNAL(positionChanged(qint64)), SLOT(slotSetSliderPosition(qint64)));
		connect(mpMediaPlayer, SIGNAL(durationChanged(qint64)), SLOT(slotSetDuration(qint64)));
		// Set volume mute mode
		connect(mVolumeMute, SIGNAL(clicked()), SLOT(slotSetMute()));
		connect(mpMediaPlayer, SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)), SLOT(changeMediaStatus(QMediaPlayer::MediaStatus)));
		// control playlist
		connect(mpPlaylist, &PlaylistGui::getMediaFileForPlay, this, &PlayerGui::getFileForPlay);
		connect(mpPlaylist, &PlaylistGui::getMediaFile, this, &PlayerGui::getFile);
		connect(this, SIGNAL(playCurrentFile()), mpPlaylist, SIGNAL(currentMediaFile()));
		
		connect(mSeekForwardButton, SIGNAL(clicked()), mpPlaylist, SIGNAL(nextMediFile()));
		connect(mSeekBackwordButton, SIGNAL(clicked()), mpPlaylist, SIGNAL(previosMediFile()));
		// change repeat mode
		connect(mRepModeButton, SIGNAL(clicked()), SLOT(slotChangeRepMode()));
		connect(this, SIGNAL(changePlaylistRepeat(bool)), mpPlaylist, SIGNAL(setRepeatAll(bool)));
	}
	
	void PlayerGui::getFile(std::shared_ptr<MediaFile> file) {
		mCurrPlayFile = file;
		if (!file)
			return;
		auto status = mpMediaPlayer->state();
		mpMediaPlayer->setMedia(QUrl::fromLocalFile(QString::fromStdString(mCurrPlayFile->path())));
		if (status != QMediaPlayer::StoppedState)
			play();
	}
	
	void PlayerGui::getFileForPlay(std::shared_ptr<MediaFile> file) {
		mCurrPlayFile = file;
		if (!file)
			return;
		play();
	}
	
	void PlayerGui::openPlaylist() {
		mpPlaylist->isVisible() ? mpPlaylist->hide() : mpPlaylist->show();
	}
	
	void PlayerGui::openLibrary() {
		mpLibrary->isVisible() ? mpLibrary->hide() : mpLibrary->show();
	}
	
	bool PlayerGui::play() {
		if (mCurrPlayFile) {
			mpMediaPlayer->setMedia(QUrl::fromLocalFile(QString::fromStdString(mCurrPlayFile->path())));
			mpMediaPlayer->play();
			if (mpMediaPlayer->state() == QMediaPlayer::PlayingState) {
				mPlayButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
				mpShowMedia->setText(QString::fromStdString(mCurrPlayFile->path()));
				return true;
			}
		}
		mPlayButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
		return false;
	}
	
	void PlayerGui::slotPlay() {
		switch(mpMediaPlayer->state()) {
			case QMediaPlayer::PlayingState:
				mPlayButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
				mpMediaPlayer->pause();
				break;
			case QMediaPlayer::PausedState:
				mPlayButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
				mpMediaPlayer->play();
				break;
			case QMediaPlayer::StoppedState:
				if (!play())
					emit playCurrentFile();
				break;
		}
	}

	void PlayerGui::slotStop() {
		mpMediaPlayer->stop();
		mPlayButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
	}
	
	void PlayerGui::slotSetMediaPosition(int n) {
		mpMediaPlayer->setPosition(n);
	}
	
	QString PlayerGui::msecsToString(qint64 sec) {
		int hours = (sec / (60 * 60 * 1000));
		int minutes = ((sec % (60 * 60 * 1000)) / (60 * 1000));
		int seconds = ((sec % (60 * 1000)) / 1000);
		return QTime(hours, minutes, seconds).toString("hh:mm:ss");
	}
	
	void PlayerGui::slotSetSliderPosition(qint64 pos) {
		mProgress->setValue(pos);
		mTime->setText(msecsToString(pos));
		int nDuration = mProgress->maximum();
		mRestTime->setText(msecsToString(nDuration - pos));
	}
	
	void PlayerGui::slotSetDuration(qint64 n) {
		mProgress->setRange(0, n);
		mTime->setText(msecsToString(0));
		mRestTime->setText(msecsToString(n));
	}
	
	void PlayerGui::slotSetMute() {
		static bool isMute = false;
		if (isMute) {
			emit mpMediaPlayer->setMuted(!isMute);
			mVolumeMute->setIcon(style()->standardIcon(QStyle::SP_MediaVolume));
			isMute = false;
		} else {
			emit mpMediaPlayer->setMuted(!isMute);
			mVolumeMute->setIcon(style()->standardIcon(QStyle::SP_MediaVolumeMuted));
			isMute = true;
		}
	}
	
	void PlayerGui::changeMediaStatus(QMediaPlayer::MediaStatus status) {
		switch(status) {
			case QMediaPlayer::EndOfMedia:
				if (mRepMode == RepMode::REP1) {
					play();
					return;
				}
				emit mSeekForwardButton->clicked();
				play();
				break;
		}
	}
	
	void PlayerGui::slotChangeRepMode() {
		switch(mRepMode) {
			case RepMode::NOREP:
				mRepModeButton->setText(getRepName(RepMode::REPALL));
				mRepMode = RepMode::REPALL;
				emit changePlaylistRepeat(true);
				break;
			case RepMode::REPALL:
				mRepModeButton->setText(getRepName(RepMode::REP1));
				mRepMode = RepMode::REP1;
				emit changePlaylistRepeat(false);
				break;
			case RepMode::REP1:
				mRepModeButton->setText(getRepName(RepMode::NOREP));
				mRepMode = RepMode::NOREP;
				emit changePlaylistRepeat(false);
				break;
		}
	}
	
	
}
