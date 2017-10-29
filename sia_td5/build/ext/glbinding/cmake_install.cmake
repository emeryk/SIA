# Install script for directory: /home/emeric/Master_2/Synthese_Image/sia_td5/ext/glbinding

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "runtime" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/glbinding" TYPE FILE FILES "/home/emeric/Master_2/Synthese_Image/sia_td5/build/ext/glbinding/VERSION")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/glbinding" TYPE FILE FILES "/home/emeric/Master_2/Synthese_Image/sia_td5/ext/glbinding/glbinding-config.cmake")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "runtime" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/glbinding" TYPE FILE FILES "/home/emeric/Master_2/Synthese_Image/sia_td5/ext/glbinding/AUTHORS")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "runtime" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/glbinding" TYPE FILE FILES "/home/emeric/Master_2/Synthese_Image/sia_td5/ext/glbinding/LICENSE")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "runtime" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/glbinding" TYPE FILE FILES "/home/emeric/Master_2/Synthese_Image/sia_td5/ext/glbinding/README.md")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "examples_data" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/glbinding" TYPE DIRECTORY FILES "/home/emeric/Master_2/Synthese_Image/sia_td5/ext/glbinding/data")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/emeric/Master_2/Synthese_Image/sia_td5/build/ext/glbinding/source/cmake_install.cmake")
  include("/home/emeric/Master_2/Synthese_Image/sia_td5/build/ext/glbinding/codegeneration/cmake_install.cmake")
  include("/home/emeric/Master_2/Synthese_Image/sia_td5/build/ext/glbinding/docs/cmake_install.cmake")
  include("/home/emeric/Master_2/Synthese_Image/sia_td5/build/ext/glbinding/deploy/cmake_install.cmake")

endif()

