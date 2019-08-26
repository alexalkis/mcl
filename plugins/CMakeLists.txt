cmake_minimum_required(VERSION 3.7)


set(CMAKE_VERBOSE_MAKEFILE ON)
set(perlSrc PerlEmbeddedInterpreter.cc)
set(pythonSrc PythonEmbeddedInterpreter.cc)

FIND_PACKAGE(PkgConfig)
include_directories (${PKGS_INCLUDE_DIRS})
include_directories(../includes ${Python2_INCLUDE_DIRS})


add_library(mpython SHARED ${pythonSrc})
add_library(mperl SHARED ${perlSrc})

#message( "What?"  ${Python_LIBRARIES})

set_target_properties(mperl PROPERTIES PREFIX "")
set_target_properties(mpython PROPERTIES PREFIX "")

execute_process(COMMAND ${PERL_EXECUTABLE} -MExtUtils::Embed -e ldopts OUTPUT_VARIABLE PERL_LINKER_FLAGS OUTPUT_STRIP_TRAILING_WHITESPACE)
message("perl-link-variable: " ${PERL_LINKER_FLAGS})
message("perl-variable: " ${PERL_LIBRARY})
# perl -MExtUtils::Embed -e ldopts
#set_target_properties(mperl PROPERTIES LINK_FLAGS "-s -rdynamic -shared -Wl,-E  -fstack-protector-strong -L/usr/local/lib  -L/usr/lib/x86_64-linux-gnu/ -lperl -ldl -lm -lpthread -lc -lcrypt")
set_target_properties(mperl PROPERTIES LINK_FLAGS "-s -rdynamic -shared ${PERL_LINKER_FLAGS}")
target_link_libraries(mperl ${PERL_LIBRARY})



add_custom_command(TARGET mperl POST_BUILD
        COMMAND "${CMAKE_COMMAND}" -E copy
        "$<TARGET_FILE:mperl>"
        "$ENV{HOME}/.mcl/plugins/perl.so"
        COMMENT "Copying perl.so to output directory")

target_link_libraries(mpython
        ${Python_LIBRARIES})

add_custom_command(TARGET mpython POST_BUILD
        COMMAND "${CMAKE_COMMAND}" -E copy
        "$<TARGET_FILE:mpython>"
        "$ENV{HOME}/.mcl/plugins/python.so"
        COMMENT "Copying to python.so output directory")