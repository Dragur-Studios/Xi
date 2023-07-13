#pragma once

#include "pch.h"

#include "architecture/application.h"
#include "architecture/game.h"

/// DLL
#define _Z 0
#define _D 1

#ifdef _DEBUG
#if _Z
#define RUNTIME_DLL_PATH "Z:/Dev/Xi/Build/Runtime/"
#elif _D
#define RUNTIME_DLL_PATH "D:/Dev/Draugr Studios/Xi/Build/Runtime/"
#endif
#else
#define EDITOR_DLL_PATH ""
#endif


#define ATTACH_EDITOR(project) HMODULE editorDLL = LoadLibraryA(RUNTIME_DLL_PATH "Editor.dll");\
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



#define ATTACH_PLAYER(project) HMODULE playerDLL = LoadLibraryA(RUNTIME_DLL_PATH "Player.dll");\
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


#define ATTACK_LAUNCHER() HMODULE launcherDLL = LoadLibraryA(RUNTIME_DLL_PATH "Project Launcher.dll");\
if(launcherDLL == nullptr)\
{\
Debug::Log("XiLauncher Could not be found? are you sure you installed the assymbley");\
return 1;\
}\
XiApplicationFunc createLauncher = (XiApplicationFunc)GetProcAddress(launcherDLL, "CreateProjectLauncher");\
if(createLauncher == nullptr){\
Debug::Log("CreateProjectLauncher(fun) could not be found!");\
return 1;\
}\
iApplication* launcher = createLauncher();\
if(launcher == nullptr){\
Debug::Log("Launcher is Null!");\
return 1;\
}\
Debug::Log("Launcher Created Succssfully!");\
launcher->OnInitilize(); \
launcher->OnTick(); \
launcher->OnShutdown(); \




