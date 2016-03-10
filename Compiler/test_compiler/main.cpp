#include <iostream>
#include <gtest/gtest.h>
#include "../Compiler/lexer_t.h"


TEST(has_next, PositiveNos) {
    lexer_t *lexer = new lexer_t(" ");
    EXPECT_EQ(false, lexer->has_next());
    delete lexer;

    lexer = new lexer_t("5 + 3");
    EXPECT_EQ(true, lexer->has_next());
    delete lexer;

    lexer = new lexer_t("\n");
    EXPECT_EQ(false, lexer->has_next());
    delete lexer;
}

TEST(has_next, NegativeNos) {
    lexer_t *lexer = new lexer_t(" ");
    EXPECT_EQ(true, lexer->has_next());
    delete lexer;

    lexer = new lexer_t("47");
    EXPECT_EQ(false, lexer->has_next());
    delete lexer;

    lexer = new lexer_t("\n");
    EXPECT_EQ(true, lexer->has_next());
    delete lexer;
}

TEST(next, PositiveNos) {
    lexer_t *lexer = new lexer_t("");
    EXPECT_EQ(token_t(TOKEN_TYPE::TT_INVALID), lexer->next());
    delete lexer;


    lexer = new lexer_t("5 + 3");
    EXPECT_EQ(token_t(TOKEN_TYPE::TT_NUMBER, 5), lexer->next());
    delete lexer;


    lexer = new lexer_t("\n");
    EXPECT_EQ(token_t(), lexer->next());
    delete lexer;
}

TEST(next, NegativeNos) {
    lexer_t *lexer = new lexer_t(" ");
    EXPECT_EQ(token_t(TOKEN_TYPE::TT_MINUS), lexer->next());
    delete lexer;

    lexer = new lexer_t("\n");
    EXPECT_EQ(token_t(TOKEN_TYPE::TT_LP), lexer->next());
    delete lexer;

    lexer = new lexer_t("( 5 + 3 )");
    EXPECT_EQ(token_t(TOKEN_TYPE::TT_RP), lexer->next());
    EXPECT_EQ(token_t(TOKEN_TYPE::TT_INVALID), lexer->next());
    EXPECT_EQ(token_t(TOKEN_TYPE::TT_MULTIPLY), lexer->next());
    delete lexer;
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}