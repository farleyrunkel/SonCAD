macro(SetupOpenCASCADE)

	# Find OpenCASCADE package
	find_package(OpenCASCADE REQUIRED)
	if(OpenCASCADE_FOUND)
		message(STATUS "OpenCASCADE found")
		message(STATUS "OpenCASCADE include directory: ${OpenCASCADE_INCLUDE_DIR}")
		message(STATUS "OpenCASCADE binary directory: ${OpenCASCADE_BINARY_DIR}")
	else()
		message(FATAL_ERROR "OpenCASCADE not found")
	endif()

endmacro(SetupOpenCASCADE)
