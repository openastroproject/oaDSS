/*
 * This file should eventually go away when all the workarounds in it
 * are resolved
 */

#pragma once

#include <stdlib.h>
#include <cstdint>

#define	_T(x)			x

#define	__int8		int8_t
#define	__int64		int64_t

#define	MAXWORD				655535

typedef	bool					BOOL;
typedef	char					CHAR;
typedef	int16_t				DWORD;
typedef	int64_t				LONG;
typedef	uint64_t*			ULONG_PTR;
typedef	char					TCHAR;
typedef const char*		LPCSTR;
typedef const char*		LPCTSTR;

typedef struct _rect {
	long	left;
	long	top;
	long	right;
	long	bottom;
} RECT;

typedef struct _RGBQUAD {
  uint8_t rgbBlue;
  uint8_t rgbGreen;
  uint8_t rgbRed;
  uint8_t rgbReserved;
} RGBQUAD;

typedef struct _BITMAP {
	int			bmWidth;
	int			bmHeight;
} BITMAP;

typedef struct _BITMAPHEADER {
	int			biSize;
	int			biWidth;
	int			biHeight;
	int			biPlanes;
	int			biBitCount;
	int			biCompression;
	int			biSizeImage;
	int			biXPelsPerMeter;
	int			biYPelsPerMeter;
	int			biClrUsed;
	int			biClrImportant;
} BITMAPHEADER;

typedef struct _BITMAPINFO {
	int						bmWidth;
	int						bmHeight;
	BITMAPHEADER	bmiHeader;
} BITMAPINFO;

class	CWnd {
};


class CWinApp {
};

typedef void*						HWND;
typedef void*						HDC;
typedef void*						HGLOBAL;

typedef void*						HBITMAP;
typedef RECT*						LPRECT;
typedef RECT						tagRECT;
typedef RGBQUAD*				LPRGBQUAD;

extern HDC							GetDC ( void* );
extern void							DeleteObject ( HBITMAP );
extern HBITMAP					CreateDIBSection( HDC, BITMAPINFO*, int, void**, void*,
														int );
extern HDC							ReleaseDC ( void*, void* );


#define	CF_BITMAP				1
#define	CF_DIB					2

#define BI_RGB					1

#define GMEM_MOVEABLE		1

#define SRCCOPY					1
