# Simple Compression

This is a losseless compression algorithm written in C++

It works by grouping repeated bytes into byte * number of times it was repeated.

### Compile & Run

    $ g++ -O2 main.cpp -o simple-compression.exe
    
    $ ./simple-compression.exe --help
    Usage: simple_compression <option> INPUT OUTPUTOptions:
        -h,--help               Show this help message
        -c,--compress           Compress INPUT and save to OUTPUT
        -d,--decompress         Decompress INPUT and save to OUTPUT
        INPUT                   Path to input file
        OUTPUT                  Path to output file
