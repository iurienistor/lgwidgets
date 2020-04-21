/**
 * File name: RkEventQueue.h
 * Project: Redkite (A small GUI toolkit)
 *
 * Copyright (C) 2019 Iurie Nistor <http://geontime.com>
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

#ifndef RK_EVENT_QUEUE_H
#define RK_EVENT_QUEUE_H

#include "Rk.h"
#include "RkObject.h"
#include "RkAction.h"

//struct RkWindowId;
//struct RkNativeWindowInfo;
class RkEvent;
class RkTimer;

class RK_EXPORT RkEventQueue {
 public:
        RkEventQueue();
        virtual ~RkEventQueue();
        void addObject(RkObject *obj);
        void removeObject(RkObject *obj);
        void postEvent(RkObject *obj, std::unique_ptr<RkEvent> event);
        void postAction(std::unique_ptr<RkAction> act);
        /* void postEvent(const RkWindowId &id, const std::shared_ptr<RkEvent> &event); */
        /* void postEvent(const RkNativeWindowInfo &info, const std::shared_ptr<RkEvent> &event); */
        /* void processEvent(const RkWindowId &id, const std::shared_ptr<RkEvent> &event); */
        /* void processEvent(const RkNativeWindowInfo &info, const std::shared_ptr<RkEvent> &event); */
        //        void processEvent(RkObject *obj, RkEvent *event);
        void subscribeTimer(RkTimer *timer);
        void unsubscribeTimer(RkTimer *timer);
        void processEvents();
        void processActions();
        void processTimers();
        void processQueue();
        void clearObjectEvents(const RkObject *obj);
        void clearObjectActions(const RkObject *obj);
        void clearEvents();
        void clearActions();
        void clearTimers();
        void clearQueue();

 protected:
        RK_DECLARE_IMPL(RkEventQueue);
        RkEventQueue(const std::shared_ptr<RkEventQueueImpl> &impl);

 private:
        RK_DISABLE_COPY(RkEventQueue);
        RK_DISABLE_MOVE(RkEventQueue);
};

#endif // RK_EVENT_QUEUE_H
