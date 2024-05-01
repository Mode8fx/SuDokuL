cmake_minimum_required(VERSION 3.2)
project(sudokul CXX)

add_executable(sudokul
	"src/main.cpp"
	"src/main.h"
	"src/config.cpp"
	"src/config.h"
	"src/game_logic.cpp"
	"src/game_logic.h"
	"src/general.h"
	"src/include.h"
	"src/include_fonts.h"
	"src/include_graphics.h"
	"src/include_music.h"
	"src/include_sfx.h"
	"src/main.cpp"
	"src/main.h"
	"src/menu_logic.cpp"
	"src/menu_logic.h"
	"src/puzzleBank.cpp"
	"src/puzzleBank.h"
	"src/shared.cpp"
	"src/shared.h"
	"src/sound_logic.cpp"
	"src/sound_logic.h"
	"src/sprite_objects.h"
	"src/sudokuGen.cpp"
	"src/sudokuGen.h"
	"src/text_objects.cpp"
	"src/text_objects.h"
	"src/transitions.cpp"
	"src/transitions.h"
	"src/window.cpp"
	"src/window.h"
	"src/fonts_include/Commodore_Pixelized_v1_2.cpp"
	"src/fonts_include/Commodore_Pixelized_v1_2.h"
	"src/graphics_include/grid_384.cpp"
	"src/graphics_include/grid_384.h"
	"src/graphics_include/grid_cursor_bottom_left.cpp"
	"src/graphics_include/grid_cursor_bottom_left.h"
	"src/graphics_include/grid_cursor_bottom_right.cpp"
	"src/graphics_include/grid_cursor_bottom_right.h"
	"src/graphics_include/grid_cursor_top_left.cpp"
	"src/graphics_include/grid_cursor_top_left.h"
	"src/graphics_include/grid_cursor_top_right.cpp"
	"src/graphics_include/grid_cursor_top_right.h"
	"src/graphics_include/grid_mini_bottom_left.cpp"
	"src/graphics_include/grid_mini_bottom_left.h"
	"src/graphics_include/grid_mini_bottom_right.cpp"
	"src/graphics_include/grid_mini_bottom_right.h"
	"src/graphics_include/grid_mini_top_left.cpp"
	"src/graphics_include/grid_mini_top_left.h"
	"src/graphics_include/grid_mini_top_right.cpp"
	"src/graphics_include/grid_mini_top_right.h"
	"src/graphics_include/logo_1080.cpp"
	"src/graphics_include/logo_1080.h"
	"src/graphics_include/logo_1440.cpp"
	"src/graphics_include/logo_1440.h"
	"src/graphics_include/logo_2160.cpp"
	"src/graphics_include/logo_2160.h"
	"src/graphics_include/logo_240.cpp"
	"src/graphics_include/logo_240.h"
	"src/graphics_include/logo_272.cpp"
	"src/graphics_include/logo_272.h"
	"src/graphics_include/logo_480.cpp"
	"src/graphics_include/logo_480.h"
	"src/graphics_include/logo_544.cpp"
	"src/graphics_include/logo_544.h"
	"src/graphics_include/logo_720.cpp"
	"src/graphics_include/logo_720.h"
	"src/graphics_include/menu_cursor.cpp"
	"src/graphics_include/menu_cursor.h"
	"src/graphics_include/sidebar_small.cpp"
	"src/graphics_include/sidebar_small.h"
	"src/graphics_include/tile1.cpp"
	"src/graphics_include/tile1.h"
	"src/graphics_include/tile2.cpp"
	"src/graphics_include/tile2.h"
	"src/graphics_include/tile3.cpp"
	"src/graphics_include/tile3.h"
	"src/graphics_include/tile_cave.cpp"
	"src/graphics_include/tile_cave.h"
	"src/graphics_include/tile_desert.cpp"
	"src/graphics_include/tile_desert.h"
	"src/graphics_include/tile_grasslands.cpp"
	"src/graphics_include/tile_grasslands.h"
	"src/graphics_include/tile_grasslands2.cpp"
	"src/graphics_include/tile_grasslands2.h"
	"src/graphics_include/tile_snowymountain.cpp"
	"src/graphics_include/tile_snowymountain.h"
	"src/music_include/addicti.cpp"
	"src/music_include/addicti.h"
	"src/music_include/ancient_days_.cpp"
	"src/music_include/ancient_days_.h"
	"src/music_include/dgtlnnv2.cpp"
	"src/music_include/dgtlnnv2.h"
	"src/music_include/electroq.cpp"
	"src/music_include/electroq.h"
	"src/music_include/insomnia.cpp"
	"src/music_include/insomnia.h"
	"src/music_include/mainmenu.cpp"
	"src/music_include/mainmenu.h"
	"src/music_include/ontario.cpp"
	"src/music_include/ontario.h"
	"src/music_include/sudoku_padawan.cpp"
	"src/music_include/sudoku_padawan.h"
	"src/sfx_include/coin1.cpp"
	"src/sfx_include/coin1.h"
)
find_package(PkgConfig REQUIRED)

