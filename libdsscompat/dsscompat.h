#pragma once

#include <cstdlib>

typedef uint32_t COLORREF;

#define RGB(r,g,b) ((( int ( b ) & 0xff ) << 16 | ( int ( g ) & 0xff ) << 8 ) | ( int ( r ) & 0xff ))

inline uint8_t GetRValue ( const COLORREF c ) { return ( c & 0xff ); }
inline uint8_t GetGValue ( const COLORREF c ) { return (( c >> 8 ) & 0xff ); }
inline uint8_t GetBValue ( const COLORREF c ) { return (( c >> 16 ) & 0xff ); }
