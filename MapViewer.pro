QT       += network
QT       += gui
QT       += opengl

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtMapViewer


HEADERS += \
    src/TileView.h \
    src/TileRequestFactory.h \
    src/TileManager.h \
    src/TileLoaderManager.h \
    src/TileInfo.h \
    src/TileCoordinateUtility.h \
    src/Tile.h \
    src/OnlineTileLoader.h \
    src/OfflineTileLoader.h \
    src/MapMarker.h \
    src/MainWindow.h \
    src/DownloadTileRequest.h \
    src/TileTypeEnum.h

SOURCES += \
    src/TileView.cpp \
    src/TileRequestFactory.cpp \
    src/TileManager.cpp \
    src/TileLoaderManager.cpp \
    src/TileInfo.cpp \
    src/TileCoordinateUtility.cpp \
    src/Tile.cpp \
    src/OnlineTileLoader.cpp \
    src/OfflineTileLoader.cpp \
    src/MapMarker.cpp \
    src/MainWindow.cpp \
    src/main.cpp \
    src/DownloadTileRequest.cpp

OTHER_FILES += \
    ressources/dark_stylesheet.qss \
    ressources/appsettings.ini

RESOURCES += \
    ressources/ressources.qrc
