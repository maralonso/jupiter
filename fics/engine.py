import re

from subprocess import Popen, PIPE, STDOUT


from utils import get_fen_board

class EngineHandler:

    def __init__(self, path):
        self.path = path
 
    def make_move(self, position):
        fen = get_fen_board(position)
        command = 'uci\nposition fen {}\ngo depth 4\n'.format(fen)
        with Popen(self.path, stdout=PIPE, stdin=PIPE, stderr=STDOUT, universal_newlines=True, bufsize=0) as proc:
            proc.stdin.write(command)
            while True:
                output = proc.stdout.readline()
                if re.findall('.*bestmove (\w+)', output):
                    break
            proc.stdin.write('quit\n')        
        return re.findall('.*bestmove (\w+)', output)[0]
