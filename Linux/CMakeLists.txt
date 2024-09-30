cmake_minimum_required(VERSION 3.16)
project(luggage_belts)

add_executable(
    ${PROJECT_NAME}
	src/main.cpp
	src/ConveyorBelt.cpp
	src/ConveyorBeltSimulator.cpp
	src/ConveyorBeltSystem.cpp
	src/Luggage.cpp
	src/MessageBroker.cpp
	src/TimeCounter.cpp
)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED)

target_compile_options(
	${PROJECT_NAME} 
	PRIVATE
		-O3
)

target_include_directories(
	${PROJECT_NAME}
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/include
		${CMAKE_CURRENT_SOURCE_DIR}/msg
)

target_link_libraries(
    ${PROJECT_NAME}
	PRIVATE
        pthread
		ncurses
)