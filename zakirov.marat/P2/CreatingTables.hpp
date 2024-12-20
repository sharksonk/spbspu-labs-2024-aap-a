#ifndef CREATINGTABLES_HPP
#define CREATINGTABLES_HPP
#include <cstddef>

namespace zakirov
{
  void tylor_string(double point, size_t addition_depth, double error);
  void tylor_table(double left, double right, size_t addition_depth,
      double kStep, double kError);
}

#endif
