#include "Card.hpp"
#include "unit_test_framework.hpp"
#include <iostream>

using namespace std;

//Validates rank and suit
TEST(test_card_ctor_1) {
    Card c(ACE, HEARTS);
    ASSERT_EQUAL(ACE, c.get_rank());
    ASSERT_EQUAL(HEARTS, c.get_suit());

}


//Validiates rank and suit 
TEST(test_card_ctor_2){
    Card d(TWO,SPADES);
    ASSERT_EQUAL(TWO, d.get_rank());
    ASSERT_EQUAL(SPADES, d.get_suit());

}

TEST(test_is_face_is_ace){
    Card a(ACE,DIAMONDS);
    Card b(QUEEN,CLUBS);
    Card d;
    ASSERT_EQUAL(true, a.is_face_or_ace());
    ASSERT_EQUAL(true, b.is_face_or_ace());
    ASSERT_EQUAL(false, d.is_face_or_ace());
    
}

TEST(test_right_bower){
    Card e(JACK,HEARTS);
    ASSERT_EQUAL(true, e.is_right_bower(HEARTS));
}

TEST(test_left_bower){
    Card f(JACK,CLUBS);
    ASSERT_EQUAL(true, f.is_left_bower(SPADES));
}

//Validates next suit
TEST(test_suit_next_1){
    ASSERT_EQUAL(CLUBS, Suit_next(SPADES));
    ASSERT_EQUAL(SPADES, Suit_next(CLUBS));
    ASSERT_EQUAL(HEARTS, Suit_next(DIAMONDS));
    ASSERT_EQUAL(DIAMONDS, Suit_next(HEARTS));
}

//Tests highest rank 
TEST(test_highest_rank){
    Card h(ACE,HEARTS);
    Card i(QUEEN,DIAMONDS);
    Card g;

    ASSERT_TRUE(h>i);
    ASSERT_TRUE(h>g);

}

//Tests lowest rank
TEST(test_lowest_rank){
    Card j(TWO,HEARTS);
    Card k(THREE,DIAMONDS);

    ASSERT_TRUE(j<k);

}

TEST(test_equal_rank){
    Card l(ACE,HEARTS);
    Card m(ACE,DIAMONDS);

    ASSERT_EQUAL(l,m);

}

TEST(mutation_test_is_left_bower) {
    Card a(JACK, CLUBS);
    // Mutate is_left_bower to always return true
    ASSERT_EQUAL(true, a.is_left_bower(SPADES));
}

TEST(mutation_test_is_trump) {
    Card a(ACE, HEARTS);
    // Mutate is_trump to always return false
    ASSERT_EQUAL(false, a.is_trump(SPADES));
}

TEST(mutation_test_card_less_with_trump) {
    Card a(JACK, CLUBS);
    Card b(KING, HEARTS);
    // Mutate Card_less to return the opposite result when comparing a and b
    ASSERT_TRUE(Card_less(a, b, HEARTS));
}

TEST(mutation_test_get_suit) {
    Card a(KING, DIAMONDS);
    Suit incorrect_suit = HEARTS;
    // Mutate get_suit to return an incorrect suit
    ASSERT_NOT_EQUAL(incorrect_suit, a.get_suit());
}

TEST(mutation_suit_next) {
    ASSERT_EQUAL(DIAMONDS, Suit_next(HEARTS));
    ASSERT_EQUAL(CLUBS, Suit_next(SPADES));
}

TEST(test_card_default_ctor_mutation) {
    Card x;
    ASSERT_EQUAL(TWO, x.get_rank());
    ASSERT_EQUAL(SPADES, x.get_suit());
}


TEST(mutation_card_stream_overload) {
    Card z(ACE, SPADES);
    stringstream ss;
    ss << z;
    ASSERT_EQUAL("Ace of Spades", ss.str());
    Card r;
    ss >> r;
    ASSERT_EQUAL(z, r);
}

TEST(mutation_card_comparison) {
    Card a(TWO, HEARTS);
    Card b(THREE, HEARTS);
    ASSERT_TRUE(a < b);
    ASSERT_FALSE(a > b);
    ASSERT_TRUE(a <= b);
    ASSERT_FALSE(a >= b);
}



// // Test the is_trump() function
TEST(test_is_trump) {
    Card g(JACK, CLUBS);
    ASSERT_TRUE(g.is_trump(CLUBS));
    ASSERT_TRUE(g.is_trump(SPADES));
    ASSERT_FALSE(g.is_trump(DIAMONDS));
}

TEST(mutation_trump_detection) {
    Card trump_card(ACE, SPADES);
    Card non_trump_card(ACE, HEARTS);
    ASSERT_TRUE(trump_card.is_trump(SPADES));
    ASSERT_FALSE(non_trump_card.is_trump(SPADES));
}

TEST(test_card_less_trump) {
    Card n(JACK, DIAMONDS); // Right bower when SPADES is trump
    Card o(JACK, HEARTS);  // Left bower when SPADES is trump
    Card p(TEN, DIAMONDS);
    ASSERT_FALSE(Card_less(n, o, DIAMONDS));
    ASSERT_TRUE(Card_less(o, n, DIAMONDS));
    ASSERT_TRUE(Card_less(p, n, DIAMONDS));
    ASSERT_TRUE(Card_less(p, o, DIAMONDS));
}

TEST_MAIN()

