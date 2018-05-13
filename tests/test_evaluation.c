#include "board.h"
#include "evaluation.h"
#include "fen.h"
#include "cu/cu.h"
#include "node.h"
#include "pieces/include/pieces.h"

TEST(evaluation_material)
{
    int32_t material;
    Node_t node;
    retval_t rv;
    char fen[] = "rbnqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RBNQKBNR w KQkq - 0 0";        

    rv = get_node_from_fen(&node, fen);
    assertEquals(rv, RV_SUCCESS);
    
    material = evaluate(node.board);
    assertEquals(0, material);

    char fen_r[] = "r7/8/8/8/8/8/8/8 w KQkq - 0 0";        
    char fen_R[] = "R7/8/8/8/8/8/8/8 w KQkq - 0 0";        

    rv = get_node_from_fen(&node, fen_r);
    assertEquals(rv, RV_SUCCESS);
    material = evaluate(node.board);
    assertTrue(ROOK_B >= material);

    rv = get_node_from_fen(&node, fen_R);
    assertEquals(rv, RV_SUCCESS);
    material = evaluate(node.board);
    assertTrue(ROOK_W <= material);

    char fen_b[] = "b7/8/8/8/8/8/8/8 w KQkq - 0 0";        
    char fen_B[] = "B7/8/8/8/8/8/8/8 w KQkq - 0 0";        

    rv = get_node_from_fen(&node, fen_b);
    assertEquals(rv, RV_SUCCESS);
    material = evaluate(node.board);
    assertTrue(BISHOP_B >= material);

    rv = get_node_from_fen(&node, fen_B);
    assertEquals(rv, RV_SUCCESS);
    material = evaluate(node.board);
    assertTrue(BISHOP_W <= material);

    char fen_n[] = "n7/8/8/8/8/8/8/8 w KQkq - 0 0";        
    char fen_N[] = "N7/8/8/8/8/8/8/8 w KQkq - 0 0";        

    rv = get_node_from_fen(&node, fen_n);
    assertEquals(rv, RV_SUCCESS);
    material = evaluate(node.board);
    assertTrue( 0 > material);

    rv = get_node_from_fen(&node, fen_N);
    assertEquals(rv, RV_SUCCESS);
    material = evaluate(node.board);
    assertTrue(0 < material);

    char fen_q[] = "q7/8/8/8/8/8/8/8 w KQkq - 0 0";        
    char fen_Q[] = "Q7/8/8/8/8/8/8/8 w KQkq - 0 0";        

    rv = get_node_from_fen(&node, fen_q);
    assertEquals(rv, RV_SUCCESS);
    material = evaluate(node.board);
    assertTrue(QUEEN_B >= material);

    rv = get_node_from_fen(&node, fen_Q);
    assertEquals(rv, RV_SUCCESS);
    material = evaluate(node.board);
    assertTrue(QUEEN_W <= material);

    char fen_k[] = "k7/8/8/8/8/8/8/8 w KQkq - 0 0";        
    char fen_K[] = "K7/8/8/8/8/8/8/8 w KQkq - 0 0";        

    rv = get_node_from_fen(&node, fen_k);
    assertEquals(rv, RV_SUCCESS);
    material = evaluate(node.board);
    assertTrue(KING_B >= material);

    rv = get_node_from_fen(&node, fen_K);
    assertEquals(rv, RV_SUCCESS);
    material = evaluate(node.board);
    assertTrue(KING_W <= material);
}

