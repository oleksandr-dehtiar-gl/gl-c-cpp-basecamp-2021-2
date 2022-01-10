#include "mediadata.hpp"
#include <algorithm>

#include "../../filesysapi/fileSysApi.hpp"

namespace mediaplayer {
	
	const char* getExtension(MediaTypes type) {
		if (type == MediaTypes::UNDEFINE_TYPE)
			return nullptr;
		return MEDIA_FILE_FORMATS_NAME[type];
	}

	std::shared_ptr<MediaFile> facoryMediaFile(const std::string& path) {
		std::string extension = filesysapi::getFileExtension(path);
		if (extension.empty())
			return std::shared_ptr<MediaFile>();
		
		// find if extension exist in support format list
		auto *end = &MEDIA_FILE_FORMATS_NAME[0] + (sizeof(MEDIA_FILE_FORMATS_NAME) / sizeof(&MEDIA_FILE_FORMATS_NAME[0]));
		auto *element = std::find(MEDIA_FILE_FORMATS_NAME, end, extension);
		if (element == end)
			return std::shared_ptr<MediaFile>();
		
		// If format exist constract corresponding object
		switch(element - &MEDIA_FILE_FORMATS_NAME[0]) {
			case 0: return std::make_shared<MediaFile>(MP3File(path));
			case 1: return std::make_shared<MediaFile>(MP4File(path));
		}
		return std::shared_ptr<MediaFile>();
	}
	
	MediaFile::MediaFile(const std::string& path, MediaTypes type)
		: mType(type), 
		mPath(filesysapi::getAbsolutePath(path)),
		mName(filesysapi::getFileNameWihtoutExtens(path))
	{
		
	}
	
}
