project(data)

find_package(OpenCL REQUIRED)
include_directories(${OpenCL_INCLUDE_DIRS})
link_directories(${OpenCL_LIBRARY})

include_directories(${DIR_INC})

add_definitions(-DDLM_SAMPLE_DIR="${DIR_SAMPLE}/")

set(SOURCE_FILES
    ${DIR_SAMPLE}/pool/main.cpp

    ${DIR_SAMPLE}/utils/program.cpp
    ${DIR_SAMPLE}/utils/utils.hpp
)

add_executable(pool ${SOURCE_FILES})
target_link_libraries (pool ${OpenCL_LIBRARY})
target_link_libraries (pool dlmCl)


