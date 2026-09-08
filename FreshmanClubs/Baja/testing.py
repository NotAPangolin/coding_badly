import PyQt6.QtWidgets as pqw
from PyQt6.QtWidgets import *
from PyQt6.QtGui import QPalette, QColor
from PyQt6.QtCore import Qt

import sys

class Color(QWidget):
    def __init__(self, color):
        super().__init__()
        self.setAutoFillBackground(True)

        palette = self.palette()
        palette.setColor(QPalette.ColorRole.Window, QColor(color))
        self.setPalette(palette)

class MainWindow(QMainWindow):

    period_open_buttons:list[QPushButton] = []

    windows = []
    plots: list = []
    
    def __init__(self, app:QApplication):
        super().__init__()

        """----------------Init----------------"""
        self.setWindowTitle("TESTING - Data Analyzer")
        self.setGeometry(600, 100, 1000, 900)

        """----------------Standard Bar & Grid Scheme----------------"""
        # ### Create Top level Layout
        # self.verticalLayout = QVBoxLayout()

        # ### Create Control Bar Layout
        # self.controlBarLayout = QHBoxLayout()
        # self.verticalLayout.addLayout(self.controlBarLayout)
        # # Assign items to control bar
        # self.controlBarLayout.addWidget(Color("green"))
        # self.controlBarLayout.addWidget(Color("gold"))

        # ### Create Grid Layout
        # self.gridLayout = QGridLayout()
        # self.verticalLayout.addLayout(self.gridLayout)

        # ## Create Grid Items
        # boxes = [(Color("blue" if ((((i % 2) == 0) or ((i//2)%2 == 0)) and (((i % 2) == 0) or ((i//2)%2 == 0))) else "gray"), i//2, i%2) for i in range(10)]
        # for box, x, y in boxes:
        #     box.setMinimumHeight(20)
        #     self.gridLayout.addWidget(box, x, y)

        # self.mainWidget = QWidget()
        # self.mainWidget.setLayout(self.verticalLayout)
        # self.setCentralWidget(self.mainWidget)

        """----------------Plain Scroll Area----------------"""
        # Create Super Layout
        self.superLayout = QVBoxLayout()
        self.superWidget = QWidget()
        self.superWidget.setLayout(self.superLayout)

        # Crate Control Bar
        self.controlBarLayout = QHBoxLayout()
        self.controlBarWidget = QWidget()
        self.controlBarWidget.setLayout(self.controlBarLayout)

        # Create Scroll/Grid Area
        self.scrollArea = QScrollArea()
        self.gridLayouy = QGridLayout()
        self.gridWidget = QWidget()
        self.gridWidget.setLayout(self.gridLayouy)
        self.scrollArea.setWidget(self.gridWidget)

        # Set Scroll Area Properties
        self.scrollArea.setVerticalScrollBarPolicy(Qt.ScrollBarPolicy.ScrollBarAlwaysOn)
        self.scrollArea.setHorizontalScrollBarPolicy(Qt.ScrollBarPolicy.ScrollBarAlwaysOff)
        self.scrollArea.setWidgetResizable(True)
        
        # Add Controls
        self.controlBarLayout.addWidget(QLabel("ougtwsghtiurogbrte"))
        self.controlBarLayout.addWidget(QPushButton("ougtwsghtiurogbrte"))
        
        # Mash Layouts Into Right Places
        self.superLayout.addWidget(self.controlBarWidget)
        self.superLayout.addWidget(self.scrollArea)
        
        self.setCentralWidget(self.superWidget)

        









        # self.mainLayout = QVBoxLayout(self)
        # self.mainLayoutWidget = QWidget(self)
        # self.setCentralWidget(self.mainLayoutWidget)

        # """----------------Controls Bar----------------"""
        # self.controls_layout = QHBoxLayout(self)
        # # self.controlsLayoutWidget = QWidget(self)
        # # self.controlsLayoutWidget.setLayout(self.controls_layout)
        # # self.controlsLayoutWidget.setStyleSheet("background-color: rgb(150,150,150)")
        

        # # File Selection
        # self.fileDialog = QFileDialog(self)
        # self.fileDialog.setAcceptMode(self.fileDialog.AcceptMode.AcceptOpen)
        # self.fileDialog.setFileMode(self.fileDialog.FileMode.ExistingFile)
        # self.fileDialog.setNameFilter("Sheets (*.csv *.xlsx)")
        # self.fileDialog.accepted.connect(self.file_selected)

        # self.select_file_button = QPushButton("Open File Selector", self)
        # self.select_file_button.clicked.connect(self.fileDialog.exec)

        # self.controls_layout.addWidget(self.select_file_button)
        # self.select_file_button.updateGeometry()

        # # Enable non-drives
        # self.real_drives_checkbox = QCheckBox(self)
        # # self.real_drives_checkbox.checkStateChanged.connect(self.changeShowRealDrives)

        # self.controls_layout.addWidget(self.real_drives_checkbox)
        # """----------------Grid/Data----------------"""
        # self.grid_layout = QGridLayout(self)
        # self.gridLayoutWidget = QWidget()
        # self.gridLayoutWidget.setLayout(self.grid_layout)

        # self.scrollArea = QScrollArea()
        # self.scrollArea.setMinimumSize(350, 300)
        # self.scrollArea.setWidgetResizable(True)
        # self.scrollArea.setWidget(self.gridLayoutWidget)
        # # self.gridLayoutWidget.setStyleSheet("background-color: aliceblue")

        # # self.setCentralWidget(scrollArea)
        # self.mainLayout.addLayout(self.controls_layout)
        # # self.mainLayout.addLayout(self.grid_layout)
        # self.mainLayout.addWidget(self.scrollArea)

    # def changeShowRealDrives(self):
    #     for button in self.period_open_buttons:
    #         should_show = ("True" in button.text()) or self.real_drives_checkbox.isChecked()
    #         if should_show:
    #             button.show()
    #         else:
    #             button.hide()

    def file_selected(self):
        # print(self.fileDialog.selectedFiles())
        file = "C:\\Users\\bmcca\\GitHub\\coding_badly\\FreshmanClubs\\Baja\\BAJA_DAQ_8_23_26.csv"
        self.file_processor = FileProcessor(file)#self.fileDialog.selectedFiles()[0])

        self.file_processor.run_data()

        self.populate_show_buttons()

        # self.file_processor.data.plot(x = 'Time', y='Speed')
        
        # plt.show()

    def populate_show_buttons(self):
        for i, period in enumerate(self.file_processor.periods):
            # Create & Style button
            self.period_open_buttons.append(QPushButton(f"open period {i+1}, is drive: {period.is_real_drive()}", self))
            self.period_open_buttons[-1].setStyleSheet("background-color: rgb(94, 196, 218)" if period.is_real_drive() else "background-color: gray")
            self.period_open_buttons[-1].pressed.connect(period.open_data_plot_win)
            # Assign Button to Layout 
            self.grid_layout.addWidget(self.period_open_buttons[-1], i+1, 0)

            # Create Plot
            if period.is_real_drive():
                self.plots.append(MplCanvas(self))
                self.plots[-1].plot_df(period.data)
                self.period_open_buttons[-1].setMinimumHeight(50)

                self.grid_layout.addWidget(self.plots[-1], i+1, 1)


if __name__ == "__main__":
    app = QApplication(sys.argv)

    window = MainWindow(app)
    window.show()

    #debug rigging
    # window.fileDialog.selectedFiles().append("C:\\Users\\bmcca\\GitHub\\coding_badly\\FreshmanClubs\\Baja\\BAJA_DAQ_8_23_26.csv")
    # window.fileDialog.selectFile("C:\\Users\\bmcca\\GitHub\\coding_badly\\FreshmanClubs\\Baja\\BAJA_DAQ_8_23_26.csv")
    # window.fileDialog.accepted.emit()
    # window.file_selected()

    app.exec()