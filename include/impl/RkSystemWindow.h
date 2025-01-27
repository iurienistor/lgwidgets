/**
 * File name: RkSystemWindow.h
 * Project: Redkite (A small GUI toolkit)
 *
 * Copyright (C) 2023 Iurie Nistor
 *
 * This file is part of Redkite.
 *
 * Redkite is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#ifndef RK_SYSTEM_WINDOW_H
#define RK_SYSTEM_WINDOW_H

#include "Rk.h"
#include "RkObject.h"
#include "RkEventQueue.h"
#include "RkCanvas.h"
#include "RkRect.h"
#include "RkColor.h"
#include "RkFont.h"
#include "RkImage.h"

class RkEvent;
class RkCloseEvent;
class RkKeyEvent;
class RkMouseEvent;
class RkWheelEvent;
class RkDropEvent;
class RkMoveEvent;
class RkResizeEvent;
class RkPaintEvent;
class RkShowEvent;
class RkHideEvent;
class RkFocusEvent;
class RkHoverEvent;
class RkMain;
struct RkWindowId;
class RkNativeWindowInfo;
class RkWidget;

#ifdef RK_OS_WIN
class RkWindowWin;
#else // GNU/Linux
class RkWindowX;
#endif // GNU/Linux

class RkSystemWindow: public RkCanvas {
public:
        using WidgetEventList = std::vector<std::pair<RkWidget*, std::unique_ptr<RkEvent>>>;
        explicit RkSystemWindow(RkWidget *widget,
                                const RkNativeWindowInfo *parent);
        virtual ~RkSystemWindow();
        void show(bool b = true);
        void setTitle(const std::string &title);
        const std::string& title() const;
        const RkNativeWindowInfo* nativeWindowInfo() const;
        RkCanvasInfo* getCanvasInfo() const override;
        RkImage& getImage();
        void freeCanvasInfo() override;
        RkWidget* parentWidget() const;
        RkWindowId id() const;
        void setSize(const RkSize &size);
        RkSize size() const;
        void setPosition(const RkPoint &p);
        RkPoint position() const;
        void setBackgroundColor(const RkColor &color);
        const RkColor& background() const;
        RkRect rect() const;
        void update();
        void close();
        bool isClosed() const;
        void setTopWidget(RkWidget *widget);
        RkWidget* getTopWidget() const;
        void setFocus(bool b = true);
        bool hasFocus() const;
        void setPointerShape(Rk::PointerShape shape);
        Rk::PointerShape pointerShape() const;
        void setScaleFactor(double factor);
        double scaleFactor() const;
        WidgetEventList processEvent(const RkEvent *event);
        void setFocusWidget(RkWidget *widget, bool b = true);
        RkWidget* getFocusWidget() const;
#ifdef RK_OS_WIN
        void setEventQueue(RkEventQueue *eventQueue);
#endif

protected:
        WidgetEventList processMouseEvent(const RkMouseEvent* event);
        RkWidget* getWidgetByGlobalPoint(RkWidget *widget, const RkPoint &globalPoint);
        bool containsGlobalPoint(RkWidget* widget, const RkPoint &globalPoint) const;
        bool widgetExists(RkWidget *widget) const;
        bool isSystemWindowCanvas() const override;

private:
        bool isWindowClosed;
        RkWidget *topWidget;
#ifdef RK_OS_WIN
        std::unique_ptr<RkWindowWin> platformWindow;
#else // GNU/Linux
        std::unique_ptr<RkWindowX> platformWindow;
#endif // GNU/Linux
        std::string windowTitle;
        RkSize windowSize;
        RkColor windowBackground;
        RkImage systemWindowImage;
        RkWidget *hoverWidget;
        RkWidget *mouseCaptureWidget;
        RkWidget *focusWidget;
};

#endif // RK_SYSTEM_WINDOW_H
