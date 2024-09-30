#include <csignal>
#include <iostream>

#include "../include/shit502.hh"

void update(int signal) { std::cout << "Updated with signal: " << signal; }

int main() {
  std::signal(0xFFFC, update);
  shit502 w65c02{};
  w65c02.VDD = 5;
  w65c02.VSS = 0;
  for (size_t i = 0; i < 9; ++i) {
    w65c02.clock();
  }
  return 0;
};