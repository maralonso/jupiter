#!/usr/bin/env python3

import logging
import time
import argparse

from fics import FICSHandler, GameEnd, IllegalMove
from engine import EngineHandler
from board import get_algebraic_notation

logging.basicConfig(level=logging.INFO, format='%(asctime)s %(message)s')

date = time.strftime("%Y,%m,%d")
timestr = time.strftime("%Y%m%d-%H%M%S")
PGN_FILE = timestr + '_jupiter_games.pgn'

NAME = 'Jupiter'

def log_new_game(position, user):

    white = position['white'] if position['white'] != user else NAME
    black = position['black'] if position['black'] != user else NAME
    logging.info("--------------------------------------------------")
    logging.info("Playing Game %s -- %s %s", position['game_n'], position['initial_time'], position['increment'])
    logging.info("%s vs %s", white, black)
    logging.info("")

    with open(PGN_FILE, 'a+') as pgn:
       pgn.write('\n\n') 
       pgn.write('[White "{}"]\n'.format(white))
       pgn.write('[Black "{}"]\n'.format(black))
       pgn.write('[Date "{}"]\n'.format(date))
       pgn.write('[Site "FICS"]\n\n')

def log_move(position, move):
    mv = ''
    if position['turn'] == 'B':
        mv += str(position['move_n']) + '. '

    mv += move
    mv += ' '

    with open(PGN_FILE, 'a+') as pgn:
        pgn.write(mv)

    if position['turn'] == 'W':
        mv = '\t' + mv
    logging.info(" %s", mv)

def log_end_game(result):
    with open(PGN_FILE, 'a+') as pgn:
        pgn.write(' ' + result)


def main(options):

    fics = FICSHandler()
    engine = EngineHandler(options.engine)

    with fics.connect(options.user, options.password):
        while True:
            if FICSHandler.GUEST_USER in options.user:
                position, turn = fics.find_game()
            else:
                position, turn = fics.seek_game()

            log_new_game(position, options.user)
            while True:
                if turn:
                    move = engine.make_move(position)
                    fics.send_move(move)
                    position['turn'] = 'W' if position['turn'] == 'B' else 'B'
                    move = get_algebraic_notation(position, move)
                    log_move(position, move)
                    turn = not turn
                else:
                    try:
                        position, turn = fics.wait_move()
                        log_move(position, position['notation'])
                        if '#' in position['notation']:
                            result = '1-0' if position['black'] == fics.user else '0-1'
                            log_end_game(result)
                            break
                    except GameEnd as game:
                        result = game.args[0] 
                        log_end_game(result)
                        break
                    except IllegalMove:
                        fics.resign()
                        result = '1-0' if position['black'] == fics.user else '0-1'
                        log_end_game(result)
                        break


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('-u', '--user', help='FICS username', default=FICSHandler.GUEST_USER)
    parser.add_argument('-p', '--password', help='FICS password')
    parser.add_argument('-e', '--engine', help='Engine binary file', default='engine/jupiter')
    args = parser.parse_args()

    main(args)

