#include <semantic/expr-nodes.h>
#include <semantic/function.h>
#include <semantic/class.h>
#include <report/errors.h>

#include "node-base.h"

using namespace grammar;

void Statement::acceptElse(misc::position const& else_pos, Block&&)
{
    error::partialStmtNotMatch(else_pos, "else", "if");
}

void Statement::acceptCatch(misc::position const& catch_pos, Block&&)
{
    error::partialStmtNotMatch(catch_pos, "catch", "try");
}

bool Expression::empty() const
{
    return false;
}

bool Expression::isName() const
{
    return false;
}

std::string Expression::reduceAsName() const
{
    error::invalidName(pos);
    return "";
}

void Expression::reduceAsParam(ParamReducingEnv& env, int) const
{
    return env.addParam(reduceAsName());
}

std::string Expression::reduceAsProperty() const
{
    return reduceAsName();
}

util::sptr<semantic::Expression const> Expression::reduceAsLeftValue() const
{
    error::invalidLeftValue(pos);
    return util::mkptr(new semantic::Undefined(pos));
}

util::sptr<semantic::Expression const> Expression::reduceAsArg(ArgReducingEnv&, int) const
{
    return reduceAsExpr();
}
