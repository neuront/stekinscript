#include <gtest/gtest.h>

#include <test/phony-errors.h>

#include "test-common.h"
#include "../yy-misc.h"

using namespace test;

TEST(Syntax, Mix)
{
    yyparse();
    ASSERT_FALSE(error::hasError());

    DataTree::expectOne()
        (misc::position(1), 0, VAR_DEF, "n")
            (misc::position(1), INTEGER, "10")

        (misc::position(3), 0, FUNC_DEF_HEAD_BEGIN, "fib")
            (misc::position(3), 0, IDENTIFIER, "n")
        (misc::position(3), 0, FUNC_DEF_HEAD_END)

            (misc::position(4), 1, FUNC_DEF_HEAD_BEGIN, "add")
            (misc::position(4), 1, FUNC_DEF_HEAD_END)

                (misc::position(5), 2, RETURN)
                    (misc::position(5), BINARY_OP_BEGIN, "+")
                    (misc::position(5), OPERAND)
                        (misc::position(5), FUNC_CALL_BEGIN, "fib")
                        (misc::position(5), ARGUMENT)
                            (misc::position(5), IDENTIFIER, "n")
                        (misc::position(5), FUNC_CALL_END)
                    (misc::position(5), OPERAND)
                        (misc::position(5), FUNC_CALL_BEGIN, "fib")
                        (misc::position(5), ARGUMENT)
                            (misc::position(5), BINARY_OP_BEGIN, "-")
                            (misc::position(5), OPERAND)
                                (misc::position(5), IDENTIFIER, "n")
                            (misc::position(5), OPERAND)
                                (misc::position(5), INTEGER, "1")
                            (misc::position(5), BINARY_OP_END)
                        (misc::position(5), FUNC_CALL_END)
                    (misc::position(5), BINARY_OP_END)

            (misc::position(6), 1, BRANCH_IFNOT)
            (misc::position(6), 1, CONDITION_BEGIN)
                (misc::position(6), BINARY_OP_BEGIN, "<")
                (misc::position(6), OPERAND)
                    (misc::position(6), IDENTIFIER, "n")
                (misc::position(6), OPERAND)
                    (misc::position(6), INTEGER, "2")
                (misc::position(6), BINARY_OP_END)
            (misc::position(6), 1, CONDITION_END)
                (misc::position(7), 2, RETURN)
                        (misc::position(7), FUNC_CALL_BEGIN, "add")
                        (misc::position(7), FUNC_CALL_END)

            (misc::position(8), 1, RETURN)
                (misc::position(8), INTEGER, "1")

            (misc::position(10), 0, BRANCH_IF)
            (misc::position(10), 0, CONDITION_BEGIN)
                (misc::position(10), BINARY_OP_BEGIN, ">")
                (misc::position(10), OPERAND)
                    (misc::position(10), IDENTIFIER, "n")
                (misc::position(10), OPERAND)
                    (misc::position(10), INTEGER, "5")
                (misc::position(10), BINARY_OP_END)
            (misc::position(10), 0, CONDITION_END)
                (misc::position(11), 1, ARITHMETICS)
                    (misc::position(11), FUNC_CALL_BEGIN, "write")
                        (misc::position(11), ARGUMENT)
                        (misc::position(11), FUNC_CALL_BEGIN, "fib")
                            (misc::position(11), ARGUMENT)
                                (misc::position(11), INTEGER, "10")
                        (misc::position(11), FUNC_CALL_END)
                    (misc::position(11), FUNC_CALL_END)
            (misc::position(12), 0, BRANCH_ELSE)
                (misc::position(13), 1, ARITHMETICS)
                    (misc::position(13), FUNC_CALL_BEGIN, "write")
                        (misc::position(13), ARGUMENT)
                            (misc::position(13), BOOLEAN, "false")
                    (misc::position(13), FUNC_CALL_END)

        (misc::position(15), 0, FUNC_DEF_HEAD_BEGIN, "print_10")
        (misc::position(15), 0, FUNC_DEF_HEAD_END)
            (misc::position(16), 1, BRANCH_IF)
            (misc::position(16), 1, CONDITION_BEGIN)
                (misc::position(16), BOOLEAN, "true")
            (misc::position(16), 1, CONDITION_END)
                (misc::position(17), 2, ARITHMETICS)
                    (misc::position(17), FUNC_CALL_BEGIN, "write")
                        (misc::position(17), ARGUMENT)
                            (misc::position(17), PRE_UNARY_OP_BEGIN, "+")
                            (misc::position(17), OPERAND)
                                (misc::position(17), FLOATING, "10.0")
                            (misc::position(17), PRE_UNARY_OP_END)
                    (misc::position(17), FUNC_CALL_END)

        (misc::position(19), 0, VAR_DEF, "x")
            (misc::position(19), IDENTIFIER, "print_10")
        (misc::position(20), 0, VAR_DEF, "y")
            (misc::position(20), IDENTIFIER, "fib")

        (misc::position(22), 0, ARITHMETICS)
            (misc::position(22), LIST_BEGIN)
            (misc::position(22), LIST_END)

        (misc::position(23), 0, ARITHMETICS)
            (misc::position(23), LIST_BEGIN)
                (misc::position(23), INTEGER, "0")
            (misc::position(23), LIST_END)

        (misc::position(24), 0, ARITHMETICS)
            (misc::position(24), LIST_BEGIN)
                (misc::position(24), IDENTIFIER, "panty")
                (misc::position(24), IDENTIFIER, "stocking")
                (misc::position(24), FUNC_CALL_BEGIN, "garterbelt")
                (misc::position(24), ARGUMENT)
                    (misc::position(24), IDENTIFIER, "chuck")
                (misc::position(24), FUNC_CALL_END)
            (misc::position(24), LIST_END)

        (misc::position(25), 0, ARITHMETICS)
            (misc::position(25), LIST_BEGIN)
                (misc::position(25), LIST_BEGIN)
                    (misc::position(25), IDENTIFIER, "zergling")
                    (misc::position(25), IDENTIFIER, "hydralisk")
                (misc::position(25), LIST_END)
                (misc::position(25), LIST_BEGIN)
                    (misc::position(25), IDENTIFIER, "marine")
                    (misc::position(25), IDENTIFIER, "firebat")
                (misc::position(25), LIST_END)
                (misc::position(25), LIST_BEGIN)
                    (misc::position(25), IDENTIFIER, "zealot")
                    (misc::position(25), IDENTIFIER, "dragoon")
                (misc::position(25), LIST_END)
            (misc::position(25), LIST_END)

        (misc::position(26), 0, ARITHMETICS)
            (misc::position(26), BINARY_OP_BEGIN, "++")
            (misc::position(26), OPERAND)
                (misc::position(26), LIST_BEGIN)
                    (misc::position(26), INTEGER, "0")
                (misc::position(26), LIST_END)
            (misc::position(26), OPERAND)
                (misc::position(26), LIST_BEGIN)
                (misc::position(26), LIST_END)
            (misc::position(26), BINARY_OP_END)

        (misc::position(27), 0, ARITHMETICS)
            (misc::position(27), BINARY_OP_BEGIN, "++")
            (misc::position(27), OPERAND)
                (misc::position(27), BINARY_OP_BEGIN, "++")
                (misc::position(27), OPERAND)
                    (misc::position(27), IDENTIFIER, "z")
                (misc::position(27), OPERAND)
                    (misc::position(27), IDENTIFIER, "z")
                (misc::position(27), BINARY_OP_END)
            (misc::position(27), OPERAND)
                (misc::position(27), IDENTIFIER, "z")
            (misc::position(27), BINARY_OP_END)

        (misc::position(35), 0, ARITHMETICS)
            (misc::position(35), LIST_PIPELINE, "2")
                (misc::position(35), LIST_BEGIN)
                (misc::position(35), LIST_END)
            (misc::position(35), PIPE_BEGIN)
                (misc::position(35), PIPE_FILTER)
                    (misc::position(35), BINARY_OP_BEGIN, "=")
                    (misc::position(35), OPERAND)
                        (misc::position(35), LIST_INDEX)
                    (misc::position(35), OPERAND)
                        (misc::position(35), INTEGER, "0")
                    (misc::position(35), BINARY_OP_END)
            (misc::position(35), PIPE_END)
            (misc::position(35), PIPE_BEGIN)
                (misc::position(35), PIPE_MAP)
                    (misc::position(35), BINARY_OP_BEGIN, "*")
                    (misc::position(35), OPERAND)
                        (misc::position(35), LIST_ELEMENT)
                    (misc::position(35), OPERAND)
                        (misc::position(35), LIST_ELEMENT)
                    (misc::position(35), BINARY_OP_END)
            (misc::position(35), PIPE_END)

        (misc::position(37), 0, VAR_DEF, "s")
            (misc::position(37), BINARY_OP_BEGIN, "+")
            (misc::position(37), OPERAND)
                (misc::position(37), STRING, "sizukani tiriyuku")
            (misc::position(37), OPERAND)
                (misc::position(37), STRING, "the quick brown fox jumps over a lazy dog.")
            (misc::position(37), BINARY_OP_END)

        (misc::position(38), 0, VAR_DEF, "sk")
            (misc::position(38), STRING, "a quote\" and something \\else in\t the\n string")

        (misc::position(39), 0, VAR_DEF, "st")
            (misc::position(39), STRING, "nomico\"misato" "nomico'misato")
    ;
    DataTree::verify();
}
