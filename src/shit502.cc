#include "../include/shit502.hh"

shit502::shit502() = default;

shit502::shit502(uint8_t live, uint8_t gnd)
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
      VSS(gnd),
      dv(live - gnd) {}

uint8_t shit502::readA() const { return A; }

uint8_t shit502::readX() const { return X; }

uint8_t shit502::readY() const { return Y; }

uint8_t shit502::readSP() const { return SP; }

uint16_t shit502::readIR() const { return IR; }

uint16_t shit502::readPC() const { return PC; }

const std::array<bool, 8>& shit502::readP() const { return P; }
