# Simple Compression
Simple compression is a lossless compression algorithm written in c++

It works by grouping repeated bytes into byte * number of times it was repeated.

## Example 
Input:  a a a b b b b b b b b b 

Output: a 3 b 9
