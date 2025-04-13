#include <iostream>
#include <fstream>
#include <cstring>
#include "Card.hpp"
#include "Pack.hpp"
#include "Player.hpp"
using namespace std;

class Game {

 public:

  //Game constructor, initializes the players and game settings
 
  Game(vector<Player*> &player_in, string &toShuffle_in, int ptsToWin_in, Pack &pack_in) 
  : players(player_in), toShuffle(toShuffle_in), ptsToWin(ptsToWin_in), pack(pack_in){}

  void play(){

    teamPts1 = 0;
    teamPts2 = 0;
    hand = 0;
    dealer = 0;

    while(teamPts1 < ptsToWin && teamPts2 < ptsToWin){
    trump_t1 = false;
    trump_t2 = false;
    trickWins_t1 = 0;
    trickWins_t2 = 0;

    shuffle();
    deal();
    make_trump();
    play_hand();
    score_track();
   
    if (dealer == players.size()-1){
      dealer = 0;
    }else{
      ++dealer;
    }

    ++hand;
      cout << players[0]->get_name() << " and " << players[2]->get_name() << 
      " have " << teamPts1 << " points" << endl;
      cout << players[1]->get_name() << " and " << players[3]->get_name() << 
      " have " << teamPts2 << " points" << endl;
      cout << endl;
  } 
  if (teamPts1 > teamPts2){
    cout << players[0]->get_name() << " and " << players[2]->get_name()
    << " win!" << endl;
  }
  else {
    cout << players[1]->get_name() << " and " << players[3]->get_name() 
    << " win!" << endl;
  }
  for (size_t i = 0; i < players.size(); ++i) {
    delete players[i];
  }
};


 private:
  vector<Player*> players;
  string toShuffle;
  int ptsToWin;
  Pack pack;

  int teamPts1;
  int teamPts2;
  int hand;
  int dealer;
  bool is_dealer;

  bool trump_t1;
  bool trump_t2;
  int trickWins_t1;
  int trickWins_t2;
  Suit trump;
  Card upcard;

  //shuffle cards
  void shuffle(){
  if (toShuffle == "shuffle"){
    pack.shuffle();
  }
  else {
    pack.reset();
  }
  }

  void deal(){
    cout << "Hand " << hand << endl;
    cout << *players[dealer] << " deals" << endl;

    vector dealing_sequence = {3, 2, 3, 2, 2, 3, 2, 3};

    int currentPlayer;
    if(dealer == players.size()-1){
      currentPlayer = 0;
    }
    else{
      currentPlayer = dealer+1;
    }
    for(int i = 0; i < dealing_sequence.size(); ++i){
      for(int j = 0; j < dealing_sequence[i]; ++j){
        players[currentPlayer]->add_card(pack.deal_one());
      }
      if(currentPlayer == players.size()-1){
        currentPlayer = 0;
      }
      else{
        ++currentPlayer;
      }
    }
    upcard = pack.deal_one();
    cout << upcard << " turned up" << endl;
  }