TEST(evaluation_rook_moves)
{
    int32_t mat1, mat2, mat3, mat4,
            mat5, mat6, mat7, mat8;
    Node_t node1, node2, node3, node4,
           node5, node6, node7, node8;
    retval_t rv;
    char fen1[] = "rb6/p7/8/8/8/8/8/8 w KQkq - 0 0";        
    char fen2[] = "r1b5/p7/8/8/8/8/8/8 w KQkq - 0 0";        
    char fen3[] = "r7/p7/8/8/8/8/8/8 w KQkq - 0 0";        
    char fen4[] = "r7/8/8/8/8/8/8/8 w KQkq - 0 0";        

    rv = get_node_from_fen(&node1, fen1);
    assertEquals(rv, RV_SUCCESS);
    rv = get_node_from_fen(&node2, fen2);
    assertEquals(rv, RV_SUCCESS);
    rv = get_node_from_fen(&node3, fen3);
    assertEquals(rv, RV_SUCCESS);
    rv = get_node_from_fen(&node4, fen4);
    assertEquals(rv, RV_SUCCESS);
    
    mat1 = rook_evaluation(node1.board, FILE_8, COL_A);
    mat2 = rook_evaluation(node2.board, FILE_8, COL_A);
    assertTrue(mat2 < mat1);
    mat3 = rook_evaluation(node3.board, FILE_8, COL_A);
    assertTrue(mat3 < mat2);
    mat4 = rook_evaluation(node4.board, FILE_8, COL_A);
    assertTrue(mat4 < mat3);

    char fen5[] = "RB6/P7/8/8/8/8/8/8 w KQkq - 0 0";        
    char fen6[] = "R1B5/P7/8/8/8/8/8/8 w KQkq - 0 0";        
    char fen7[] = "R7/P7/8/8/8/8/8/8 w KQkq - 0 0";        
    char fen8[] = "R7/8/8/8/8/8/8/8 w KQkq - 0 0";        

    rv = get_node_from_fen(&node5, fen5);
    assertEquals(rv, RV_SUCCESS);
    rv = get_node_from_fen(&node6, fen6);
    assertEquals(rv, RV_SUCCESS);
    rv = get_node_from_fen(&node7, fen7);
    assertEquals(rv, RV_SUCCESS);
    rv = get_node_from_fen(&node8, fen8);
    assertEquals(rv, RV_SUCCESS);
    
    mat5 = rook_evaluation(node5.board, FILE_8, COL_A);
    mat6 = rook_evaluation(node6.board, FILE_8, COL_A);
    assertTrue(mat6 > mat5);
    mat7 = rook_evaluation(node7.board, FILE_8, COL_A);
    assertTrue(mat7 > mat6);
    mat8 = rook_evaluation(node8.board, FILE_8, COL_A);
    assertTrue(mat8 > mat7);
}

TEST(evaluation_rook_doubled)
{
    int32_t mat1, mat2, mat3, mat4, mat5, mat6;
    Node_t node1, node2, node3, node4, node5, node6;
    retval_t rv;

    char fen1[] = "r6b/8/8/8/8/8/8/b7 w KQkq - 0 0";
    char fen2[] = "r6r/8/8/8/8/8/8/b7 w KQkq - 0 0";
    char fen3[] = "r6b/8/8/8/8/8/8/r7 w KQkq - 0 0";
  
    rv = get_node_from_fen(&node1, fen1);
    assertEquals(rv, RV_SUCCESS);
    rv = get_node_from_fen(&node2, fen2);
    assertEquals(rv, RV_SUCCESS);
    rv = get_node_from_fen(&node3, fen3);
    assertEquals(rv, RV_SUCCESS);
  
    mat1 = rook_evaluation(node1.board, FILE_8, COL_A);
    mat2 = rook_evaluation(node2.board, FILE_8, COL_A);
    assertTrue(mat2 < mat1);
    mat3 = rook_evaluation(node3.board, FILE_8, COL_A);
    assertTrue(mat3 < mat1);

    char fen4[] = "R6B/8/8/8/8/8/8/B7 w KQkq - 0 0";        
    char fen5[] = "R6R/8/8/8/8/8/8/B7 w KQkq - 0 0";        
    char fen6[] = "R6B/8/8/8/8/8/8/R7 w KQkq - 0 0";        
    
    rv = get_node_from_fen(&node4, fen4);
    assertEquals(rv, RV_SUCCESS);
    rv = get_node_from_fen(&node5, fen5);
    assertEquals(rv, RV_SUCCESS);
    rv = get_node_from_fen(&node6, fen6);
    assertEquals(rv, RV_SUCCESS);
    
    mat4 = rook_evaluation(node4.board, FILE_8, COL_A);
    mat5 = rook_evaluation(node5.board, FILE_8, COL_A);
    assertTrue(mat5 > mat4);
    mat6 = rook_evaluation(node6.board, FILE_8, COL_A);
    assertTrue(mat6 > mat4);

}

