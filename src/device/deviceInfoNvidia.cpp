#if !defined(DLM_CL_SKIP_DEVICE_NVIDIA)
#include "dlm/env/macro.h"
DLM_CMODULE_START
#include "cl/cl_ext_nvidia.h"
DLM_CMODULE_END
#include "dlm/cl/device.hpp"
using namespace dlmcl;

void DeviceInfoBuilder::fillNvidia(void) noexcept
{
    cl_int err;

    cl_uint warp;
    err = clGetDeviceInfo(dev, CL_DEVICE_WARP_SIZE_NV, sizeof(warp), &warp, NULL);
    if (err == CL_SUCCESS)
        deviceInfo.compute.warp = warp;

    cl_bool isSMA;
    err = clGetDeviceInfo(dev, CL_DEVICE_INTEGRATED_MEMORY_NV, sizeof(isSMA), &isSMA, NULL);
    if (err == CL_SUCCESS)
        deviceInfo.memory.isSMA = (isSMA != 0);

}

#endif // DLM_CL_SKIP_DEVICE_AMD
