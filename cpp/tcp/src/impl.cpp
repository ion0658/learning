
#include <sys/socket.h>
#include <string.h>
#include <vector>
#include <errno.h>

#include "impl.h"
#include "app_protocol.h"

RustLikeResult::Result<int, int> send_ping(int fd)
{
    ProtocolHeaderT header{};
    header.magic = PROTOCOL_MAGIC;
    header.type = ProtocolType::PING;
    header.length = 0;
    if (send(fd, &header, sizeof(header), 0) < 0)
    {
        return RustLikeResult::Result<int, int>::Err(errno);
    }
    return RustLikeResult::Result<int, int>::Ok(0);
}

RustLikeResult::Result<int, int> send_pong(int fd)
{
    ProtocolHeaderT header{};
    header.magic = PROTOCOL_MAGIC;
    header.type = ProtocolType::PONG;
    header.length = 0;
    if (send(fd, &header, sizeof(header), 0) < 0)
    {
        return RustLikeResult::Result<int, int>::Err(errno);
    }
    return RustLikeResult::Result<int, int>::Ok(0);
}

RustLikeResult::Result<int, int> send_data(int fd, const uint8_t *data, size_t length)
{
    if (data == nullptr || length == 0)
    {
        return RustLikeResult::Result<int, int>::Err(-1);
    }

    int err = 0;
    size_t buffer_size = sizeof(ProtocolHeaderT) + length;
    std::vector<uint8_t> buffer(buffer_size, 0);
    do
    {
        ProtocolHeaderT *header = reinterpret_cast<ProtocolHeaderT *>(buffer.data());
        header->magic = PROTOCOL_MAGIC;
        header->type = ProtocolType::DATA;
        header->length = length;
        memcpy(header->data, data, length);
        err = send(fd, buffer.data(), buffer.size(), 0) < 0;
    } while (0);
    if (err < 0)
    {
        return RustLikeResult::Result<int, int>::Err(errno);
    }
    return RustLikeResult::Result<int, int>::Ok(0);
}

RustLikeResult::Result<int, int> send_error(int fd, int code)
{
    size_t buffer_size = sizeof(ProtocolHeaderT) + sizeof(code);
    std::vector<uint8_t> buffer(buffer_size, 0);

    ProtocolHeaderT *header = reinterpret_cast<ProtocolHeaderT *>(buffer.data());
    header->magic = PROTOCOL_MAGIC;
    header->type = ProtocolType::ERROR;
    header->length = sizeof(code);
    memcpy(header->data, &code, sizeof(code));
    if (send(fd, buffer.data(), buffer.size(), 0) < 0)
    {
        return RustLikeResult::Result<int, int>::Err(errno);
    }
    return RustLikeResult::Result<int, int>::Ok(0);
}

RustLikeResult::Result<ProtocolHeaderT, int> recv_header(int fd)
{
    ProtocolHeaderT header = {};
    if (recv(fd, &header, sizeof(ProtocolHeaderT), 0) < 0)
    {
        return RustLikeResult::Result<ProtocolHeaderT, int>::Err(errno);
    }
    return RustLikeResult::Result<ProtocolHeaderT, int>::Ok(header);
}

RustLikeResult::Result<std::vector<uint8_t>, int> recv_body(int fd, size_t length)
{
    std::vector<uint8_t> buffer(length, 0);
    if (length == 0)
    {
        return RustLikeResult::Result<std::vector<uint8_t>, int>::Ok(buffer);
    }

    if (recv(fd, buffer.data(), length, 0) < 0)
    {
        return RustLikeResult::Result<std::vector<uint8_t>, int>::Err(errno);
    }
    return RustLikeResult::Result<std::vector<uint8_t>, int>::Ok(buffer);
}

RustLikeResult::Result<std::vector<uint8_t>, int> recv_data(int fd)
{
    auto result = recv_header(fd);
    if (result.is_err())
    {
        return RustLikeResult::Result<std::vector<uint8_t>, int>::Err(result.inner.error);
    }
}