  void make_trump() {
    bool makeTrump; //if action is true, it orders up
    int currentPlayer = (dealer + 1) % players.size();
    int round = 1;

    for (int i = 0; i < 8; ++i) {
        if (currentPlayer == dealer) {
            is_dealer = true;
        } else {
            is_dealer = false;
        }

        if (i == 4) {
            round = 2;
        }

        makeTrump = players[currentPlayer]->make_trump(upcard, is_dealer, round, trump);

        if (makeTrump) {
            cout << players[currentPlayer]->get_name() << " orders up " << trump << endl;
            if (currentPlayer == 0 || currentPlayer == 2) {
                trump_t1 = true;
            } else {
                trump_t2 = true;
            }
            i = 8; // Exit loop once trump is ordered up
        }
        else if (currentPlayer == players.size()-1) {
            cout << players[currentPlayer]->get_name() << " passes" << endl;
            currentPlayer = 0;
        }
        else{
          cout << players[currentPlayer]->get_name() << " passes" << endl;
           ++currentPlayer;
        }
    }
    cout << endl;
    if (round == 1) {
        players[dealer]->add_and_discard(upcard);
    }
}

void play_hand() {
    int currentPlayer;
    int trickCounter;

    if (dealer == players.size() - 1) {
        currentPlayer = 0;
    } else {
        currentPlayer = dealer + 1;
    }

    for (int j = 0; j < 5; ++j) {
        Card led_card = players[currentPlayer]->lead_card(trump);
        Card leader = led_card;
        trickCounter = currentPlayer;
        cout << led_card << " led by " << *players[currentPlayer] << endl;
        ++currentPlayer;

        if (trickCounter == 0 || trickCounter == 2) {
            ++trickWins_t1;
        } else {
            ++trickWins_t2;
        }

        for (int i = 0; i < 3; ++i) {
            if (currentPlayer > players.size() - 1) {
                currentPlayer = 0;
            }

            Card played = players[currentPlayer]->play_card(led_card, trump);
            cout << played << " played by " << *players[currentPlayer] << endl;
            if (Card_less(leader, played, led_card, trump)) {
                leader = played;
                trickCounter = currentPlayer;
            }
            ++currentPlayer;
        }
        cout << *players[trickCounter] << " takes the trick" << endl;
        cout << endl;
        currentPlayer = trickCounter;
    }
}


void score_track(){

    if(trickWins_t1 > trickWins_t2){
      cout << *players[0] << " and " << *players[2] << " win the hand" << endl;
    }
    else{
      cout << *players[1] << " and " << *players[3] << " win the hand" << endl;
    }

    if(trump_t1 && trickWins_t1 < trickWins_t2){
      cout << "euchred!" << endl;
      teamPts2 += 2;
    }
    else if(trump_t2 && trickWins_t1 > trickWins_t2){
      cout << "euchred!" << endl;
      teamPts1 += 2;
    }
    else if(trickWins_t1 == 5 && trump_t1){
      cout << "march!" << endl;
      teamPts1 += 2;
    }
    else if(trickWins_t2 == 5 && trump_t2){
      cout << "march!" << endl;
      teamPts2 += 2;
    }
    else if(trickWins_t1 > trickWins_t2){
      ++teamPts1;
    }
    else{
      ++teamPts2;
    }
}



};


///// DRIVER IS BELOW /////


int main(int argc, char **argv) {
  // Read command line args and check for errors
  
  string shuffleString = argv[2];

  string ptsToWinString = argv[3];
  int ptsToWin = stoi(ptsToWinString);

  string playerType0 = argv[5];
  string playerType1 = argv[7];
  string playerType2 = argv[9];
  string playerType3 = argv[11];

  if (argc != 12 
    || (shuffleString != "noshuffle" && shuffleString != "shuffle")
     || (ptsToWin < 1 || ptsToWin > 100)
     || (playerType0 != "Simple" && playerType0 != "Human")
     || (playerType1 != "Simple" && playerType1 != "Human") 
     || (playerType2 != "Simple" && playerType2 != "Human")
     || (playerType3 != "Simple" && playerType3 != "Human")){

    cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
     << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
     << "NAME4 TYPE4" << endl;

    return -1;

  };

  ///// FILE PROCESSING TO GET THE PACK
  string pack_filename = argv[1];
  ifstream infile;
  infile.open(pack_filename);
  if (!infile.is_open()){
    cout << "Error opening " << pack_filename << endl;
    return -1;
  }

  for(int i = 0; i < argc; ++i){
    if(i == argc - 1){
      cout << argv[i] << " " << endl;
    }
    else{
      cout << argv[i] << " ";
    }
  }

  Pack cardPack(infile); //uses constructor for Pack
  infile.close();

  //create an array of the players and their types
  string *player_names = new string[4];
  string *player_types = new string[4];

  int indexNames = 0;
  int indexTypes = 0;

  for (int i = 0; i < 4; i++){
    indexNames = (i*2)+4;
    indexTypes = (i*2)+5;
    player_names[i] = argv[indexNames];
    player_types[i] = argv[indexTypes];
  }

  // create a vector that uses player factory to 
  //create a player and a vector to it
  vector<Player*> player_in; //to be distinguished from private variable
  
  for (int i = 0; i < 4; i++){
    player_in.push_back(Player_factory(player_names[i],player_types[i]));
  }

  Game game(player_in, shuffleString, ptsToWin, cardPack);
  game.play();

  delete[] player_names;
  delete[] player_types;
};


