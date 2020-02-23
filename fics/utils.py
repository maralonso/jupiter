import re


rows = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h']

black_pieces = {
    'r': 5,
    'n': 3,
    'b': 3,
    'q': 9,
    'p': 1
}

white_pieces = {
    'R': 5,
    'N': 3,
    'B': 3,
    'Q': 9,
    'P': 1
}

def get_double_push(move):                    
    if move[0] in rows and move[2] == move[0] and abs(int(move[1]) - int(move[3]) == 3):
        return str(rows.index(move[0]))
    return '-1'    

def get_fen_board(position):
    fen = ''

    for row in position['board'].split():
        l = re.findall('-+', row)
        l.sort(key=len, reverse=True)
        for r in l:
            row = re.sub('-' * len(r), str(len(r)), row)
        fen += row + '/'
    fen = fen[:-1]
    fen += ' ' + position['turn'].lower()
    fen += ' ' + 'K' if position['w_short_castle'] == '1' else '-'        
    fen += 'Q' if position['w_long_castle'] == '1' else '-'        
    fen += 'k' if position['b_short_castle'] == '1' else '-'        
    fen += 'q' if position['b_long_castle'] == '1' else '-'        

    if position['double_push'] == '-1':
        fen += ' - '
    else:    
        fen += ' ' + rows[int(position['double_push'])]
        fen += '3 ' if position['turn'] == 'B' else '6 '
        
    fen += position['reversible_moves']
    fen += ' ' + position['move_n'] 
    return fen
              
def move_board(postion, move):
    board = ''
    rws =  position['board'].split('/')

    src_row = rws[int(move[1])]
    dst_row = rws[int(move[3])]

    src_col = rows.index(move[0])
    dst_col = rows.index(move[2])
    rws[dst_row][dst_col] = rws[src_row][src_col]
    rws[src_row][src_col] = '-'

    return '/'.join(rws)

def check_castles(move):
    w_s = True
    w_l = True
    b_s = True
    b_l = True

    if move[0] == 'e': 
        if move[1] == '1':
            w_s = False
            w_l = False 
        if move[1] == '8':
            b_s = False
            b_l = False 
    if move[0] == 'a':
        if move[1] == 1:
            w_l = False
        if move[1] == 8:
            b_l = False
    if move[0] == 'h': 
        if move[1] == 1:
            w_s = False
        if move[1] == 8:
            b_s = False    
      
    return w_s, w_l, b_s, b_l

def count_material(board):
    wm = 0
    bm = 0
    for r in board.split('/'):
        for c in r:
            if c in black_pieces.keys():
                bm += black_pieces[c]
            if c in white_pieces.keys():
                wm += white_pieces[c]

    return wm, bm                

def _build_position(self, position, move):
        
        position['relation'] = '1'
        position['double_push'] = get_double_push(move)
        position['board'] = move_board(position, move) 
        position['turn'] = 'W' if position['turn'] == 'B' else 'B'
        position['move_n'] = str(int(position['move_n']) + 1) if position['turn'] == 'B' else position['move_n']
        
        ws, wl, bs, bl = check_castles(move)
        position['w_short_castle'] = position['w_short_castle'] if ws else '-'
        position['w_long_castle'] = position['w_long_castle'] if wl else '-'
        position['b_short_castle'] = position['b_short_castle'] if bs else '-'
        position['b_long_castle'] = position['b_long_castle'] if bl else '-'

        wm, bm = count_material(position['board'])
        if wm != int(position['w_material']) or bm != int(position['b_material']) or move[0] in rows:
            position['reversible_moves'] = '0'
        else:
            position['reversible_moves'] = str(int(position['reversible_moves']) + 1)
                
        position['w_material'] = str(wm)
        position['b_material'] = str(bm)
        
        position['w_time'] = values[15]
        position['b_time'] = values[16]
        position['time_taken'] = values[19]
        position['notation'] = values[20]

def get_pretty_notation(position, move):
    pretty = ''
    rws =  position['board'].split('/')

    src_row = rws[int(move[1])]
    dst_row = rws[int(move[3])]

    src_col = rows.index(move[0])
    dst_col = rows.index(move[2])
    
    if rws[src_row][src_col] not in ['p', 'P']:
        pretty += rws[src_row][src_col]
        if rws[dst_row][dst_col] != '-':
            pretty += 'x'
        pretty += move[2]
        pretty += move[3]    
    else:
        pretty += move[0]


