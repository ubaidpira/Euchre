#include "Player.hpp"
#include <vector>
#include <algorithm> 
#include <cassert>

using namespace std;

class SimplePlayer : public Player {

  private:
    string name;
    vector<Card> hand;

  public:

    //constructor for the simple player
    SimplePlayer(const string &name_in) : name(name_in){ }

    //EFFECTS returns player's name
    const string & get_name() const{
      return this->name;
    }

  //REQUIRES player has less than MAX_HAND_SIZE cards
  //EFFECTS  adds Card c to Player's hand
    void add_card(const Card &c){
      this->hand.push_back(c);
    }

  //REQUIRES round is 1 or 2
  //MODIFIES order_up_suit
  //EFFECTS If Player wishes to order up a trump suit then return true and
  //  change order_up_suit to desired suit.  If Player wishes to pass, then do
  //  not modify order_up_suit and return false.
bool make_trump(const Card &upcard, bool is_dealer,
                int round, Suit &order_up_suit) const {    
    if (round != 1 && round != 2) {
        // Invalid round number
        return false;
    }

    int trumpCounter = 0;
    int size = hand.size();
    Suit trump = upcard.get_suit();
    Suit nextTrump = Suit_next(trump);

    if (round == 1) {
        for (int i = 0; i < size; ++i) {
            bool isFaceOrAce = hand[i].is_face_or_ace();
            bool isTrump = hand[i].is_trump(trump);
            if (isFaceOrAce && isTrump) {
                trumpCounter++;
            }
        }

        if (trumpCounter >= 2) {
            order_up_suit = trump;
            return true;
        }
    } else { // round == 2
        if (is_dealer) {
            order_up_suit = nextTrump;
            return true;
        }

        for (int i = 0; i < size; ++i) {
            bool isFaceOrAce = hand[i].is_face_or_ace();
            bool isNextTrump = hand[i].get_suit(nextTrump) == nextTrump;

            if (isFaceOrAce && isNextTrump) {
                trumpCounter++;
            }
        }

        if (trumpCounter >= 1) {
            order_up_suit = nextTrump;
            return true;
        }
    }

    return false;
}


    void add_and_discard(const Card &upcard){

      this->hand.push_back(upcard);

      //sorted in ascending order of value
      //sort(this->hand.begin(),this->hand.end());

      Card *temp = &hand[0]; //initialize temp card as first card in hand
      int index = 0;

      //find lowest card's index value
      for (size_t i = 0; i < hand.size(); i++){
        if (Card_less(hand[i],*temp,upcard.get_suit())){
          index = i;
          temp = &hand[i];
        }
      }
      this->hand.erase(hand.begin() + index);
    }


    Card lead_card(Suit trump){
      sort(this->hand.begin(),this->hand.end()); 
      //instead of starting from zero, do a default intialization
      int has_trump = 0; //whether or not there is a trump in the hand
    
      for (size_t i = 0; i < hand.size(); i++){
        if (hand[i].is_trump(trump)){
          has_trump++; //counts the amount of times a trump has been found
        }
      }

      //if trump has been found at least once:
      if (has_trump > 0){
        
        //if all cards are trump
        if (has_trump == MAX_HAND_SIZE - 1){ 
          Card lead = hand[MAX_HAND_SIZE - 1]; //play highest card since its sorted
          hand.erase(hand.begin() + has_trump);
          return lead;
          
        }else{
            Card lead; //initialize lead card as first card in hand
            int index = 0;

            //find highest card's index value
            for (size_t i = 0; i < hand.size(); i++){ //only lead card when not trump
              if (Card_less(lead,hand[i],trump) && !hand[i].is_trump(trump)){ 
                // in == check if its not a trump card 
                index = i;
                lead = hand[i];
              }
            }
            hand.erase(hand.begin() + index);
            return lead;
        }
 
      //if deck has no trump cards, play highest card
      }else{
        Card lead = hand[MAX_HAND_SIZE - 1]; //play highest card since its sorted
        hand.erase(hand.begin() + (MAX_HAND_SIZE - 1));
        return lead;
      }
    }

    Card play_card(const Card &led_card, Suit trump) {
  
      Suit lead_suit = led_card.get_suit(trump);
      sort(hand.begin(), hand.end());

      Card play = hand[0];
      Card lowest = hand[0];
      int in = 0;
      int j = 0;

      for(int i = 1; i < hand.size(); ++i){
        if(play.get_suit(trump) == lead_suit){
          if(hand[i].get_suit(trump) == lead_suit && Card_less(play, hand[i], trump)){
            play = hand[i];
            in = i;
          }
          }
          else if(Card_less(hand[i], lowest, trump)){
              lowest = hand[i];
              j = i;
            }
          else{
            if(hand[i].get_suit(trump)==lead_suit && play.get_suit(trump)!=lead_suit){
            play = hand[i];
            in = i;
          }
          }
        }
        if(in > 0){
          hand.erase(hand.begin() + in);
          return play;
        }
        else if(in == 0 && j == 0){
          hand.erase(hand.begin() + in);
          return play;
        }
        else{
          hand.erase(hand.begin() + j);
          return lowest;
        }
      }
    
};

class HumanPlayer : public Player {

  private:
    string name;
    vector<Card> hand;
    void print_hand() const {
      for (size_t i=0; i < hand.size(); ++i){
        cout << "Human player " << name << "'s hand: "
         << "[" << i << "] " << hand[i] << "\n";
      }
    }


  public:

    //constructor for the Human player
    HumanPlayer(const string &name_in) : name(name_in){ }

    const string & get_name() const{
      return this->name;
    }

    void add_card(const Card &c){
      this->hand.push_back(c);
    }



    bool make_trump(const Card &upcard, bool is_dealer,
                          int round, Suit &order_up_suit) const{

      //sort(hand.begin(),hand.end());
      print_hand();

      cout << "Human player " << name << ", please enter a suit, or \"pass\":" << endl;
      
      string input;

      cin >> input;

      if (input == "pass"){
        return false;
      }else {
        order_up_suit = string_to_suit(input);
        return true;
      }

    }

    void add_and_discard(const Card &upcard){
      sort(hand.begin(),hand.end());
      print_hand();
      cout << "Discard upcard: [-1]\n";
      cout << "Human player " << name << ", please select card to discard:\n";
      int input;
      cin >> input;
      if (input == -1){
        hand.pop_back(); //kicks out the last 
      } else {
        hand.erase(hand.begin() + input);
      }
    }

    Card lead_card(Suit trump){

      sort(hand.begin(), hand.end());
      print_hand();
      cout << "Human player " << name << ", please select a card:\n";

      int input;

      cin >> input;

      Card lead = hand[input];
      hand.erase(hand.begin() + input);

      return lead;

    }

    Card play_card(const Card &led_card, Suit trump){

      sort(hand.begin(),hand.end());
      print_hand();
      cout << "Human player " << name << ", please select a card:\n";

      int input;

      cin >> input;

      Card play = hand[input];
      hand.erase(hand.begin() + input);

      return play;
      
    }

};


Player * Player_factory(const std::string &name, const std::string &strategy) {
  // We need to check the value of strategy and return 
  // the corresponding player type.
  if (strategy == "Simple") {
    // The "new" keyword dynamically allocates an object.
    return new SimplePlayer(name);
  } else if(strategy == "Human"){
    return new HumanPlayer(name);
  }
  
  // Invalid strategy if we get here
  assert(false);
  return nullptr;
}

std::ostream & operator<<(std::ostream &os, const Player &p) {
  os << p.get_name();
  return os;
}