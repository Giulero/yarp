MACRO(YarpTag)

SET(OS_TAG linux)
IF (WIN32)
	SET(OS_TAG winnt)
ENDIF (WIN32)

ENDMACRO(YarpTag)

YarpTag()

