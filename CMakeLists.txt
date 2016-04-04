cmake_minimum_required(VERSION 2.8)
project(starry_night)

set (CMAKE_C_FLAGS "-std=c99 -Wall -Wextra ${CMAKE_C_FLAGS}")

set_source_files_properties(tags PROPERTIES GENERATED true)

add_custom_target(tags
        COMMAND ctags -R .
	        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

add_executable (starry_night
		src/main.c
	       )

find_package(PkgConfig)
pkg_check_modules(NCURSESW "ncursesw" REQUIRED)

include_directories(${NCURSESW_INCLUDE_DIRS})

target_link_libraries(starry_night ncursesw)

install(TARGETS starry_night
	RUNTIME DESTINATION bin
	)
