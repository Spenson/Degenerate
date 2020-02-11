#pragma once
#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>

namespace DegenSerialize
{
	class iSerializable
	{
	public:
		virtual ~iSerializable() = default;
		//virtual bool serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) = 0;
		virtual bool deserialize(rapidjson::Document* document) = 0;

	};
}