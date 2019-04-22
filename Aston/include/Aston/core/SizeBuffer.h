#pragma once

#include <utility>
#include "CoreWrapper.h"

class SizeBuffer {
private:
    std::string name;
    void        *pBuffer{};
    CoreWrapper *buffer{};

public:
    explicit SizeBuffer(std::string name)
    {
        this->name = std::move(name);
        init();
    }

    void write(const unsigned int &size)
    {
        buffer->writeByte(&size, 4);
    }

    void read(unsigned int &size)
    {
        memcpy(&size, pBuffer, 4);
    }

    ~SizeBuffer()
    {
        delete buffer;
    }

private:
    void init()
    {
        buffer = new CoreWrapper(this->name, 4);
        buffer->getBuffer(pBuffer);
    }

};