cmake_minimum_required(VERSION 3.5)
project(sudokul CXX)

file(GLOB SOURCES
	"src/*.cpp" "src/*.h"
	"src/fonts_include/*.cpp"
	"src/fonts_include/*.h"
	"src/graphics_include/all_res/*.cpp"
	"src/graphics_include/all_res/*.h"
	"src/graphics_include/normal_res/*.cpp"
	"src/graphics_include/normal_res/*.h"
	"src/music_include/*.cpp"
	"src/music_include/*.h"
	"src/sfx_include/*.cpp"
	"src/sfx_include/*.h"
)
add_executable(sudokul ${SOURCES})
find_package(PkgConfig REQUIRED)

if (NO_QUIT)
	add_definitions(-DNO_QUIT)
endif()

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