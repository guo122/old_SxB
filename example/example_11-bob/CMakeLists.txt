
set(PROJECT_NAME example_11-bob)

set(SRCROOT ${CMAKE_ROOT_DIR}/example/example_11-bob)

set(DIR_SRCS 
	${SRCROOT}/main.cpp
	${SRCROOT}/bob.h
	${SRCROOT}/bob.cpp
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
