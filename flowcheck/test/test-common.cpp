#include <test/common.h>
#include <test/phony-errors.h>
#include <test/phony-warnings.h>
#include <proto/function.h>
#include <util/string.h>

#include "test-common.h"

using namespace test;

DataTree& DataTree::operator()(misc::position const& pos
                             , NodeType const& type
                             , std::string const& str)
{
    BaseType::operator()(type, FlowcheckData(pos), str);
    return *this;
}

DataTree& DataTree::operator()(misc::position const& pos, NodeType const& type)
{
    BaseType::operator()(type, FlowcheckData(pos));
    return *this;
}

DataTree& DataTree::operator()(misc::position const& pos, NodeType const& type, int size)
{
    BaseType::operator()(type, FlowcheckData(pos, size));
    return *this;
}

DataTree& DataTree::operator()(misc::position const& pos
                             , NodeType const& type
                             , std::string const& str
                             , int size)
{
    BaseType::operator()(type, FlowcheckData(pos, size), str);
    return *this;
}

DataTree& DataTree::operator()(NodeType const& type)
{
    BaseType::operator()(type, FlowcheckData());
    return *this;
}

DataTree& DataTree::operator()(NodeType const& type, std::string const& str)
{
    BaseType::operator()(type, FlowcheckData(), str);
    return *this;
}

std::ostream& operator<<(std::ostream& os, FlowcheckData const& data)
{
    return -1 == data.size
        ? (os << data.pos)
        : (os << data.pos << " size=" << data.size);
}

NodeType const test::BOOLEAN("boolean");
NodeType const test::INTEGER("integer");
NodeType const test::FLOATING("floating");
NodeType const test::STRING("string");
NodeType const test::LIST("list");
NodeType const test::BINARY_OP("binary operation");
NodeType const test::PRE_UNARY_OP("prefix unary operation");
NodeType const test::CALL("call");
NodeType const test::REFERENCE("var reference");
NodeType const test::LIST_ELEMENT("list element");
NodeType const test::LIST_INDEX("list index");

NodeType const test::LIST_PIPELINE("list pipeline");
NodeType const test::PIPE_MAP("pipe map");
NodeType const test::PIPE_FILTER("pipe filter");

NodeType const test::VAR_DEF("var definition");

NodeType const test::STATEMENT("statement");
NodeType const test::ARITHMETICS("arithmetics");
NodeType const test::RETURN("return");
NodeType const test::RETURN_NOTHING("return nothing");

NodeType const test::FUNC_DECL("func decl");
NodeType const test::PARAMETER("parameter");

NodeType const test::SCOPE_BEGIN("scope begin");
NodeType const test::SCOPE_END("scope end");

NodeType const test::BRANCH("branch");

void FlowcheckTest::SetUp()
{
    clearErr();
    clearWarn();
}

void FlowcheckTest::TearDown()
{
    DataTree::verify();
}
