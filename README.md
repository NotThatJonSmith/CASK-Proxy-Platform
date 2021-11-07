# CASK-Proxy-Platform
Device models as apparently expected by the RISC-V Proxy Kernel

## TODOs

The very next thing to do on this is to remove EventQueue and instead use a
plain old STL queue, and then I can remove EventQueue from CASK entirely,
because that was a really overzealous move.

Then, this will develop only as quickly as needed to support the software that
developers care to run on the proxy kernel. It's likely that interactivity with
the UART will require interrupts to be fleshed out, which will make the core
local interruptor device necessary.