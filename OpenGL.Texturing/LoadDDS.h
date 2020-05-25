#pragma once

#include <string>
#include <vector>
#include <filesystem>
typedef unsigned int uint;

// https://www.khronos.org/opengl/wiki/S3_Texture_Compression
// https://docs.microsoft.com/en-us/windows/win32/direct3ddds/dx-graphics-dds-pguide

namespace RV
{
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
		LoadDDS() = default;
		LoadDDS(std::filesystem::path path);
		LoadDDS(std::string&& path);
		~LoadDDS();

		void Load(const std::string&& path);
		void Load(std::filesystem::path path);

		constexpr bool IsLoaded() { return m_Success; }
		constexpr std::string& GetError() { return m_ErrorMessage; }

		constexpr int Width() { return m_Width; }
		constexpr int Height() { return m_Height; }
		constexpr uint Format() { return m_Format; }

		constexpr int MipmapCount() { return m_MipmapCount; }

		std::vector<DDSMipmap> mipmaps;

	private:
		bool m_Success = false;
		std::string m_ErrorMessage;

		int m_Width = 0;
		int m_Height = 0;
		int m_MipmapCount = 0;

		uint m_Format = 0;
	};
}