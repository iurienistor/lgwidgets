/**
 * File name: RkObject.h
 * Project: Redkite (A small GUI toolkit)
 *
 * Copyright (C) 2020 Iurie Nistor
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

#ifndef RK_OBJECT_H
#define RK_OBJECT_H

#include "Rk.h"
#include "RkObserver.h"

#include <unordered_set>

class RkEvent;
class RkEventQueue;

class RK_EXPORT RkObject {
 public:
        explicit RkObject(RkObject *parent = nullptr);
        virtual ~RkObject();
        Rk::ObjectType type() const;
        RkObject* parent() const;
        const std::unordered_set<RkObject*>& children() const;
        void setEventQueue(RkEventQueue* queue);
        RkEventQueue* eventQueue() const;
        virtual void event(RkEvent *event);
        void rk__add_bound_object(RkObject* obj);

 protected:
        RK_DECLARE_IMPL(RkObject);
        explicit RkObject(RkObject *parent, std::unique_ptr<RkObjectImpl> impl);
        void rk__add_observer(std::unique_ptr<RkObserver> observer);
        const std::vector<std::unique_ptr<RkObserver>>& rk__observers() const;

 private:
        RK_DISABLE_COPY(RkObject);
        RK_DISABLE_MOVE(RkObject);
        void addChild(RkObject *child);
        void removeChild(RkObject *child);
        void removeObservers(RkObject *ob);
        void removeBoundObject(RkObject *obj);
        friend class RkEventQueue;
};

#endif // RK_OBJECT_H