TEST(evaluation_rook_x_ray)
{
    int32_t mat1, mat2, mat3, mat4, mat5, mat6;
    Node_t node1, node2, node3, node4, node5, node6;
    retval_t rv;

    char fen1[] = "rn6/p7/8/8/8/8/8/8 w KQkq - 0 0";        
    char fen2[] = "rn6/p7/8/8/8/8/8/Q7 w KQkq - 0 0";        
    char fen3[] = "rn5Q/p7/8/8/8/8/8/8 w KQkq - 0 0";        
    
    rv = get_node_from_fen(&node1, fen1);
    assertEquals(rv, RV_SUCCESS);
    rv = get_node_from_fen(&node2, fen2);
    assertEquals(rv, RV_SUCCESS);
    rv = get_node_from_fen(&node3, fen3);
    assertEquals(rv, RV_SUCCESS);
    
    mat1 = rook_evaluation(node1.board, FILE_8, COL_A);
    mat2 = rook_evaluation(node2.board, FILE_8, COL_A);
    assertTrue(mat2 < mat1);
    mat3 = rook_evaluation(node3.board, FILE_8, COL_A);
    assertTrue(mat3 < mat1);

    char fen4[] = "R6B/8/8/8/8/8/8/B7 w KQkq - 0 0";        
    char fen5[] = "R6R/8/8/8/8/8/8/B7 w KQkq - 0 0";        
    char fen6[] = "R6B/8/8/8/8/8/8/R7 w KQkq - 0 0";        
    
    rv = get_node_from_fen(&node4, fen4);
    assertEquals(rv, RV_SUCCESS);
    rv = get_node_from_fen(&node5, fen5);
    assertEquals(rv, RV_SUCCESS);
    rv = get_node_from_fen(&node6, fen6);
    assertEquals(rv, RV_SUCCESS);
    
    mat4 = rook_evaluation(node4.board, FILE_8, COL_A);
    mat5 = rook_evaluation(node5.board, FILE_8, COL_A);
    assertTrue(mat5 > mat4);
    mat6 = rook_evaluation(node6.board, FILE_8, COL_A);
    assertTrue(mat6 > mat4);
}

TEST(evaluation_bishop_moves)
{
    int32_t mat1, mat2, mat3, mat4,
            mat5, mat6, mat7, mat8;
    Node_t node1, node2, node3, node4,
           node5, node6, node7, node8;
    retval_t rv;
    char fen1[] = "8/8/2p1p3/3b4/2p1p3/8/2P5/8 w KQkq - 0 0";        
    char fen2[] = "8/8/4p3/3b4/2p1p3/8/2P5/8 w KQkq - 0 0";        
    char fen3[] = "8/8/8/3b4/2p1p3/8/2P5/8 w KQkq - 0 0";        
    char fen4[] = "8/8/8/3b4/4p3/8/2P5/8 w KQkq - 0 0";        

    rv = get_node_from_fen(&node1, fen1);
    assertEquals(rv, RV_SUCCESS);
    rv = get_node_from_fen(&node2, fen2);
    assertEquals(rv, RV_SUCCESS);
    rv = get_node_from_fen(&node3, fen3);
    assertEquals(rv, RV_SUCCESS);
    rv = get_node_from_fen(&node4, fen4);
    assertEquals(rv, RV_SUCCESS);
    
    mat1 = bishop_evaluation(node1.board, FILE_5, COL_D);
    mat2 = bishop_evaluation(node2.board, FILE_5, COL_D);
    assertTrue(mat2 < mat1);
    mat3 = bishop_evaluation(node3.board, FILE_5, COL_D);
    assertTrue(mat3 < mat2);
    mat4 = bishop_evaluation(node4.board, FILE_5, COL_D);
    assertTrue(mat4 < mat3);

    char fen5[] = "8/2p5/2P1P3/3B4/2P1P3/8/8/8 w KQkq - 0 0";        
    char fen6[] = "8/2p5/4P3/3B4/2P1P3/8/8/8 w KQkq - 0 0";        
    char fen7[] = "8/2p5/8/3B4/2P1P3/8/8/8 w KQkq - 0 0";        
    char fen8[] = "8/2p5/8/3B4/4P3/8/8/8 w KQkq - 0 0";        

    rv = get_node_from_fen(&node5, fen5);
    assertEquals(rv, RV_SUCCESS);
    rv = get_node_from_fen(&node6, fen6);
    assertEquals(rv, RV_SUCCESS);
    rv = get_node_from_fen(&node7, fen7);
    assertEquals(rv, RV_SUCCESS);
    rv = get_node_from_fen(&node8, fen8);
    assertEquals(rv, RV_SUCCESS);
    
    mat5 = bishop_evaluation(node5.board, FILE_5, COL_D);
    mat6 = bishop_evaluation(node6.board, FILE_5, COL_D);
    assertTrue(mat6 > mat5);
    mat7 = bishop_evaluation(node7.board, FILE_5, COL_D);
    assertTrue(mat7 > mat6);
    mat8 = bishop_evaluation(node8.board, FILE_5, COL_D);
    assertTrue(mat8 > mat7);
}

