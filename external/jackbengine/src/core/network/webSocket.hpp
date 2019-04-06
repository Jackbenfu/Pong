//
// webSocket.hpp
// jackbengine
//
// Created by Damien Bendejacq on 18/02/2016.
// Copyright © 2016 Damien Bendejacq. All rights reserved.
//

#ifndef __WEB_SOCKET_H__
#define __WEB_SOCKET_H__

#include <unordered_map>
#include <string>
#include <vector>
#include <arpa/inet.h>

#include "easywsclient/easywsclient.hpp"

#include "common.hpp"
#include "webSocketEvent.hpp"
#include "systemSocketMessageType.hpp"

namespace Jackbengine {

template<typename TListener>
class WebSocket
{
public:
    explicit WebSocket(const TListener& listener);
    virtual ~WebSocket();

    using Deserializer = const WebSocketEvent*(*)(const byte *data, int size);
    using Callback = void(TListener::*)(const WebSocketEvent *message);

    bool open(const std::string& url);
    void close();

    void poll();

    void setCallback(short type, Callback callback);

protected:
    void send(short type, std::vector<byte>& data) const;

    void setDeserializer(short type, Deserializer deserializer, bool acknowledge);

    const TListener& m_listener;

    std::unordered_map<short, Deserializer> m_deserializers;
    std::unordered_map<short, bool> m_acknowledges;
    std::unordered_map<short, Callback> m_callbacks;

private:
    easywsclient::WebSocket::pointer m_socket = nullptr;

    const int MESSAGE_HEADER_SIZE = 6;

    bool parseMessage(const std::vector<byte>& message, short *type, int *id);
    void acknowledgeMessage(int id);
};

union MessageTypeUnion
{
    short type;
    byte bytes[2];
};

union MessageIdUnion
{
    int id;
    byte bytes[4];
};

template<typename TListener>
WebSocket<TListener>::WebSocket(const TListener& listener)
    : m_listener(listener)
{ }

template<typename TListener>
WebSocket<TListener>::~WebSocket()
{
    close();

    DELETE_SAFE(m_socket);
}

template<typename TListener>
bool WebSocket<TListener>::open(const std::string& url)
{
    if (nullptr == m_socket)
    {
        m_socket = easywsclient::WebSocket::from_url(url);

        return nullptr != m_socket;
    }

    return false;
}

template<typename TListener>
void WebSocket<TListener>::close()
{
    if (nullptr != m_socket)
    {
        m_socket->close();
    }
}

template<typename TListener>
void WebSocket<TListener>::poll()
{
    if (easywsclient::WebSocket::CLOSED == m_socket->getReadyState())
    {
        close();
        return;
    }

    m_socket->poll();

    m_socket->dispatchBinary(
        [this](const std::vector<byte>& message)
        {
            short messageType;
            int messageId;

            if (!parseMessage(message, &messageType, &messageId))
            {
                throw std::runtime_error("Invalid network message, does not contain type or id");
            }

            auto itd = m_deserializers.find(messageType);
            if (m_deserializers.end() == itd)
            {
                throw std::runtime_error("No deserializer found for network message [" + std::to_string(messageType) + "]");
            }

            auto messageData = message.data() + MESSAGE_HEADER_SIZE;
            auto messageSize = message.size() - MESSAGE_HEADER_SIZE;

            auto event = (itd->second)(messageData, messageSize);

            auto itc = m_callbacks.find(messageType);
            if (m_callbacks.end() == itc)
            {
                throw std::runtime_error("No callback found for message [" + std::to_string(messageType) + "]");
            }

            (const_cast<TListener&>(m_listener).*itc->second)(event);

            auto ita = m_acknowledges.find(messageType);
            if (m_acknowledges.end() != ita && ita->second)
            {
                acknowledgeMessage(messageId);
            }
        }
    );
}

template<typename TListener>
void WebSocket<TListener>::send(short type, std::vector<byte>& payload) const
{
    if (nullptr != m_socket)
    {
        union MessageTypeUnion typeUnion;
        typeUnion.type = htons(type);
        payload.insert(payload.begin(), typeUnion.bytes[1]);
        payload.insert(payload.begin(), typeUnion.bytes[0]);

        m_socket->sendBinary(payload);
    }
}

template<typename TListener>
void WebSocket<TListener>::setCallback(short type, Callback callback)
{
    m_callbacks[type] = callback;
}

template<typename TListener>
void WebSocket<TListener>::setDeserializer(short type, Deserializer deserializer, bool acknowledge)
{
    m_deserializers[type] = deserializer;
    m_acknowledges[type] = acknowledge;
}

template<typename TListener>
bool WebSocket<TListener>::parseMessage(const std::vector<byte> &message, short *type, int *id)
{
    if (MESSAGE_HEADER_SIZE > message.size())
    {
        return false;
    }

    union MessageTypeUnion typeUnion;
    typeUnion.bytes[0] = message[0];
    typeUnion.bytes[1] = message[1];
    *type = ntohs(typeUnion.type);

    union MessageIdUnion idUnion;
    idUnion.bytes[0] = message[2];
    idUnion.bytes[1] = message[3];
    idUnion.bytes[2] = message[4];
    idUnion.bytes[3] = message[5];
    *id = ntohl(idUnion.id);

    printf("%6i ", *id);

    return true;
}

template<typename TListener>
void WebSocket<TListener>::acknowledgeMessage(int id)
{
    std::vector<byte> data;

    union MessageIdUnion idUnion;
    idUnion.id = htonl(id);
    data.push_back(idUnion.bytes[0]);
    data.push_back(idUnion.bytes[1]);
    data.push_back(idUnion.bytes[2]);
    data.push_back(idUnion.bytes[3]);

    printf("%6i ACKNOWLEDGE\n", id);

    send(SystemSocketMessageType::ACKNOWLEDGE, data);
}

} // namespace Jackbengine

#endif // __WEB_SOCKET_H__
