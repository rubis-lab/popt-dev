from PyQt5.QtWidgets import QMainWindow
from PyQt5 import uic
import subprocess
rtp_ui = uic.loadUiType('popt_dev/gui/rtp.ui')[0]


class RTPFuncs(QMainWindow, rtp_ui):
    def __init__(self, **kwargs):
        super().__init__()
        self.setupUi(self)

        print('rtp_ui -- init')
        self.btn_test.clicked.connect(self.test_func)
        
        self.btn_eg1.clicked.connect(self.eg1_func)
        self.btn_cmake.clicked.connect(self.cmake_func)
        self.btn_make.clicked.connect(self.make_func)
        return

    def test_func(self):
        print('test_btn clicked.')
        return
        
    def cmake_func(self):
        print('cmake_func clicked')
        cwd = "/home/rubis/popt-dev/eg1/build"
        subprocess.Popen(["cmake", ".."], cwd = cwd)
        return
    
    def make_func(self):
        print('make_func clicked')
        cwd = "/home/rubis/popt-dev/eg1/build"
        subprocess.Popen(["make"], cwd = cwd)
        return

    def eg1_func(self):
        print('eg1_func clicked')
        cwd = "/home/rubis/popt-dev/eg1/build"
        subprocess.Popen(["sudo", "./EG1", "../sample.json"], cwd = cwd)