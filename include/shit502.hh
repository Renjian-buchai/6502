#if !defined(SHIT502_HH)
#define SHIT502_HH

#include <array>
#include <cstdint>

/// @brief Assumes 5V
class shit502 {
 public:
  uint16_t addressBus = 0;
  uint8_t dataBus = 0;
  bool busEnable = 0;

  bool IRQB = 1;
  bool MLB = 1;
  bool NMIB = 1;
  bool NC = 0;

  bool RWB = 1;
  bool RDY = 1;
  bool RESB = 1;

  bool SOB = 1;

  bool SYNC = 0;

  double VDD = 0;
  double VSS = 0;

  bool VPB = 1;

  enum class flags : uint8_t { N, V, US_M, B, D, I, Z, C };

  enum class errStatus : uint8_t {
    NONE,
    FRIED,
  };

 public:
  shit502();

  shit502(double VDD, double VSS = 0);

  uint8_t readA() const;
  uint8_t readX() const;
  uint8_t readY() const;
  uint8_t readSP() const;
  uint16_t readIR() const;
  uint16_t readPC() const;
  const std::array<bool, 8>& readP() const;

  errStatus clock();

 private:
  uint8_t A;
  uint8_t X;
  uint8_t Y;
  uint8_t SP;
  std::array<bool, 8> P;
  uint16_t IR;
  uint16_t PC;
};

#endif