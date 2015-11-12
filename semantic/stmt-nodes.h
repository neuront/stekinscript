#ifndef __STEKIN_SEMANTIC_STATEMENT_NODES_H__
#define __STEKIN_SEMANTIC_STATEMENT_NODES_H__

#include <string>

#include <util/pointer.h>

#include "node-base.h"
#include "block.h"

namespace semantic {

    struct Arithmetics
        : Statement
    {
        Arithmetics(misc::position const& pos, util::sptr<Expression const> e)
            : Statement(pos)
            , expr(std::move(e))
        {}

        void compile(BaseCompilingSpace& space) const;
        bool isAsync() const;

        util::sptr<Expression const> const expr;
    };

    struct Branch
        : Statement
    {
        Branch(misc::position const& pos, util::sptr<Expression const> p, Block c, Block a)
            : Statement(pos)
            , predicate(std::move(p))
            , consequence(std::move(c))
            , alternative(std::move(a))
        {}

        void compile(BaseCompilingSpace& space) const;
        bool isAsync() const;

        util::sptr<Expression const> const predicate;
        Block const consequence;
        Block const alternative;
    };

    struct Return
        : Statement
    {
        Return(misc::position const& pos, util::sptr<Expression const> retval)
            : Statement(pos)
            , ret_val(std::move(retval))
        {}

        void compile(BaseCompilingSpace& space) const;
        bool isAsync() const;

        util::sptr<Expression const> const ret_val;
    };

    struct NameDef
        : Statement
    {
        NameDef(misc::position const& pos, std::string const& n, util::sptr<Expression const> i)
            : Statement(pos)
            , name(n)
            , init(std::move(i))
        {}

        void compile(BaseCompilingSpace& space) const;
        bool isAsync() const;

        std::string const name;
        util::sptr<Expression const> const init;
    };

    struct Extern
        : Statement
    {
        Extern(misc::position const& pos, std::vector<std::string> const& n)
            : Statement(pos)
            , names(n)
        {}

        void compile(BaseCompilingSpace& space) const;

        bool isAsync() const { return false; }

        std::vector<std::string> const names;
    };

    struct Export
        : Statement
    {
        Export(misc::position const& pos
             , std::vector<std::string> const& e
             , util::sptr<Expression const> v)
                : Statement(pos)
                , export_point(std::move(e))
                , value(std::move(v))
        {}

        void compile(BaseCompilingSpace& space) const;
        bool isAsync() const;

        std::vector<std::string> const export_point;
        util::sptr<Expression const> const value;
    };

    struct AttrSet
        : Statement
    {
        AttrSet(misc::position const& pos
              , util::sptr<Expression const> s
              , util::sptr<Expression const> v)
            : Statement(pos)
            , set_point(std::move(s))
            , value(std::move(v))
        {}

        void compile(BaseCompilingSpace& space) const;
        bool isAsync() const;

        util::sptr<Expression const> const set_point;
        util::sptr<Expression const> const value;
    };

    struct ExceptionStall
        : Statement
    {
        ExceptionStall(misc::position const& pos, Block fl, Block c)
            : Statement(pos)
            , try_block(std::move(fl))
            , catch_block(std::move(c))
        {}

        void compile(BaseCompilingSpace& space) const;
        bool isAsync() const;

        Block const try_block;
        Block const catch_block;
    };

    struct Throw
        : Statement
    {
        Throw(misc::position const& pos, util::sptr<Expression const> e)
            : Statement(pos)
            , exception(std::move(e))
        {}

        void compile(BaseCompilingSpace& space) const;

        bool isAsync() const { return false; }

        util::sptr<Expression const> const exception;
    };

}

#endif /* __STEKIN_SEMANTIC_STATEMENT_NODES_H__ */
