# Define the path for the lock file
set(LOCK_FILE "${CMAKE_SOURCE_DIR}/xcode/.xcode_project_generation.lock")

# Check if the xcode directory exists and create it if necessary
if (NOT EXISTS ${CMAKE_SOURCE_DIR}/xcode)
    message(STATUS "Creating xcode directory...")
    file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/xcode)
endif()

# Check if the lock file exists
if (NOT EXISTS ${LOCK_FILE})
    message(STATUS "Generating Xcode project...")

    # Create the lock file
    file(WRITE ${LOCK_FILE} "Xcode project generation in progress")

    set(TOOLCHAIN_ARG "-DCMAKE_TOOLCHAIN_FILE=${Z_VCPKG_TOOLCHAIN_DIR}/vcpkg.cmake")

    # Generate Xcode project
    execute_process(
            COMMAND ${CMAKE_COMMAND} -G "Xcode" ${CMAKE_SOURCE_DIR} ${TOOLCHAIN_ARG}
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/xcode
            RESULT_VARIABLE result
    )

    if (result)
        file(REMOVE ${LOCK_FILE})
        message(FATAL_ERROR "Failed to generate Xcode project")
    else()
        file(WRITE ${LOCK_FILE} "Xcode project generation completed")
        message(STATUS "Xcode project generated successfully")
    endif()
else()
    message(STATUS "Xcode project already exists or is being generated.")
endif()
