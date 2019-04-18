cmake_minimum_required(VERSION 3.5)

# Project Name
PROJECT(generator)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

include_directories (
../include  
)

add_executable(${PROJECT_NAME} ../src/generator.cpp ../src/ArrayList.cpp ../src/Point.cpp ../src/boxGenerator.cpp ../src/coneGenerator.cpp ../src/toFile.cpp ../src/planeGenerator.cpp ../src/sphereGenerator.cpp )

if  (WIN32)

	set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
	
endif(WIN32)






