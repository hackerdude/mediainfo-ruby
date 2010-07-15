
#include "rice/Class.hpp"
#include "rice/Data_Type.hpp"
#include "rice/Constructor.hpp"
#include "rice/Enum.hpp"
#include "rice/Module.hpp"

#include <string.h>
#include <MediaInfoDLL/MediaInfoDLL.h>
#define MediaInfoNameSpace MediaInfoDLL

using namespace Rice;
using namespace MediaInfoNameSpace;

extern "C" void Init_mediainfo_ruby()
{
		//printf( "Dude!\n");
		//define_module("MediaInfoLib").
    define_enum<stream_t>("MediaInfoLib_StreamKind")
      .define_value("General", Stream_General)
      .define_value("Video", Stream_Video)
      .define_value("Audio", Stream_Audio)
      .define_value("Text", Stream_Text)
      .define_value("Chapters", Stream_Chapters)
      .define_value("Image", Stream_Image)
      .define_value("Menu", Stream_Menu)
      .define_value("Max", Stream_Max)
		;

		//define_module("MediaInfo").
		define_enum<info_t>("MediaInfoLib_InfoKind")
		.define_value("Name", Info_Name)
		.define_value("Text", Info_Text)
		.define_value("Measure", Info_Measure)
		.define_value("Options", Info_Options)
		.define_value("Name_Text", Info_Name_Text)
		.define_value("Measure_Text", Info_Measure_Text)
		.define_value("Info", Info_Info)
		.define_value("HowTo", Info_HowTo)
		//.define_value("Domain", Info_Domain)
		.define_value("Max", Info_Max)
		;
		//define_class<File__Analyze>("File__Analyze")
		//;
		typedef std::string(MediaInfo::*get_info)(stream_t,size_t,size_t,info_t);
		typedef std::string(MediaInfo::*get_info_somewhere)(stream_t, size_t,const std::string,info_t,info_t);
		typedef std::string(MediaInfo::*get_info_string)(stream_t StreamKind, size_t StreamNumber, const std::string &Parameter, info_t InfoKind, info_t SearchKind);
		

		define_module("MediaInfoLib").
			define_class<MediaInfo>("MediaInfo")
			.define_constructor(Constructor<MediaInfo>())
			.define_method("_inform", &MediaInfo::Inform)
			.define_method("option", &MediaInfo::Option)
			.define_method("open", &MediaInfo::Open)
			.define_method("close", &MediaInfo::Close)
			.define_method("state_get", &MediaInfo::State_Get)
			.define_method("count_get", &MediaInfo::Count_Get)
			.define_method("get", get_info(&MediaInfo::Get))
			// TODO Enabling this breaks with "address of overloaded function with no contextual type information".. Signature doesn't match
			.define_method("get_value", get_info_string(&MediaInfo::Get))
			//.define_method("_count_get", &MediaInfo::Count_Get)
			;
		//printf( "OK so at least MediaInfo is initialized now\n");
}
