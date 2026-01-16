#include <protocols/ScreenCopy/GScreenCopyManager.h>
#include <linux/input-event-codes.h> 

#include <iostream>
#include <cstdlib>
#include <string>
#include <array>

#include <LCompositor.h>
#include <LSeat.h>
#include <LKeyboard.h>
#include <LScene.h>
#include <LLauncher.h>
#include <LTimer.h>
#include <LGlobal.h>
#include <LClient.h>

#include "compositor.h"


void Compositor::initialized()
{
    setenv("WAYLAND_DISPLAY", getenv("LOUVRE_WAYLAND_DISPLAY"), 1);

    assets = std::make_unique<Assets>();
    systemd = std::make_unique<Systemd>();

    /* Configure already plugged input devices, check the Seat class */
    G::seat()->configureInputDevices();

    Int32 totalWidth { 0 };

    // Initializes and arranges outputs from left to right
    setupOutputs()

    /* Sets a background wallpaper using swaybg */;
    LLauncher::launch(std::string("swaybg -m fill -i ") + (compositor()->defaultAssetsPath() / "wallpaper.png").string());

    /* Launches Waybar */;
    LLauncher::launch("waybar");

    /* Launches some bottom panel */
    LLauncher::launch("sfwbar");
}

void Compositor::uninitialized()
{
    /* All factory objects, client resources and backends are still available at this point.
     * Textures should be released here before the graphic backend is uninitialized */

    assets.reset();
    systemd.reset();
}

LFactoryObject *Compositor::createObjectRequest(LFactoryObject::Type objectType, const void *params)
{
    if (objectType == LFactoryObject::Type::LOutput)
        return new Output(params);

    if (objectType == LFactoryObject::Type::LClient)
        return new Client(params);

    if (objectType == LFactoryObject::Type::LSurface)
        return new Surface(params);

    if (objectType == LFactoryObject::Type::LToplevelRole)
        return new ToplevelRole(params);

    if (objectType == LFactoryObject::Type::LPopupRole)
        return new PopupRole(params);

    if (objectType == LFactoryObject::Type::LSubsurfaceRole)
        return new SubsurfaceRole(params);

    if (objectType == LFactoryObject::Type::LSessionLockRole)
        return new SessionLockRole(params);

    if (objectType == LFactoryObject::Type::LCursorRole)
        return new CursorRole(params);

    if (objectType == LFactoryObject::Type::LDNDIconRole)
        return new DNDIconRole(params);

    if (objectType == LFactoryObject::Type::LSeat)
        return new Seat(params);

    if (objectType == LFactoryObject::Type::LPointer)
        return new Pointer(params);

    if (objectType == LFactoryObject::Type::LKeyboard)
        return new Keyboard(params);

    if (objectType == LFactoryObject::Type::LTouch)
        return new Touch(params);

    if (objectType == LFactoryObject::Type::LClipboard)
        return new Clipboard(params);

    if (objectType == LFactoryObject::Type::LDND)
        return new DND(params);

    if (objectType == LFactoryObject::Type::LSessionLockManager)
        return new SessionLockManager(params);

    /* Returning nullptr tells Louvre to use the default class for the given LFactoryObject type */
    return nullptr;
}

void Compositor::onAnticipatedObjectDestruction(LFactoryObject *object)
{
    if (object->factoryObjectType() == LFactoryObject::Type::LClient)
    {
        /* Bye bye client */
    }

    /* Do not delete the object! */
}

bool Compositor::createGlobalsRequest()
{
    /* The default imp creates all globals supported by Louvre */
    return LCompositor::createGlobalsRequest();
}

bool Compositor::globalsFilter(LClient *client, LGlobal *global)
{

#ifdef SETTINGS_XDG_DESKTOP_PORTAL_SCREENCAST_ONLY
    if (global->isType<Protocols::ScreenCopy::GScreenCopyManager>() && systemd && systemd->xdgDesktopPortalWlrPID != 0)
    {
        pid_t clientPID;
        client->credentials(&clientPID);

        if ((UInt32)clientPID != systemd->xdgDesktopPortalWlrPID)
            return false;
    }
#endif

    return true;
}