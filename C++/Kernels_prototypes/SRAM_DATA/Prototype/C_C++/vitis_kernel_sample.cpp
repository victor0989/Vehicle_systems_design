// Vitis C/C++
    auto device = xrt::device(device_index);
    auto uuid = device.load_xclbin(binaryFile);

    auto ip1 = xrt::ip(device, uuid, "Vadd_A_B:{Vadd_A_B_1}");
    // Allocate Buffer in Global Memory
    auto ip1_boA = xrt::bo(device, vector_size_bytes, 1);
    auto ip1_boB = xrt::bo(device, vector_size_bytes, 1);
    // Map the contents of the buffer object into host memory
    auto bo0_map = ip1_boA.map<int*>();
    auto bo1_map = ip1_boB.map<int*>();


buf_addr[0] = ip1_boA.address();
buf_addr[1] = ip1_boB.address();
// synchronize buffer content device
ip1_boA.sync(XCL_BO_SYNC_BO_TO_DEVICE);
ip1_boB.sync(XCL_BO_SYNC_BO_TO_DEVICE);

// Reg A (input address)
ip1.write_register(A_OFFSET, buf_addr[0]);
ip1.write_register(A_OFFSET + 4, buf_addr[0] >> 32);

// Staert kernel control register
unit32 axi_ctrl = IP_START;
ip1.write_register(USER_OFFSET, axi_ctrl);

//wait until the IP is done by Reading from the control register
while (axi_ctrl != IP_IDLE) {
    axi_ctrl = ip1.read_register(USER_OFFSET);
}

// Sync the output buffer back to the host
memory
ip1_boB.sync(XCL_SYNC_BO_FROM_DEVICE);

//To support user-managed RTL kernels, you will write your host application using the XRT Native API, defining the RTL kernel as an xrt::ip object as shown above, and accessing the kernel through register read and write.

