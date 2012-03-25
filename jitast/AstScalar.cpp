// Copyright 2012 Chris Jang (fastkor@gmail.com) under The Artistic License 2.0

#include "AstScalar.hpp"
#include "PrecType.hpp"

namespace chai_internal {

////////////////////////////////////////////////
// scalar_u32, scalar_i32
// scalar_f32, scalar_f64

AstScalar::AstScalar(const uint32_t uintValue)
    : BaseAst(1, 1, PrecType::UInt32),
      _uintValue(uintValue),
      _intValue(0),
      _floatValue(0),
      _doubleValue(0) { }

AstScalar::AstScalar(const int32_t intValue)
    : BaseAst(1, 1, PrecType::Int32),
      _uintValue(0),
      _intValue(intValue),
      _floatValue(0),
      _doubleValue(0) { }

AstScalar::AstScalar(const float floatValue)
    : BaseAst(1, 1, PrecType::Float),
      _uintValue(0),
      _intValue(0),
      _floatValue(floatValue),
      _doubleValue(0) { }

AstScalar::AstScalar(const double doubleValue)
    : BaseAst(1, 1, PrecType::Double),
      _uintValue(0),
      _intValue(0),
      _floatValue(0),
      _doubleValue(doubleValue) { }

uint32_t AstScalar::uintValue(void) const
{
    return _uintValue;
}

int32_t AstScalar::intValue(void) const
{
    return _intValue;
}

float AstScalar::floatValue(void) const
{
    return _floatValue;
}

double AstScalar::doubleValue(void) const
{
    return _doubleValue;
}

void AstScalar::accept(VisitAst& v)
{
    v.visit(*this);
}

}; // namespace chai_internal
