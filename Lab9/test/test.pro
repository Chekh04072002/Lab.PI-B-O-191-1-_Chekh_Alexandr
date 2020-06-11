include(gtest_dependency.pri)

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += thread
CONFIG -= qt

HEADERS += \
        ../../Desktop/Lab9_Project_for_tests/IKeypad.h \
        ../../Desktop/Lab9_Project_for_tests/ILatch.h \
        ../../Desktop/Lab9_Project_for_tests/lockcontroller.h \
        tst_tests.h

SOURCES += \
        ../../Desktop/Lab9_Project_for_tests/lockcontroller.cpp \
        main.cpp
INCLUDEPATH += C:\Users\user\Desktop\Lab9_Project_for_tests
