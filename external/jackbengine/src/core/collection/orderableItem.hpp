//
// orderableItem.hpp
// jackbengine
//
// Created by Damien Bendejacq on 19/10/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#ifndef __ORDERABLE_ITEM_H__
#define __ORDERABLE_ITEM_H__

class OrderableItem
{
public:
    virtual int order() const = 0;
};

#endif // __ORDERABLE_ITEM_H__
