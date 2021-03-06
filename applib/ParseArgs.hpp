// Copyright 2012 Chris Jang (fastkor@gmail.com) under The Artistic License 2.0

#ifndef _CHAI_PARSE_ARGS_HPP_
#define _CHAI_PARSE_ARGS_HPP_

#include <cstddef>

namespace chai_internal {
    namespace Evergreen {
        class MatmulBase;
        class MatmulMM;
        class MatmulMV;
    };
    class OCLInit;
    class StandardEM;
};

namespace chai {

////////////////////////////////////////
// parse command line arguments

class ParseArgs
{
    const int _argc;
    char**    _argv;

    size_t _deviceIdx;
    size_t _batching;
    size_t _general;
    size_t _precA;
    size_t _precB;
    size_t _precC;
    size_t _vecLenA;
    size_t _vecLenB;
    size_t _vecLenC;
    size_t _dimM;
    size_t _dimN;
    size_t _dimK;
    size_t _transA;
    size_t _transB;

    bool _includeSendDataToDevice;
    bool _includeReadDataFromDevice;

    bool _noInterpret;

    void setVecLength(const char tok,
                      size_t& vecLen) const;

    void setVecLengthLimits(const size_t vecLen,
                            const bool useImages,
                            size_t& startIdx,
                            size_t& stopIdx) const;

    size_t precChar(const char UISD) const;

public:
    ParseArgs(int argc, char *argv[]);

    // used by regular DSL applications
    ParseArgs& noInterpret(void);
    void initVM(void);

#ifdef _CHAI_OCL_INIT_HPP_
    // used by application tools with direct control over runtime
    bool getOpt(chai_internal::OCLinit& cinit);
    size_t getDeviceIndex(void) const;
#endif

#ifdef _CHAI_EVERGREEN_MATMUL_BASE_HPP_
    void setOpt(chai_internal::Evergreen::MatmulMMBase& kernelGen);
    void setOpt(chai_internal::Evergreen::MatmulMVBase& kernelGen);

    void setOpt(chai_internal::Evergreen::MatmulBase& kernelGen,
                size_t& startA,
                size_t& startB,
                size_t& startC,
                size_t& stopA,
                size_t& stopB,
                size_t& stopC);
#endif

#ifdef _CHAI_STANDARD_EM_HPP_
    void setOpt(chai_internal::StandardEM& stdEM);
#endif
};

}; // namespace chai

#endif
