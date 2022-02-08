QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Graph_Representation.cpp \
    comp.cpp \
    dialog2.cpp \
    dialog3.cpp \
    error_handle.cpp \
    format.cpp \
    main.cpp \
    mainwindow.cpp \
    minify.cpp \
    project.cpp \
    tree.cpp

HEADERS += \
    Graph_representation.h \
    comp.h \
    dialog2.h \
    dialog3.h \
    error_handle.h \
    format.h \
    mainwindow.h \
    minify.h \
    tree.h

FORMS += \
    dialog2.ui \
    dialog3.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

GRAPHVIZ_PATH = "C:/Program Files/Graphviz"
DEFINES += WIN32_DLL
DEFINES += GVDLL
INCLUDEPATH += $$GRAPHVIZ_PATH/include/graphviz
LIBS += -L$$GRAPHVIZ_PATH/lib -lgvc -lcgraph  -lcdt

RESOURCES += \
    All_the_resour.qrc

DISTFILES += \
    Consistency_output.xml \
    Modification.xml \
    compression_output.xml \
    decompression_output.xml \
    format_output.xml \
    minify_output.xml \
    temp.xml \
    toJson_output.json
