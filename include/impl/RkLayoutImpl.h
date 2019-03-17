/**
 * File name: RkLayoutImpl.h
 * Project: Redkite (A small GUI toolkit)
 *
 * Copyright (C) 2019 Iurie Nistor (http://quamplex.com/redkite)
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

#ifndef RK_LAYOUT_IMPL_H
#define RK_LAYOUT_IMPL_H

#include "RkLayout.h"

class RkLayoutElement {
 public:
        enum class Type : int {
                BoxWidget,
                BoxSpace,
                BoxLayout,
                GridWidget,
                GridLayout,
        };

        enum  Alignment : int {
                Unaligned,
                AlignLeft,
                AlignRight,
        };

        RkLayoutElement();
        virtual ~RkLayoutElement();
        virtual Type type() const = 0;
        Alignemnt alignment() const;
        void setAlignemnt(Alignment align);
        virtual std::pair<int, int> minSize() const = 0;
        virtual std::pair<int, int> maxSize() const = 0;
        virtual void setSize(std::pair<int, int>) = 0;
        virtual void setWidth(int width) = 0;
        virtual void setHeight(int height) = 0;
        virtual void width(int width) const = 0;
        virtual void hight(int height) const = 0;
        virtual bool fixedWidth() const = 0;
        virtual bool fixedHeight() const = 0;
        bool strachable() const;
        void setStachable(bool strachable);

 private:
        Type elementType;
        Alignment elementAlignemnt;
        bool isStrachable;
};

class RkLayout::RkLayoutImpl {
 public:
        explicit RkLayoutImpl(RkLayout* interface, RkWidget* parent = nullptr);
        virtual ~RkLayoutImpl();
        void addElement(std::unique_ptr<RkLayoutElement> elements);
        void setPadding(int padding);
        int padding();
        virtual void update() = 0;
        std::list<RkLayoutElement*>& layoutElements();
        RkWidget* getParentWidget();
        std::list<RkLayoutElement*>& getLayoutElements();

 private:
        RK_DISABLE_COPY(RkLayoutImpl)
        RK_DISABLE_MOVE(RkLayoutImpl)
        RK_DECALRE_INTERFACE_PTR(RkLayout)
        RkWidget *parentWidget;
        std::list<RkLayoutElement*> layoutElements;
        int elementsPagging;
};

#endif // RK_LAYOUT_IMPL_H