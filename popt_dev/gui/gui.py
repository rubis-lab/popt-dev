import sys
from popt_dev.gui.rtp_funcs import RTPFuncs
from PyQt5.QtWidgets import QApplication


def start_gui():
    app = QApplication(sys.argv)
    rtp_ui = RTPFuncs()
    rtp_ui.show()
    app.exec_()


if __name__ == '__main__':
    start_gui()
