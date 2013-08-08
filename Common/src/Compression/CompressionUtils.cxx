#include <zlib.h>
#include "Utils/Guards.hxx"
#include "Compression/CompressionUtils.hxx"

namespace Core4
{
    //--------------------------------------------------------------------------------------------------------------------------
    void CompressionUtils::compress(const std::vector<char> & source, std::vector<char> & dest)
    {
        dest.resize(compressBound(source.size()));
        uLongf destLen(dest.size());
        int res = compress2((Bytef*)&dest[0], &destLen, (Bytef*)&source[0], source.size(), Z_DEFAULT_COMPRESSION);
        CORE4_CHECK(res != Z_MEM_ERROR, "Not enough memory")
        CORE4_CHECK(res != Z_BUF_ERROR, "Not enough room in the output buffer");
        CORE4_CHECK(res == Z_OK,        "Compression error");
        dest.resize(destLen);
    }

    //--------------------------------------------------------------------------------------------------------------------------
    void CompressionUtils::decompress(const std::vector<char> & source, std::vector<char> & dest, size_t unpackedSize)
    {
        dest.resize(unpackedSize);
        uLongf destLen(unpackedSize);
        int res = uncompress((Bytef*)&dest[0], &destLen, (Bytef*)&source[0], source.size());
        CORE4_CHECK(res != Z_MEM_ERROR,  "Not enough memory");
        CORE4_CHECK(res != Z_BUF_ERROR,  "Not enough room in the output buffer");
        CORE4_CHECK(res != Z_DATA_ERROR, "Data error");
        CORE4_CHECK(res == Z_OK,         "Decompression error");
    }
} // namespace C4
