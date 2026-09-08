import PyQt6.QtWidgets as pqw
from PyQt6.QtWidgets import *
from PyQt6.QtCore import Qt
# import PyQt6.QtGui as pqG
 
import sys

# import pandas as pd

from Processing import FileProcessor, DriverPeriod
from Plotting import TableModel, Figure, MplCanvas
from DriverPeriod import DriverPeriod

class MainWindow(QMainWindow):

    # period_checkboxes:list[QCheckBox] = []
    # period_open_buttons:list[QPushButton] = []
    # period_data_layouts:list[QWidget] = []

    # windows = []
    # plots: list[MplCanvas] = []
    
    file_processor:FileProcessor = None

    def __init__(self, app:QApplication):
        super().__init__()

        """----------------Init----------------"""
        self.setWindowTitle("Data Analyzer")

        # Set Window size
        wSize = app.primaryScreen().size()
        self.setGeometry(wSize.width()*1//6, wSize.height()*1//6, wSize.width()*2//3, wSize.height()*2//3)
        self.setMinimumSize(100,100)

        self.initGUI()

    def initGUI(self):
        """----------------Create Layouts----------------"""
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
        self.gridLayout = QGridLayout()
        self.gridWidget = QWidget()
        self.gridWidget.setLayout(self.gridLayout)
        self.scrollArea.setWidget(self.gridWidget)

        # Set Scroll Area Properties
        self.scrollArea.setVerticalScrollBarPolicy(Qt.ScrollBarPolicy.ScrollBarAlwaysOn)
        self.scrollArea.setHorizontalScrollBarPolicy(Qt.ScrollBarPolicy.ScrollBarAlwaysOff)
        self.scrollArea.setWidgetResizable(True)
        
        # Mash Layouts Into Right Places
        self.superLayout.addWidget(self.controlBarWidget)
        self.superLayout.addWidget(self.scrollArea)
        
        self.setCentralWidget(self.superWidget)


        """----------------Add Controls----------------"""
        # File Selection
        self.fileDialog = QFileDialog(self)
        self.fileDialog.setAcceptMode(self.fileDialog.AcceptMode.AcceptOpen)
        self.fileDialog.setFileMode(self.fileDialog.FileMode.ExistingFile)
        self.fileDialog.setNameFilter("Sheets (*.csv *.xlsx)")
        self.fileDialog.accepted.connect(self.file_selected)

        self.select_file_button = QPushButton("Open File Selector", self)
        self.select_file_button.clicked.connect(self.fileDialog.exec)

        self.controlBarLayout.addWidget(self.select_file_button)
        self.select_file_button.updateGeometry()

        # Enable non-drives
        self.show_empty_drives_box = QCheckBox(self)
        self.show_empty_drives_box.setChecked(False)
        self.show_empty_drives_box.checkStateChanged.connect(self.refreshHiddenPeriods)
        self.show_empty_drives_box.setText("Show Empty Periods")

        self.controlBarLayout.addWidget(self.show_empty_drives_box)

    def refreshHiddenPeriods(self):
        # for i in range(len(self.period_open_buttons)):
        #     if self.file_processor.periods[i].is_real_drive() or self.show_empty_drives_box.isChecked():
        #         self.period_open_buttons[i].show()
        #         self.period_data_layouts[i].show()
        #     else:
        #         self.period_open_buttons[i].hide()
        #         self.period_data_layouts[i].hide()
        for period in self.file_processor.periods:
            if period.is_real_drive() or self.show_empty_drives_box.isChecked():
                period.showGui()
            else:
                period.hideGui()

    def file_selected(self):
        # print(self.fileDialog.selectedFiles())
        # file = self.fileDialog.selectedFiles()[0]
        file = "C:\\Users\\bmcca\\GitHub\\coding_badly\\FreshmanClubs\\Baja\\BAJA_DAQ_8_23_26.csv"
        self.file_processor = FileProcessor(file)

        self.file_processor.run_data()

        self.populate_period_data()

        # self.file_processor.data.plot(x = 'Time', y='Speed')
        
        # plt.show()

    def populate_period_data(self):
        for i, period in enumerate(self.file_processor.periods):
            # Have DriverPeriod generate and store gui elements
            period.genDisplayElements(self.gridLayout, i)

            ## Assign period's gui elements to layout
            # # Create Checkbox
            # self.gridLayout.addWidget(period.checkbox, i+1, 0)

            # # Button 
            # self.gridLayout.addWidget(period.button, i+1, 1)

            # # Labels
            # self.gridLayout.addWidget(period.labelsWidget, i+1, 3)

            # # Create Plot
            # self.gridLayout.addWidget(period.plot, i+1, 2)

        # Hide if should be hidden
        self.refreshHiddenPeriods()

        # Add Additional Controls
        self.combine_periods_button = QPushButton("Combine Selected Periods")
        self.combine_periods_button.clicked.connect(self.aggregateSelectedPeriods)
        self.controlBarLayout.addWidget(self.combine_periods_button)

    def aggregateSelectedPeriods(self):
        # Create Period
        newPeriod = DriverPeriod(names=self.file_processor.names)
        names = []
        frames = []
        for period in self.file_processor.periods:
            if period.isSelected():
                frames.append(period.data)
                names.append(period.getName())

        newPeriod.aggregate_from_frames(frames)
        # print("---new: \n", newPeriod.data)

        self.file_processor.periods.append(newPeriod)
        print('GENRATING DISP')
        self.file_processor.periods[-1].genDisplayElements(self.gridLayout, self.file_processor.periods.__len__()+1)
        newPeriod.setName("'" + "' + '".join(names) + "'")

        self.refreshHiddenPeriods()

if __name__ == "__main__":
    app = QApplication(sys.argv)

    window = MainWindow(app)
    window.show()

    #debug rigging
    window.fileDialog.accepted.emit()
    # window.fileDialog.selectedFiles().append("C:\\Users\\bmcca\\GitHub\\coding_badly\\FreshmanClubs\\Baja\\BAJA_DAQ_8_23_26.csv")
    # window.fileDialog.selectFile("C:\\Users\\bmcca\\GitHub\\coding_badly\\FreshmanClubs\\Baja\\BAJA_DAQ_8_23_26.csv")
    # window.file_selected()

    app.exec()