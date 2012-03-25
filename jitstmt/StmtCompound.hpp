// Copyright 2012 Chris Jang (fastkor@gmail.com) under The Artistic License 2.0

#ifndef _CHAI_STMT_COMPOUND_HPP_
#define _CHAI_STMT_COMPOUND_HPP_

#include <vector>

#include "Stmt.hpp"

namespace chai_internal {

////////////////////////////////////////
// compound AST statement

class StmtCompound : public Stmt
{
    std::vector< Stmt* > _stmts;

public:
    StmtCompound(void);
    ~StmtCompound(void);

    bool swappable(const Stmt&) const;

    void accept(VisitStmt&);

    std::vector< Stmt* >& stuffInside(void);
    const std::vector< Stmt* >& stuffInside(void) const;
};

}; // namespace chai_internal

#endif
