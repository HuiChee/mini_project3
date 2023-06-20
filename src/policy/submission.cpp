#include <cstdlib>

#include "../state/state.hpp"
#include "./submission.hpp"

int Submission::alpha_beta_pruning(State *state, int depth, int alpha, int beta, bool max_player){
  if(depth == 0)
    return -(state->evaluate());
  if(!state->legal_actions.size())
    state->get_legal_actions();
  auto actions = state->legal_actions;
  if(max_player){
    int best_move = -9999;
    for(auto new_move : actions){
        State* new_state = state->next_state(new_move);
        best_move = std::max(best_move, alpha_beta_pruning(new_state, depth-1, alpha, beta, !max_player));
        alpha = std::max(alpha, best_move);
        if(beta <= alpha){
          return best_move;
        }
    }
    return best_move;
  }
  else{
    int best_move = 9999;
    for(auto new_move : actions){
        State* new_state = state->next_state(new_move);
        best_move = std::min(best_move, alpha_beta_pruning(new_state, depth-1, alpha, beta, !max_player));
        beta = std::min(beta, best_move);
        if(beta <= alpha){
          return best_move;
        }
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
Move Submission::get_move(State *state, int depth){
  if(!state->legal_actions.size())
    state->get_legal_actions();
  auto actions = state->legal_actions;
  auto best_actions = actions[0];
  bool max_player = true;
  int best_move = -9999;
  for(auto new_move : actions){
    State* new_state = state->next_state(new_move);
    int value = alpha_beta_pruning(new_state, depth-1, -10000, 10000, !max_player);
    if(value >= best_move){
        best_move = value;
        best_actions = new_move;
    }
  }
  return best_actions;
}