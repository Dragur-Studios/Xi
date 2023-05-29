#pragma once

#include "pch.h"

#include "architecture/application.h"
#include "architecture/game.h"

/// DLL

#define ATTACH_EDITOR(project) HMODULE editorDLL = LoadLibraryA("Z:/Dev/Xi/Build/Runtime/Editor.dll");\
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
ATTACH_GAME(editor, project); \
editor->OnInitilize();\
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
ATTACH_GAME(player, project)\
player->OnInitilize();\
player->OnTick();\
player->OnShutdown();\


#define ATTACH_GAME(iapp, project) \
iapp->Load(project);\


