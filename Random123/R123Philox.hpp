// Copyright 2012 Chris Jang (fastkor@gmail.com) under The Artistic License 2.0

#ifndef _CHAI_R123_PHILOX_HPP_
#define _CHAI_R123_PHILOX_HPP_

#include <ostream>
#include <set>

#include "R123Util.hpp"

namespace chai_internal {

////////////////////////////////////////
// Random123 OpenCL Philox PRNG

class R123Philox : public R123Util
{
    const std::set< size_t > _precSet;
    const std::set< size_t > _vecLenSet;

    void _mulhilo(std::ostream& os, const size_t PR) const;
    void _bumpkey(std::ostream& os, const size_t PR, const size_t VL) const;
    void _roundFun(std::ostream& os, const size_t PR, const size_t VL) const;
    void _roundEnum(std::ostream& os, const size_t PR, const size_t VL) const;
    void _typedef(std::ostream& os, const size_t PR, const size_t VL) const;
    void _keyinit(std::ostream& os, const size_t PR, const size_t VL) const;
    void _R(std::ostream& os, const size_t PR, const size_t VL) const;
    void _entry(std::ostream& os, const size_t PR, const size_t VL) const;

public:
    R123Philox(const std::set< size_t >& precSet,
               const std::set< size_t >& vecLenSet);

    void print(std::ostream& os) const;
};

}; // namespace chai_internal

#endif
