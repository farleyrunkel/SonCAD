# cpplint.cmake


# This function runs cpplint on the provided source files
function(run_cpplint)
    # Find the cpplint executable
    find_program(CPPLINT_EXECUTABLE NAMES cpplint)

    if (NOT CPPLINT_EXECUTABLE)
        message(FATAL_ERROR "Cpplint is not found!")
    endif()

    # Iterate through the provided source files and run cpplint on each one
    foreach(source_file ${ARGN})
        if (${source_file} MATCHES "\\.(cc|h)$")
            file(RELATIVE_PATH sourceDirRelFilePath ${CMAKE_SOURCE_DIR} ${source_file})
            message(STATUS "sourceDirRelFilePath: " ${sourceDirRelFilePath})

            # Create the path for the cpplint output file
            set(output_file "${CMAKE_BINARY_DIR}/${sourceDirRelFilePath}.cpplint")

            if(WIN32)
                add_custom_command(
                    OUTPUT  ${output_file}  # Ensure we are specifying the output file here
                    COMMAND ${CPPLINT_EXECUTABLE} --verbose=3 --filter=-build/include_order ${source_file} > ${output_file} 2>&1 || exit /b 0
                    DEPENDS ${source_file}
                    COMMENT "Running cpplint for ${source_file} on Windows and saving output to ${output_file}"
                    VERBATIM
                )
            else()
                add_custom_command(
                    OUTPUT  ${output_file}  # Ensure we are specifying the output file here
                    COMMAND ${CPPLINT_EXECUTABLE} --verbose=3 --filter=-build/include_order ${source_file} > ${output_file} 2>&1 || true
                    DEPENDS ${source_file}
                    COMMENT "Running cpplint for ${source_file} on Linux and saving output to ${output_file}"
                    VERBATIM
                )
            endif()
        endif()
    endforeach()
endfunction()

# This function creates a custom target to run cpplint for the given files
function(add_cpplint_target target_name)
    set(SOURCE_FILES ${ARGN})
    run_cpplint(${SOURCE_FILES})

    # Create a list of .cpplint files
    set(CPPLINT_OUTPUTS "")
    foreach(source_file ${SOURCE_FILES})
        if (${source_file} MATCHES "\\.(cc|h)$")
            file(RELATIVE_PATH sourceDirRelFilePath ${CMAKE_SOURCE_DIR} ${source_file})
            list(APPEND CPPLINT_OUTPUTS "${CMAKE_BINARY_DIR}/${sourceDirRelFilePath}.cpplint")
        endif()
    endforeach()

    # Print CPPLINT_OUTPUTS
    message(STATUS "Generated CPPLINT_OUTPUTS:")
    foreach(output_file ${CPPLINT_OUTPUTS})
        message(STATUS "  ${output_file}")
    endforeach()

    add_custom_target(${target_name} ALL DEPENDS ${CPPLINT_OUTPUTS})

    # Iterate over the list of cpplint output files and add a command to print each file's content
    foreach(output_file ${CPPLINT_OUTPUTS})
        add_custom_command(
            TARGET ${target_name}  # Attach the command to the custom target
            POST_BUILD  # Run this command after the target is built
            COMMAND ${CMAKE_COMMAND} -E echo "===== Cpplint of ${output_file} ====="
            COMMAND ${CMAKE_COMMAND} -E cat ${output_file}  # Print the content of the file
            COMMENT "Printing contents of ${output_file}"
        )
    endforeach()
endfunction()
