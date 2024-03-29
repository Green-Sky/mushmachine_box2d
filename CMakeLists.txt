cmake_minimum_required(VERSION 3.9 FATAL_ERROR)

project(mm_box2d CXX C)

set(BOX2D_BUILD_UNIT_TESTS OFF CACHE INTERNAL "")
set(BOX2D_BUILD_TESTBED OFF CACHE INTERNAL "")
set(BOX2D_BUILD_DOCS OFF CACHE INTERNAL "")
add_subdirectory("./box2d")

##############################

add_library(mm_box2d INTERFACE
	#./src/mm_box2d/components/world.hpp
)

target_include_directories(mm_box2d INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/src")

target_link_libraries(mm_box2d INTERFACE
	engine
	#common_components

	box2d
)

###############################

## top down input system
#add_library(mm_box2d_td_movement
	#./src/mm_box2d/systems/top_down_movement.hpp
	#./src/mm_box2d/systems/top_down_movement.cpp
#)

#target_include_directories(mm_box2d_td_movement PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")

#target_link_libraries(mm_box2d_td_movement
	#mm_box2d
#)

###############################

## collision map loader for tilemaps
#add_library(mm_box2d_tilemap
	#./src/mm_box2d/tilemap_box2d.hpp
	#./src/mm_box2d/tilemap_box2d.cpp
#)

#target_include_directories(mm_box2d_tilemap PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")

#target_link_libraries(mm_box2d_tilemap
	#mm_box2d
	#tilemap
#)

###############################

# Box2D Debug Draw for mm
add_library(mm_box2d_debug_draw
	./src/mm_box2d/opengl/render_tasks/box2d_debug_draw.hpp
	./src/mm_box2d/opengl/render_tasks/box2d_debug_draw.cpp

	./src/mm_box2d/opengl/render_tasks/draw.h
	./src/mm_box2d/opengl/render_tasks/draw.cpp
)

target_include_directories(mm_box2d_debug_draw PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")

target_link_libraries(mm_box2d_debug_draw
	mm_box2d
	opengl_renderer_s
)

#if(EMSCRIPTEN)
	#set_target_properties(mm_box2d_debug_draw PROPERTIES COMPILE_FLAGS "-s USE_SDL=2")
	#set_target_properties(mm_box2d_debug_draw PROPERTIES LINK_FLAGS "-s USE_SDL=2 -s USE_WEBGL2=1 -s FULL_ES2=1 -s FULL_ES3=1")
#endif()

