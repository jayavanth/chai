// Copyright 2011 Chris Jang (fastkor@gmail.com) under The Artistic License 2.0

#include "DispatchInterp.hpp"

using namespace std;

namespace chai_internal {

DispatchInterp::DispatchInterp(void)
    : _outStack(NULL) { }

DispatchInterp::~DispatchInterp(void)
{
    for (map< uint32_t, BaseInterp* >::const_iterator
         it = _dtable.begin();
         it != _dtable.end();
         it++)
    {
        delete (*it).second;
    }
}

void DispatchInterp::addOp(const uint32_t opCode, BaseInterp* op)
{
    _dtable[opCode] = op;
}

void DispatchInterp::setContext(stack< vector< FrontMem* > >& outStack)
{
    _outStack = &outStack;
}

void DispatchInterp::setContext(VectorTrace& vt)
{
    for (map< uint32_t, BaseInterp* >::const_iterator
         it = _dtable.begin();
         it != _dtable.end();
         it++)
    {
        (*it).second->setContext(vt);
    }
}

void DispatchInterp::setContext(MemManager& mm)
{
    for (map< uint32_t, BaseInterp* >::const_iterator
         it = _dtable.begin();
         it != _dtable.end();
         it++)
    {
        (*it).second->setContext(mm);
    }
}

void DispatchInterp::visit(const uint32_t variable, const uint32_t version)
{
    _tmpVariable.push_back(variable);
    _tmpVersion.push_back(version);
}

void DispatchInterp::visit(const uint32_t opCode)
{
    // lookup operation handler
    BaseInterp* op = _dtable[opCode];

    // push any stream arguments first
    for (size_t i = 0; i < _tmpVariable.size(); i++)
    {
        op->push(_tmpVariable[i], _tmpVersion[i], *_outStack);
    }
    _tmpVariable.clear();
    _tmpVersion.clear();

    // dispatch to operation handler
    op->eval(_tmpStak, *_outStack);
}

void DispatchInterp::visit(const double scalar)
{
    _tmpStak.push(scalar);
}

void DispatchInterp::visit(void* ptr)
{
    _tmpStak.push(ptr);
}

}; // namespace chai_internal
