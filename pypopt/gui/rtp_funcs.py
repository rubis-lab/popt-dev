from PyQt5.QtWidgets import QMessageBox, QFileSystemModel, QMainWindow
from PyQt5 import uic, QtCore
import subprocess
import os
from pypopt.core.log import new_logger
rtp_ui = uic.loadUiType('pypopt/gui/rtp.ui')[0]


class RTPFuncs(QMainWindow, rtp_ui):
    def __init__(self, **kwargs):
        super().__init__()
        self.setupUi(self)
        self.log = new_logger(__name__)
        self.log.info('rtp_ui -- init')
        self.btn_test.clicked.connect(self.test_func)

        self.btn_eg1.clicked.connect(self.eg1_func)
        self.btn_cmake.clicked.connect(self.cmake_func)
        self.btn_make.clicked.connect(self.make_func)
        self.build_dir = os.path.join(os.getcwd(), 'samples/omp/build')
        self.data_dir = os.path.join(os.getcwd(), 'samples/omp/data')
        self.target_name = 'omp'

        # omp tab
        self.init_omp_tab()

        self.check_sys()

        # eg1_ts_cfg_treeview browser
        eg1_ts_cfg_root_dir = os.path.join(self.data_dir, 'ts')
        eg1_ts_cfg_filter = ['*.json']
        self.eg1_ts_cfg_file_browser_model = QFileSystemModel()
        self.eg1_ts_cfg_file_browser_model.setRootPath(
            eg1_ts_cfg_root_dir)
        self.eg1_ts_cfg_file_browser_model.setNameFilters(
            eg1_ts_cfg_filter)
        self.eg1_ts_cfg_treeview.setModel(
            self.eg1_ts_cfg_file_browser_model)
        self.eg1_ts_cfg_treeview.setRootIndex(
            self.eg1_ts_cfg_file_browser_model.index(
                eg1_ts_cfg_root_dir))
        self.eg1_ts_cfg_treeview.setContextMenuPolicy(
            QtCore.Qt.CustomContextMenu)

        # eg1_exp_cfg_treeview browser
        eg1_exp_cfg_root_dir = os.path.join(self.data_dir, 'exp')
        eg1_exp_cfg_filter = ['*.json']
        self.eg1_exp_cfg_file_browser_model = QFileSystemModel()
        self.eg1_exp_cfg_file_browser_model.setRootPath(
            eg1_exp_cfg_root_dir)
        self.eg1_exp_cfg_file_browser_model.setNameFilters(
            eg1_exp_cfg_filter)
        self.eg1_exp_cfg_treeview.setModel(
            self.eg1_exp_cfg_file_browser_model)
        self.eg1_exp_cfg_treeview.setRootIndex(
            self.eg1_exp_cfg_file_browser_model.index(
                eg1_exp_cfg_root_dir))
        self.eg1_exp_cfg_treeview.setContextMenuPolicy(
            QtCore.Qt.CustomContextMenu)
        return

    def check_sys(self):
        u = os.uname()
        if '-rt' in str(u.version):
            self.log.info('running in rt system')
            self.is_rt = True
        else:
            self.log.info('running in non-rt system')
            self.is_rt = False
        return

    # inits
    def init_omp_tab(self):
        # treeview_omp_exp_cfg browser
        root_dir_omp_exp_cfg = os.path.join(self.data_dir, 'exp')
        self.log.info('root_dir_omp_exp_cfg ' + root_dir_omp_exp_cfg)
        filter_omp_exp_cfg = ['*.json']
        self.browser_model_omp_exp_cfg = QFileSystemModel()
        self.browser_model_omp_exp_cfg.setRootPath(
            root_dir_omp_exp_cfg)
        self.browser_model_omp_exp_cfg.setNameFilters(
            filter_omp_exp_cfg)
        self.treeview_omp_exp_cfg.setModel(
            self.browser_model_omp_exp_cfg)
        self.treeview_omp_exp_cfg.setRootIndex(
            self.browser_model_omp_exp_cfg.index(
                root_dir_omp_exp_cfg))
        self.treeview_omp_exp_cfg.setContextMenuPolicy(
            QtCore.Qt.CustomContextMenu)

        # treeview_omp_ts_cfg browser
        root_dir_omp_ts_cfg = os.path.join(self.data_dir, 'ts')
        filter_omp_ts_cfg = ['*.json']
        self.browser_model_omp_ts_cfg = QFileSystemModel()
        self.browser_model_omp_ts_cfg.setRootPath(
            root_dir_omp_ts_cfg)
        self.browser_model_omp_ts_cfg.setNameFilters(
            filter_omp_ts_cfg)
        self.treeview_omp_ts_cfg.setModel(
            self.browser_model_omp_ts_cfg)
        self.treeview_omp_ts_cfg.setRootIndex(
            self.browser_model_omp_ts_cfg.index(
                root_dir_omp_ts_cfg))
        self.treeview_omp_ts_cfg.setContextMenuPolicy(
            QtCore.Qt.CustomContextMenu)
        return

    def test_func(self):
        self.log.info('test_btn clicked.')
        return

    def cmake_func(self):
        if not self.is_rt:
            self.log.info('cannot run in non-rt')
            return False
        # create build directory if not exists
        if not os.path.exists(self.build_dir):
            try:
                self.log.info('creating build dir')
                os.makedirs(self.build_dir)
            except Exception as e:
                self.log.error(e)
                return False

        self.log.info('cmake')
        subprocess.Popen(['cmake', '..'], cwd=self.build_dir)
        return True

    def make_func(self):
        if not self.is_rt:
            self.log.info('cannot run in non-rt')

        if os.path.isfile(os.path.join(self.build_dir, 'Makefile')):
            self.log.info('make')
            subprocess.Popen(["make"], cwd=self.build_dir)
            return True
        else:
            self.log.error('Makefile does not exist.')
            return False

    def eg1_func(self):
        index = self.eg1_ts_cfg_treeview.currentIndex()
        eg1_ts_cfg_path = \
            self.eg1_ts_cfg_file_browser_model.filePath(index)
        self.log.info('selected: ' + str(eg1_ts_cfg_path))
        if eg1_ts_cfg_path == '':
            QMessageBox.information(self, 'Alarm', 'Select eg1_ts_cfg!')
            return False

        if not self.is_rt:
            self.log.info('cannot run in non-rt')
        if os.path.isfile(os.path.join(self.build_dir, self.target_name)):
            self.log.info('opening eg1.')
            subprocess.Popen(['sudo', './EG1', str(eg1_ts_cfg_path)],
                cwd=self.build_dir)
            return True
        else:
            self.log.error('eg1 does not exist (maybe not compiled).')
            return False
