#include "LoadDDS.h"
#include <fstream>
#pragma warning(disable : 6385)

#include <iostream>
#include <GL\glew.h>

void LoadDDS::Load(const std::string&& path)
{
	std::ifstream file(path, std::ios::binary);

	if (!file.is_open())
	{
		std::cout << "Could not open file\n";
	}

	std::streampos begin = file.tellg();
	file.seekg(0, std::ios::end);
	std::streampos end = file.tellg();

	int size = static_cast<int>(end - begin);

	char* buffer = new char[size];

	file.seekg(0, std::ios::beg);
	file.read(buffer, size);
	file.close();

	// Parse the data

	// Check that it has DDS header
	
	if (buffer[0] != 'D' || buffer[1] != 'D' || buffer[2] != 'S')
	{
		std::cout << "Not a DDS file\n";
	}

	// Get width
	height = (buffer[12]) | (buffer[13] << 8) | (buffer[14] << 16) | (buffer[15] << 24);
	width = (buffer[16]) | (buffer[17] << 8) | (buffer[18] << 16) | (buffer[19] << 24);
	mipmap_count = (buffer[28]) | (buffer[29] << 8) | (buffer[30] << 16) | (buffer[31] << 24);

	int blockSize = 0;
	if (buffer[87] == '1')
	{
		format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
		blockSize = 8;
	}
	else if (buffer[87] == '3')
	{
		format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
		blockSize = 16;
	}
	else if (buffer[87] == '5')
	{
		format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
		blockSize = 16;
	}
	else
	{
		std::cout << "Not supported\n";
	}

	// Only do first mipmap
	int header_size = 128;

	int temp_width = width;
	int temp_height = height;

	int offset = 0;
	for (int i = 0; i < mipmap_count; ++i)
	{
		DDSMipmap mipmap;
		mipmap.level = i;
		mipmap.width = temp_width;
		mipmap.height = temp_height;
		mipmap.texture_size = ((mipmap.width + 3) / 4) * ((mipmap.height + 3) / 4) * blockSize;
		mipmap.data = new unsigned char[mipmap.texture_size];
		memcpy(mipmap.data, buffer + 128 + offset, mipmap.texture_size);

		offset += mipmap.texture_size;
		temp_width /= 2;
		temp_height /= 2;

		mipmaps.push_back(mipmap);
	}
}
