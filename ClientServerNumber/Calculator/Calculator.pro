QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QT += core5compat

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../ClientServerNumbers/BigInteger.cpp \
    ../ClientServerNumbers/ClientNumber.cpp \
    ../ClientServerNumbers/ExponentialNotation.cpp \
    ../ClientServerNumbers/FormulaRecognition.cpp \
    ../ClientServerNumbers/RationalNumerics.cpp \
    ../ClientServerNumbers/ServerRationalNumber.cpp \
    ../ClientServerNumbers/pch.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    ../ClientServerNumbers/BigInteger.h \
    ../ClientServerNumbers/ClientNumber.h \
    ../ClientServerNumbers/ExponentialNotation.h \
    ../ClientServerNumbers/FormulaManager.h \
    ../ClientServerNumbers/FormulaRecognition.h \
    ../ClientServerNumbers/NodeStack.h \
    ../ClientServerNumbers/Operation.h \
    ../ClientServerNumbers/RationalNumerics.h \
    ../ClientServerNumbers/ServerRationalNumber.h \
    ../ClientServerNumbers/StackList.h \
    ../ClientServerNumbers/framework.h \
    ../ClientServerNumbers/pch.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    src/deletePicture.png
