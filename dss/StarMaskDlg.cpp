#include "dss_common.h"

#include "StarMaskDlg.h"
#include "DSSCommon.h"


extern QString STARMASKFILE_FILTERS;

namespace DSS {

	class SaveMaskDlg : public QFileDialog
	{
#if 0
		public:
	SaveMaskDlg ( bool bOpenFileDialog, // true == open, false == save as
		LPCTSTR lpszDefExt = nullptr,
		LPCTSTR lpszFileName = nullptr,
		std::uint32_t dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		LPCTSTR lpszFilter = nullptr,
		QWidget* pParentWnd = nullptr ) : QFileDialog ( bOpenFileDialog, lpszDefExt, lpszFileName, dwFlags, lpszFilter, pParentWnd)
#endif

	};

	StarMaskDlg::StarMaskDlg ( QWidget* parent )
		: QDialog ( parent )
	{
		QSettings	settings;
	
		/*
    QLabel *label;
    QComboBox *starShape;
    QLabel *shapeImage;
    QCheckBox *hotPixels;
    QSlider *thresholdSlider;
    QSlider *minSlider;
    QSlider *maxSlider;
    QLabel *thresholdLabel;
    QLabel *minLabel;
    QLabel *maxLabel;
    QSlider *pcSlider;
    QSlider *pixSlider;
    QLabel *pcLabel;
    QLabel *pixLabel;
		QDialogButtonBox *buttonBox;
		*/

		ZFUNCTRACE_RUNTIME();

    setupUi ( this );

		thresholdSlider->setMinimum ( 2 );
		thresholdSlider->setMaximum ( 100 );
		minSlider->setMinimum ( 2 );
		minSlider->setMaximum ( 10 );
		maxSlider->setMinimum ( 10 );
		maxSlider->setMaximum ( 2 * STARMAXSIZE );
		pcSlider->setMinimum ( 10 );
		pcSlider->setMaximum ( 200 );
		pixSlider->setMinimum ( 0 );
		pixSlider->setMaximum ( 10 );

		// The compiler can't find a matching function if I just use pointers
		// rather than SLOT/SIGNAL for this first one.  No idea why atm
		connect ( starShape, SIGNAL( currentIndexChanged ( int )), this,
				SLOT( updateStarShapePreview ( int )));
		connect ( thresholdSlider, &QSlider::sliderMoved, this,
				&StarMaskDlg::thresholdUpdated );
		connect ( minSlider, &QSlider::sliderMoved, this,
				&StarMaskDlg::minUpdated );
		connect ( maxSlider, &QSlider::sliderMoved, this,
				&StarMaskDlg::maxUpdated );
		connect ( pcSlider, &QSlider::sliderMoved, this,
				&StarMaskDlg::percentUpdated );
		connect ( pixSlider, &QSlider::sliderMoved, this,
				&StarMaskDlg::pixUpdated );
		connect ( buttonBox, &QDialogButtonBox::accepted, this,
				&StarMaskDlg::ok );
		connect ( buttonBox, &QDialogButtonBox::rejected, this,
				&StarMaskDlg::cancel );
	}


	void
	StarMaskDlg::initialise ( void )
	{
		QSettings		settings;

		const auto dwStarShape = settings.value("StarMask/StarShape", 0).toUInt();
		starShape->setCurrentIndex ( dwStarShape );

		bool bHotPixels = settings.value("StarMask/DetectHotPixels", false).toBool();
		hotPixels->setChecked ( bHotPixels );

		const auto dwThreshold = settings.value("StarMask/DetectionThreshold", 10).toUInt();
		thresholdSlider->setSliderPosition ( dwThreshold );

		const auto dwPercent = settings.value("StarMask/PercentRadius", 100).toUInt();
		pcSlider->setSliderPosition ( dwPercent );

		const auto dwPixel = settings.value("StarMask/PixelIncrease", 0).toUInt();
		pixSlider->setSliderPosition ( dwPixel );

		const auto dwMinSize = settings.value("StarMask/MinSize", 2).toUInt();
		minSlider->setSliderPosition ( dwMinSize );

		const auto dwMaxSize = settings.value("StarMask/MaxSize", 25).toUInt();
		maxSlider->setSliderPosition ( dwMaxSize );

		updateTexts();
		updateStarShapePreview ( dwStarShape );

#if QT_VERSION >= 0x00060500
    Qt::ColorScheme colorScheme { QGuiApplication::styleHints()->colorScheme() };
#endif
	}


	void
	StarMaskDlg::updateTexts()
	{
		int						lPos;
		QString				strText;

		lPos = thresholdSlider->sliderPosition();
		thresholdUpdated ( lPos );
		lPos = minSlider->sliderPosition();
		minUpdated ( lPos );
		lPos = maxSlider->sliderPosition();
		maxUpdated ( lPos );
		lPos = pcSlider->sliderPosition();
		percentUpdated ( lPos );
		lPos = pixSlider->sliderPosition();
		pixUpdated ( lPos );
	};

	void
	StarMaskDlg::updateStarShapePreview ( int index )
	{
		const QString maskImages[] = {
			"StarShape_Bell.png",
			"StarShape_TruncatedBell.png",
			"StarShape_Cone.png",
			"StarShape_TruncatedCone.png",
			"StarShape_Cubic.png",
			"StarShape_Quadratic.png",
		};
		
		if ( index >= 0 && index < ( sizeof ( maskImages ) /
					sizeof ( maskImages[0] ))) {
			shapeImage->setPixmap ( QPixmap ( ":/starmask/" + maskImages [ index ] ));
		}
	}

	void
	StarMaskDlg::thresholdUpdated ( int newVal )
	{
		thresholdLabel->setText ( QString ( tr ( "%1%" )).arg ( newVal ));
	}

