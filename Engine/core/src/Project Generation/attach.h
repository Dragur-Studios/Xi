#pragma once

#include "pch.h"

#include "architecture/application.h"
#include "architecture/game.h"

#include "IO/xenv.h"

#define ENGINE_PATH "engine_path"

#define _EDITOR_(project)if(!XEnv::Load("config.env")) return 1;\
auto path = XEnv::Get(ENGINE_PATH);\
HMODULE launcherDLL = LoadLibraryA((path +"Editor.dll");\
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



#define _PLAYER_(project)if(!XEnv::Load("config.env")) return 1;\
auto path = XEnv::Get(ENGINE_PATH);\
HMODULE launcherDLL = LoadLibraryA((path + "Player.dll");\
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


#define _LAUNCHER_() if(!XEnv::Load("config.env")) return 1;\
auto path = XEnv::Get(ENGINE_PATH);\
HMODULE launcherDLL = LoadLibraryA((path + "Project Launcher.dll").c_str());\
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




