#pragma once
#include "../state/state.hpp"


/**
 * @brief Policy class for manimax policy, 
 * your policy class should have get_move method
 */
class Alpha_Beta_Pruning{
public:
  static Move get_move(State *state, int depth);
  static int alpha_beta_pruning(State *state, int depth, int alpha, int beta, bool max_player);
};