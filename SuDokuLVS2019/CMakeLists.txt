cmake_minimum_required(VERSION 3.2)
project(sudokul CXX)

add_executable(sudokul
	"src/main.cpp"
	"src/config.h"
	"src/game_logic.h"
	"src/general.h"
	"src/include.h"
	"src/menu_logic.h"
	"src/puzzleBank.cpp"
	"src/puzzleBank.h"
	"src/shared.h"
	"src/sound_logic.h"
	"src/sprite_objects.h"
	"src/sudokuGen.cpp"
	"src/sudokuGen.h"
	"src/text_objects.h"
	"src/transitions.h"
)

# Doesn't work; use VS project file for Windows compilation
if(WINDOWS32)
	target_link_libraries(sudokul -L${CMAKE_CURRENT_LIST_DIR}/SDL2/SDL2-2.0.14/lib/x86 -L${CMAKE_CURRENT_LIST_DIR}/SDL2/SDL2_image-2.0.5/lib/x86 -L${CMAKE_CURRENT_LIST_DIR}/SDL2/SDL2_mixer-2.0.4/lib/x86 -L${CMAKE_CURRENT_LIST_DIR}/SDL2/SDL2_ttf-2.0.15/lib/x86)
	find_package(PkgConfig REQUIRED)
	target_link_libraries(sudokul PkgConfig::SDL2 PkgConfig::SDL2_image PkgConfig::SDL2_mixer PkgConfig::SDL2_ttf)
	target_link_options(sudokul PRIVATE -static-libgcc -static-libstdc++)
	add_definitions(-DSDL_MAIN_HANDLED)
endif()

if (WIIU)
	include("${DEVKITPRO}/wut/share/wut.cmake" REQUIRED)
	find_package(PkgConfig REQUIRED)
	add_definitions(-DWII_U)

	target_link_libraries(sudokul -L${DEVKITPRO}/portlibs/wiiu/lib -L${DEVKITPRO}/portlibs/ppc/lib -L${DEVKITPRO}/wut/lib)
	# target_link_libraries(sudokul -lSDL2_ttf -lSDL2_mixer -lmodplug -lvorbisfile -lvorbis -logg -lSDL2_gfx -lSDL2_image -lSDL2 -lfreetype -lpng -lmpg123 -lbz2 -ljpeg -lz -lwut)
	pkg_check_modules(SDL2 REQUIRED IMPORTED_TARGET SDL2)
	pkg_check_modules(SDL2_image REQUIRED IMPORTED_TARGET SDL2_image)
	pkg_check_modules(SDL2_mixer REQUIRED IMPORTED_TARGET SDL2_mixer)
	pkg_check_modules(SDL2_ttf REQUIRED IMPORTED_TARGET SDL2_ttf)
	target_link_libraries(sudokul PkgConfig::SDL2 PkgConfig::SDL2_image PkgConfig::SDL2_mixer PkgConfig::SDL2_ttf)

	set(SDL2_INCLUDE_DIRS
	"${DEVKITPRO}/portlibs/wiiu/include/SDL2;\
	${DEVKITPRO}/portlibs/ppc/include;\
	${DEVKITPRO}/wut/include;\
	${DEVKITPRO}/devkitPPC/powerpc-eabi/include;"
	)
	include_directories(${SDL2_INCLUDE_DIRS})

	wut_create_rpx(sudokul)

	install(FILES "${CMAKE_CURRENT_BINARY_DIR}/sudokul.rpx"
			DESTINATION "${CMAKE_INSTALL_PREFIX}")
endif()
unset(WINDOWS32 CACHE)
unset(WIIU CACHE)