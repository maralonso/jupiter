#include "board.h"
#include "pieces.h"

extern retval_t EXEC_ROTATE_0(Node_t *node, square sq, Eval_Whith_Rotation func);
extern retval_t EXEC_ROTATE_90(Node_t *node, square sq, Eval_Whith_Rotation func);
extern retval_t EXEC_ROTATE_180(Node_t *node, square sq, Eval_Whith_Rotation func);
extern retval_t EXEC_ROTATE_270(Node_t *node, square sq, Eval_Whith_Rotation func);
extern retval_t exec_with_rotation(Node_t *node, square sq, uint8_t rotation, void *f); 
