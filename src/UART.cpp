#include <UART.hpp>

namespace CASK {

UART::UART(std::ostream *out) : out(out) { }

__uint32_t UART::Read32(__uint32_t startAddress, __uint32_t size, char* dst) {

    if (size != 4) {
        *out << "WARNING: UART only accepts IO in four-byte words" << std::endl;
        return 0;
    }

    if (startAddress >= 4) {
        // *out << "WARNING: out-of-bounds read from UART regs" << std::endl;
        return 0;
    }

    if (startAddress == UART_REG_TXFIFO) {
        return size;
    }

    // TODO proper bounds checks
    for (unsigned int i = 0; i < size; i++) {
        dst[i] = state[startAddress+i];
    }

    return size;
}

__uint32_t UART::Write32(__uint32_t startAddress, __uint32_t size, char* src) {

    if (startAddress >= 4) {
        // *out << "WARNING: out-of-bounds write to UART regs" << std::endl;
        return 0;
    }

    // TODO proper bounds checks
    for (unsigned int i = 0; i < size; i++)
        if (startAddress + i == UART_REG_TXFIFO) {
            *out << src[i];
        } else if (startAddress + i != UART_REG_RXFIFO) {
            state[startAddress + i] = src[i];
        }   

    return size;
}

__uint64_t UART::Write64(__uint64_t startAddress, __uint64_t size, char* src) {
    return Write32(startAddress & 0xffffffff, size, src);
}

__uint128_t UART::Write128(__uint128_t startAddress, __uint128_t size, char* src) {
    return Write32(startAddress & 0xffffffff, size, src);
}

__uint64_t UART::Read64(__uint64_t startAddress, __uint64_t size, char* dst) {
    return Read32(startAddress & 0xffffffff, size, dst);
}

__uint128_t UART::Read128(__uint128_t startAddress, __uint128_t size, char* dst) {
    return Read32(startAddress & 0xffffffff, size, dst);
}

__uint32_t UART::Fetch32(__uint32_t startAddress, __uint32_t size, char* dst) {
    return 0;
}

__uint64_t UART::Fetch64(__uint64_t startAddress, __uint64_t size, char* dst) {
    return 0;
}

__uint128_t UART::Fetch128(__uint128_t startAddress, __uint128_t size, char* dst) {
    return 0;
}

} // namespace CASK
