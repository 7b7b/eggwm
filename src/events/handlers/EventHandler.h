/**
 * Copyright (C) 2014 Leslie Zhai <xiang.zhai@i-soft.com.cn>
 *
 * @file /src/eggwm/events/handlers/EventHandler.h
 *
 * @~spanish
 * Este archivo es parte del proyecto Egg Window Manager, usted puede
 * redistribuirlo y/o modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Egg Window Manager project, you can redistribute it
 * and/or modify it under the terms of the GNU GPL v3.
 *
 * @class  EventHandler
 * @author José Expósito
 */
#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include "src/util/Include.h"
#include "src/xwindows/XWindowList.h"
#include "src/xwindows/XWindow.h"
#include "src/standards/EWMHRoot.h"


/**
 * @~spanish
 * Interfaz que deben implementar todos los manejadores de eventos.
 *
 * @~english
 * Interface that must implement all event handlers.
 */
class EventHandler {

    protected:

        /**
         * @~spanish
         * Lista de ventanas.
         *
         * @~english
         * Window list.
         */
        XWindowList* wl;

    public:

        /**
         * @~spanish
         * Constructora por defecto.
         * @param wl La lista de ventanas.
         *
         * @~english
         * Default constructor.
         * @param wl The window list.
         */
        EventHandler(XWindowList* wl) {
            this->wl = wl;
        }

        /**
         * @~spanish
         * Procesa el evento.
         * @param event El evento a procesar.
         * @return true para evitar que el evento sea tratado con normalidad, es
         *         decir, cuando ya lo tratamos nosotros, false para que el
         *         evento se trate con normalidad.
         *
         * @~english
         * Process the event.
         * @param event The event to be processed.
         * @return true if you want to stop the event from being processed, ie
         *         when we treat ourselves, false for normal event dispatching.
         */
        virtual bool processEvent(XEvent* event) = 0;

#if QT_VERSION >= 0x050000
        virtual bool processEvent(xcb_generic_event_t* event) = 0;
#endif

};

#endif // EVENTHANDLER_H
