
set(PROJECT_NAME eg_ios_00-HelloWorld)

set(SRCROOT ${CMAKE_ROOT_DIR}/example/eg_ios_00-HelloWorld)

set(DIR_SRCS 
	${SRCROOT}/main.mm
	${SRCROOT}/logo.h
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
