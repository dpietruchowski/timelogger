QT += quick sql widgets
CONFIG += c++17

QMAKE_CXXFLAGS += -std=c++17

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    cpp/main.cpp \
    cpp/timelog/Timelog.cpp \
    cpp/timelog/Timespan.cpp \
    cpp/TimeLogger.cpp \
    cpp/timelog/DayLogs.cpp \
    cpp/timelog/TimelogsData.cpp \
    cpp/timelog/TimelogsModel.cpp \
    cpp/utils/VectorSignals.cpp \
    cpp/utils/VectorModel.cpp \
    cpp/timelog/TimespansData.cpp \
    cpp/timelog/TimespansModel.cpp

RESOURCES += qml/qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    cpp/timelog/Timelog.h \
    cpp/timelog/Timespan.h \
    cpp/TimeLogger.h \
    cpp/timelog/DayLogs.h \
    cpp/timelog/TimelogsData.h \
    cpp/timelog/TimelogsModel.h \
    cpp/utils/VectorSignals.h \
    cpp/utils/VectorData.h \
    cpp/utils/VectorModel.h \
    cpp/timelog/TimespansData.h \
    cpp/timelog/TimespansModel.h

INCLUDEPATH += \
    cpp \
    cpp/utils \
    cpp/timelog

DISTFILES +=
