#include <algorithm>
#include <map>

#include <output/stmt-nodes.h>
#include <output/expr-nodes.h>
#include <output/list-pipe.h>
#include <output/function.h>
#include <output/methods.h>
#include <output/name-mangler.h>
#include <util/string.h>

#include "test-common.h"

using namespace test;
using namespace output;

static void writeList(util::ptrarr<Expression const> const& list)
{
    list.iter([&](util::sptr<Expression const> const& member, int)
              {
                  member->str();
              });
}

void Block::write(std::ostream&) const
{
    DataTree::actualOne()(SCOPE_BEGIN);
    std::for_each(_local_decls.begin()
                , _local_decls.end()
                , [&](std::string const& s)
                  {
                      DataTree::actualOne()(FWD_DECL, s);
                  });
    _funcs.iter([&](util::sptr<Function const> const& func, int)
                {
                    func->write(dummyos());
                });
    _stmts.iter([&](util::sptr<Statement const> const& stmt, int)
                {
                    stmt->write(dummyos());
                });
    DataTree::actualOne()(SCOPE_END);
}

void Block::append(util::sptr<Block> b)
{
    _stmts.append(std::move(b->_stmts));
    _funcs.append(std::move(b->_funcs));
    _classes.append(std::move(b->_classes));
}

void Function::write(std::ostream&) const
{
    std::vector<std::string> params(parameters());
    DataTree::actualOne()(FUNCTION, mangledName(), params.size());
    std::for_each(params.begin()
                , params.end()
                , [&](std::string const& pn)
                  {
                      DataTree::actualOne()(PARAMETER, pn);
                  });
    body()->write(dummyos());
}

util::sptr<Expression const> Function::callMe(
        misc::position const& pos, util::ptrarr<Expression const> args) const
{
    return util::mkptr(new output::Call(
                pos, util::mkptr(new Reference(pos, mangledName())),
                std::move(args)));
}

util::sref<Statement const> RegularFunction::body() const
{
    return *body_stmt;
}

std::string RegularFunction::mangledName() const
{
    return name;
}

std::vector<std::string> RegularFunction::parameters() const
{
    return params;
}

std::vector<std::string> RegularAsyncFunction::parameters() const
{
    std::vector<std::string> p(params);
    p.insert(p.begin() + async_param_index, "# RegularAsyncParam");
    return p;
}

std::string RegularAsyncReturnCall::str() const
{
    DataTree::actualOne()(pos, REGULAR_ASYNC_RETURN);
    val->str();
    return "";
}

util::sref<Statement const> AnonymousCallback::body() const
{
    return *_body;
}

std::string AnonymousCallback::mangledName() const
{
    return "# AnonymousCallback";
}

util::sref<Block> AnonymousCallback::bodyFlow()
{
    return *_body;
}

std::vector<std::string> ConditionalCallback::parameters() const
{
    return std::vector<std::string>({ "ConditionalCallback # Parameter" });
}

std::vector<std::string> NoParamCallback::parameters() const
{
    return std::vector<std::string>();
}

std::vector<std::string> AsyncCatcher::parameters() const
{
    return std::vector<std::string>({ "AsyncCatcher # Parameter" });
}

std::string MemberAccess::str() const
{
    DataTree::actualOne()(pos, BINARY_OP, "[.]");
    referee->str();
    DataTree::actualOne()(pos, REFERENCE, member);
    return "";
}

void Return::write(std::ostream&) const
{
    DataTree::actualOne()(RETURN);
    ret_val->str();
}

void Export::write(std::ostream&) const
{
    DataTree::actualOne()(EXPORT);
    std::for_each(export_point.begin()
                , export_point.end()
                , [&](std::string const& name)
                  {
                      DataTree::actualOne()(PARAMETER, name);
                  });
    DataTree::actualOne()(EXPORT_VALUE);
    value->str();
}

void AsyncCallResultDef::write(std::ostream&) const
{
    DataTree::actualOne()(ASYNC_RESULT_DEF);
    async_result->str();
}

void Branch::write(std::ostream&) const
{
    DataTree::actualOne()(BRANCH);
    predicate->str();
    consequence->write(dummyos());
    alternative->write(dummyos());
}

void Arithmetics::write(std::ostream&) const
{
    DataTree::actualOne()(ARITHMETICS);
    expr->str();
}

void ThisDeclaration::write(std::ostream&) const
{
    DataTree::actualOne()(DEC_THIS);
}

void ExceptionStall::write(std::ostream&) const
{
    DataTree::actualOne()(TRY);
    try_block->write(dummyos());
    DataTree::actualOne()(CATCH);
    catch_block->write(dummyos());
}

void Throw::write(std::ostream&) const
{
    DataTree::actualOne()(THROW);
    exception->str();
}

void PipelineContinue::write(std::ostream&) const
{
    DataTree::actualOne()(PIPELINE_CONTINUE);
}

std::string Undefined::str() const
{
    DataTree::actualOne()(pos, UNDEFINED);
    return "";
}

std::string BoolLiteral::str() const
{
    DataTree::actualOne()(pos, BOOLEAN, util::str(value));
    return "";
}

std::string IntLiteral::str() const
{
    DataTree::actualOne()(pos, INTEGER, util::str(value));
    return "";
}

std::string FloatLiteral::str() const
{
    DataTree::actualOne()(pos, FLOATING, util::str(value));
    return "";
}

std::string StringLiteral::str() const
{
    DataTree::actualOne()(pos, STRING, value);
    return "";
}

std::string ListLiteral::str() const
{
    DataTree::actualOne()(pos, LIST, value.size());
    writeList(value);
    return "";
}

std::string PipeElement::str() const
{
    DataTree::actualOne()(pos, PIPE_ELEMENT);
    return "";
}

