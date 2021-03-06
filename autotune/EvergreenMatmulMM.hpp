// Copyright 2012 Chris Jang (fastkor@gmail.com) under The Artistic License 2.0

#ifndef _CHAI_EVERGREEN_MATMUL_MM_HPP_
#define _CHAI_EVERGREEN_MATMUL_MM_HPP_

#include <ostream>
#include <set>
#include <string>
#include <vector>

#include "ArrayBuf.hpp"
#include "CodeVars.hpp"
#include "EvergreenMatmulBase.hpp"
#include "OCLdevice.hpp"

namespace chai_internal {

namespace Evergreen {

////////////////////////////////////////
// Evergreen::MatmulMMBase

class MatmulMMBase : public MatmulBase
{
protected:
    MatmulMMBase(void);
    virtual ~MatmulMMBase(void);

    // inner product accumulation
    std::string assignMAD(
                    const std::vector< std::vector< PrivateVar > >& accum,
                    const std::vector< std::vector< PrivateVar > >& valueA,
                    const std::vector< std::vector< PrivateVar > >& valueB,
                    const size_t j,         // output row
                    const size_t k,         // output component
                    const size_t l ) const; // inner product component

    // inner product loop reordering
    std::ostream& assignMAD(
                      std::ostream& os,
                      const size_t loopOrder, // 3! = 6 combinations
                      const std::vector< std::vector< PrivateVar > >& accum,
                      const std::vector< std::vector< PrivateVar > >& valueA,
                      const std::vector< std::vector< PrivateVar > >& valueB )
                      const;

public:
    std::string kernelForename(void) const;

    bool validParams(void) const;
    bool getParams(std::vector<size_t>& params) const;
    std::string exogenousKey(void) const;

    void toggleParamMarks(void);                               // pure virtual
    bool getParams(std::set< std::vector<size_t> >& paramSet); // pure virtual
    void setParams(const std::vector<size_t>& params);         // pure virtual
    std::string kernelName(void) const;                        // pure virtual
    std::vector<size_t> globalWorkItems(void) const;           // pure virtual
    std::vector<size_t> localWorkItems(void) const;            // pure virtual
    size_t numberFlops(void) const;                            // pure virtual
};

////////////////////////////////////////
// Evergreen::MatmulMM

class MatmulMM : public MatmulMMBase,
                 protected ParamInlineDim,
                 protected ParamLoopOrder,
                 protected ParamGlobalID
{
    ArrayBuf* _A;
    ArrayBuf* _B;
    ArrayBuf* _C;

    enum CheckOutputMode
    {
        NO_CHECK,
        SENTINEL_CHECK,
        PARANOID_CHECK
    };

    CheckOutputMode _checkOutputMode;
    bool            _checkOutputTouched;
    double          _paranoidLimit;

    // GEMM is alpha times AB plus beta times C
    double _alpha;
    double _beta;

    const size_t _deviceIndex;

    bool setArgsInternal(OCLkernel& ckernel,
                         ArrayBuf* A,
                         ArrayBuf* B,
                         ArrayBuf* C,
                         const double alpha,
                         const double beta);

public:
    MatmulMM(const size_t deviceIndex);
    ~MatmulMM(void);

    // validate calculation
    void noCheck(void);
    void sentinelCheck(void);
    void paranoidCheck(const double absDiffLimit);

    // (autotuning) allocate buffers and set kernel matrix arguments
    bool setArgs(OCLdevice& cdev,
                 OCLkernel& ckernel);

    // invoke kernel on real data
    bool setArgs(OCLkernel& ckernel,
                 ArrayBuf* A,
                 ArrayBuf* B,
                 ArrayBuf* C,
                 const double alpha = 1,
                 const double beta = 0);

    void clearArgs(void);

    // data transfer
    bool syncInput(void);
    bool syncOutput(void);

    // check output, sometimes bad kernels do nothing
    bool checkOutput(void);

    // prints the kernel source
    std::ostream& print(std::ostream&) const;
};

}; // namespace Evergreen

}; // namespace chai_internal

#endif
