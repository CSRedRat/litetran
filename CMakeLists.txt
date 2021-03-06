cmake_minimum_required(VERSION 2.8.10)

set(APP_EXECUTABLE_NAME litetran)
set(APP_NAME LiteTran)
set(APP_VERSION 0.2)

if(APPLE)
    set(APP_GUI_TYPE MACOSX_BUNDLE)
elseif(UNIX)
    set(APP_BINARY_INSTALL_PATH ${CMAKE_INSTALL_PREFIX}/bin)
    set(APP_ICONS_INSTALL_PATH ${CMAKE_INSTALL_PREFIX}/share/pixmaps)
    set(APP_I18N_INSTALL_PATH ${CMAKE_INSTALL_PREFIX}/share/litetran/i18n)
    set(APP_I18N_LOAD_PATH ${APP_I18N_INSTALL_PATH})
elseif(WIN32)
    set(APP_BINARY_INSTALL_PATH ${CMAKE_INSTALL_PREFIX})
    set(APP_ICONS_INSTALL_PATH ${CMAKE_INSTALL_PREFIX})
    set(APP_I18N_INSTALL_PATH ${CMAKE_INSTALL_PREFIX}/i18n)
    set(APP_I18N_LOAD_PATH i18n)
    set(APP_GUI_TYPE WIN32)
    set(QT_USE_QTMAIN TRUE)
endif()

project(${APP_NAME})
set(PROJECT_VERSION ${APP_VERSION})
set(CMAKE_BUILD_TYPE Release)

if(CMAKE_BUILD_TYPE STREQUAL Debug)
    if(CMAKE_COMPILER_IS_GNUCC AND UNIX)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")
    endif()
endif()

if(NOT MSVC)
    if("${CMAKE_SYSTEM_PROCESSOR}" STREQUAL "x86_64")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
    endif("${CMAKE_SYSTEM_PROCESSOR}" STREQUAL "x86_64")
endif()

find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Network REQUIRED)
find_package(Qt5Multimedia REQUIRED)
find_package(Qt5LinguistTools REQUIRED)

add_subdirectory(src/3rdparty)

include_directories(
${CMAKE_CURRENT_BINARY_DIR}
${CMAKE_CURRENT_BINARY_DIR}/src
${THIRD_PARTY_DIRS})

configure_file(src/defines.h.in src/defines.h)

set(HEADERS
src/mainwindow.h
src/texttoolbar.h
src/settings.h
src/trayicon.h
src/languagedb.h
src/translate.h
src/request.h
src/pronounce.h
src/popup.h
src/textedit.h
src/clipboard.h)

set(SOURCES
src/main.cpp
src/mainwindow.cpp
src/texttoolbar.cpp
src/settings.cpp
src/trayicon.cpp
src/languagedb.cpp
src/translate.cpp
src/request.cpp
src/pronounce.cpp
src/popup.cpp
src/textedit.cpp
src/clipboard.cpp)

set(TRANSLATIONS_FILES
i18n/English.ts
i18n/Russian.ts)

set(RESOURCES resources.qrc)
set(FILES_TO_TRANSLATE ${SOURCES})

option(UPDATE_TRANSLATIONS OFF)
set(UPDATE_TRANSLATIONS OFF)
if(UPDATE_TRANSLATIONS)
    message(WARNING "Updating translation files")
    qt5_create_translation(QM_FILES ${FILES_TO_TRANSLATE} ${TRANSLATIONS_FILES})
else()
    qt5_add_translation(QM_FILES ${TRANSLATIONS_FILES})
endif()

add_custom_target(lupdate DEPENDS ${QM_FILES})

qt5_add_resources(RC_SOURCES ${RESOURCES})
qt5_wrap_cpp(MOC_SOURCES ${HEADERS})

add_executable(${APP_EXECUTABLE_NAME} ${APP_GUI_TYPE} ${RC_SOURCES} ${SOURCES} ${MOC_SOURCES} ${QM_FILES} litetran.rc)
qt5_use_modules(${APP_EXECUTABLE_NAME} Widgets Core Network Multimedia)

target_link_libraries(${APP_EXECUTABLE_NAME} ${THIRD_PARTY_LIBS})

if(APPLE)
    find_library(CORE_SERVICES_LIBRARY CoreServices)
    find_library(CARBON_LIBRARY Carbon)
    target_link_libraries(${APP_EXECUTABLE_NAME} ${CORE_SERVICES_LIBRARY} ${CARBON_LIBRARY})
endif()

if(MINGW)
    add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/litetranico.o
                       COMMAND  windres.exe -i${CMAKE_CURRENT_SOURCE_DIR}/litetran.rc
                       -o ${CMAKE_CURRENT_BINARY_DIR}/litetranico.o)
endif()

install(TARGETS ${APP_EXECUTABLE_NAME} DESTINATION ${APP_BINARY_INSTALL_PATH})
install(FILES ${QM_FILES} DESTINATION ${APP_I18N_INSTALL_PATH})

if(UNIX)
    install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/icons/ui/litetran.png DESTINATION ${APP_ICONS_INSTALL_PATH})
    install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/litetran.desktop DESTINATION ${CMAKE_INSTALL_PREFIX}/share/applications)
endif()
