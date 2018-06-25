//-----------------------------------------------------------------------------------
//
//	COLORREFs definitions
//
//	Anton M. Krivtsov
//
//	16.03.2000
//	04.03.2006
//
//-----------------------------------------------------------------------------------

#ifndef __colors_H__
#define __colors_H__

//----------------------------------------------------------------

typedef unsigned long COLORREF;

//#define RGB(r, g ,b)  ((DWORD) (((BYTE) (r) | ((WORD) (g) << 8)) | (((DWORD) (BYTE) (b)) << 16))) 
//#define RGB(r, g ,b)  ((__int32) (((__int8) (r) | ((__int16) (g) << 8)) | (((__int32) (__int8) (b)) << 16))) 
#define RGB(r, g ,b) (r + 256 * g + 65536 * b) 

//----------------------------------------------------------------

static const int C0		=   0;
static const int C1		=  64;
static const int C2		= 128;
static const int C3		= 192;
static const int C4		= 255;

//static const unsigned long 
COLORREF BLACK		= RGB(C0, C0, C0);
//static const unsigned long 
COLORREF WHITE		= RGB(C4, C4, C4);

 
COLORREF WHITE_	= RGB(254, 254, 254);
 COLORREF _BLACK	= RGB(1, 1, 1);

 COLORREF RED		= RGB(C4, C0, C0);
  COLORREF GREEN		= RGB(C0, C4, C0);
  COLORREF BLUE		= RGB(C0, C0, C4);

COLORREF RED_		= RGB(C2, C0, C0);
 COLORREF GREEN_	= RGB(C0, C2, C0);
 COLORREF BLUE_		= RGB(C0, C0, C2);

 COLORREF RED__		= RGB(C1, C0, C0);
 COLORREF GREEN__	= RGB(C0, C1, C0);
 COLORREF BLUE__	= RGB(C0, C0, C1);

 COLORREF _RED		= RGB(C4, C2, C2);
 COLORREF _GREEN	= RGB(C2, C4, C2);
 COLORREF _BLUE		= RGB(C2, C2, C4);

 COLORREF __RED		= RGB(C4, C3, C3);
 COLORREF __GREEN	= RGB(C3, C4, C3);
 COLORREF __BLUE	= RGB(C3, C3, C4);

 COLORREF CYAN		= RGB(C0, C4, C4);
 COLORREF MAGENTA	= RGB(C4, C0, C4);
 COLORREF YELLOW	= RGB(C4, C4, C0);

 COLORREF CYAN_		= RGB(C0, C2, C2);
 COLORREF MAGENTA_	= RGB(C2, C0, C2);
 COLORREF YELLOW_	= RGB(C2, C2, C0);

 COLORREF CYAN__	= RGB(C0, C1, C1);
 COLORREF MAGENTA__ = RGB(C1, C0, C1);
 COLORREF YELLOW__	= RGB(C1, C1, C0);

 COLORREF _CYAN		= RGB(C2, C4, C4);
 COLORREF _MAGENTA	= RGB(C4, C2, C4);
 COLORREF _YELLOW	= RGB(C4, C4, C2);

 COLORREF __CYAN	= RGB(C3, C4, C4);
 COLORREF __MAGENTA	= RGB(C4, C3, C4);
 COLORREF __YELLOW	= RGB(C4, C4, C3);

 COLORREF __GREY	= RGB(240, 240, 240);
 COLORREF _GREY		= RGB(224, 224, 224);
 COLORREF GREY		= RGB(C3, C3, C3);
 COLORREF GREY_		= RGB(C2, C2, C2);
 COLORREF GREY__	= RGB(C1, C1, C1);

 COLORREF PALE_GREEN	= RGB(192, 220, 192);
 COLORREF LIGHT_BLUE	= RGB(166, 202, 240);
 COLORREF OFF_WHITE		= RGB(255, 251, 240);
 COLORREF MEDIUM_GREY	= RGB(160, 160, 164);

//#define		 Grey(c)  RGB(c,  c,  c)

//----------------------------------------------------------------

#endif //__colors_H__
