#include <iostream>
#include <fstream>

void Compress(std::string& inputFileName, std::string& outputFileName)
{
    std::fstream input;
    std::ofstream output;
    input.open(inputFileName, std::ios::in | std::ios::binary | std::ios::ate);
    output.open(outputFileName, std::ios::out | std::ios::binary);

    if (!input.is_open())
    {
        std::cout << "Error while opening input file.";
        return;
    }
    if (!output.is_open())
    {
        std::cout << "Error while opening output file.";
        return;
    }
    else
    {
        std::streampos size;
        // because we used std::ios::ate as mode parameter, it sets the initial position (get) at the end of the file
        size = input.tellg();
        std::cout << "original size is: " << (u_int64_t)size << " bytes.\n";

        // keep reading same character until it changes, then write the character then its count
        unsigned char previous,current, count = 1;
        input.seekg(0);
        previous = input.get();
        for (u_int64_t i = 1; i <= size; i++)
        {
            input.seekg(i);
            current = input.get();
            //if count is bigger than 1 byte then write the target byte with 255 size, then start again with count = 0
            if (current != previous || (u_int8_t)count == UINT8_MAX)
            {
                output.write((const char*)&previous,1);
                output.write((const char*)&count, 1);
                previous = current;
                count = 1;
            }
            else
                count++;
        }
        std::cout << "compressed size is: " << (u_int64_t)output.tellp() << " bytes.\n"
                  << "space saving is: " << (1 -(float)output.tellp() / (float)size) * 100 << "%" << std::endl;
        input.close();
        output.close();
    }
}
void Decompress(std::string& inputFileName, std::string& outputFileName)
{
    std::ifstream compressed;
    std::ofstream decompressed;
    compressed.open(inputFileName, std::ios::in | std::ios::binary | std::ios::ate);
    decompressed.open(outputFileName, std::ios::out | std::ios::binary);

    if (!compressed.is_open())
    {
        std::cout << "Error while opening input file.";
        return;
    }
    if (!decompressed.is_open())
    {
        std::cout << "Error while opening output file.";
        return;
    }
    else
    {
        unsigned char byte, count;
        u_int64_t size = compressed.tellg();

        std::cout << "compressed size is: " << (u_int64_t)size << " bytes.\n";
        for (u_int64_t i = 0; i < size; i += 2) {
            compressed.seekg(i);
            byte = compressed.get();
            compressed.seekg(i + 1);
            count = compressed.get();
            for (u_int8_t j = 0; j < count; j++)
            {
                decompressed.write((const char*)&byte, 1);
            }
        }
        std::cout << "decompressed size is: " << (u_int64_t)decompressed.tellp() << " bytes.\n" << std::endl;
        compressed.close();
        decompressed.close();
    }
}
static void show_usage()
{
    std::cout << "Usage: simple_compression <option> INPUT OUTPUT"
              << "Options:\n"
              << "\t-h,--help        \tShow this help message\n"
              << "\t-c,--compress    \tCompress INPUT and save to OUTPUT\n"
              << "\t-d,--decompress  \tDecompress INPUT and save to OUTPUT\n"
              << "\tINPUT            \tPath to input file\n"
              << "\tOUTPUT           \tPath to output file\n"
              << std::endl;
}
int main(int argc, char* argv[])
{
    if (argc != 4 || ((std::string)argv[1] != "-c" && (std::string)argv[1] != "--decompress" &&
                      (std::string)argv[1] != "-d") && (std::string)argv[1] != "--decompress" ||
                      (std::string)argv[1] == "-h" || (std::string)argv[1] == "--help")
    {
        show_usage();
        return 0;
    }
    else
    {
        std::string inputFile = argv[2], outputFile = argv[3];
        if ((std::string)argv[1] == "-c" || (std::string)argv[1] == "--compress")
            Compress(inputFile, outputFile);
        else
            Decompress(inputFile, outputFile);
    }
    return 0;
}