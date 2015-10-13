#ifndef __STEKIN_SEMANTIC_FUNCTION_H__
#define __STEKIN_SEMANTIC_FUNCTION_H__

#include <output/function.h>

#include "block.h"

namespace semantic {

    struct Function {
        virtual ~Function() {}
        Function(Function const&) = delete;

        Function(misc::position const& ps
               , std::string const& func_name
               , std::vector<std::string> const& params
               , Block func_body)
            : pos(ps)
            , name(func_name)
            , param_names(params)
            , body(std::move(func_body))
        {}

        util::sptr<output::Function const> compile(util::sref<SymbolTable> st) const
        {
            return this->compile(st, false);
        }

        util::sptr<output::Statement const> compileAsMemberFunc(util::sref<SymbolTable> st) const
        {
            return this->_compileBody(st, true);
        }

        virtual util::sptr<output::Function const> compile(
                    util::sref<SymbolTable> st, bool class_space) const;

        misc::position const pos;
        std::string const name;
        std::vector<std::string> const param_names;
        Block const body;
    protected:
        virtual util::sptr<output::Statement const> _compileBody(
                    util::sref<SymbolTable> st, bool class_space) const;
    };

    struct RegularAsyncFunction
        : Function
    {
        RegularAsyncFunction(misc::position const& pos
                           , std::string const& func_name
                           , std::vector<std::string> const& params
                           , int async_param_idx
                           , Block func_body)
            : Function(pos, func_name, params, std::move(func_body))
            , async_param_index(async_param_idx)
        {}

        int const async_param_index;

        util::sptr<output::Function const> compile(
                    util::sref<SymbolTable> st, bool class_space) const;
    protected:
        util::sptr<output::Statement const> _compileBody(
                    util::sref<SymbolTable> st, bool class_space) const;
    };

}

#endif /* __STEKIN_SEMANTIC_FUNCTION_H__ */
