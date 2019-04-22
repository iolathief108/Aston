#pragma once

#include "Aston/core/CoreWrapper.h"
#include "Aston/core/SerializeWrapper.h"
#include "Aston/core/SizeBuffer.h"
#include "bitsery/traits/string.h"


class ObjectBuffer {
public:
    ObjectBuffer(const char *name, unsigned int size) : bufferSize(size)
    {
        //std::string n = name;
        this->pName = new std::string(name);
        init();
    }

    ~ObjectBuffer()
    {
        delete pWrittenSize;
        delete pBuffer;
        delete pSerializer;
        delete pBufferSize;
        delete pName;
    }

    template<class T>
    void writeObject(const T &obj)
    {
        Buffer       buffer;
        unsigned int writtenSize = pSerializer->serialize(obj, buffer);

        pWrittenSize->write(writtenSize);
        pBufferSize->write(buffer.size());

        pBuffer->writeByte(buffer);
    }

    template<class T>
    void getObject(T &obj)
    {
        Buffer buffer;
        UINT   writtenSize;
        UINT   bufferSize;
        pWrittenSize->read(writtenSize);
        pBufferSize->read(bufferSize);

        pBuffer->getData(buffer, bufferSize);
        pSerializer->deserialize(buffer, writtenSize, obj);
    }


private:
    void init()
    {
        std::string writtenSizeName = *this->pName;
        writtenSizeName += "writtenSizeInfo";

        std::string bufferSizeName = *this->pName;
        bufferSizeName += "bufferSizeInfo";

        pWrittenSize = new SizeBuffer(writtenSizeName.c_str());
        pBufferSize  = new SizeBuffer(bufferSizeName.c_str());

        pBuffer     = new CoreWrapper(*this->pName, this->bufferSize);
        pSerializer = new SerializeWrapper();

        pBuffer->getBuffer(pBufferPrimitive);
    }

private:
    std::string  *pName;
    unsigned int bufferSize;
    void         *pBufferPrimitive{};

    SizeBuffer *pWrittenSize{};
    SizeBuffer *pBufferSize{};

    CoreWrapper      *pBuffer{};
    SerializeWrapper *pSerializer{};
};



