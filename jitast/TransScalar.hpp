// Copyright 2012 Chris Jang (fastkor@gmail.com) under The Artistic License 2.0

#ifndef _CHAI_TRANS_SCALAR_HPP_
#define _CHAI_TRANS_SCALAR_HPP_

#include <cstddef>

#include "BaseTrans.hpp"

namespace chai_internal {

////////////////////////////////////////
// dispatched operation

class TransScalar : public BaseTrans
{
    const size_t _precision;

protected:
    BaseAst* sub_eval(void) const;

public:
    TransScalar(const size_t precision);
};

}; // namespace chai_internal

#endif