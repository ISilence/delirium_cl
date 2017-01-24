#ifndef DLM_CL_MEMORY_HPP_
#define DLM_CL_MEMORY_HPP_
#include <stddef.h>

#include "dlm/env/system.h"
#include "dlm/allocator.hpp"
#include "dlm/cl/base.hpp"
#include "dlm/cl/device.hpp"
#include "dlm/cl/deviceInfo.hpp"

namespace dlmcl {



class Memory
{
protected:
    Device& device;
    size_t memsize;
    cl_mem_flags accessType;

    cl_mem deviceMemory;
    void* hostMemory;

    static cl_mem_flags getMapType(const cl_mem_flags accessType);
    static bool isAccessTypeValid(const cl_mem_flags accessType);

public:
    enum DLM_MEMORY_CONTEXT_TYPE {
        MCT_HOST,
        MCT_DEVICE
    };

    Memory(const Memory&) = delete;
    Memory(Device& device, size_t size, cl_mem_flags accessType) :
        device(device),
        memsize(size),
        accessType(accessType),
        hostMemory(nullptr)
    {
        if (!isAccessTypeValid(accessType))
            throw new CLException();
    }
    virtual ~Memory(void) {};
    virtual void switchToHost(cl_command_queue queue) = 0;
    virtual void switchToDevice(cl_command_queue queue) = 0;


    // ================
    //  helpers

    inline size_t getSize() const
    {
        return memsize;
    }

    inline cl_mem_flags getAccessType() const
    {
        return accessType;
    }

    inline cl_mem getDeviceMemory(void)
    {
        return deviceMemory;
    }

    inline void* getHostMemory(void)
    {
        return hostMemory;
    }

    inline void switchContext(cl_command_queue queue, enum DLM_MEMORY_CONTEXT_TYPE type)
    {
        if (type == MCT_HOST)
            switchToHost(queue);
        else
            switchToDevice(queue);
    }

    // ================
    // static api

    static Memory* getOptimal(Device& dev, size_t size, cl_mem_flags accessType);

};

class GenericMemory : public Memory
{
    bool isDevice;

public:
    GenericMemory(Device& device, size_t size, cl_mem_flags accessType);
    virtual ~GenericMemory();

    virtual void switchToHost(cl_command_queue queue) override;
    virtual void switchToDevice(cl_command_queue queue) override;
};


class HostMemory : public Memory
{
protected:
    cl_mem_flags maptype;
    bool isDeviceMode;

    HostMemory(Device& device): Memory(device, 0, CL_MEM_READ_WRITE), maptype(0), isDeviceMode(true) {}

public:
    HostMemory(Device& device, size_t size, cl_mem_flags accessType);
    virtual ~HostMemory();

    virtual void switchToHost(cl_command_queue queue) override;
    virtual void switchToDevice(cl_command_queue queue) override;
};


class DeviceMemory : public HostMemory
{
public:
    DeviceMemory(Device& device, size_t size, cl_mem_flags accessType);
};

} // ::dlmcl
#endif // DLM_CL_MEMORY_HPP_