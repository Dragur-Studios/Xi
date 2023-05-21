#pragma once

#include "pch.h"

#include "architecture/application.h"
#include "architecture/game.h"

/// DLL

#define ATTACH_EDITOR(gameName) HMODULE editorDLL = LoadLibraryA("Runtime/Editor.dll");\
if (editorDLL == nullptr)\
{\
Debug::Log("Editor DLL has not been loaded!"); \
return 1;\
}\
XiApplication createEditor = (XiApplication)GetProcAddress(editorDLL, "CreateEditor"); \
if (createEditor == nullptr)\
{\
Debug::Log("Editor Create Function Pointer Could Not Be found!!");\
return 1;\
}\
iApplication* editor = createEditor();\
if (editor == nullptr)\
{\
Debug::Log("Editor Creation Failed!");\
return 1;\
}\
Debug::Log("Editor Created Successfully.");\
ATTACH_GAME(editor, gameName); \
editor->OnInitilize();\
editor->OnTick();\
editor->OnShutdown();\



#define ATTACH_PLAYER(gameName) HMODULE playerDLL = LoadLibraryA("Runtime/Player.dll");\
if (playerDLL == nullptr)\
{\
Debug::Log("Player DLL has not been loaded!"); \
return 1;\
}\
XiApplication createPlayer = (XiApplication)GetProcAddress(playerDLL, "CreatePlayer"); \
if (createPlayer == nullptr)\
{\
Debug::Log("Player Create Function Pointer Could Not Be found!!");\
return 1;\
}\
iApplication* player = createPlayer();\
if (player == nullptr)\
{\
Debug::Log("Player Creation Failed!");\
return 1;\
}\
Debug::Log("Player Created Successfully.");\
ATTACH_GAME(player, gameName)\
player->OnInitilize();\
player->OnTick();\
player->OnShutdown();\


#define ATTACH_GAME(iapp, gameName) HMODULE gameDLL = LoadLibraryA((gameName->GetName() + ".dll").c_str()); \
if(gameDLL == nullptr){ \
Debug::Log("Game Could Not Be Loaded"); \
return -1;\
}\
XiGame createGamefn = (XiGame)GetProcAddress(gameDLL, "CreateGame");\
if(createGamefn == nullptr)\
{\
Debug::Log("Create Game Function Not Found"); \
return -2;\
}\
iGame* game = createGamefn();\
if(game == nullptr)\
{\
Debug::Log("Game Creation Failed!"); \
return -2;\
}\
Debug::Log("Game Creation Succeess!"); \
iapp->Load(game);\


