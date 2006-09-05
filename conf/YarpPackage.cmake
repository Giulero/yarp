#
# Packing stuff
#
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Yet Another Robot Platform")
SET(CPACK_PACKAGE_NAME "yarp")
SET(CPACK_PACKAGE_VENDOR "YARP")
SET(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/README")
INCLUDE(YarpVersion)
SET(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/COPYING")
SET(CPACK_SOURCE_PACKAGE_FILE_NAME
  "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}")


#  if you are making debian packages, this is useful, but not otherwise
#CONFIGURE_FILE(${CMAKE_SOURCE_DIR}/conf/control.in
#               ${CMAKE_BINARY_DIR}/DEBIAN/control @ONLY IMMEDIATE)
#INSTALL_FILES(/doc/DEBIAN FILES ${CMAKE_BINARY_DIR}/DEBIAN/control)

IF(EXISTS "${CMAKE_ROOT}/Modules/CPack.cmake")

#  if you are trying to distribute, this is useful, but not otherwise
#  IF (WIN32 AND NOT CYGWIN)
#    INCLUDE(YarpInstallRequiredSystemLibraries)
#    INSTALL_FILES(/bin .dll ${ACE_LIBRARY} ${ACE_DEBUG_LIBRARY})
#    # just in case it is needed and not present
#    INSTALL_FILES(/bin FILES ${CMAKE_SOURCE_DIR}/conf/Microsoft.VC80.CRT.manifest)
#  ENDIF (WIN32 AND NOT CYGWIN)

  SET(CPACK_PACKAGE_EXECUTABLES "yarp" "yarp")
  INCLUDE(CPack)


ENDIF(EXISTS "${CMAKE_ROOT}/Modules/CPack.cmake")