	void
	StarMaskDlg::minUpdated ( int newVal )
	{
		minLabel->setText ( QString ( tr ( "%1 pixels" )).arg ( newVal ));
	}

	void
	StarMaskDlg::maxUpdated ( int newVal )
	{
		maxLabel->setText ( QString ( tr ( "%1 pixels" )).arg ( newVal ));
	}

	void
	StarMaskDlg::percentUpdated ( int newVal )
	{
		pcLabel->setText ( QString ( tr ( "%1%" )).arg ( newVal ));
	}

	void
	StarMaskDlg::pixUpdated ( int newVal )
	{
		pixLabel->setText ( QString ( tr ( "%1 pixel(s)" )).arg ( newVal ));
	}

	void
	StarMaskDlg::ok ( void )
	{
		//if (AskOutputFile())
		{
			QSettings			settings;
			int						saveVal;

			saveVal = starShape->currentIndex();
			settings.setValue ( "StarMask/StarShape", static_cast<uint>( saveVal ));
			saveVal = hotPixels->isChecked() ? 1 : 0;
			settings.setValue( "StarMask/DetectHotPixels",
					static_cast<uint>( saveVal ));
			saveVal = thresholdSlider->sliderPosition();
			settings.setValue ( "StarMask/DetectionThreshold",
					static_cast<uint>( saveVal ));
			saveVal = minSlider->sliderPosition();
			settings.setValue ( "StarMask/MinSize", static_cast<uint>( saveVal ));
			saveVal = maxSlider->sliderPosition();
			settings.setValue ( "StarMask/MaxSize", static_cast<uint>( saveVal ));
			saveVal = pcSlider->sliderPosition();
			settings.setValue ( "StarMask/PercentRadius",
					static_cast<uint>( saveVal ));
			saveVal = pixSlider->sliderPosition();
			settings.setValue ( "StarMask/PixelIncrease",
					static_cast<uint>( saveVal ));
		}
		done ( QDialog::Accepted );
	}

	void
	StarMaskDlg::cancel ( void )
	{
		done ( QDialog::Rejected );
	}

}


#if (0)
// CStarMaskDlg dialog
/* ------------------------------------------------------------------- */

class CSaveMaskDlg : public CFileDialog
{
	DECLARE_DYNAMIC(CSaveMaskDlg)

public :
	CSaveMaskDlg(bool bOpenFileDialog, // true for FileOpen, false for FileSaveAs
		LPCTSTR lpszDefExt = nullptr,
		LPCTSTR lpszFileName = nullptr,
		std::uint32_t dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		LPCTSTR lpszFilter = nullptr,
		CWnd* pParentWnd = nullptr):CFileDialog(bOpenFileDialog, lpszDefExt, lpszFileName, dwFlags, lpszFilter, pParentWnd)
	{
	};

	virtual ~CSaveMaskDlg() {};

//protected:
//	virtual void OnTypeChange()
//	{
//		CFileDialog::OnTypeChange();
//		CString			strFileName = GetFileTitle();
//
//		if (strFileName.GetLength())
//		{
//			if (m_ofn.nFilterIndex == 1)
//				strFileName += ".tif";
//			else
//				strFileName += ".fits";
//			SetControlText(FILE_DIALOG_NAME, strFileName);
//		};
//	};
};

/* ------------------------------------------------------------------- */

CStarMaskDlg::CStarMaskDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(CStarMaskDlg::IDD, pParent)
{
	m_bOutputFITS = false;
}

/* ------------------------------------------------------------------- */

CStarMaskDlg::~CStarMaskDlg()
{
}

/* ------------------------------------------------------------------- */


bool CStarMaskDlg::AskOutputFile()
{
	bool					bResult = false;
	CString					strTitle;
	QSettings				settings;

	auto dwFileType = settings.value("StarMask/FileType", 0).toUInt();

	strTitle.LoadString(IDS_TITLE_MASK);

	CSaveMaskDlg			dlgSave(false,
								nullptr,
								nullptr,
								OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_ENABLESIZING,
								STARMASKFILE_FILTERS,
								this);

	// Get Base directory from base output file
	CString					strBaseDirectory;
	TCHAR					szDrive[1+_MAX_DRIVE];
	TCHAR					szDir[1+_MAX_DIR];

	_tsplitpath(m_strOutputFile, szDrive, szDir, nullptr, nullptr);
	strBaseDirectory = szDrive;
	strBaseDirectory += szDir;

	if (strBaseDirectory.GetLength())
		dlgSave.m_ofn.lpstrInitialDir = strBaseDirectory.GetBuffer(_MAX_PATH);

	TCHAR				szBigBuffer[20000];

	if (dwFileType==2)
		lstrcpy(szBigBuffer, _T("StarMask.fits"));
	else
		lstrcpy(szBigBuffer, _T("StarMask.tif"));

	dlgSave.GetOFN().lpstrFile = szBigBuffer;
	dlgSave.GetOFN().nMaxFile  = sizeof(szBigBuffer) / sizeof(szBigBuffer[0]);
	dlgSave.GetOFN().lpstrTitle = strTitle.GetBuffer(200);
	dlgSave.GetOFN().nFilterIndex = dwFileType;

	if (dlgSave.DoModal() == IDOK)
	{
		POSITION		pos;

		pos = dlgSave.GetStartPosition();
		if (pos)
		{
			m_strOutputFile = dlgSave.GetNextPathName(pos);

			dwFileType = dlgSave.GetOFN().nFilterIndex;
			settings.setValue("StarMask/FileType", (uint)dwFileType);
			bResult = true;
			m_bOutputFITS = (dwFileType == 2);
		};
	};

	return bResult;
};

/* ------------------------------------------------------------------- */


#endif
