# Install script for directory: /home/ppan/cs3505/libHaru/libharu-libharu-d84867e

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/usr/local")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

# Install shared libraries without execute permission?
IF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  SET(CMAKE_INSTALL_SO_NO_EXE "0")
ENDIF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES
    "/home/ppan/cs3505/libHaru/libharu-libharu-d84867e/include/hpdf.h"
    "/home/ppan/cs3505/libHaru/libharu-libharu-d84867e/include/hpdf_types.h"
    "/home/ppan/cs3505/libHaru/libharu-libharu-d84867e/include/hpdf_consts.h"
    "/home/ppan/cs3505/libHaru/libharu-libharu-d84867e/include/hpdf_version.h"
    "/home/ppan/cs3505/libHaru/libharu-libharu-d84867e/include/hpdf_annotation.h"
    "/home/ppan/cs3505/libHaru/libharu-libharu-d84867e/include/hpdf_catalog.h"
    "/home/ppan/cs3505/libHaru/libharu-libharu-d84867e/include/hpdf_conf.h"
    "/home/ppan/cs3505/libHaru/libharu-libharu-d84867e/include/hpdf_destination.h"
    "/home/ppan/cs3505/libHaru/libharu-libharu-d84867e/include/hpdf_doc.h"
    "/home/ppan/cs3505/libHaru/libharu-libharu-d84867e/include/hpdf_encoder.h"
    "/home/ppan/cs3505/libHaru/libharu-libharu-d84867e/include/hpdf_encrypt.h"
    "/home/ppan/cs3505/libHaru/libharu-libharu-d84867e/include/hpdf_encryptdict.h"
    "/home/ppan/cs3505/libHaru/libharu-libharu-d84867e/include/hpdf_error.h"
    "/home/ppan/cs3505/libHaru/libharu-libharu-d84867e/include/hpdf_ext_gstate.h"
    "/home/ppan/cs3505/libHaru/libharu-libharu-d84867e/include/hpdf_font.h"
    "/home/ppan/cs3505/libHaru/libharu-libharu-d84867e/include/hpdf_fontdef.h"
    "/home/ppan/cs3505/libHaru/libharu-libharu-d84867e/include/hpdf_gstate.h"
    "/home/ppan/cs3505/libHaru/libharu-libharu-d84867e/include/hpdf_image.h"
    "/home/ppan/cs3505/libHaru/libharu-libharu-d84867e/include/hpdf_info.h"
    "/home/ppan/cs3505/libHaru/libharu-libharu-d84867e/include/hpdf_list.h"
    "/home/ppan/cs3505/libHaru/libharu-libharu-d84867e/include/hpdf_mmgr.h"
    "/home/ppan/cs3505/libHaru/libharu-libharu-d84867e/include/hpdf_objects.h"
    "/home/ppan/cs3505/libHaru/libharu-libharu-d84867e/include/hpdf_outline.h"
    "/home/ppan/cs3505/libHaru/libharu-libharu-d84867e/include/hpdf_pages.h"
    "/home/ppan/cs3505/libHaru/libharu-libharu-d84867e/include/hpdf_page_label.h"
    "/home/ppan/cs3505/libHaru/libharu-libharu-d84867e/include/hpdf_streams.h"
    "/home/ppan/cs3505/libHaru/libharu-libharu-d84867e/include/hpdf_u3d.h"
    "/home/ppan/cs3505/libHaru/libharu-libharu-d84867e/include/hpdf_utils.h"
    "/home/ppan/cs3505/libHaru/libharu-libharu-d84867e/include/hpdf_pdfa.h"
    "/home/ppan/cs3505/libHaru/libharu-libharu-d84867e/include/hpdf_3dmeasure.h"
    "/home/ppan/cs3505/libHaru/libharu-libharu-d84867e/include/hpdf_exdata.h"
    "/home/ppan/cs3505/libHaru/libharu-libharu-d84867e/include/hpdf_config.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/." TYPE FILE FILES
    "/home/ppan/cs3505/libHaru/libharu-libharu-d84867e/README"
    "/home/ppan/cs3505/libHaru/libharu-libharu-d84867e/CHANGES"
    "/home/ppan/cs3505/libHaru/libharu-libharu-d84867e/INSTALL"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/." TYPE DIRECTORY FILES "/home/ppan/cs3505/libHaru/libharu-libharu-d84867e/if")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  INCLUDE("/home/ppan/cs3505/libHaru/libharu-libharu-d84867e/src/cmake_install.cmake")
  INCLUDE("/home/ppan/cs3505/libHaru/libharu-libharu-d84867e/demo/cmake_install.cmake")

ENDIF(NOT CMAKE_INSTALL_LOCAL_ONLY)

IF(CMAKE_INSTALL_COMPONENT)
  SET(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
ELSE(CMAKE_INSTALL_COMPONENT)
  SET(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
ENDIF(CMAKE_INSTALL_COMPONENT)

FILE(WRITE "/home/ppan/cs3505/libHaru/libharu-libharu-d84867e/${CMAKE_INSTALL_MANIFEST}" "")
FOREACH(file ${CMAKE_INSTALL_MANIFEST_FILES})
  FILE(APPEND "/home/ppan/cs3505/libHaru/libharu-libharu-d84867e/${CMAKE_INSTALL_MANIFEST}" "${file}\n")
ENDFOREACH(file)
