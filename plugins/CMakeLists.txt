cmake_minimum_required(VERSION 3.7)


set(CMAKE_VERBOSE_MAKEFILE ON)
set(perlSrc PerlEmbeddedInterpreter.cc)
set(pythonSrc PythonEmbeddedInterpreter.cc)

FIND_PACKAGE(PkgConfig)
include_directories (${PKGS_INCLUDE_DIRS})
include_directories(../includes)
include_directories(/usr/lib/x86_64-linux-gnu/perl/5.26.1/CORE/)
include_directories(/usr/include/python2.7/)

add_library(mperl SHARED ${perlSrc})
add_library(mpython SHARED ${pythonSrc})

set_target_properties(mperl PROPERTIES PREFIX "")
set_target_properties(mpython PROPERTIES PREFIX "")

# perl -MExtUtils::Embed -e ldopts
set_target_properties(mperl PROPERTIES LINK_FLAGS "-s -rdynamic -shared -Wl,-E  -fstack-protector-strong -L/usr/local/lib  -L/usr/lib/x86_64-linux-gnu/ -lperl -ldl -lm -lpthread -lc -lcrypt")
target_link_libraries(mperl
        perl)

add_custom_command(TARGET mperl POST_BUILD
        COMMAND "${CMAKE_COMMAND}" -E copy
        "$<TARGET_FILE:mperl>"
        "$ENV{HOME}/.mcl/plugins/perl.so"
        COMMENT "Copying perl.so to output directory")

target_link_libraries(mpython
        python2.7)

add_custom_command(TARGET mpython POST_BUILD
        COMMAND "${CMAKE_COMMAND}" -E copy
        "$<TARGET_FILE:mpython>"
        "$ENV{HOME}/.mcl/plugins/python.so"
        COMMENT "Copying to python.so output directory")