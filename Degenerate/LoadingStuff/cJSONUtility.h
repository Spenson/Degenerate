#pragma once

#include <fstream>
#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/ostreamwrapper.h>
#include "iSerializable.h"


namespace DegenSerialize
{
	class cJSONUtility
	{
	public:
		static rapidjson::Document open_document(const std::string& filename)
		{
			std::ifstream input_file(filename);
			if (!input_file.is_open())
			{
				return nullptr;
			}

			rapidjson::IStreamWrapper isw(input_file);
			rapidjson::Document document;
			document.ParseStream(isw);

			return document;
		}

		//static bool serialize(iSerializable* object, rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer)
		//{
		//	return object->serialize(writer);
		//}

		static bool deserialize(iSerializable* object, rapidjson::Document* document)
		{
			return object->deserialize(document);
		}
	};
}
