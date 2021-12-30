# Simple Compression
Simple compression is a lossless compression algorithm written in c++

It works by grouping repeated bytes into byte * number of times it was repeated.

### Example 
Input:  a a a b b b b b b b b b 

Output: a 3 b 9

### Compile & Run

    $ g++ -O2 main.cpp -o simple-compression.exe
    
    $ ./simple-compression.exe --help
    Usage: simple_compression <option> INPUT OUTPUTOptions:
        -h,--help               Show this help message
        -c,--compress           Compress INPUT and save to OUTPUT
        -d,--decompress         Decompress INPUT and save to OUTPUT
        INPUT                   Path to input file
        OUTPUT                  Path to output file
