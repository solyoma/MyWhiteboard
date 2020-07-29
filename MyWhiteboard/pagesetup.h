#pragma once
#ifndef _PAGESETUP_H
#define _PAGESETUP_H

#include <QtWidgets/QDialog>

#include "ui_pagesetup.h"

class PageSetupDialog : public QDialog
{
	Q_OBJECT
public:
	enum Flags:char { 
						pfPrintBackgroundImage = 1,			
						pfWhiteBackground 	   = 2		// or use display mode which may be dark
					};

	int resolutionIndex;		// screen resolution in resolution combobox
	int horizPixels;			// horizontal pixel count
	int screenDiagonal;			// from text in inch
	int unitFactor;				// index of units (0: inch, 1: cm, 2: mm)
	int orientation;			// 0: portrait, 1: landscape
	int flags;					// ORed bit 0: print background image, 
	QString actPrinter;


	PageSetupDialog(QWidget* parent, QString actPrinter);
	~PageSetupDialog();

	int GetScreenSize(QSize& size);
private:
	Ui::PageSetupClass ui;

	static int _h[];
	static int _w[];
	bool _busy = false;

	int _GetIndexForHorizPixels(int hp);
	int _GetScreenSize(int index, QSize& size);

private slots:
	void on_cbScreenResolution_currentIndexChanged(int i);
	void on_sbHorizPixels_valueChanged(int val);
	void on_edtScreenDiag_textChanged(QString& txt);
	void on_cbUnit_currentIndexChanged(int i);
	void on_cbOrientation_currentIndexChanged(int i);
	void on_cbPrinterSelect_currentIndexChanged(int i);
	void on_chkPrintBackgroundImage_toggled(bool b);
	void on_chkWhiteBackground_toggled(bool b);
};

#endif