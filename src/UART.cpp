#include <UART.hpp>

namespace CASK {

UART::UART(std::ostream *out) : out(out) { }

__uint32_t UART::Read32(__uint32_t startAddress, __uint32_t size, char* dst) {

    if (size != 4) {
        *out << "WARNING: UART only accepts IO in four-byte words" << std::endl;
        return 0;
    }

    if (startAddress % 4 != 0) {
        *out << "WARNING: UART only accepts four-byte aligned start addresses" << std::endl;
        return 0;
    }

    dst[0] = dst[1] = dst[2] = dst[3] = 0;

    switch (startAddress) {
    case UART_REG_TXFIFO * 4:
        // Reading back from the TXFIFO queue is nonsense but not illegal
        break;
    case UART_REG_RXFIFO * 4:
        // Reading 4B from the RX FIFO
        dst[0] = state[startAddress+0];
        dst[1] = state[startAddress+1];
        dst[2] = state[startAddress+2];
        dst[3] = state[startAddress+3];
        break;
    case UART_REG_TXCTRL * 4:
        dst[0] = txen ? 1 : 0;
        break;
    case UART_REG_RXCTRL * 4:
        dst[0] = rxen ? 1 : 0;
        break;
    case UART_REG_IE * 4:
        *out << "WARNING: Unimplemented UART register" << std::endl;
        break;
    case UART_REG_IP * 4:
        *out << "WARNING: Unimplemented UART register" << std::endl;
        break;
    case UART_REG_DIV * 4:
        *out << "WARNING: Unimplemented UART register" << std::endl;
        break;
    default:
        *out << "WARNING: Out-of-bounds read from UART regs" << std::endl;
        break;
    }

    return size;
}

__uint32_t UART::Write32(__uint32_t startAddress, __uint32_t size, char* src) {

    if (size != 4) {
        *out << "WARNING: UART only accepts IO in four-byte words" << std::endl;
        return 0;
    }

    if (startAddress % 4 != 0) {
        *out << "WARNING: UART only accepts four-byte aligned start addresses" << std::endl;
        return 0;
    }

    // TODO def'd values are not mul4 and they should be
    switch (startAddress) {
    case UART_REG_TXFIFO * 4:
        for (unsigned int i = 0; i < size; i++) {
            *out << src[i];
        }  
        break;
    case UART_REG_RXFIFO * 4:
        // Writing to the RX buffer is nonsense
        break;
    case UART_REG_TXCTRL * 4:
        txen = src[0] != 0;
        break;
    case UART_REG_RXCTRL * 4:
        rxen = src[0] != 0;
        break;
    case UART_REG_IE * 4:
        *out << "WARNING: Write to unimplemented UART register" << std::endl;
        break;
    case UART_REG_IP * 4:
        *out << "WARNING: Write to unimplemented UART register" << std::endl;
        break;
    case UART_REG_DIV * 4:
        *out << "WARNING: Write to unimplemented UART register" << std::endl;
        break;
    default:
        *out << "WARNING: Out-of-bounds write to UART regs" << std::endl;
        break;
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
