/**
 * Copyright (C) 2014 Leslie Zhai <xiang.zhai@i-soft.com.cn>
 *
 * @file /src/eggwm/EggWM.h
 *
 * @~spanish
 * Este archivo es parte del proyecto Egg Window Manager, usted puede
 * redistribuirlo y/o modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Egg Window Manager project, you can redistribute it
 * and/or modify it under the terms of the GNU GPL v3.
 *
 * @class  EggWM
 * @author José Expósito
 */
#ifndef EGGWM_H
#define EGGWM_H

#include "src/util/Include.h"
#include "src/standards/EWMHRoot.h"
#include "src/standards/WMCheckWindow.h"
#include "src/events/factory/EventFactory.h"

#if QT_VERSION >= 0x050000                                                         
class MyXcbEventFilter : public QAbstractNativeEventFilter                         
{                                                                                  
public:
    MyXcbEventFilter() :m_WindowList(NULL) {}

    virtual bool nativeEventFilter(const QByteArray &eventType, void *message, long *) Q_DECL_OVERRIDE
    {                                                                              
        xcb_generic_event_t* event = static_cast<xcb_generic_event_t*>(message);
        if (m_WindowList == NULL) return false;
        EventFactory* eventFactory = EventFactory::getInstance();
        eventFactory->initialize(m_WindowList);
        EventHandler* handler = eventFactory->getEventHandler(event->response_type & ~0x80);
        if (handler) handler->processEvent(event);
        return false;                                                              
    }

    void setWindowList(XWindowList* windowList) { m_WindowList = windowList; }

private:
    XWindowList* m_WindowList;
};                                                                                 
#endif

/**
 * @~spanish
 * Corazón del gestor de ventanas. Se encarga de procesar los distintos eventos
 * con ayuda de sus correspondientes handlers.
 *
 * @~english
 * Heart of the window manager. Is responsible for process the various events
 * using their associated handlers.
 */
class EggWM : public QApplication {

    private:

        /**
         * @~spanish
         * Véntana para que los clientes sepan que hay un WM ejecutándose.
         *
         * @~english
         * Window used to indicate to the clients that a WM is running.
         */
        WMCheckWindow* wmCheckWindow;

        /**
         * @~spanish
         * Lista con las ventanas gestionadas por el WM.
         *
         * @~english
         * List of windows managed by the WM.
         */
        XWindowList* windowList;

        /**
         * @~spanish
         * Factoría de eventos.
         *
         * @~english
         * Event factory.
         */
        EventFactory* eventFactory;

        //----------------------------------------------------------------------

        /**
         * @~spanish
         * Envía diversos hints requeridos por el estándar EWMH a la ventana
         * raíz.
         *
         * @~english
         * Send various hints required by the EWMH standard to the root window.
         */
        void sendHints();

        /**
         * @~spanish
         * Asocia cada tipo de evento a su correspondiente handler. Es decir,
         * inicializa eventHandlerHash.
         *
         * @~english
         * Associate each event type with his handler. That is, initialized
         * eventHandlerHash.
         */
        void attachEventHandler();

    protected:

        /**
         * @~spanish
         * Reimplementa el método QApplication::x11EventFilter. En este método
         * se recibirán todos los eventos que deberá gestionar el WM (previa
         * llamada a XSelectInput en el constructor) y se gestionarán como
         * corresponda, sirviendose de los distintos "handlers" de eventos.
         * @param event El evento que se ha producido.
         * @return true para evitar que el evento sea tratado con normalidad, es
         *         decir, cuando ya lo tratamos nosotros, false para que el
         *         evento se trate connormalidad.
         *
         * @~english
         * Reimplement the method QApplication::x11EventFilter. In this method
         * recives all events that will be managed by the WM (previously calling
         * XSelectInput function in the constructor) and manage it as appropiate
         * using the correct event handler.
         * @param event The event that occurred.
         * @return true if you want to stop the event from being processed, ie
         *         when we treat ourselves, false for normal event dispatching.
         */
        virtual bool x11EventFilter(XEvent* event);

    public:

        /**
         * @~spanish
         * Constructor.
         * @param argc Número de argumentos recibidos por consola.
         * @param argv Lista de argumentos.
         *
         * @~english
         * Constructor.
         * @param argc Number of arguments received by console.
         * @param argv Argument list.
         */
        EggWM(int argc, char** argv);

        /**
         * @~spanish
         * Destructor.
         *
         * @~english
         * Destructor.
         */
        virtual ~EggWM();

#if QT_VERSION >= 0x050000
        MyXcbEventFilter myXEv;
#endif
};

#endif // EGGWM_H
