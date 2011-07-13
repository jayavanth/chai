// Copyright 2011 Chris Jang (fastkor@gmail.com) under The Artistic License 2.0

#ifndef _CHAI_TRANS_CONVERT_HPP_
#define _CHAI_TRANS_CONVERT_HPP_

#include "BaseTrans.hpp"

namespace chai_internal {

////////////////////////////////////////
// dispatched operation

class TransConvert : public BaseTrans
{
    const bool _isDouble;

protected:
    BaseAst* sub_eval(void) const;

public:
    TransConvert(const bool isDouble);
};

}; // namespace chai_internal

#endif
