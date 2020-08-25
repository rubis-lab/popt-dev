import sys
from pypopt.gui.rtp_funcs import RTPFuncs
from PyQt5.QtWidgets import QApplication
from pypopt.core.log import new_logger
import configparser


def start_gui():
    app = QApplication(sys.argv)
    rtp_args = {
        'terminal_pid': sys.argv[1]
    }
    rtp_ui = RTPFuncs(**rtp_args)
    rtp_ui.show()
    app.exec_()


if __name__ == '__main__':
    cfg = configparser.ConfigParser()
    cfg.read('pypopt/default.ini')
    log = new_logger(__name__)
    log.info('name: ' + cfg['common']['name'])

    start_gui()
