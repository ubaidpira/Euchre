#include "Pack.hpp"
#include <cassert>

// EFFECTS: Initializes the Pack to be in the following standard order:
//          the cards of the lowest suit arranged from lowest rank to
//          highest rank, followed by the cards of the next lowest suit
//          in order from lowest to highest rank, and so on.
// NOTE: The standard order is the same as that in pack.in.
// NOTE: Do NOT use pack.in in your implementation of this function
Pack::Pack() : next(0){ 
  //initializes next as the value of zero

  //order of pack.in 9->Ace of Spades then 9->Ace of Hearts
  //then 9->Ace of Clubs then 9->Ace of Diamonds

  for (int i = SPADES; i < DIAMONDS + 1; i++){

    for (int j = NINE; j < ACE + 1; j++){
      cards[next++] = Card(static_cast<Rank>(j),static_cast<Suit>(i));
      //this->next++;
    }
  }

  this->reset(); //called to put the next index back at the beginning

}

// REQUIRES: pack_input contains a representation of a Pack in the
//           format required by the project specification
// MODIFIES: pack_input
// EFFECTS: Initializes Pack by reading from pack_input.
Pack::Pack(std::istream& pack_input) : next(0){ 
  //initializes next as the value of zero

  //string of is meant to represent the word of in proper Pack format
  std::string pack_rank, ofWord, pack_suit;

  while(pack_input >> pack_rank >> ofWord >> pack_suit){
    cards[next++] = Card(string_to_rank(pack_rank),
                                   string_to_suit(pack_suit));
    //this->next++;
  }

  this->reset(); //called to put the next index back at the beginning

}

// REQUIRES: cards remain in the Pack
// EFFECTS: Returns the next card in the pack and increments the next index
Card Pack::deal_one(){
  
  //what to do when the current index is the last card? (not sure tbh)
  assert(this->next <= 23);
  //this->next++;
  return cards[next++];

}

// EFFECTS: Resets next index to first card in the Pack
void Pack::reset() {
  this->next = 0;
}

// EFFECTS: Shuffles the Pack and resets the next index. This
//          performs an in shuffle seven times. See
//          https://en.wikipedia.org/wiki/In_shuffle.
void Pack::shuffle(){

  //reset(); //make sure the next is set to 0

  const int pack_size = 24;

  //create 2 temp arrays that contain the unadjusted cards shuffles
  //seperated into 2 hands
  Card *low_hand = new Card[pack_size/2];
  Card *high_hand = new Card[pack_size/2];

  //copy the current pack into the 2 hands
  for (int i = 0; i < pack_size/2; i++){
    low_hand[i] = cards[i];
    high_hand[i] = cards[i + pack_size/2];
  }
 
  //run it 7 times to shuffle 7 times 
  for (int i = 0; i < 7; i++){

    int track_low_hand_index, track_high_hand_index;
    track_low_hand_index = 0;
    track_high_hand_index = 0;

    for (int j = 0; j < pack_size; j++){

      if (next % 2 == 1){
        cards[next] = low_hand[track_low_hand_index];
        track_low_hand_index++;
      }else {
        cards[next] = high_hand[track_high_hand_index];
        track_high_hand_index++;
      }

      this->next++;

    }

    for (int k = 0; k < pack_size/2; k++){
      low_hand[k] = this->cards[k];
      high_hand[k] = this->cards[k + pack_size/2];
    }

    reset(); //resets next to 0

  }
  
  delete[] low_hand;
  delete[] high_hand;

}

// EFFECTS: returns true if there are no more cards left in the pack
bool Pack::empty() const{
  
  if (this->next == 24){ //last card in the pack.in
    return true;
  }else{
    return false;
  }

}