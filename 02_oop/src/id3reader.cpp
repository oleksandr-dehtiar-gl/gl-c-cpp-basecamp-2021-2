#include <fstream>
#include <algorithm>
#include <stdexcept>

#include <iostream>
#include <cstddef>

#include "id3reader.hpp"
#include "filesysapi/fileSysApi.hpp"

namespace mediaplayer {
	
	constexpr int genrecount = 192;
	constexpr char* genreNames[genrecount] = {
		"Blues",
		"Classic Rock",
		"Country",
		"Dance",
		"Disco",
		"Funk",
		"Grunge",
		"Hip-Hop",
		"Jazz",
		"Metal",
		"New Age",
		"Oldies",
		"Other",
		"Pop",
		"Rhythm and Blues",
		"Rap",
		"Reggae",
		"Rock",
		"Techno",
		"Industrial",
		"Alternative",
		"Ska",
		"Death Metal",
		"Pranks",
		"Soundtrack",
		"Euro-Techno",
		"Ambient",
		"Trip-Hop",
		"Vocal",
		"Jazz & Funk",
		"Fusion",
		"Trance",
		"Classical",
		"Instrumental",
		"Acid",
		"House",
		"Game",
		"Sound clip",
		"Gospel",
		"Noise",
		"Alternative Rock",
		"Bass",
		"Soul",
		"Punk",
		"Space",
		"Meditative",
		"Instrumental Pop",
		"Instrumental Rock",
		"Ethnic",
		"Gothic",
		"Darkwave",
		"Techno-Industrial",
		"Electronic",
		"Pop-Folk",
		"Eurodance",
		"Dream",
		"Southern Rock",
		"Comedy",
		"Cult",
		"Gangsta",
		"Top 40",
		"Christian Rap",
		"Pop/Funk",
		"Jungle music",
		"Native US",
		"Cabaret",
		"New Wave",
		"Psychedelic",
		"Rave",
		"Showtunes",
		"Trailer",
		"Lo-Fi",
		"Tribal",
		"Acid Punk",
		"Acid Jazz",
		"Polka",
		"Retro",
		"Musical",
		"Rock ’n’ Roll",
		"Hard Rock",
		"Folk",
		"Folk-Rock",
		"National Folk",
		"Swing",
		"Fast Fusion",
		"Bebop",
		"Latin",
		"Revival",
		"Celtic",
		"Bluegrass",
		"Avantgarde",
		"Gothic Rock",
		"Progressive Rock",
		"Psychedelic Rock",
		"Symphonic Rock",
		"Slow Rock",
		"Big Band",
		"Chorus",
		"Easy Listening",
		"Acoustic",
		"Humour",
		"Speech",
		"Chanson",
		"Opera",
		"Chamber Music",
		"Sonata",
		"Symphony",
		"Booty Bass",
		"Primus",
		"Porn Groove",
		"Satire",
		"Slow Jam",
		"Club",
		"Tango",
		"Samba",
		"Folklore",
		"Ballad",
		"Power Ballad",
		"Rhythmic Soul",
		"Freestyle",
		"Duet",
		"Punk Rock",
		"Drum Solo",
		"A cappella",
		"Euro-House",
		"Dance Hall",
		"Goa music",
		"Drum & Bass",
		"Club-House",
		"Hardcore Techno",
		"Terror",
		"Indie",
		"BritPop",
		"Negerpunk",
		"Polsk Punk",
		"Beat",
		"Christian Gangsta Rap",
		"Heavy Metal",
		"Black Metal",
		"Crossover",
		"Contemporary Christian",
		"Christian Rock",
		"Merengue",
		"Salsa",
		"Thrash Metal",
		"Anime",
		"Jpop",
		"Synthpop",
		"Abstract",
		"Art Rock",
		"Baroque",
		"Bhangra",
		"Big beat",
		"Breakbeat",
		"Chillout",
		"Downtempo",
		"Dub",
		"EBM",
		"Eclectic",
		"Electro",
		"Electroclash",
		"Emo",
		"Experimental",
		"Garage",
		"Global",
		"IDM",
		"Illbient",
		"Industro-Goth",
		"Jam Band",
		"Krautrock",
		"Leftfield",
		"Lounge",
		"Math Rock",
		"New Romantic",
		"Nu-Breakz",
		"Post-Punk",
		"Post-Rock",
		"Psytrance",
		"Shoegaze",
		"Space Rock",
		"Trop Rock",
		"World Music",
		"Neoclassical",
		"Audiobook",
		"Audio Theatre",
		"Neue Deutsche Welle",
		"Podcast",
		"Indie-Rock",
		"G-Funk",
		"Dubstep",
		"Garage Rock",
		"Psybient"
	};
	
	constexpr int size_header = 3;
	constexpr int size_title = 30;
	constexpr int size_artist = 30;
	constexpr int size_album = 30;
	constexpr int size_year = 4;
	constexpr int size_comment = 28;
	constexpr int size_zerobyte = 1;
	constexpr int size_track = 1;
	constexpr int size_genre = 1;
	
	struct HeaderID3v1 {
		char header[size_header];
		char title[size_title];
		char artist[size_artist];
		char album[size_album];
		char year[size_year];
		char comment[size_comment];
		char zerobyte[size_zerobyte];
		char track[size_track];
		char genre[size_genre];
	};
	
	void ID3v1Reader::setInvalidStatus() {
		mStatus = false;
		std::string().swap(mTitle);
		std::string().swap(mYear);
		std::string().swap(mGenre);
	}
	
	ID3v1Reader::ID3v1Reader() : mStatus(false) { }
	
	ID3v1Reader::ID3v1Reader(const std::string &filename) {
		readID3v1header(filename);
	}
	
	bool ID3v1Reader::setnewfile(const std::string &filename) {
		readID3v1header(filename);
		return *this;
	}
	
	int ID3v1Reader::find_length_name(char *arr, int size) {
		int i = 0;
		while (i < size) {
			if (arr[i] <= 0)
				break;
			++i;
		}
		return i;
	}
	
	void ID3v1Reader::readID3v1header(const std::string& filename) {
		static HeaderID3v1 metadata;
		setInvalidStatus();

		// check if file extension is mp3
		if ((filesysapi::getFileExtension(filename) != "mp3") || (filename.empty()))
			return;

		// try to open file mp3
		std::ifstream fin(filename, std::ios::in | std::ios::binary);
		if (!fin.is_open())
			return;
		
		// read metadata from the end of file
		auto *fbuf = fin.rdbuf();
		fbuf->pubseekpos(fbuf->pubseekoff(-sizeof(metadata), fin.end));
		fbuf->sgetn((char*)(&metadata), sizeof(metadata));
		fin.close();

		// get title
		std::string title(&metadata.title[0], find_length_name(&metadata.title[0], size_title));
		// get year
		std::string year(&metadata.year[0], find_length_name(&metadata.year[0], size_year));
		// get genre
		std::string genre;
		int iGenre = (int)metadata.genre[0];
		if (iGenre >= 0 && iGenre <= genrecount)
			genre.assign(genreNames[iGenre]);

		// set new metadata
		title.swap(mTitle);
		year.swap(mYear);
		genre.swap(mGenre);

		mStatus = true;
	}
	
}
