#include "pieces.h"
#include "evaluation.h"

/**
 * Material
 * Pawn structure
 * Pieces evaluation
 * Mobility
 * Center control
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

static bool piece_attack_square(Board board, square from, square to)
{
    bool attaked;
    switch(board[from[0]][from[1]]) {
        case PAWN_B:
        case PAWN_W:
            attaked = pawn_attak_square(board, from, to);
            break;
        case ROOK_B:
        case ROOK_W:
            attaked = rook_attak_square(board, from, to);
            break;
        case KNIGHT_B:
        case KNIGHT_W:
            attaked = knight_attak_square(board, from, to);
            break;
        case BISHOP_B:
        case BISHOP_W:
            attaked = bishop_attak_square(board, from, to);
            break;
        case QUEEN_B:
        case QUEEN_W:
            attaked = queen_attak_square(board, from, to);
            break;
        default:
            attaked = false;
            break;
    }

    return attaked;
}


static int32_t center_control(Board board)
{
    int8_t turn;
    int32_t control = 0;
    square c4 = {FILE_4, COL_C};
    square c5 = {FILE_5, COL_C};
    square d4 = {FILE_4, COL_D};
    square d5 = {FILE_5, COL_D};
    square e4 = {FILE_4, COL_E};
    square e5 = {FILE_5, COL_E};
    square f4 = {FILE_4, COL_F};
    square f5 = {FILE_5, COL_F};

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (board[i][j] != 0) {
                square from = {i, j};
                turn = TURN(board, i, j);

                if (piece_attack_square(board, from, c4)) {
                    control += CENTER_CONTROL_C4_POND * turn;
                }
                if (piece_attack_square(board, from, c5)) {
                    control += CENTER_CONTROL_C4_POND * turn;
                }
                if (piece_attack_square(board, from, d4)) {
                    control += CENTER_CONTROL_C4_POND * turn;
                }
                if (piece_attack_square(board, from, d5)) {
                    control += CENTER_CONTROL_C4_POND * turn;
                }
                if (piece_attack_square(board, from, e4)) {
                    control += CENTER_CONTROL_C4_POND * turn;
                }
                if (piece_attack_square(board, from, e5)) {
                    control += CENTER_CONTROL_C4_POND * turn;
                }
                if (piece_attack_square(board, from, f4)) {
                    control += CENTER_CONTROL_C4_POND * turn;
                }
                if (piece_attack_square(board, from, f5)) {
                    control += CENTER_CONTROL_C4_POND * turn;
                }
            }
        }
    }
    return control;
}

int32_t evaluate(Board board)
{
    return (material_evaluation(board) +
            pieces_evaluation(board) +
            center_control(board));
}
