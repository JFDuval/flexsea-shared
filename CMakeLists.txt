# logger and utilities has plan specific code
if(FLEXSEA_TYPE STREQUAL PLAN)
	file(GLOB_RECURSE FLEX_SHARED_SRCS
		${CMAKE_CURRENT_SOURCE_DIR}/i2t/src/*.c
		${CMAKE_CURRENT_SOURCE_DIR}/logger/src/*.c
		${CMAKE_CURRENT_SOURCE_DIR}/utilities/src/*.c
	)
# on manage we only want to use the device spec file for the current project
else()
	file(GLOB_RECURSE FLEX_SHARED_SRCS
		${CMAKE_CURRENT_SOURCE_DIR}/i2t/src/*.c
	)
endif()

set(FLEX_SHARED_SRCS
	${FLEX_SHARED_SRCS}
	PARENT_SCOPE
)
