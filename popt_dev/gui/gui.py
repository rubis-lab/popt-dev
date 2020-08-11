import sys
from popt_dev.gui.rtp_funcs import RTPFuncs
from PyQt5.QtWidgets import QApplication
from popt_dev.core.log import new_logger
import configparser


def start_gui():
    app = QApplication(sys.argv)
    rtp_ui = RTPFuncs()
    rtp_ui.show()
    app.exec_()


if __name__ == '__main__':
    cfg = configparser.ConfigParser()
    cfg.read('popt_dev/default.ini')
    log = new_logger(__name__)
    log.info('name: ' + cfg['common']['name'])

    start_gui()
