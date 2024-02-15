#pragma once

#include <QtCore>
#include <QDialog>

#include "commonresource.h"
#include "ui_StarMaskDlg.h"


namespace DSS
{
	class StarMaskDlg : public QDialog, public ::Ui::StarMaskDlg
	{
		Q_OBJECT

public:
		StarMaskDlg ( QWidget* pParent = nullptr );
		~StarMaskDlg ( void ) {};
		void initialise ( void );
		void setBaseFilename ( LPCTSTR szOutputFile );
		void getOutputFileName( QString& strOutputFile, bool& bFits );

private:
		void updateTexts ( void );
		bool askOutputFile ( void );

private slots:
		void updateStarShapePreview (int index );
		void thresholdUpdated ( int newVal );
		void minUpdated ( int newVal );
		void maxUpdated ( int newVal );
		void percentUpdated ( int newVal );
		void pixUpdated ( int newVal );
		void ok ( void );
		void cancel ( void );

private:
		bool m_bOutputFITS;
		fs::path	m_strOutputFile;
		QString	m_filenameFilter;
	};
}
