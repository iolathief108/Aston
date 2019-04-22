
#pragma once

#include <utility>
#include <Windows.h>
#include <iostream>
#include <vector>

class CoreWrapper {

public:
    explicit CoreWrapper(const std::string &name, const unsigned int &bufferSize)
    {
        this->name       = name;
        this->bufferSize = bufferSize;
        init();
    }

    virtual ~CoreWrapper()
    {
        destroyBuffer();
    }

    /**
     *
     * @param pData pointer to data
     * @param size size of the data to be write
     */
    void writeByte(const void *pData, unsigned int size)
    {
        memcpy(pBuffer, pData, size);
    }

    void writeByte(std::vector<unsigned char> &data)
    {
        writeByte(&data[0], bufferSize > data.size() ? data.size() : bufferSize);
    }

    void writeByte(std::vector<unsigned char> &data, unsigned int size)
    {
        writeByte(&data[0], bufferSize > size ? size : bufferSize);
    }

    void getBuffer(void *&pSharedBuffer) const
    {
        pSharedBuffer = this->pBuffer;
    }

    void **getBuffer()
    {
        return &pBuffer;
    }

    void getData(std::vector<unsigned char> &buffer, unsigned int writtenSize)
    {
        buffer.reserve(writtenSize);

        if (writtenSize > bufferSize)
            writtenSize = bufferSize;

        for (unsigned int x = 0; x < writtenSize; x++) {
            buffer.push_back(*(static_cast<unsigned char *>(pBuffer) + x));
        }

    }

    std::string getName() const
    {
        return name;
    }

    unsigned int getBufferSize() const
    {
        return bufferSize;
    }

private:
    void init()
    {
        this->_objName += "Local\\";
        this->_objName += this->name;

        makeBuffer();
    }

    //return value was true if operation was success
    bool makeBuffer()
    {
        _mapFile = CreateFileMapping(
                INVALID_HANDLE_VALUE,
                nullptr,
                PAGE_READWRITE,
                0,
                bufferSize,
                _objName.c_str());

        pBuffer = MapViewOfFile(
                _mapFile,
                FILE_MAP_ALL_ACCESS,
                0,
                0,
                bufferSize);

        return _mapFile != nullptr && pBuffer != nullptr;
    }

    void destroyBuffer()
    {
        UnmapViewOfFile(pBuffer);
        CloseHandle(_mapFile);
    }

    std::string   name;
    unsigned long bufferSize{};
    void          *pBuffer;

    std::string _objName;
    HANDLE      _mapFile;

};



