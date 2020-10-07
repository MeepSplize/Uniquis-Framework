#pragma once

#ifdef _DEBUG

#define DEBUG_ONLY(x) do { x } while(false)

#define RELEASE_ONLY(x) do { } while(false)

#else

#define DEBUG_ONLY(x) do { } while(false)

#define RELEASE_ONLY(x) do { x } while(false)

#endif

#define VS_PATH L"res\\Shaders\\Vertex Shaders\\"
#define GS_PATH L"res\\Shaders\\Geometry Shaders\\"
#define PS_PATH L"res\\Shaders\\Pixel Shaders\\"

#define FONT_PATH    L"res\\Fonts\\"
#define DEFAULT_FONT L"Calibri.ttf"

#define DEBUG_FREETYPE(x) if (x) { __debugbreak(); }