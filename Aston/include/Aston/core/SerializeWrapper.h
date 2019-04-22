#pragma once

#include <bitsery/bitsery.h>
#include <bitsery/adapter/buffer.h>
#include <bitsery/traits/vector.h>

using Buffer = std::vector<unsigned char>;
using OutputAdapter = bitsery::OutputBufferAdapter<Buffer>;
using InputAdapter = bitsery::InputBufferAdapter<Buffer>;

class SerializeWrapper {
public:

    template<typename T>
    unsigned int serialize(const T &client, Buffer &buffer)
    {
        return bitsery::quickSerialization<OutputAdapter>(buffer, client);
    }

    template<typename T>
    bool deserialize(Buffer &buffer, unsigned int &writtenSize, T &res)
    {
        auto state = bitsery::quickDeserialization<InputAdapter>({buffer.begin(), writtenSize}, res);
        return state.first == bitsery::ReaderError::NoError && state.second;
    }
};

