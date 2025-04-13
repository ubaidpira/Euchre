#include "Player.hpp"
#include "unit_test_framework.hpp"
#include <iostream>

using namespace std;



TEST(test_add_card) {
    Player* player = Player_factory("John", "Simple");
    Card card(ACE, HEARTS);

    player->add_card(card);

    // Check if the card is added to the player's hand
    ASSERT_EQUAL(player->play_card(card, HEARTS), card);

    delete player;

}

TEST(test_player_get_name) {
    Player * rawan = Player_factory("Rawan", "Simple");
    ASSERT_EQUAL("Rawan", rawan->get_name());
    delete rawan;
}


TEST(test_add_and_discard){

    Player * bob = Player_factory("Bob", "Simple");

    Card a(Card(NINE, SPADES));
    Card b(Card(JACK, HEARTS));
    Card c(Card(QUEEN, DIAMONDS));
    Card d(Card(TEN, CLUBS));
    Card e(Card(ACE, SPADES));
    Card f(Card(QUEEN, HEARTS));
    
    bob->add_card(a);
    bob->add_card(b);
    bob->add_card(c);
    bob->add_card(d);
    bob->add_card(e);
    bob->add_card(f);


    Card upcard(ACE, HEARTS);
    bob->add_and_discard(upcard);

    Card card_led = bob->lead_card(HEARTS);
    ASSERT_EQUAL(card_led, e); 

    Card card_led2(ACE, CLUBS);
    Card card_played = bob->play_card(card_led2, HEARTS);
    ASSERT_EQUAL(card_played, d);

    // Card card_led3 = bob->lead_card(HEARTS);
    // ASSERT_EQUAL(card_led3, upcard);

    delete bob;
}

TEST(test_player_play_card_p1){
    Player * rawan = Player_factory("Rawan", "Simple");
    Card ace_clubs = Card(ACE,CLUBS);
    Suit trump = CLUBS;
    rawan->add_card(ace_clubs);
    ASSERT_EQUAL(ace_clubs,rawan->play_card(ace_clubs,trump));
    
    delete rawan;
}

TEST(test_simple_player_make_trump_round_1) {
    Player * simple = Player_factory("Rawan", "Simple");
    Card upcard(ACE, DIAMONDS);
    Suit order_up_suit;

    // Test with round 1 and more than 2 trump cards in hand
    simple->add_card(Card(JACK, DIAMONDS));
    simple->add_card(Card(KING, DIAMONDS));
    simple->add_card(Card(ACE, SPADES));
    ASSERT_TRUE(simple->make_trump(upcard, false, 1, order_up_suit));
    ASSERT_EQUAL(order_up_suit, DIAMONDS);

    // Test with round 1 and less than 2 trump cards in hand
    simple->add_card(Card(TEN, SPADES));
    ASSERT_TRUE(simple->make_trump(upcard, false, 1, order_up_suit));

    delete simple;
}

TEST(test_player_play_card_p2){
    Player * rawan = Player_factory("Rawan", "Simple");

    Card ace_clubs;
    Card ace_spades;
    Suit trump = CLUBS;
    rawan->add_card(ace_clubs);
    rawan->add_card(ace_spades);

    ASSERT_EQUAL(ace_clubs,rawan->play_card(ace_clubs,trump));
    ASSERT_EQUAL(ace_spades,rawan->play_card(ace_clubs,trump));

    delete rawan;

}

TEST(test_player_play_decision) {
    Player * rawan = Player_factory("Rawan", "Simple");

    Card ace_clubs;
    Suit trump = CLUBS;
    rawan->add_card(ace_clubs);
    
    ASSERT_EQUAL(ace_clubs, rawan->play_card(ace_clubs, trump));

    delete rawan;
}


TEST(test_f_simple_player) {
    Player* simple = Player_factory("TestSimple", "Simple");
    ASSERT_EQUAL("TestSimple", simple->get_name());
    
    delete simple;
}

TEST(test_f_human_player) {
    Player* human = Player_factory("TestHuman", "Human");
    ASSERT_EQUAL("TestHuman", human->get_name());
    
    delete human;
}

TEST(mut_fixd_name_return) {
    Player * mutant = Player_factory("NotAMutant", "Simple");
    ASSERT_NOT_EQUAL("Mutant", mutant->get_name());

    delete mutant;
}

TEST(test_card_played_from_hand) {
    cout << "Running test_card_played_from_hand..." << endl;
    Player* nawar = Player_factory("Nawar", "Simple");
    Card ace_hearts = Card(ACE, HEARTS);
    nawar->add_card(ace_hearts);
    Suit trump = HEARTS;

    ASSERT_EQUAL(ace_hearts, nawar->play_card(ace_hearts, trump));

    delete nawar;
}

TEST(simp_player_p_trump_round_1) {
    Player * simple = Player_factory("Bob", "Simple");
    Card upcard(ACE, CLUBS);
    Suit order_up_suit;

    // Test with round 1 and no trump cards in hand
    simple->add_card(Card(NINE, SPADES));
    simple->add_card(Card(TEN, HEARTS));
    simple->add_card(Card(QUEEN, DIAMONDS));
    ASSERT_FALSE(simple->make_trump(upcard, false, 1, order_up_suit));

    delete simple;

}

TEST(test_player_make_trump) {
    
    Player * bob = Player_factory("Bob", "Simple");
    Card card1 = Card(NINE, CLUBS);
    Card upcard = Card(KING, SPADES);
    bob->add_card(card1);
    Suit order_up_suit = DIAMONDS;
    bool result = bob->make_trump(upcard, true, 1, order_up_suit);
    if (result) {
        ASSERT_TRUE(upcard.is_trump(order_up_suit));
    } else {
        ASSERT_FALSE(upcard.is_trump(order_up_suit));
    }

    delete bob; 
}

// TEST(test_player_make_trump2) {
    
//     Player * bob = Player_factory("Bob", "Simple");
//     Card card1 = Card(NINE, CLUBS);
//     Card upCard = Card(KING, SPADES);
//     bob->add_card(card1);
//     Suit order_up_suit = DIAMONDS;
//     bob->make_trump(upCard, true, 1, order_up_suit);
//     ASSERT_TRUE(upCard.is_trump(order_up_suit));

//     delete bob; 
// }

TEST_MAIN()

