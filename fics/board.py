
files = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h']

def get_files_and_ranks(move):
    i_file = files.index(move[0])
    i_rank = int(move[1]) - 1
    f_file = files.index(move[2])
    f_rank = int(move[3]) - 1

    return i_file, i_rank, f_file, f_rank

def get_only_knight_move(board, piece, move):
    initial_file, initial_rank, final_file, final_rank = get_files_and_ranks(move)

    for f in [final_file - 2, final_file + 2]:
        for r in [final_rank + 1, final_rank -1]:
            try:
                if board[r][f] == piece and (f != initial_file or r != initial_rank):
                    if move[0] == files[f]: 
                        return str(initial_rank)
                    else:
                        return move[0]
            except IndexError:
                pass
    for f in [final_file - 1, final_file + 1]:
        for r in [final_rank + 2, final_rank -2]:
            try:
                if board[r][f] == piece and (f != initial_file or r != initial_rank):
                    if move[0] == files[f]: 
                        return str(initial_rank)
                    else:
                        return move[0]
            except IndexError:
                pass
    return ''


def get_only_rook_move(board, piece, move):    
    initial_file, initial_rank, final_file, final_rank = get_files_and_ranks(move)

    for n in reversed(range(0, final_file)):
        if board[final_rank][n] == piece and  n != initial_rank:
            return move[0]
        if board[final_rank][n] != '-':
            break
    
    for n in range(final_file, 8):
        if board[final_rank][n] == piece and  n != initial_rank:
            return move[0]
        if board[final_rank][n] != '-':
            break    

    for n in reversed(range(0, final_rank)):
        if board[n][final_file] == piece and  n != initial_file:
            return move[1]
        if board[n][final_file] != '-':
            break    
    for n in range(final_rank, 8):
        if board[n][final_file] == piece and  n != initial_file:
            return move[1]
        if board[n][final_file] != '-':
            break    
    return ''

def king_castle(move):

    if move[0] == 'e' and move[2] == 'g':    
        return 'O-O'
    if move[1] == 'e' and move[3] == 'c':
        return 'O-O-O'

    return None   

def get_algebraic_notation(position, move):
    initial_file, initial_rank, final_file, final_rank = get_files_and_ranks(move)

    board = position['board'].split() 
    board.reverse()
    piece = board[initial_rank][initial_file]
    notation = move[0] if piece in ['p', 'P'] else piece.upper()

    if piece in ['n', 'N']:
        notation += get_only_knight_move(board, piece, move)

    if piece in ['r', 'R']:
        notation += get_only_rook_move(board, piece, move)

    if piece in ['k', 'K']:
        castle = king_castle(move)
        if castle:
            return castle
            
    if board[final_rank][final_file] != '-':
        notation += 'x'

    if notation[0] not in files or notation[-1] == 'x':    
        notation += move[2]
    notation += move[3]    

    return notation
