#pragma once

#include <QtWidgets/QMainWindow>
#include <QApplication>
#include <QColorDialog>
#include <QFileDialog>
#include <QImageWriter>
#include <QInputDialog>
#include <QMenuBar>
#include <QMessageBox>
#include <QSpinBox>
#include <QCloseEvent>
#include <QEvent>
#include <QActionGroup>

#include "snipper.h"

#include "ui_MyWhiteboard.h"

class DrawArea;

const int HISTORY_DEPTH = 20;

enum ScreenMode { smSystem, smDark, smBlack };

class MyWhiteboard : public QMainWindow
{
	Q_OBJECT

public:
	MyWhiteboard(QWidget *parent = Q_NULLPTR);

protected:
	void closeEvent(QCloseEvent* event) override;
	void showEvent(QShowEvent* event) override;

private slots:
	void on_actionNew_triggered();


	void on_actionLoad_triggered();
	void on_actionSave_triggered();
	void on_actionSaveAs_triggered();

	void on_actionLoadBackground_triggered();
	void on_actionSaveVisible_triggered();
	void SaveVisibleAsTriggered();

	void on_actionUndo_triggered();
	void on_actionRedo_triggered();
	void on_action_Black_triggered() { _SetBlackPen(); _SetCursor(DrawArea::csPen); _SetPenWidth(); };
	void on_action_Red_triggered()	 { _SetRedPen();   _SetCursor(DrawArea::csPen); _SetPenWidth(); };
	void on_action_Green_triggered() { _SetGreenPen(); _SetCursor(DrawArea::csPen); _SetPenWidth(); };
	void on_action_Blue_triggered()  { _SetBluePen();  _SetCursor(DrawArea::csPen); _SetPenWidth(); };
	void on_action_Eraser_triggered();
	void on_action_Screenshot_triggered();

	void on_actionClearCanvas_triggered();
	void on_actionClearBackgroundImage_triggered();
	void on_action_Print_triggered() { _drawArea->Print();  }
	void on_actionAbout_triggered();

	void on_actionLightMode_triggered();
	void on_actionDarkMode_triggered();
	void on_actionBlackMode_triggered();

	void on_action_Mark_triggered() {/*TODO*/ ; }

	void slotPenWidthChanged(int val);

	void SlotForUndo(bool b);
	void SlotForRedo(bool b);
	void SlotForFocus();
	void SlotForPointerType(QTabletEvent::PointerType pt);

	void SlotForScreenshotReady(QRect geometry);
	void SlotForScreenShotCancelled();

private:
	Ui::MyWhiteboardClass ui;

	bool _busy = false;
	bool _firstShown = false;	// main window was shown first

	bool	_eraserOn = false;
	int		_penWidth = 3,
			_eraserWidth = 30;
	MyPenKind _actPen = penBlack;
	QString _backgroundImageName;	// get format from extension
	QString _saveName;				// last saved data file
	QString _sImageName;			// background image
	QByteArray _fileFormat = "png";

	DrawArea * _drawArea;
	QSpinBox * _psbPenWidth = nullptr;
	QList<QAction*> _saveAsActs;
	QActionGroup* _penGroup, *_modeGroup;

	Snipper* plblScreen = nullptr;		// screen grab label

	QString _sBackgroundColor = "#FFFFFF",
			_sTextColor = "#000000";

	ScreenMode _screenMode = smSystem;

	QString _lastDir, _lastFile;

	void RestoreState();
	void SaveState();

	void _SaveLastDirectory(QString fileName);
	void _LoadData(QString fileName);

	void _CreateAndAddActions();
	void _AddSaveAsVisibleMenu();
	bool _SaveIfYouWant(bool mustAsk = false);
	bool _SaveFile();
	bool _SaveBackgroundImage();
		 
	void _SelectPenForAction(QAction* paction);

	void _SelectPen();	// for _actPen

	void _SetPenKind();

	void _SetPenKind(MyPenKind color);

	void _SetCursor(DrawArea::CursorShape cs);

	void _SetBlackPen();
	void _SetRedPen()  ;
	void _SetGreenPen();
	void _SetBluePen() ;
		 
	void _SetPenWidth();

	void _ConnectDisconnectScreenshotLabel(bool join); // toggle

	void _SetupMode(ScreenMode mode);
};
