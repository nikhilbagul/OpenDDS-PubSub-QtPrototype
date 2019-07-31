QT += quick
CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

########## For IDL Static library dependencies ##########################
LIBS += -L$$PWD/IDL/ -lIDLCommonLib
INCLUDEPATH += $$PWD/IDL
DEPENDPATH += $$PWD/IDL
PRE_TARGETDEPS += $$PWD/IDL/libIDLCommonLib.a

########## For DDS Shared library dependencies ##########################

LIBS += -L/usr/local/lib/dds/lib/ -lACE \
        -lOpenDDS_Dcps \
        -lOpenDDS_Rtps \
        -lOpenDDS_InfoRepoServ \
        -lOpenDDS_Shmem \
        -lOpenDDS_FACE \
        -lOpenDDS_Model \
        -lOpenDDS_Tcp \
        -lOpenDDS_Federator \
        -lOpenDDS_Multicast \
        -lOpenDDS_Udp \
        -lOpenDDS_InfoRepoDiscovery \
        -lOpenDDS_Rtps \
        -lOpenDDS_monitor \
        -lOpenDDS_InfoRepoLib \
        -lOpenDDS_Rtps_Udp

LIBS += -L/usr/local/lib/dds/lib/ -lACEXML \
        -lACEXML_Parser

LIBS += -L/usr/local/lib/dds/lib/ -lTAO \
        -lTAO_CosNaming \
        -lTAO_IORManip \
        -lTAO_PI_Server \
        -lTAO_AnyTypeCode \
        -lTAO_CosNaming_Serv \
        -lTAO_IORTable \
        -lTAO_PortableGroup \
        -lTAO_Async_IORTable \
        -lTAO_CosNaming_Skel \
        -lTAO_ImR_Activator \
        -lTAO_PortableServer \
        -lTAO_Async_ImR_Client_IDL \
        -lTAO_DynamicInterface \
        -lTAO_ImR_Activator_IDL \
        -lTAO_Strategies \
        -lTAO_BiDirGIOP \
        -lTAO_FTORB_Utils \
        -lTAO_ImR_Client \
        -lTAO_Svc_Utils \
        -lTAO_CSD_Framework \
        -lTAO_FT_ClientORB \
        -lTAO_ImR_Locator \
        -lTAO_Valuetype \
        -lTAO_CSD_ThreadPool \
        -lTAO_FT_ServerORB \
        -lTAO_ImR_Locator_IDL \
        -lTAO_CodecFactory \
        -lTAO_IDL_BE \
        -lTAO_Messaging \
        -lTAO_Codeset \
        -lTAO_IDL_FE \
        -lTAO_PI

INCLUDEPATH += /usr/local/lib/dds/include
DEPENDPATH  += /usr/local/lib/dds/include
##################################################################

SOURCES += \
        main.cpp \
    Boilerplate.cpp \
    DataReaderListenerImpl.cpp

HEADERS += \
    Boilerplate.h \
    DataReaderListenerImpl.h

RESOURCES += qml.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DCPS_PROTOCOL_SETTINGS_FILE = $$PWD/rtps.ini
OTHER_FILES += $$DCPS_PROTOCOL_SETTINGS_FILE

# These are executed post link and we don't have to run make install
QMAKE_POST_LINK += "cp $$DCPS_PROTOCOL_SETTINGS_FILE $$$$OUT_PWD/OpenDDSSubscriber.app/Contents/MacOS"
