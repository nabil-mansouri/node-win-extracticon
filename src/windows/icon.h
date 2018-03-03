#include <windows.h>
#include <iostream>
#include <commctrl.h>
#include <commoncontrols.h>
#include <shlguid.h>
#include <olectl.h>
#include <wchar.h>

typedef struct
{
    WORD idReserved; // must be 0
    WORD idType;     // 1 = ICON, 2 = CURSOR
    WORD idCount;    // number of images (and ICONDIRs)

    // ICONDIR [1...n]
    // ICONIMAGE [1...n]

} ICONHEADER;

//
// An array of ICONDIRs immediately follow the ICONHEADER
//
typedef struct
{
    BYTE bWidth;
    BYTE bHeight;
    BYTE bColorCount;
    BYTE bReserved;
    WORD wPlanes;   // for cursors, this field = wXHotSpot
    WORD wBitCount; // for cursors, this field = wYHotSpot
    DWORD dwBytesInRes;
    DWORD dwImageOffset; // file-offset to the start of ICONIMAGE

} ICONDIR;

//
// After the ICONDIRs follow the ICONIMAGE structures -
// consisting of a BITMAPINFOHEADER, (optional) RGBQUAD array, then
// the color and mask bitmap bits (all packed together
//
typedef struct
{
    BITMAPINFOHEADER biHeader; // header for color bitmap (no mask header)
    //RGBQUAD rgbColors[1...n];
    //BYTE bXOR[1]; // DIB bits for color bitmap
    //BYTE bAND[1]; // DIB bits for mask bitmap

} ICONIMAGE;

static UINT WriteIconHeader(HANDLE hFile, int nImages);

static UINT NumBitmapBytes(BITMAP *pBitmap);

static UINT WriteIconImageHeader(HANDLE hFile, BITMAP *pbmpColor, BITMAP *pbmpMask);

static BOOL GetIconBitmapInfo(HICON hIcon, ICONINFO *pIconInfo, BITMAP *pbmpColor, BITMAP *pbmpMask);


static UINT WriteIconDirectoryEntry(HANDLE hFile, int nIdx, HICON hIcon, UINT nImageOffset);

static UINT WriteIconData(HANDLE hFile, HBITMAP hBitmap);

BOOL SaveIcon(TCHAR *szIconFile, HICON hIcon[], int nNumIcons);