
set(PROJECT_NAME example_11-coc)

set(PROJECT_MIDDLE_DIR example)

set(SRCROOT ${CMAKE_ROOT_DIR}/${PROJECT_MIDDLE_DIR}/${PROJECT_NAME})

set(DIR_SRCS 
	${SRCROOT}/main.cpp
	${SRCROOT}/coc.h
	${SRCROOT}/coc.cpp
)
			
Add_Definitions(
    -D_HAS_ITERATOR_DEBUGGING=0
    -DBGFX_CONFIG_RENDERER_METAL=1
)

sxb_add_executable(
				${PROJECT_NAME} 
				FOLDER "example" 
				SOURCES ${DIR_SRCS}
)
