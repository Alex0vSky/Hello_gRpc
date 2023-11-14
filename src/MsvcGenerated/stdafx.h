// stdafx.h - STanDartApplicationFrameworkX/pch for system headers

#ifdef __clang__
#	pragma clang diagnostic ignored "-Wc++98-compat"
#	pragma clang diagnostic ignored "-Wc++98-compat-pedantic"
#	pragma clang diagnostic ignored "-Wzero-as-null-pointer-constant"
#	pragma clang diagnostic ignored "-Wold-style-cast"
#endif // __clang__

// disable min and max macros
#define NOMINMAX
#ifdef _DEBUG
#	include <crtdbg.h>
#	ifndef D3D_DEBUG_INFO
#		define D3D_DEBUG_INFO
#	endif
#endif
#pragma warning( push )
#pragma warning( disable: 5039 )
#include "framework.h"
#pragma warning( pop )

#pragma comment( lib, "ShlWApi" )

// Include Synaptics SDK headers
//	Search Synaptics SDK in internet -- use query "SynCOMAPIv1_0.zip", found "https://code.google.com/archive/p/aboutc/downloads?page=2", download link "https://storage.googleapis.com/google-code-archive-downloads/v2/code.google.com/aboutc/SynCOMAPIv1_0.zip"
#ifdef __clang__
#	pragma clang diagnostic push
#	pragma clang diagnostic ignored "-Wreserved-id-macro"
#	pragma clang diagnostic ignored "-Wnonportable-system-include-path"
#	pragma clang diagnostic ignored "-Wmicrosoft-enum-forward-reference"
#	pragma clang diagnostic ignored "-Wnon-virtual-dtor"
#	pragma clang diagnostic ignored "-Wmicrosoft-enum-value"
#	pragma clang diagnostic ignored "-Wc++98-compat-pedantic"
#	pragma clang diagnostic ignored "-Wnewline-eof"
#endif // __clang__

#ifndef __INTELLISENSE__
#endif // __INTELLISENSE__

#ifdef __clang__
#	pragma clang diagnostic pop
#endif // __clang__
