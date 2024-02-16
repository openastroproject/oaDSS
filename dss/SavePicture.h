#pragma once

#include <QtCore>
#include <QWidget>

#include "DSSCommon.h"
#include "ui_SavePicture.h"

namespace DSS
{
  class SavePicture : public QWidget, public ::Ui::SavePicture
	{
		Q_OBJECT

public:
		SavePicture ( bool bOpenFileDialog, LPCTSTR lpszDefExt,
				LPCTSTR lpszFileName, LPCTSTR lpszFilter, QWidget* parent = nullptr );
		~SavePicture ( void );
		void initialise ( void );

private slots:
		void nonePressed ( void );
		void zipPressed ( void );
		void lzwPressed ( void );
		void applyPressed ( void );
		void embedPressed ( void );
		void rectangleChanged ( int state );
		void filterChanged ( const QString& newFilter );

private:
		bool						m_bApplied;
		bool						m_bEnableUseRect;
		bool						m_bUseRect;
		TIFFCOMPRESSION m_Compression;

public:
		void setApplied ( bool applied );
		bool getApplied ( void );
		void setUseRect ( bool enabled, bool use );
		bool getUseRect ( void );
		void setCompression ( TIFFCOMPRESSION compression );
		TIFFCOMPRESSION getCompression ( void );
	};
}
