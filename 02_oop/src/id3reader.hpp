#ifndef ID3V1READER_HPP
#define ID3V1READER_HPP

#include <string>

namespace mediaplayer {
	
	class ID3v1Reader {
	private:
		std::string mTitle;
		std::string mYear;
		std::string mGenre;
		bool mStatus;
	private:
		void setInvalidStatus();
		void readID3v1header(const std::string& filename);
		int find_length_name(char *arr, int size);
	public:
		explicit ID3v1Reader(const std::string &filename);
		ID3v1Reader();
		ID3v1Reader(const ID3v1Reader&) = delete;
		ID3v1Reader& operator=(const ID3v1Reader&) = delete;
	public:
		operator bool() { return mStatus; }
		bool setnewfile(const std::string &filename);
		std::string getTitle() { return mTitle; }
		std::string getYear() { return mYear; }
		std::string getGenre() { return mGenre; }
	};
	
}

#endif // ID3V1READER_HPP
