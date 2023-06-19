#include <cstdlib>

#include "../state/state.hpp"
#include "./minimax.hpp"

int Minimax::minimax(State *state, int depth, bool max_player){
  if(depth == 0)
    return -(state->evaluate());
  if(!state->legal_actions.size())
    state->get_legal_actions();
  auto actions = state->legal_actions;
  if(max_player){
    int best_move = -9999;
    for(auto new_move : actions){
        State* new_state = state->next_state(new_move);
        best_move = std::max(best_move, minimax(new_state, depth-1, !max_player));
    }
    return best_move;
  }
  else{
    int best_move = 9999;
    for(auto new_move : actions){
        State* new_state = state->next_state(new_move);
        best_move = std::min(best_move, minimax(new_state, depth-1, !max_player));
    }
    return best_move;
  }
}
/**
 * @brief Use minimax get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */
Move Minimax::get_move(State *state, int depth){
  if(!state->legal_actions.size())
    state->get_legal_actions();
  auto actions = state->legal_actions;
  auto best_actions = actions[0];
  bool max_player = true;
  int best_move = -9999;
  for(auto new_move : actions){
    State* new_state = state->next_state(new_move);
    int value = minimax(new_state, depth-1, !max_player);
    if(value >= best_move){
        best_move = value;
        best_actions = new_move;
    }
  }
  return best_actions;
}