TEST(evaluation_bishop_unexpulsable)
{
    int32_t mat1, mat2, mat3, mat4;
    Node_t node1, node2, node3, node4;
    retval_t rv;
    char fen1[] = "8/8/8/3b4/8/8/2P5/8 w KQkq - 0 0";        
    char fen2[] = "8/8/2p5/3b4/8/8/8/8 w KQkq - 0 0";        

    rv = get_node_from_fen(&node1, fen1);
    assertEquals(rv, RV_SUCCESS);
    rv = get_node_from_fen(&node2, fen2);
    assertEquals(rv, RV_SUCCESS);
    
    mat1 = bishop_evaluation(node1.board, FILE_5, COL_D);
    mat2 = bishop_evaluation(node2.board, FILE_5, COL_D);
    assertTrue(mat2 < mat1);

    char fen3[] = "8/8/2p5/8/8/3B4/8/8 w KQkq - 0 0";        
    char fen4[] = "8/8/8/8/8/3B4/2P5/8 w KQkq - 0 0";        

    rv = get_node_from_fen(&node3, fen3);
    assertEquals(rv, RV_SUCCESS);
    rv = get_node_from_fen(&node4, fen4);
    assertEquals(rv, RV_SUCCESS);
    
    mat3 = bishop_evaluation(node3.board, FILE_3, COL_D);
    mat4 = bishop_evaluation(node4.board, FILE_3, COL_D);
    assertTrue(mat4 >  mat3);
}

TEST(evalution_bishop_x_ray)
{
    int32_t mat1, mat2, mat3, mat4;
    Node_t node1, node2, node3, node4;
    retval_t rv;
    char fen1[] = "8/1b6/8/8/8/8/6P1/8 w KQkq - 0 0";        
    char fen2[] = "8/1b6/8/8/8/8/6P1/7K w KQkq - 0 0";        

    rv = get_node_from_fen(&node1, fen1);
    assertEquals(rv, RV_SUCCESS);
    rv = get_node_from_fen(&node2, fen2);
    assertEquals(rv, RV_SUCCESS);
    
    mat1 = bishop_evaluation(node1.board, FILE_7, COL_B);
    mat2 = bishop_evaluation(node2.board, FILE_7, COL_B);
    assertTrue(mat2 < mat1);

    char fen3[] = "8/1p6/8/8/8/8/6B1/8 w KQkq - 0 0";        
    char fen4[] = "k7/1p6/8/8/8/8/6B1/8 w KQkq - 0 0";        

    rv = get_node_from_fen(&node3, fen3);
    assertEquals(rv, RV_SUCCESS);
    rv = get_node_from_fen(&node4, fen4);
    assertEquals(rv, RV_SUCCESS);
    
    mat3 = bishop_evaluation(node3.board, FILE_2, COL_G);
    mat4 = bishop_evaluation(node4.board, FILE_2, COL_G);
    assertTrue(mat4 >  mat3);

}