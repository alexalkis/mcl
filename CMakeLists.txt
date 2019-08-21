cmake_minimum_required(VERSION 3.7)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

#find_package(SQLite3 REQUIRED)
#set(CMAKE_VERBOSE_MAKEFILE ON)

project(mcl)
set(CMAKE_CXX_STANDARD 11)
include_directories(includes)
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
set_target_properties(mcl PROPERTIES LINK_FLAGS "-s -rdynamic")

target_link_libraries(mcl
        ncurses
        dl
        z
        pthread
        m
        perl
        python2.7
        mperl
        mpython
        )

add_subdirectory(plugins)