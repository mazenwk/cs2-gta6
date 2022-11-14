QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bullet.cpp \
    enemy.cpp \
    main.cpp \
    player.cpp \
    powerpellet.cpp

HEADERS += \
    bullet.h \
    constants.h \
    enemy.h \
    player.h \
    powerpellet.h

FORMS +=

### Copies the resources directory to the build folder
copydata.commands = $(COPY_DIR) \"$$shell_path($$PWD\\resources)\" \"$$shell_path($$OUT_PWD\\resources)\"
first.depends = $(first) copydata
export(first.depends)
export(copydata.commands)
QMAKE_EXTRA_TARGETS += first copydata

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target