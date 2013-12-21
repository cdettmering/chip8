include_directories (${PROJECT_SOURCE_DIR}/include)
set (HEADERS Memory.hpp Cpu.hpp BitUtils.hpp)
set (SOURCES main.cpp Memory.cpp Cpu.cpp BitUtils.cpp)
add_executable (chip8 ${SOURCES})
