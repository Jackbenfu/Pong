//
// orderedHeterogeneousCollection.hpp
// jackbengine
//
// Created by Damien Bendejacq on 18/10/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#ifndef __ORDERED_HETEROGENEOUS_COLLECTION_H__
#define __ORDERED_HETEROGENEOUS_COLLECTION_H__

#include <map>
#include <string>
#include <memory>
#include <algorithm>
#include "common.hpp"
#include "orderableItem.hpp"

namespace Jackbengine {

template<typename TBase>
class OrderedHeterogeneousCollection
{
    DISALLOW_COPY_AND_MOVE(OrderedHeterogeneousCollection<TBase>)

public:
    OrderedHeterogeneousCollection() = default;
    ~OrderedHeterogeneousCollection() = default;

    template<typename TItem>
    TItem& get() const;

    template<typename TItem>
    bool any() const;

    template<typename TItem, typename ...Args>
    void add(Args&& ...args);

    template<typename TItem>
    void remove();

    template<typename TItem>
    void enable(bool enable);

    template<typename TFunction>
    void apply(TFunction function);

private:
    template<typename TItem>
    std::tuple<size_t, bool, std::unique_ptr<TBase>>& find();
    template<typename TItem>
    const std::tuple<size_t, bool, std::unique_ptr<TBase>>& find() const;

    std::map<int, std::tuple<size_t, bool, std::unique_ptr<TBase>>> m_collection;
};

template<typename TBase>
template<typename TItem>
TItem& OrderedHeterogeneousCollection<TBase>::get() const
{
    static_assert(std::is_base_of<TBase, TItem>::value);

    const auto& tuple = find<TItem>();

    if (!std::get<1>(tuple))
    {
        throw std::runtime_error(
            std::string("Item is disabled: ") + std::string(GET_TYPE_NAME(TItem))
        );
    }

    return dynamic_cast<TItem&>(*std::get<2>(tuple));
}

template<typename TBase>
template<typename TItem>
bool OrderedHeterogeneousCollection<TBase>::any() const
{
    static_assert(std::is_base_of<TBase, TItem>::value);

    const auto typeId = GET_TYPE_ID(TItem);
    const auto it = std::find_if(
        m_collection.cbegin(),
        m_collection.cend(),
        [&typeId](const auto& pair) { return std::get<0>(pair.second) == typeId; }
    );

    return it != m_collection.end() && std::get<0>(it->second);
}

template<typename TBase>
template<typename TItem, typename ...Args>
void OrderedHeterogeneousCollection<TBase>::add(Args&& ...args)
{
    static_assert(std::is_base_of<TBase, TItem>::value);
    static_assert(std::is_base_of<OrderableItem, TBase>::value);

    if (any<TItem>())
    {
        throw std::runtime_error(
            std::string("Item already exists: ") + std::string(GET_TYPE_NAME(TItem))
        );
    }

    const auto typeId = GET_TYPE_ID(TItem);

    auto item = std::make_unique<TItem>(std::forward<Args>(args)...);
    const auto key = (OrderableItem*)(item.get());

    m_collection.insert(
        std::make_pair(
            key->order(),
            std::make_tuple(typeId, true, std::move(item))
        )
    );
}

template<typename TBase>
template<typename TItem>
void OrderedHeterogeneousCollection<TBase>::remove()
{
    static_assert(std::is_base_of<TBase, TItem>::value);

    const auto typeId = GET_TYPE_ID(TItem);
    const auto it = std::find_if(
        m_collection.cbegin(),
        m_collection.cend(),
        [&typeId](const auto& pair) { return std::get<0>(pair.second) == typeId; }
    );

    if (it != m_collection.end())
    {
        m_collection.erase(it->first);
    }
}

template<typename TBase>
template<typename TItem>
void OrderedHeterogeneousCollection<TBase>::enable(bool enable)
{
    static_assert(std::is_base_of<TBase, TItem>::value);

    auto& tuple = find<TItem>();

    std::get<1>(tuple) = enable;
}

template<typename TBase>
template<typename TFunction>
void OrderedHeterogeneousCollection<TBase>::apply(TFunction function)
{
    for (const auto& pair : m_collection)
    {
        const auto& tuple = pair.second;
        if (!std::get<1>(tuple))
        {
            continue;
        }

        auto& item = *std::get<2>(tuple);
        function(item);
    }
}

template<typename TBase>
template<typename TItem>
std::tuple<size_t, bool, std::unique_ptr<TBase>>& OrderedHeterogeneousCollection<TBase>::find()
{
    const auto typeId = GET_TYPE_ID(TItem);
    const auto it = std::find_if(
        m_collection.cbegin(),
        m_collection.cend(),
        [&typeId](const auto& pair) { return std::get<0>(pair.second) == typeId; }
    );

    if (it == m_collection.end())
    {
        throw std::runtime_error(
            std::string("Item does not exist: ") + std::string(GET_TYPE_NAME(TItem))
        );
    }

    return it->second;
}

template<typename TBase>
template<typename TItem>
const std::tuple<size_t, bool, std::unique_ptr<TBase>>& OrderedHeterogeneousCollection<TBase>::find() const
{
    const auto typeId = GET_TYPE_ID(TItem);
    const auto it = std::find_if(
        m_collection.cbegin(),
        m_collection.cend(),
        [&typeId](const auto& pair) { return std::get<0>(pair.second) == typeId; }
    );

    if (it == m_collection.end())
    {
        throw std::runtime_error(
            std::string("Item does not exist: ") + std::string(GET_TYPE_NAME(TItem))
        );
    }

    return it->second;
}

} // namespace Jackbengine

#endif // __ORDERED_HETEROGENEOUS_COLLECTION_H__
