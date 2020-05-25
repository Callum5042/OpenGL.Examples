#pragma once

#include <string>
#include <vector>

// https://www.khronos.org/opengl/wiki/S3_Texture_Compression
// https://docs.microsoft.com/en-us/windows/win32/direct3ddds/dx-graphics-dds-pguide

struct DDSMipmap
{
	int width;
	int height;
	unsigned char* data;

	int texture_size;

	int level;
};

class LoadDDS
{
public:
	void Load(const std::string&& path);

	int width;
	int height;
	int mipmap_count;

	unsigned int format;

	std::vector<DDSMipmap> mipmaps;
};