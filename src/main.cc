#include <array>
#include <cstdint>
#include <iostream>
#include <string>

#include "components.hh"

enum state {
  uninitialised,
  vectoring,
};

std::array<uint8_t, 1> status{// 7 cycles to initialise processor
                              10};

namespace reg {
uint16_t pc = 0;
}

namespace bus {
uint16_t abus = 0;
uint8_t dbus = 0;
}  // namespace bus

void log() {
  // std::cout << std::bitset<16>(reg::pc) << " " << std::bitset<16>(bus::abus)
  //           << " " << std::bitset<8>(bus::dbus) << "\n";
}

inline constexpr uint16_t resetVectorL = 0xFFFC % 0x8000;
inline constexpr uint16_t resetVectorH = 0xFFFD % 0x8000;

template <size_t N>
void initialise(std::array<uint8_t, N>& _status, uint32_t& cycleBuffer,
                uint8_t& dbus, uint16_t& abus, uint16_t& pc) {
  while (_status[uninitialised] > 2 && cycleBuffer) {
    cycleBuffer -= 1;
    _status[uninitialised] -= 1;
    log();
  }

  if (_status[uninitialised] == 2) {
    abus = resetVectorL;
    dbus = rom[abus];
    if (pc == 0) {
      pc = dbus;
    } else {
      // Clear lower 8 bits
      pc &= 0b1111'1111 << 8;
      pc |= dbus;
    }
    _status[uninitialised] -= 1;

    log();
  } else if (_status[uninitialised] == 1) {
    abus = resetVectorH;
    dbus = rom[abus];
    if (pc == 0) {
      pc = dbus << 8;
    } else {
      pc &= 0b1111'1111;
      pc |= dbus << 8;
    }
    _status[uninitialised] -= 1;

    log();
  }

  return;
}

int main(int argc [[maybe_unused]], const char** argv [[maybe_unused]],
         const char** envp [[maybe_unused]]) {
  for (uint32_t cycleBuffer; true;) {
    std::string instructionBuffer;

    std::cout << "> ";
    std::getline(std::cin, instructionBuffer, '\n');

    // Count clock pulses
    for (std::string::const_iterator it = instructionBuffer.cbegin();
         it != instructionBuffer.cend(); ++it) {
      switch (*it) {
        case 'q':
          goto cleanup;

        case 'P':
        case 'p':
          cycleBuffer += 1;
          break;

        default:
          continue;
      }
    }

    if (status[uninitialised]) {
      initialise(status, cycleBuffer, bus::dbus, bus::abus, reg::pc);
      if (!status[uninitialised]) {
        std::cout << "initialised\n";
      }
    }
  }

cleanup:

  return 0;
}
