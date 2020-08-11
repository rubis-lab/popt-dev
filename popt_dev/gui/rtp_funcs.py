from PyQt5.QtWidgets import QMainWindow
from PyQt5 import uic
rtp_ui = uic.loadUiType('popt_dev/gui/rtp.ui')[0]


class RTPFuncs(QMainWindow, rtp_ui):
    def __init__(self, **kwargs):
        super().__init__()
        self.setupUi(self)

        print('rtp_ui -- init')
        self.btn_test.clicked.connect(self.test_func)
        return

    def test_func(self):
        print('test_btn clicked.')
        return