
TEMPLATE     = app
TARGET       = eggwm
QT          += core gui widgets x11extras

OBJECTS_DIR += build
MOC_DIR     += build
LIBS        += -lX11

target.path  = $${PREFIX}/bin

config.path  = $${PREFIX}/$${DATADIR}/eggwm
config.files = data/*

INSTALLS += target config

include(src/eggwm.pri)
