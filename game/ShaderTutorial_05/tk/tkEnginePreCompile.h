// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

//#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
#define USE_VSM		//定義でVSMが有効。

#define USE_ORTHO_PROJECTION

/*!
* @brief	定義でDirectX9で動作
*/
#define TK_PLATFORM_DX9

#if defined( TK_PLATFORM_DX9 )
#include <windows.h>
#endif // #if defined( TK_PLATFORM_DX9 )
#include <memory>
#include <XInput.h> // XInput API
#pragma comment(lib, "Xinput.lib")
#ifdef _DEBUG
#include <DxErr.h>
#pragma comment(lib, "dxerr.lib")
#endif
#include <list>
#include <vector>
#include <map>
#include <algorithm>
#include <xaudio2.h>
#include <x3daudio.h>
#include <xaudio2fx.h>
#include <mmiscapi.h>
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "X3daudio.lib")

#include "typedef.h"
#include "tkAssert.h"
#include "tkNoncopyable.h"
#include "tkLog.h"
#include "..\pad\KeyInput.h"




// TODO: reference additional headers your program requires here
