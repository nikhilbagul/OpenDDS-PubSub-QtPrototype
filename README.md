# OpenDDS-PubSub-QtPrototype

Qt verson: Qt for Mac 5.12.0

clang-1000.10.44.2

OpenDDS 3.13

This repository contains two Qt Quick based UI applications deploying OpenDDS as the communication protocol. 


# IDL

The IDL files for the desired message format can be found under /IDL

The serialization and key support files required to marshal and demarshal the
Message, as well as the type support code for the data readers and writers is already compiled by the TAO IDL compiler and can be found under /IDL

# Publisher and Subsriber

The Pub-Sub apps are based on the messenger.minimal example as part of the OpenDDS examples.
These apps communicate over OpenDDS in a RTPS mode

# Compiling and running the applications

1. To build the app one would require qmake (for compilation) and Qt Creator IDE to read and open the project.
2. Qt (FOSS) can be obtained from https://www.qt.io/download
3. Once downloaded and installed, open the apps via QtCreator and hit run to build & run the apps. 
4. To view the console/application logs in the application itself, disable the 'run in terminal' option from the project settings, else it will trigger the console every time the applicaton is fired from within the QtCreator IDE

