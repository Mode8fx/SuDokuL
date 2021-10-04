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

if (VITA)
	include("${VITASDK}/share/vita.cmake" REQUIRED)
	# find_package(PkgConfig REQUIRED)
	add_definitions(-DVITA)
	
	set(VITA_APP_NAME "SuDokuL")
	set(VITA_TITLEID  "SDKL39690")
	set(VITA_VERSION  "01.00")

	target_link_libraries(sudokul SDL2_ttf SDL2_mixer SDL2_image SDL2 freetype png png16 bz2 jpeg z mikmod mpg123 FLAC vorbisfile vorbis ogg webp pthread)
	# find_package(SDL2 REQUIRED)
	# target_link_libraries(sudokul SDL2_ttf SDL2_mixer SDL2_image SDL2)
	target_link_libraries(sudokul
		SceDisplay_stub
		SceCtrl_stub
		SceAudio_stub
		SceSysmodule_stub
		SceGxm_stub
		SceCommonDialog_stub
		SceAppMgr_stub
		SceTouch_stub
		SceMotion_stub
		SceHid_stub
		m
	)

	include_directories("${VITASDK}/arm-vita-eabi/include;${VITASDK}/arm-vita-eabi/include/SDL2;")

	vita_create_self(sudokul.self sudokul)
	vita_create_vpk(sudokul.vpk ${VITA_TITLEID} sudokul.self
		VERSION ${VITA_VERSION}
		NAME ${VITA_APP_NAME}
		FILE sce_sys/icon0.png sce_sys/icon0.png
		FILE sce_sys/livearea/contents/bg.png sce_sys/livearea/contents/bg.png
		FILE sce_sys/livearea/contents/startup.png sce_sys/livearea/contents/startup.png
		FILE sce_sys/livearea/contents/template.xml sce_sys/livearea/contents/template.xml
	)
endif()

unset(WINDOWS32 CACHE)
unset(WIIU CACHE)
unset(VITA CACHE)