cmake_minimum_required(VERSION 2.8.11 FATAL_ERROR)
project(sitemap LANGUAGES CXX)


include(GNUInstallDirs)

	set( CMAKE_CXX_FLAGS "-std=c++11 -stdlib=libc++ -Wall" )

	unset(ENV{BOOST_ROOT})
	set(Boost_USE_STATIC_LIBS ON) # only find static libs
	set(Boost_USE_MULTITHREADED ON)
	find_package(Boost)
	if(NOT ${Boost_FOUND})
		message( ERROR " Unable to find Boost" )
	else()
		message( STATUS "Using Boost package: ${Boost_VERSION}" ) 
		message( STATUS "Boost includes: ${Boost_INCLUDE_DIRS}" ) 
		message( STATUS "Boost libs: ${Boost_LIBRARY_DIRS}" ) 
		include_directories(${Boost_INCLUDE_DIRS})
		link_directories(${Boost_LIBRARY_DIRS})
	endif()

include_directories("include")

file(GLOB src src/*.cpp src/*.h include/${PROJECT_NAME}/*.h)

add_library(${PROJECT_NAME} ${src})

# Attach header directory information
# to the targets for when we are part of a parent build (ie being pulled
# in via add_subdirectory() rather than being a standalone build).
target_include_directories(${PROJECT_NAME} INTERFACE "include")

# Install rules
install(TARGETS ${PROJECT_NAME} 
		LIBRARY DESTINATION "lib"
		ARCHIVE DESTINATION "lib"
		RUNTIME DESTINATION "bin"
	)
install(DIRECTORY include/${PROJECT_NAME} DESTINATION include) 

add_executable(sm sample/sm.cpp)

target_link_libraries(sm ${PROJECT_NAME}
	debug boost_system-mt-d
	debug boost_filesystem-mt-d

	optimized boost_system-mt
	optimized boost_filesystem-mt
	)
