#pragma once
#ifndef _INCLUDE_APP_PROTOCOL_H
#define _INCLUDE_APP_PROTOCOL_H

#include <cstdint>

constexpr uint8_t PROTOCOL_MAGIC = 0xFF;
enum class ProtocolType : uint8_t
{
    PING = 0x00,
    PONG = 0x01,
    DATA = 0x02,
    ERROR = 0x03,
};

#pragma pack(push, 1)
struct ProtocolHeaderT
{
    uint8_t magic;
    ProtocolType type;
    uint16_t length;
    uint8_t data[0];
};
#pragma pack(pop)

#endif // _INCLUDE_APP_PROTOCOL_H
