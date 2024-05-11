# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/Users/Ben/CLionProjects/BasicRender/cmake-build-debug/_deps/rlimgui-src"
  "C:/Users/Ben/CLionProjects/BasicRender/cmake-build-debug/_deps/rlimgui-build"
  "C:/Users/Ben/CLionProjects/BasicRender/cmake-build-debug/_deps/rlimgui-subbuild/rlimgui-populate-prefix"
  "C:/Users/Ben/CLionProjects/BasicRender/cmake-build-debug/_deps/rlimgui-subbuild/rlimgui-populate-prefix/tmp"
  "C:/Users/Ben/CLionProjects/BasicRender/cmake-build-debug/_deps/rlimgui-subbuild/rlimgui-populate-prefix/src/rlimgui-populate-stamp"
  "C:/Users/Ben/CLionProjects/BasicRender/cmake-build-debug/_deps/rlimgui-subbuild/rlimgui-populate-prefix/src"
  "C:/Users/Ben/CLionProjects/BasicRender/cmake-build-debug/_deps/rlimgui-subbuild/rlimgui-populate-prefix/src/rlimgui-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Users/Ben/CLionProjects/BasicRender/cmake-build-debug/_deps/rlimgui-subbuild/rlimgui-populate-prefix/src/rlimgui-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/Users/Ben/CLionProjects/BasicRender/cmake-build-debug/_deps/rlimgui-subbuild/rlimgui-populate-prefix/src/rlimgui-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
