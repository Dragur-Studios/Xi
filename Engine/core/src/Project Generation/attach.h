#pragma once

#include "pch.h"

#include "architecture/application.h"
#include "architecture/game.h"

/// DLL
#define _Z 1
#define _D 0

#ifdef _DEBUG
#if _Z
#define EDITOR_DLL_PATH "Z:/Dev/Xi/Build/Runtime/Editor.dll"
#elif _D
#define EDITOR_DLL_PATH "D:/Dev/Draugr Studios/Xi/Build/Runtime/Editor.dll"
#endif
#else
#define EDITOR_DLL_PATH "Editor.dll"
#endif


#define ATTACH_EDITOR(project) HMODULE editorDLL = LoadLibraryA(EDITOR_DLL_PATH);\
if (editorDLL == nullptr)\
{\
Debug::Log("Editor DLL has not been loaded!"); \
return 1;\
}\
XiGameApplicationFunc createEditor = (XiGameApplicationFunc)GetProcAddress(editorDLL, "CreateEditor"); \
if (createEditor == nullptr)\
{\
Debug::Log("Editor Create Function Pointer Could Not Be found!!");\
return 1;\
}\
iGameApplication* editor = createEditor();\
if (editor == nullptr)\
{\
Debug::Log("Editor Creation Failed!");\
return 1;\
}\
Debug::Log("Editor Created Successfully.");\
editor->OnInitilize(project);\
editor->OnTick();\
editor->OnShutdown();\



#define ATTACH_PLAYER(project) HMODULE playerDLL = LoadLibraryA("Runtime/Player.dll");\
if (playerDLL == nullptr)\
{\
Debug::Log("Player DLL has not been loaded!"); \
return 1;\
}\
XiGameApplicationFunc createPlayer = (XiGameApplicationFunc)GetProcAddress(playerDLL, "CreatePlayer"); \
if (createPlayer == nullptr)\
{\
Debug::Log("Player Create Function Pointer Could Not Be found!!");\
return 1;\
}\
iGameApplication* player = createPlayer();\
if (player == nullptr)\
{\
Debug::Log("Player Creation Failed!");\
return 1;\
}\
Debug::Log("Player Created Successfully.");\
player->OnInitilize(project);\
player->OnTick();\
player->OnShutdown();\




