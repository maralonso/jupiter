#include "board.h"


#define ROTATION_0     (1 << 0)
#define ROTATION_90    (1 << 1)
#define ROTATION_180   (1 << 2)
#define ROTATION_270   (1 << 3)

typedef retval_t (*Eval_Whith_Rotation)(
        Node_t *node, 
        square sq, 
        uint8_t fil, 
        uint8_t col);


inline retval_t EVAL_ROTATE_0(Node_t *node, square sq, Eval_Whith_Rotation func)
{
    retval_t rv;

    for (int i = sq[0]; i <= FILE_8; i++) { 
        for (int j = sq[1]; j <= COL_H; j++) { 
            rv = func(node,sq, i, j);
            SUCCES_OR_RETURN(rv);
        } 
    }
    return RV_SUCCESS;
}

inline retval_t EVAL_ROTATE_90(Node_t *node, square sq, Eval_Whith_Rotation func)
{
    retval_t rv;

    for (int i = sq[1]; i <= FILE_8; i++) { 
        for (int j = sq[0]; j >= COL_A; j--) { 
            rv = func(node, sq, i, j);
            SUCCES_OR_RETURN(rv);
        } 
    } 
    return RV_SUCCESS;
}

inline retval_t EVAL_ROTATE_180(Node_t *node, square sq, Eval_Whith_Rotation func)
{
    retval_t rv;

    for (int i = sq[0]; i >= COL_A; i--) { 
        for (int j = sq[1]; j >= FILE_1; j--) { 
            rv = func(node, sq, i, j);
            SUCCES_OR_RETURN(rv);
        } 
    } 
    return RV_SUCCESS;
}

inline retval_t EVAL_ROTATE_270(Node_t *node, square sq, Eval_Whith_Rotation func)
{
    retval_t rv;

    for (int i = sq[1]; i >= FILE_1; i--) { 
        for (int j = sq[0]; j <= COL_H; j++) { 
            rv = func(node, sq, i, j);
            SUCCES_OR_RETURN(rv);
        } 
    } 
    return RV_SUCCESS;
}

inline retval_t eval_with_rotation(Node_t *node, square sq, 
                              uint8_t rotation, void *func)
{
    if (rotation & ROTATION_0) {
        EVAL_ROTATE_0(node, sq, func);
    }
    if (rotation & ROTATION_90) {
        EVAL_ROTATE_90(node, sq, func);
    }
    if (rotation & ROTATION_180) {
        EVAL_ROTATE_0(node, sq, func);
    }
    if (rotation & ROTATION_270) {
        EVAL_ROTATE_0(node, sq, func);
    }

    return RV_SUCCESS;
}
