#include "pieces.h"
#include "evaluation.h"

/**
 * Material
 * Pawn structure
 * Pieces evaluation
 * Mobility
 * Center control
 * King safety
 */

static int material_evaluation(Board board)
{
    int material = 0;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            material += board[i][j];
        }
    }
    return material;
}

static int32_t pieces_evaluation(Board board)
{
    int32_t material = 0;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            switch(board[i][j]) {
                case PAWN_B:
                case PAWN_W:
                    material += pawn_evaluation(board, i, j);
                    break;
                case ROOK_B:
                case ROOK_W:
                    material += rook_evaluation(board, i, j);
                    break;
                case KNIGHT_B:
                case KNIGHT_W:
                    material += knight_evaluation(board, i, j);
                    break;
                case BISHOP_B:
                case BISHOP_W:
                    material += bishop_evaluation(board, i, j);
                    break;
                case QUEEN_B:
                case QUEEN_W:
                    material += queen_evaluation(board, i, j);
                    break;
                case KING_B:
                case KING_W:
                    material += king_evaluation(board, i, j);
                    break;
                default:
                    break;
            }
        }
    }
    return material;
}

int evaluate(Board board)
{
    return (material_evaluation(board) +
            pieces_evaluation(board));
}
