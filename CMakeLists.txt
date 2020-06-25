cmake_minimum_required(VERSION 3.7)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
project(mcl)

FIND_PACKAGE(PkgConfig)

find_package(SDL2)
if(SDL2_FOUND)
    # Using an underscore like SDL2_mixer doesn't work
    pkg_check_modules(SDL2mixer SDL2_mixer)
    if(SDL2mixer_FOUND)
        message("Sound is possible. SDL2 and SDL2_mixer found.")
    else()
        message("Sound is possible. SDL2 found but SDL2_mixer not found.")
    endif()
    #pkg_check_modules(SDL2mixer REQUIRED SDL2_mixer)
    #message("----->" ${SDL2mixer_FOUND})
    #message(${SDL2mixer_INCLUDE_DIRS})
    #message(${SDL2mixer_LIBRARIES})
else()
    message("SDL2 not installed.  No sound.")
endif()


set(CURSES_NEED_NCURSES True)
find_package(Curses REQUIRED)

find_package(Perl)
find_package(PerlLibs)
find_package(Python2 COMPONENTS Development)
find_package(Lua)

#message("Curses: " ${CURSES_LIBRARIES})
if(Python2_FOUND)
    option(ENABLE_Python_plugins "Turn on Plugins that depend on python existing" ${Python2_FOUND})
    message("Python plugin: " ${ENABLE_Python_plugins})
endif()

if(PERLLIBS_FOUND)
    include_directories(includes ${PERL_INCLUDE_PATH})
    option(ENABLE_Perl_plugins "Turn on Plugins that depend on perl existing" ${PERLLIBS_FOUND})
    message("Perl plugin: " ${ENABLE_Perl_plugins})
endif()

if(LUA_FOUND)
    option(ENABLE_Lua_plugins "Turn on Plugins that depend on lua existing" ${LUA_FOUND})
    message("Lua plugin: " ${ENABLE_Lua_plugins})
endif()






message( "Main cmakefile Perl version: " ${PERL_VERSION_STRING})
message( "Main cmakefile Python version: "  ${Python2_VERSION})
message( "Main cmakefile Lua version: "  ${LUA_VERSION_STRING})
#find_package(SQLite3 REQUIRED)
#set(CMAKE_VERBOSE_MAKEFILE ON)


set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
    includes/Action.h
    includes/Alias.h
    includes/Bitvalues.h
    includes/Borg.h
    includes/Buffer.h
    includes/Chat.h
    includes/Color.h
    includes/config.h
    includes/Config.h
    includes/Control.h
    includes/cui.h
    includes/Curses.h
    includes/defs.h
    includes/EmbeddedInterpreter.h
    includes/global.h
    includes/Group.h
    includes/Hotkey.h
    includes/InputBox.h
    includes/InputLine.h
    includes/Interpreter.h
    includes/Label.h
    includes/List.h
    includes/mccpDecompress.h
    includes/mcl.h
    includes/MessageBox.h
    includes/MessageWindow.h
    includes/misc.h
    includes/MUD.h
    includes/NullEmbeddedInterpreter.h
    includes/Numbered.h
    includes/Option.h
    includes/OutputWindow.h
    includes/PerlEmbeddedInterpreter.h
    includes/Pipe.h
    includes/Plugin.h
    includes/ProxyWindow.h
    includes/PythonEmbeddedInterpreter.h
    includes/LuaEmbeddedInterpreter.h
    includes/Screen.h
    includes/ScrollbackSearch.h
    includes/Selectable.h
    includes/Selection.h
    includes/Session.h
    includes/Shell.h
    includes/Socket.h
    includes/StaticBuffer.h
    includes/StatusLine.h
    includes/String.h
    includes/TTY.h
    includes/Window.h
  Alias.cc
  Borg.cc
  Buffer.cc
  Chat.cc
  Config.cc
  Curses.cc
  Embedded.cc
  Group.cc
  Hotkey.cc
  InputBox.cc
  InputLine.cc
  Interpreter.cc
  main.cc
  mccpDecompress.c
  misc.cc
  MUD.cc
  Option.cc
  OutputWindow.cc
  Pipe.cc
  Screen.cc
  Selectable.cc
  Selection.cc
  Session.cc
  Shell.cc
  Socket.cc
  StaticBuffer.cc
  StatusLine.cc
  String.cc
  TTY.cc
  Window.cc)




add_executable(mcl ${SOURCE_FILES})
set_target_properties(mcl PROPERTIES LINK_FLAGS "-rdynamic")

target_link_libraries(mcl
        ncurses
        dl
        z
        pthread
        m
        )

if(ENABLE_Python_plugins)
    target_link_libraries(
            mcl
            python2.7
            mpython
    )
endif()
if(ENABLE_Perl_plugins)
    target_link_libraries(
            mcl
            perl
            mperl
    )
endif()
if(ENABLE_Lua_plugins)
    target_link_libraries(
            mcl
            mlua
    )
endif()
add_subdirectory(plugins)