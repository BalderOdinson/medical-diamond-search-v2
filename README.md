## Medical Diamond Search

Optimized implementation of special variation of diamond search algorithm for motion estimation.

This was based on implementation that I have done during my Project course on university. 
The [original](https://github.com/BalderOdinson/Medical-Diamond-Search) implementation was done in C# and was too slow for real usage. 
The idea was to make optimized solution that can be used in real-time.

### How to build
```
cmake . -Bcmake-build-release -DCMAKE_BUILD_TYPE=Release
cd cmake-build-release && make
```