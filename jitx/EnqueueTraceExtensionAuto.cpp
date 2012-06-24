// Copyright 2012 Chris Jang (fastkor@gmail.com) under The Artistic License 2.0

#include "EnqueueTrace.hpp"
#include "StmtExtensionAuto.hpp"

using namespace std;

namespace chai_internal {

////////////////////////////////////////
// VisitStmt

void EnqueueTrace::visit(StmtExtensionAuto& s)
{
    if (_failure) return;
    if (_printer) _printer->visit(s);

    if (! s.extensionEnqueueAuto(_memMgr, _vt))
        _failure = true;
}

}; // namespace chai_internal