if (WIIU)
	include("${DEVKITPRO}/wut/share/wut.cmake" REQUIRED)
	add_definitions(-DWII_U)
	add_definitions(-DMOUSE_INPUT)

	target_link_libraries(sudokul -L${DEVKITPRO}/portlibs/wiiu/lib -L${DEVKITPRO}/portlibs/ppc/lib -L${DEVKITPRO}/wut/lib)
	# pkg_check_modules(SDL2 REQUIRED IMPORTED_TARGET SDL2)
	# pkg_check_modules(SDL2_image REQUIRED IMPORTED_TARGET SDL2_image)
	# pkg_check_modules(SDL2_mixer REQUIRED IMPORTED_TARGET SDL2_mixer)
	# pkg_check_modules(SDL2_ttf REQUIRED IMPORTED_TARGET SDL2_ttf)
	# target_link_libraries(sudokul PkgConfig::SDL2 PkgConfig::SDL2_image PkgConfig::SDL2_mixer PkgConfig::SDL2_ttf)
	# target_link_libraries(sudokul -lSDL2_ttf -lSDL2_mixer -lmodplug -lvorbisfile -lvorbis -logg -lSDL2_image -lSDL2 -lfreetype -lpng -lmpg123 -lbz2 -ljpeg -lz -lwut)
	PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
	PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
	PKG_SEARCH_MODULE(SDL2MIXER REQUIRED SDL2_mixer>=2.0.0)
	PKG_SEARCH_MODULE(SDL2TTF REQUIRED SDL2_ttf>=2.0.0)
	INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} ${SDL2MIXER_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIRS})
	TARGET_LINK_LIBRARIES(sudokul ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2MIXER_LIBRARIES} ${SDL2TTF_LIBRARIES})

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

elseif (VITA)
	include("${VITASDK}/share/vita.cmake" REQUIRED)
	add_definitions(-DVITA)
	add_definitions(-DMOUSE_INPUT)
	
	set(VITA_APP_NAME "SuDokuL")
	set(VITA_TITLEID  "SDKL39690")
	set(VITA_VERSION  "01.00")
	
	PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
	PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
	PKG_SEARCH_MODULE(SDL2MIXER REQUIRED SDL2_mixer>=2.0.0)
	PKG_SEARCH_MODULE(SDL2TTF REQUIRED SDL2_ttf>=2.0.0)
	INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} ${SDL2MIXER_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIRS})
	TARGET_LINK_LIBRARIES(sudokul ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2MIXER_LIBRARIES} ${SDL2TTF_LIBRARIES})

	# target_link_libraries(sudokul SDL2_ttf SDL2_mixer SDL2_image SDL2 freetype png png16 bz2 jpeg z mikmod modplug mpg123 xmp FLAC vorbisfile vorbis ogg webp pthread)
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

else()
	if (LINUX)
		add_definitions(-DLINUX)
	endif()
	PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
	PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
	PKG_SEARCH_MODULE(SDL2MIXER REQUIRED SDL2_mixer>=2.0.0)
	PKG_SEARCH_MODULE(SDL2TTF REQUIRED SDL2_ttf>=2.0.0)
	INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} ${SDL2MIXER_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIRS})
	TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2MIXER_LIBRARIES} ${SDL2TTF_LIBRARIES})

endif()

unset(WIIU CACHE)
unset(VITA CACHE)
unset(LINUX CACHE)