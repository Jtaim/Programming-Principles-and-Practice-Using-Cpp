#pragma once

#define WIN32
#define WIN32_LEAN_AND_MEAN
//#define NOGDICAPMASKS
//#define NOSYSMETRICS
//#define NOMENUS
//#define NOICONS
//#define NOSYSCOMMANDS
//#define NORASTEROPS
//#define OEMRESOURCE
//#define NOATOM
//#define NOCLIPBOARD
//#define NOCOLOR
//#define NOCTLMGR
//#define NODRAWTEXT
//#define NOKERNEL
//#define NONLS
//#define NOMEMMGR
//#define NOMETAFILE
#define NOMINMAX
//#define NOOPENFILE
//#define NOSCROLL
//#define NOSERVICE
//#define NOSOUND
//#define NOTEXTMETRIC
//#define NOWH
//#define NOCOMM
//#define NOKANJI
//#define NOHELP
//#define NOPROFILER
//#define NODEFERWINDOWPOS
//#define NOMCX
//#define NORPC
//#define NOPROXYSTUB
//#define NOIMAGE
//#define NOTAPE
//#define STRICT

#include <cstdlib>              // for exit(0)

#pragma warning(push)
#pragma warning(disable : 4244) // 'argument' : conversion from 'type1' to 'type2', possible loss of data
#pragma warning(disable : 4458) // declaration of 'identifier' hides class member
#pragma warning(disable : 4100) // 'identifier' : unreferenced formal parameter

#include "FL/Fl.H"
#include "FL/Fl_Box.H"
#include "FL/Fl_Window.H" 
#include "FL/Fl_Button.H" 
#include "FL/Fl_Input.H" 
#include "FL/Fl_Output.H" 
#include "FL/fl_draw.H"
#include "FL/Enumerations.H"
#include "FL/Fl_Group.H"

#include "Fl/Fl_JPEG_Image.H"
#include "Fl/Fl_GIF_Image.H"

#pragma warning( pop )
