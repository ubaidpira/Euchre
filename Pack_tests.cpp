#include "Pack.hpp"
#include "unit_test_framework.hpp"

#include <iostream>

using namespace std;

TEST(test_pack_default_ctor) {
    Pack pack;
    Card first = pack.deal_one();
    ASSERT_EQUAL(NINE, first.get_rank());
    ASSERT_EQUAL(SPADES, first.get_suit());
    Card second_card = pack.deal_one();
    Card third_card = pack.deal_one();
    Card fourth_card = pack.deal_one();
    Card fifth_card = pack.deal_one();
    Card sixth_card = pack.deal_one();
    Card seventh_card = pack.deal_one();
    ASSERT_EQUAL(second_card, Card(TEN,SPADES));
    ASSERT_EQUAL(third_card, Card(JACK,SPADES));
    ASSERT_EQUAL(fourth_card, Card(QUEEN,SPADES));
    ASSERT_EQUAL(fifth_card, Card(KING,SPADES));
    ASSERT_EQUAL(sixth_card, Card(ACE,SPADES));
    ASSERT_EQUAL(seventh_card, Card(NINE,HEARTS));
}

TEST(test_pack_shuffle) {
  Pack pack;
  pack.shuffle();
  Card first_card = pack.deal_one();
  Card second_card = pack.deal_one();
  /* Card third_card = pack.deal_one();
  Card fourth_card =pack.deal_one();
  Card fifth_card = pack.deal_one();
  Card sixth_card = pack.deal_one();
  Card seventh_card = pack.deal_one();
  ASSERT_EQUAL(seventh_card, Card(TEN, HEARTS));
  ASSERT_EQUAL(sixth_card, Card(QUEEN, HEARTS));
  ASSERT_EQUAL(fifth_card, Card(TEN, CLUBS));
  ASSERT_EQUAL(fourth_card, Card(NINE, CLUBS));
  ASSERT_EQUAL(third_card, Card(JACK, CLUBS)); */
  ASSERT_EQUAL(second_card, Card(JACK, HEARTS)); 
  ASSERT_EQUAL(first_card, Card(KING, CLUBS));
}

// Add more tests here

TEST_MAIN()
