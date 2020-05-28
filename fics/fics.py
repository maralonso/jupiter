import logging
import re


from telnetlib import Telnet
from contextlib import contextmanager

logging.basicConfig(level=logging.DEBUG, format='%(asctime)s %(message)s')

class GameEnd(Exception):
    pass
class IllegalMove(Exception):
    pass

class FICSHandler:
    
    FICS_URL = 'freechess.org'
    FICS_PORT = 5000
    GUEST_USER = 'guest'
    FICS_PROMPT = 'fics%'
    SEEK_5_CMD = 'seek 5'
    SEEK_10_CMD = 'seek 10'
    SEEK_15_CMD = 'seek 15'

    def __init__(self, url=None, port=None, user=None):
        self.url = url or self.FICS_URL
        self.port = port or self.FICS_PORT

    def _login(self, user, passw):
        self.telnet.read_until(b'login: ')
        self.telnet.write(user.encode())
        self.telnet.write('\n'.encode())
        if self.GUEST_USER in user:
            self.telnet.read_until('enter the server as "'.encode())
            self.user = self.telnet.read_until(b'"').decode()[:-1]
        else:
            self.telnet.read_until('password:'.encode())
            self.telnet.write(passw.encode())
            self.telnet.write('\n'.encode())

        self.telnet.write('\n'.encode())
        logging.info("Connected to %s as %s", self.url, self.user)

    def _config(self):
        self.telnet.write(b'set seek 0\n')
        self.telnet.write(b'set style 12\n')

    def _parse_game(self, game):
        pattern = re.compile('([\w]+)\s+\(....\)\s+([\w]+)\s+\(....\)\s+[\w]+\s+[\w]+\s+([\d]+)\s+([\d]+)')
        values = re.findall(pattern, game)[0]
        gm = {}
        gm['white'] = values[0]
        gm['black'] = values[1]
        gm['time'] = values[2]
        gm['increment'] = values[3]
        return gm

    def _decode_position(self, stream):
        position = {}
        stream = re.sub('.*<12>', '', stream)
        position['board'] = re.findall('([\w-]{8} [\w-]{8} [\w-]{8} [\w-]{8} [\w-]{8} [\w-]{8} [\w-]{8} [\w-]{8})', stream)[0]
        stream = re.sub(position['board'], '', stream)
        values = stream.split()[1:]
    
        position['turn'] = values[0]
        position['double_push'] = values[1]
        position['w_short_castle'] = values[2]
        position['w_long_castle'] = values[3]
        position['b_short_castle'] = values[4]
        position['b_long_castle'] = values[5]
        position['reversible_moves'] = values[6]
        position['game_n'] = values[7]
        position['white'] = values[8]
        position['black'] = values[9]
        position['relation'] = values[10]
        position['initial_time'] = values[11]
        position['increment'] = values[12]
        position['w_material'] = values[13]
        position['b_material'] = values[14]
        position['w_time'] = values[15]
        position['b_time'] = values[16]
        position['move_n'] = values[17]
        position['verbose'] = values[18]
        position['time_taken'] = values[19]
        position['notation'] = values[20]
        position['orientation'] = values[21]

        return position

    def _get_move(self):
        while True:
            output = self.telnet.read_until(self.FICS_PROMPT.encode()).decode()
            if '<12>' in output:
                return self._decode_position(output)

    def _valid_move(self, position):
        if position['turn'] == 'W' and not self.user in position['white']:
            return False
        if position['turn'] == 'B' and not self.user in position['black']:
            return False
        return True

    @contextmanager    
    def connect(self, user, passw):
        self.telnet = Telnet(host=self.url, port=self.port)
        self.user = user
        self._login(user, passw)
        self._config()
        try:
            yield
        finally:
            self.telnet.close()        
        
    def seek_game(self):
        logging.info('seeking games...')
        self.telnet.write(self.SEEK_5_CMD.encode())
        self.telnet.write(b'\n')
        self.telnet.write(self.SEEK_10_CMD.encode())
        self.telnet.write(b'\n')
        self.telnet.write(self.SEEK_15_CMD.encode())
        self.telnet.write(b'\n')
        output = self.telnet.read_until('Creating: '.encode()).decode()
        game = self.telnet.read_until(b'{').decode()
        logging.info('Playing ' + game[:-1])
        self.telnet.read_until(b'}').decode()
        position = self._get_move()
        color = 'W' if self.user in position['white'] else 'B'
        turn = color == position['turn']
        return position, turn

    def find_game(self):  
        logging.info('Looking for games...')
        pattern = re.compile('[\d]+[\s ][\d+]+\s+[\w()]+\s+[\d]+\s+[\d]+\s+[\w]+\s+[\w]+')

        while True:
            self.telnet.write(b'sought\n')

            output = self.telnet.read_until('ads displayed'.encode()).decode('utf8')
            games = re.findall(pattern, output)
            for game in games:
                if 'standard' in game.split()[-1] or 'blitz' in game.split()[-1]:
                    self.telnet.write(('play ' + game.split()[0] + '\n').encode())
                    output = self.telnet.read_until('Creating: '.encode(), timeout=5).decode()
                    if 'seek is not available' in output:
                        continue
                    else:
                        game = self.telnet.read_until(b'{').decode()
                        logging.info('Playing ' + game[:-1])
                        self.telnet.read_until(b'}').decode()
                        position = self._get_move()
                        color = 'W' if self.user in position['white'] else 'B'
                        turn = color == position['turn']
                        return position, turn

    def wait_move(self):
        while True:
            output = self.telnet.read_until(self.FICS_PROMPT.encode()).decode()
            if 'Illegal move' in output:
                logging.error(output)
                raise IllegalMove

            if '{' in output:
                logging.warning(output)
                try:
                    result = re.findall('.*{.*} (.-.)', output)[0]
                except:
                    logging.error('No result?')
                    result = ''
                raise GameEnd(result)
                
            if '<12>' in output:
                position = self._decode_position(output)
                if self._valid_move(position):
                    color = 'W' if self.user in position['white'] else 'B'
                    oponent = position['white'] if color == 'B' else position['black']
                    return position, True

    def send_move(self, move):
        self.telnet.write(move.encode())
        self.telnet.write('\n'.encode())

    def resign(self):
        self.telnet.write('resign \n'.encode())
