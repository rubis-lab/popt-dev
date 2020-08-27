from PyQt5.QtWidgets import QMessageBox, QFileSystemModel, QMainWindow, QTextEdit, QLabel, QVBoxLayout
from PyQt5 import uic, QtCore
import subprocess
import os
import numpy as np
from pypopt.core.log import new_logger
from matplotlib.backends.backend_qt5agg import FigureCanvas, NavigationToolbar2QT as NavigationToolbar
from matplotlib.figure import Figure
rtp_ui = uic.loadUiType('pypopt/gui/rtp.ui')[0]



class RTPFuncs(QMainWindow, rtp_ui):
    def __init__(self, **kwargs):
        super().__init__()
        self.setupUi(self)
        self.log = new_logger(__name__)
        self.log.info('init')
        self.terminal_pid = kwargs.get('terminal_pid', -1)       
        self.log.info('terminal_pid: ' + str(self.terminal_pid))
        self.label_tid.setText("pid : " + str(self.terminal_pid))

        #test
        self.btn_test.clicked.connect(self.test_func)
        self.check_sys()

        # eg1 tab
        self.build_dir = os.path.join(os.getcwd(), 'samples/omp/build')
        self.data_dir = os.path.join(os.getcwd(), 'samples/omp/data')
        self.btn_eg1.clicked.connect(self.eg1_func)
        self.btn_cmake.clicked.connect(self.cmake_func)
        self.btn_make.clicked.connect(self.eg1_make_func)
        self.init_eg1_tab()

        # cpu setter tab
        self.scripts_dir = os.path.join(os.getcwd(), 'scripts') 
        self.line_edit_set_nvp.setText('4')
        self.line_edit_set_cpu.setText('4')
        self.btn_set_freq.clicked.connect(self.set_freq_func)
        self.btn_set_cpu.clicked.connect(self.set_cpu_func)
        self.init_cpu_setter_tab() 
        
        # omp tab
        self.omp_build_dir = os.path.join(os.getcwd(), 'samples/omp/build')
        self.omp_data_dir = os.path.join(os.getcwd(), 'samples/omp/data')
        self.omp_log_dir = os.path.join(os.getcwd(), 'samples/omp/build')
        self.rts_build_dir = os.path.join(os.getcwd(), 'rts/build')
        self.target_name = 'omp'
        self.btn_rts_rebuild.clicked.connect(self.rts_rebuild_func)
        self.btn_rts_build.clicked.connect(self.rts_build_func)
        
        self.init_omp_tab()

        # init graph
        self.init_graph()        

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
    
    # init eg1
    def init_eg1_tab(self):
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

    # init cpu setter
    def init_cpu_setter_tab(self):
        # treeview_scripts_cfg browser
        self.log.info('root_dir_scripts_cfg ' + self.scripts_dir)
        filter_scripts_cfg = ['*.sh']
        self.browser_model_scripts_cfg = QFileSystemModel()        
        self.browser_model_scripts_cfg.setRootPath(
            self.scripts_dir)        
        self.browser_model_scripts_cfg.setNameFilters(
            filter_scripts_cfg)
        self.treeview_scripts_cfg.setModel(
            self.browser_model_scripts_cfg)
        self.treeview_scripts_cfg.setRootIndex(
            self.browser_model_scripts_cfg.index(
                self.scripts_dir))
        self.treeview_scripts_cfg.setContextMenuPolicy(
            QtCore.Qt.CustomContextMenu)
        return

    # init opm tab
    def init_omp_tab(self):
        # treeview_omp_exp_cfg browser
        root_dir_omp_exp_cfg = os.path.join(self.omp_data_dir, 'exp')
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
        root_dir_omp_ts_cfg = os.path.join(self.omp_data_dir, 'ts')
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

        # treeview_omp_log_file
        root_dir_omp_log_file = self.omp_log_dir
        filter_omp_log_file = ['*.out']
        self.browser_model_omp_log_file = QFileSystemModel()
        self.browser_model_omp_log_file.setRootPath(
            root_dir_omp_log_file)
        self.browser_model_omp_log_file.setNameFilters(
            filter_omp_log_file)
        self.treeview_omp_log_file.setModel(
            self.browser_model_omp_log_file)
        self.treeview_omp_log_file.setRootIndex(
            self.browser_model_omp_log_file.index(
                root_dir_omp_log_file))
        self.treeview_omp_log_file.setContextMenuPolicy(
            QtCore.Qt.CustomContextMenu)

        # omp tab buttons
        self.btn_omp_rebuild.clicked.connect(self.omp_rebuild_func)
        self.btn_omp_build.clicked.connect(self.omp_build_func)
        self.btn_omp_run.clicked.connect(self.omp_run_func)
        self.btn_omp_analyze.clicked.connect(self.omp_analyze_func)

        return

    # init graph
    def init_graph(self):
        layout = QVBoxLayout(self.widget_omp_plt_task1)
        static_canvas = FigureCanvas(Figure(figsize=(5, 3)))
        layout.addWidget(static_canvas)
        self.addToolBar(NavigationToolbar(static_canvas, self))
        self._static_ax = static_canvas.figure.subplots()
        # self.print_graph()
             
        return 

    def test_func(self):
        self.log.info('test_btn clicked.')
        return

    #For eg1 tab
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

    def eg1_make_func(self):
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

    # For Cpu setter tab
    def set_cpu_func(self):        
        index = self.treeview_scripts_cfg.currentIndex()
        scripts_cfg_path = \
            self.browser_model_scripts_cfg.filePath(index)
        self.log.info('selected: ' + str(scripts_cfg_path))
        self.log.info(self.line_edit_set_cpu.text())
        self.log.info('opening setcpu.')
        subprocess.Popen(['./cpuset.sh',self.line_edit_set_cpu.text(),str(self.terminal_pid)],
            cwd=self.scripts_dir)
        return
    
    def set_freq_func(self):                
        self.log.info(self.line_edit_set_nvp.text())        
        subprocess.Popen(['sudo','nvpmodel','-m',self.line_edit_set_nvp.text()])
        return

    # For omp tab    
    def rts_rebuild_func(self):
        # create build directory if not exists
        if not os.path.exists(self.rts_build_dir):
            try:
                self.log.info('creating rts_build dir')
                os.makedirs(self.rts_build_dir)
            except Exception as e:
                self.log.error(e)
                return False

        # cmake                
        self.log.info('rts_cmake')
        subprocess.Popen(['cmake', '..'], cwd=self.rts_build_dir)

        # make & make install
        if os.path.isfile(os.path.join(self.rts_build_dir, 'Makefile')):
            self.log.info('rts_make & install')
            if(self.make_func(self.rts_build_dir)):
                subprocess.Popen(["make","install"], cwd=self.rts_build_dir)
                return True
            else:
                return False
        else:
            self.log.error('Makefile does not exist.')
            return False
    
    def rts_build_func(self):
        # make & make install
        if os.path.isfile(os.path.join(self.rts_build_dir, 'Makefile')):
            self.log.info('rts_make & install')
            if(self.make_func(self.rts_build_dir)):
                subprocess.Popen(["make","install"], cwd=self.rts_build_dir)
                return True
            else:
                return False            
        else:
            self.log.error('Makefile does not exist.')
            return False

    def omp_rebuild_func(self):
        # create build directory if not exists
        if not os.path.exists(self.omp_build_dir):
            try:
                self.log.info('creating omp_build dir')
                os.makedirs(self.omp_build_dir)
            except Exception as e:
                self.log.error(e)
                return False

        # cmake                
        self.log.info('cmake')
        subprocess.Popen(['cmake', '..'], cwd=self.omp_build_dir)

        # make                
        self.log.info('omp_make')
        if(self.make_func(self.omp_build_dir)):                
            return True
        else:
            self.log.error('Makefile does not exist.')
            return False
        

    def omp_build_func(self):
        # make
        self.log.info('omp_make')
        if(self.make_func(self.omp_build_dir)):                
            return True
        else:
            self.log.error('Makefile does not exist.')
            return False

    def omp_run_func(self):
        #index of exp
        index_exp = self.treeview_omp_exp_cfg.currentIndex()
        omp_exp_cfg_path = \
            self.browser_model_omp_exp_cfg.filePath(index_exp)
        # index of ts        
        index_ts = self.treeview_omp_ts_cfg.currentIndex()
        omp_ts_cfg_path = \
            self.browser_model_omp_ts_cfg.filePath(index_ts)
        
        # check select exp & ts file
        self.log.info('selected: ' + str(omp_exp_cfg_path) + str(omp_ts_cfg_path))
        if omp_exp_cfg_path == '':
            QMessageBox.information(self, 'Alarm', 'Select omp_exp_cfg!')
            return False
        elif omp_ts_cfg_path == '':
            QMessageBox.information(self, 'Alarm', 'Select omp_ts_cfg!')
            return False        
        
        # check rt
        if not self.is_rt:
            self.log.info('cannot run in non-rt')
        if os.path.isfile(os.path.join(self.omp_build_dir, self.target_name)):
            self.log.info('opening omp.')
            subprocess.Popen(['./omp',str(omp_exp_cfg_path), str(omp_ts_cfg_path)],
                cwd=self.omp_build_dir)            
            return True
        else:
            self.log.error('omp does not exist (maybe not compiled).')
            return False

    # For make
    def make_func(self,path):
        if not self.is_rt:
            self.log.info('cannot run in non-rt')
        if path == '':
            QMessageBox.information(self, 'Alarm', 'Path is empty!')
            return False
        else:
            if os.path.isfile(os.path.join(path, 'Makefile')):                
                subprocess.Popen(["make","-j8"], cwd=path)
                return True
            else:
                return False
    # For omp analyze
    def omp_analyze_func(self):

        index_log_file = self.treeview_omp_log_file.currentIndex()
        omp_log_file_path = \
            self.browser_model_omp_log_file.filePath(index_log_file)

        thr_data = []
        with open(omp_log_file_path, 'r') as f:
            lines = f.readlines()
            for line in lines:                
                if '$' not in line:
                    continue
                thr_data_raw = line.split('$')[1].split(' ')                
                thr_data.append({
                    'task_id': int(thr_data_raw[0]),
                    'iter': int(thr_data_raw[1]),
                    'exec_time': float(thr_data_raw[2]) / 10**6,
                    'period': float(thr_data_raw[3]) / 10**6,
                    'deadline': float(thr_data_raw[4]) / 10**6,
                    'start_time': float(thr_data_raw[5]) / 10**6,
                    'end_time': float(thr_data_raw[6]) / 10**6,
                    'response_time': float(thr_data_raw[7]) / 10**6,
                    'slack': float(thr_data_raw[8]) / 10**6
                })
        
        # calc mean response time
        averages = {}
        for key in thr_data[0].keys():
            tmp_sum = 0
            for td in thr_data:
                tmp_sum += td[key]
            averages[key] = tmp_sum / len(thr_data)
            ret = key + ': ' + str(averages[key])
            if 'task_id' not in key or 'iter' not in key:
                ret += ' ms'
            print(ret)

            
            


        return 
    # For graph
    def print_graph(self):
        # open file
        '''
        index_file = 2
        tmp_f1 = open_file(index_file)
        '''
        data_folder = "samples/omp/build/"
        file_to_open = data_folder + "DummyWorkload-exp2-0.out"
        tmp_f1 = open(file_to_open,"r")        

        # file to data
        x1_data, y1_data = self.file_to_data(tmp_f1)

        # print graph
        self._static_ax.bar(x1_data, y1_data)

        return
    '''
    def open_file(self, idx_file):
        data_folder = "samples/omp/build/"
        file_to_open = data_folder + "DummyWorkload-exp" + idx_file + "-0.out"
        tmp_f = open(file_to_open,"r")

        return tmp_f
    '''
    #file to data
    def file_to_data(self,tmp_file):
        thr = []
        x_data = []
        y_data = []

        # read thr & split
        while True:
            tmp = tmp_file.readline()
            line_sp = tmp.split(' ')
            dat = line_sp[7:]
            if not tmp:
                break    
            thr.append(dat)

        # thr to data
        self.log.info(thr[0][4])
        temp = float(thr[0][4])
        for i in range(len(thr)):                
            y_data.append(float(thr[i][6]))
            x_data.append(float(thr[i][4])-temp)

        return x_data, y_data

    