std::string PipeIndex::str() const
{
    DataTree::actualOne()(pos, PIPE_INDEX);
    return "";
}

std::string PipeKey::str() const
{
    DataTree::actualOne()(pos, PIPE_KEY);
    return "";
}

std::string PipeResult::str() const
{
    DataTree::actualOne()(pos, PIPE_RESULT);
    return "";
}

std::string ListAppend::str() const
{
    DataTree::actualOne()(pos, BINARY_OP, "++");
    lhs->str();
    rhs->str();
    return "";
}

std::string Reference::str() const
{
    DataTree::actualOne()(pos, REFERENCE, name);
    return "";
}

std::string SubReference::str() const
{
    DataTree::actualOne()(pos, SUB_REFERENCE, name);
    return "";
}

std::string TransientParamReference::str() const
{
    DataTree::actualOne()(pos, TRANSIENT_PARAMETER, name);
    return "";
}

std::string ImportedName::str() const
{
    DataTree::actualOne()(pos, IMPORTED_NAME, name);
    return "";
}

std::string Call::str() const
{
    DataTree::actualOne()(pos, CALL, args.size());
    callee->str();
    writeList(args);
    return "";
}

std::string SuperConstructorCall::str() const
{
    DataTree::actualOne()(pos, SUPER_CONSTRUCTOR_CALL, args.size());
    writeList(args);
    return "";
}

std::string Lookup::str() const
{
    DataTree::actualOne()(pos, BINARY_OP, "[]");
    collection->str();
    key->str();
    return "";
}

std::string ListSlice::str() const
{
    DataTree::actualOne()(pos, LIST_SLICE);
    list->str();
    begin->str();
    end->str();
    step->str();
    return "";
}

std::string Dictionary::str() const
{
    DataTree::actualOne()(pos, DICT_BEGIN);
    items.iter([&](util::ptrkv<Expression const> const& kv, int)
               {
                   DataTree::actualOne()(pos, DICT_ITEM);
                   kv.key->str();
                   kv.value->str();
               });
    DataTree::actualOne()(pos, DICT_END);
    return "";
}

std::string Assignment::str() const
{
    DataTree::actualOne()(pos, BINARY_OP, "[=]");
    lhs->str();
    rhs->str();
    return "";
}

std::string BinaryOp::str() const
{
    DataTree::actualOne()(pos, BINARY_OP, op);
    lhs->str();
    rhs->str();
    return "";
}

std::string PreUnaryOp::str() const
{
    DataTree::actualOne()(pos, PRE_UNARY_OP, op);
    rhs->str();
    return "";
}

std::string Lambda::str() const
{
    DataTree::actualOne()(pos, FUNCTION, param_names.size());
    std::for_each(param_names.begin()
                , param_names.end()
                , [&](std::string const& pn)
                  {
                      DataTree::actualOne()(PARAMETER, pn);
                  });
    if (mangle_as_param) {
        DataTree::actualOne()(MANGLE_AS_PARAM);
    }
    body->write(dummyos());
    return "";
}

std::string RegularAsyncLambda::str() const
{
    std::vector<std::string> p(param_names);
    p.insert(p.begin() + async_param_index, "# RegularAsyncParam");
    DataTree::actualOne()(pos, FUNCTION, p.size());
    std::for_each(p.begin()
                , p.end()
                , [&](std::string const& pn)
                  {
                      DataTree::actualOne()(PARAMETER, pn);
                  });
    body->write(dummyos());
    return "";
}

std::string This::str() const
{
    DataTree::actualOne()(pos, THIS);
    return "";
}

std::string SuperFunc::str() const
{
    DataTree::actualOne()(pos, SUPER_FUNC, property);
    return "";
}

std::string Conditional::str() const
{
    DataTree::actualOne()(pos, CONDITIONAL);
    predicate->str();
    consequence->str();
    alternative->str();
    return "";
}

std::string ExceptionObj::str() const
{
    DataTree::actualOne()(pos, EXCEPTION_OBJ);
    return "";
}

std::string ConditionalCallbackParameter::str() const
{
    DataTree::actualOne()(pos, COND_CALLBACK_PARAM);
    return "";
}

std::string AsyncReference::str() const
{
    DataTree::actualOne()(pos, ASYNC_REFERENCE);
    return "";
}

std::string RegularAsyncCallbackArg::str() const
{
    DataTree::actualOne()(pos, FUNCTION);
    DataTree::actualOne()(PARAMETER, "# RegularAsyncCallbackParameters");
    raiser("");
    body->write(dummyos());
    return "";
}

std::string AsyncPipeline::str() const
{
    DataTree::actualOne()(pos, ASYNC_PIPELINE);
    list->str();
    recursion->write(dummyos());
    succession->write(dummyos());
    raiser("");
    return "";
}

std::string SyncPipeline::str() const
{
    DataTree::actualOne()(pos, SYNC_PIPELINE);
    list->str();
    section->write(dummyos());
    return "";
}

Method method::throwExc()
{
    return [](std::string const&)
           {
               DataTree::actualOne()(EXC_THROW);
               return "";
           };
}

Method method::callbackExc()
{
    return [](std::string const&)
           {
               DataTree::actualOne()(EXC_CALLBACK);
               return "";
           };
}

Method method::asyncCatcher(std::string const& s)
{
    return [=](std::string const&)
           {
               DataTree::actualOne()(ASYNC_CATCH_FUNC, s);
               return "";
           };
}

int Block::count() const { return 0; }
int Export::count() const { return 0; }
int ExceptionStall::count() const { return 0; }
std::string output::formName(std::string const& name) { return name; }
std::string output::formSubName(std::string const& name, util::id) { return name + '$'; }
