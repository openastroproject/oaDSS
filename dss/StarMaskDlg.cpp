#include "dss_common.h"

#include "StarMaskDlg.h"
#include "DSSCommon.h"

namespace DSS {

	StarMaskDlg::StarMaskDlg ( QWidget* parent )
		: QDialog ( parent )
	{
		QSettings	settings;
	
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

		m_bOutputFITS = false;
		m_strOutputFile = "";

		m_filenameFilter = QCoreApplication::translate("DeepSkyStacker","TIFF Image (*.tiff *.tif);;FITS Image (*.fits *.fts *.fit)","IDS_FILTER_MASK");
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
		if ( askOutputFile())
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

	bool
	StarMaskDlg::askOutputFile ( void )
	{
		bool						bResult = false;
		QSettings				settings;
	
		auto dwFileType = settings.value("StarMask/FileType", 0).toUInt();
	
		fs::path initialDir = m_strOutputFile;
		if ( dwFileType == 2 )
			initialDir.replace_filename ( "StarMask.fits" );
		else
			initialDir.replace_filename ( "StarMask.tif" );

		QString	filename = QFileDialog::getSaveFileName ( this,
				tr ( "Save the StarMask as ..."), initialDir.c_str(),
				m_filenameFilter );

		if ( filename != "" ) {
			/*
			 * This is a bit of a cack-handed way to work out whether the format
			 * will be FITS or not, but there doesn't seem to be a neat way to
			 * manage it in Qt.  Not using a dialog through the static functions
			 * would allow fetching the filter selected, but it would still come
			 * down to a string comparison.  The index of the filter doesn't seem
			 * to be avaiable.  So do it the most compact way.
			 */
			m_strOutputFile = filename.toStdString();
			fs::path extn = m_strOutputFile.extension();
			if ( extn == "fits" || extn == "fts"|| extn == "fit" ) {
				m_bOutputFITS = true;
				bResult = true;
			} else {
				if ( extn == "tif" || extn == "tiff" ) {
					m_bOutputFITS = false;
					bResult = true;
				} else {
					qDebug() << "file extension not recognised: " << extn.c_str();
					bResult = false;
				}
			}
		}
	
		return bResult;
	}


	void
	StarMaskDlg::setBaseFilename ( LPCTSTR szOutputFile )
	{
    m_strOutputFile = szOutputFile;
		m_strOutputFile.replace_filename ( "StarMask" );
	};


	void
	StarMaskDlg::getOutputFileName( QString& strOutputFile, bool& bFits )
	{
		strOutputFile = m_strOutputFile.c_str();
		bFits = m_bOutputFITS;
	};

}
