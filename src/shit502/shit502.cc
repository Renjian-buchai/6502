#include "../../include/shit502.hh"

#include <csignal>

shit502::shit502() = default;

shit502::shit502(double live, double gnd)
    : addressBus(0),
      dataBus(0),
      busEnable(0),
      IRQB(1),
      MLB(1),
      NMIB(1),
      NC(1),
      RWB(1),
      RDY(1),
      RESB(1),
      SOB(1),
      SYNC(0),
      VDD(live),
      VSS(gnd) {}

uint8_t shit502::readA() const { return A; }

uint8_t shit502::readX() const { return X; }

uint8_t shit502::readY() const { return Y; }

uint8_t shit502::readSP() const { return SP; }

uint16_t shit502::readIR() const { return IR; }

uint16_t shit502::readPC() const { return PC; }

const std::array<bool, 8>& shit502::readP() const { return P; }

#include <iostream>

/// @brief Pulses the clock and steps 1 clock cycle
/// @note Raises signal 0xFFFC to indicate to the program to update all
/// components
/// @return None if unpowered, or there is no error
shit502::errStatus shit502::clock() {
  if (VDD - VSS < -0.3 || VDD - VSS > 7.0) {
    return errStatus::FRIED;
  }

  if (VDD - VSS < 4.75 || VDD - VSS > 5.25) {
    return errStatus::NONE;
  }

  static uint8_t initialised = 9;

  if (initialised > 0) {
    if (initialised == 2) {
      addressBus = 0xFFFC;
      busEnable = 1;
      RWB = 1;
      std::raise(0xFFFC);  // Update signal
      PC = dataBus;
      std::cout << "PC: " << PC;
    } else if (initialised == 1) {
      addressBus = 0xFFFD;
      busEnable = 1;
      RWB = 1;
      std::raise(0xFFFC);
      PC |= dataBus << 8;
      std::cout << "PC: " << PC;
    }

    std::cout << initialised;

    initialised -= 1;

    return errStatus::NONE;
  }

  return errStatus::NONE;
}
