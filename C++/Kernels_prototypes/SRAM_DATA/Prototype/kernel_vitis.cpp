//C++ develop- kernels-API/RAM-verilog/IP block design, conf ADAM
//Developing Applications
//Programming Model
//Writing the Software Application
//Developing PL Kernels using C++
//Packaging RTL Kernels
//Programming Versal AI Engines

//the code for C++ kernels written and optimized in an HLS component can be compiled in the Vitis tools either from the v++ command line as explained in //Compiling C/C++ PL Kernels, or from a System project in the Vitis unified IDE as explained in Using the Vitis Unified IDE.

extern "C" {
           void kernel_function(int *in, int *out, int size);
        }

//XRT-Managed Kernels	User-Managed Kernels
//The object class for an XRT-managed kernel is xrt::kernel
//The software application communicates with the XRT-managed kernel using higher-level commands such as set_arg, run, and wait
//The user does not need to know the low-level details of the programmable registers and kernel execution protocols
//Control and status registers provide XRT with a known interface to interact with the kernel, which makes these high-level commands possible
//If needed, it is also possible to control an XRT-managed kernel as a user-managed kernel (using atomic register reads and write)
//OpenCL API can also be used with XRT-managed kernels (cl::kernel)

//desarrollar
#include <xrt/xrt_device.h>
#include <experimental/xrt_xclbin.h>

//Setup the Environment
unsigned int device_index = 0;
std::string binaryFile = parser.value("kernel.xclbin");
std::cout << "Open the device" << device_index << std::endl;
auto device = xrt::device(device_index);
std::cout << "Load the xclbin " << binaryFile << std::endl;
auto uuid = device.load_xclbin(binaryFile);


#include <xrt/xrt_kernel.h>
#include <xrt/xrt_bo.h>

auto krnl = xrt::kernel(device, uuid, "vadd");

std::cout << "Allocate Buffer in Global Memory";
auto bo0 = xrt::bo(device, vector_size_bytes, krnl.group_id(0));
auto bo1 = xrt::bo(device, vector_size_bytes, krnl.group_id(1));
auto bo_out = xrt::bo(device, vector_size_bytes, krnl.group_id(2));

//kernel object(xrt::kernel)
//kernel.group_id().

krnl1 = xrt::kernel(device, xclbin_uuid, "vadd::{vadd_1,vadd_2}";
krnl2 = xrt::kernel(device, xclbin_uuid, "vadd:{vadd_3}");

krnl1 can be used to launch the CUs vadd_1 and vadd_2 which have matching connectivity, and krnl2 can be used to launch vadd_3, which has different connectivity.

std::cout << "Allocate Buffer in Global Memory\n";
auto bo0 = xrt::bo(device, vector_size_bytes, krnl.group_id(0));
auto bo1 = xrt::bo(device, vector_size_bytes, krnl.group_id(1));
auto bo_out = xrt::bo(device, vector_size_bytes, krnl.group_id(2));

sing xrt::bo::sync()
Use xrt::bo::sync to sync data from the host to the device with XCL_BO_SYNC_TO_DEVICE flag, or from the device to the host with XCL_BO_SYNC_FROM_DEVICE flag using xrt::bo::write, or xrt::bo::read to write the buffer from the host application, or read the buffer from the device.

bo0.write(buff_data);
bo0.sync(XCL_BO_SYNC_TO_DEVICE);
bo1.write(buff_data);
bo1.sync(XCL_SYNC_BO_TO_DEVICE);
…
bo_out.sync(XCL_BO_SYNC_BO_FROM_DEVICE);
bo_out.read(buff_data);

