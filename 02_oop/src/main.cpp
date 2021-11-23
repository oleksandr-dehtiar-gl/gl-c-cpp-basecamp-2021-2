#include <QtWidgets>
#include <QTextStream>
#include <QStyle>
#include <QTextStream>
#include <QMediaMetaData>
#include <QAudioDecoder>

#include <iostream>
#include <fstream>

#include "filesysapi/fileSysApi.hpp"
#include "id3reader.hpp"

#include "player/playlist/playlistgui.hpp"

std::ofstream fout("metadatalist.txt");
mediaplayer::ID3v1Reader id3;

int main(int argc, char** argv) {

	/*// Test table show list
	QWidget window;
	
	QLabel *queryLabel = new QLabel(QApplication::translate("nestedLayout", "Query:"));
	QLineEdit *queryEdit = new QLineEdit();
	QTableView *resultView = new QTableView();
	
	QStandardItemModel model;
	model.setHorizontalHeaderLabels(
		QStringList() << QApplication::translate("nestedLayout", "Name")
					<< QApplication::translate("nestedLayout", "Office"));
	
	QList<QStringList> rows = QList<QStringList>()
		<< (QStringList() << "Verne Nilsen" << "123")
		<< (QStringList() << "Carlos Tang" << "77")
		<< (QStringList() << "Bronwyn Hawcroft" << "119")
		<< (QStringList() << "Alessandre Hanssen" << "32")
		<< (QStringList() << "Andrew John Bakken" << "54")
		<< (QStringList() << "Vanessa Weatherley" << "85")
		<< (QStringList() << "Rebecca Dickens" << "17")
		<< (QStringList() << "David Bradley" << "42")
		<< (QStringList() << "Knut Walters" << "34")
		<< (QStringList() << "Andrea Jones" << "25");
	
	foreach(QStringList row, rows) {
		QList<QStandardItem*> items;
		foreach(QString text, row) {
			items.append(new QStandardItem(text));
		}
		model.appendRow(items);
	}
	
	resultView->setModel(&model);
	resultView->verticalHeader()->hide();
	resultView->horizontalHeader()->setStretchLastSection(true);
	
	QHBoxLayout *queryLayout = new QHBoxLayout();
	queryLayout->addWidget(queryLabel);
	queryLayout->addWidget(queryEdit);
	
	QVBoxLayout *mainLayout = new QVBoxLayout();
	mainLayout->addLayout(queryLayout);
	mainLayout->addWidget(resultView);
	window.setLayout(mainLayout);
	
	window.setWindowTitle(QApplication::translate("nestedLayout", "Nested Layout"));
	
	
	
	window.show();
	*/
	/*// Test Standart ModelQStandardItemModel
	QStandardItemModel model(5, 3);
	
	for (int nTop = 0; nTop < 5; ++nTop) {
		QModelIndex index = model.index(nTop, 0);
		model.setData(index, "item man " + QString::number(nTop + 1));
		
		model.insertRows(0, 4, index);
		model.insertColumns(0, 3, index);
		for (int nRow = 0; nRow < 4; ++nRow) {
			for (int nCol = 0; nCol < 3; ++nCol) {
				QString strPos = QString("%1,%2").arg(nRow).arg(nCol);
				model.setData(model.index(nRow, nCol, index), strPos);
			}
		}
	}
	
	QTreeView treeView;
	treeView.setModel(&model);
	treeView.show();
	*/
	/*// Test FileSystem model
	
	QSplitter spl(Qt::Horizontal);
	QFileSystemModel model;
	
	model.setRootPath(QDir::rootPath());
	
	QTreeView *pTreeView = new QTreeView;
	pTreeView->setModel(&model);
	
	QTableView *pTableView = new QTableView;
	pTableView->setModel(&model);
	
	// Siganl/Slot connection
	QObject::connect(pTreeView, SIGNAL(clicked(const QModelIndex&)),
					pTableView, SLOT(setRootIndex(const QModelIndex&))
					);
	QObject::connect(pTableView, SIGNAL(activated(const QModelIndex&)),
					pTreeView, SLOT(setCurrentIndex(const QModelIndex&))
					);
	// QObject::connect(pTableView, SIGNAL(activated(const QModelIndex&)),
					// pTreeView, SLOT(setRootIndex(const QModelIndex&))
					// );
	
	spl.addWidget(pTreeView);
	spl.addWidget(pTableView);
	spl.show();
	*/	
	/*// Test custom model intList
	IntListModel model(QList<int>() << 123 << 2341 << 32 << 5342 << 723);
	
	QListView list;
	list.setModel(&model);
	list.show();
	
	QTableView table;
	table.setModel(&model);
	table.show();
	*/
	/*// Test select file from fileTree
	QTextStream out(stdout);
	out << QFileDialog::getExistingDirectory(0, "Directory Dialog", "");
	*/
	/*// Test file system 
	std::list<std::string> flist;
	filesysapi::getFileList(flist, ".");
	std::ofstream fout("listfile.txt");
	for (auto &a : flist)
		fout << filesysapi::getPathnamePart(filesysapi::getAbsolutePath(a)) << " ==> " 
				<< filesysapi::getFilenamePart(a) << " ==> " 
				<< filesysapi::getFileExtension(filesysapi::getFilenamePart(a)) << std::endl;
	*/
	/*// Write all mp3 files in file 
	mediaplayer::ID3v1Reader id3;
	std::ofstream fout("metadatalist.txt");
	std::list<std::string> filelist;

	filesysapi::getFileList(filelist, "e:");
	for (auto &filename : filelist) {
		if (id3.setnewfile(filename)) {
			fout << filename << std::endl;
			fout << "- title: " << id3.getTitle()
				 << "\n- genre: " << id3.getGenre() 
				 << "\n- year : " << id3.getYear() << "\n";
		}
	}*/
	
	QApplication app(argc, argv);
	
	mediaplayer::PlaylistGui pl;
	pl.show();
	
	return app.exec();
}
