#
# Copyright 2021 Mondlied@github.com
#
#    Licensed under the Apache License, Version 2.0 (the "License");
#    you may not use this file except in compliance with the License.
#    You may obtain a copy of the License at
#
#        http://www.apache.org/licenses/LICENSE-2.0
#
#    Unless required by applicable law or agreed to in writing, software
#    distributed under the License is distributed on an "AS IS" BASIS,
#    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#    See the License for the specific language governing permissions and
#    limitations under the License.

cmake_minimum_required(VERSION 3.16)

project(CppSamples)

set(SOURCES)

# function for adding subcomponents
function(cpp_samples_component SOURCE_GROUP)
    cmake_parse_arguments(SAMPLE_COMPONENT "" "DIRECTORY" "" ${ARGN})
    set(SRC_DIR ".")
    set(SOURCES_LOCAL)
    if (DEFINED SAMPLE_COMPONENT_DIRECTORY)
        set(SRC_DIR ${SAMPLE_COMPONENT_DIRECTORY})
    endif()
    
    foreach(_SRC IN LISTS SAMPLE_COMPONENT_UNPARSED_ARGUMENTS)
        list(APPEND SOURCES_LOCAL "${SRC_DIR}/${_SRC}")
    endforeach()
    
    source_group(SOURCE_GROUP FILES ${SOURCES_LOCAL})

    set(SOURCES ${SOURCES} ${SOURCES_LOCAL} PARENT_SCOPE)
endfunction()

cpp_samples_component(Programs DIRECTORY programs
    Program.cpp
    Program.hpp
    Programs.cpp
    Programs.hpp
)

foreach(_DIR IN ITEMS
    collections/linked_list
    variant
)
    include("${_DIR}/sources.cmake")
endforeach()

#create the actual target
add_executable(CppSamples main.cpp ${SOURCES})
set_target_properties(CppSamples PROPERTIES
    CXX_STANDARD 17
)
target_include_directories(CppSamples PRIVATE .)