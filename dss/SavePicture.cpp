#include "dss_common.h"

#include "SavePicture.h"

namespace DSS {

	SavePicture::SavePicture ( QString lpszDefExt, QString lpszFileName,
			QString lpszFilter, QWidget* parent ) : QWidget ( parent )
	{
		QFileDialog* fileDlg = new QFileDialog ( parent );
		fileDlg->setOption ( QFileDialog::DontUseNativeDialog );
		verticalLayout->addWidget ( fileDlg, Qt::AlignTop );
		
		ZFUNCTRACE_RUNTIME();

		setupUi ( this );

		m_bApplied = false;
		m_bEnableUseRect = false;
		m_bUseRect = false;
		m_Compression = TC_DEFLATE;

		connect ( noneButton, &QRadioButton::pressed, this,
				&SavePicture::nonePressed );
		connect ( zipButton, &QRadioButton::pressed, this,
				&SavePicture::zipPressed );
		connect ( lzwButton, &QRadioButton::pressed, this,
				&SavePicture::lzwPressed );
		connect ( applyButton, &QRadioButton::pressed, this,
				&SavePicture::applyPressed );
		connect ( embedButton, &QRadioButton::pressed, this,
				&SavePicture::embedPressed );
		connect ( rectangle, &QCheckBox::stateChanged, this,
				&SavePicture::rectangleChanged );
		connect ( fileDlg, &QFileDialog::filterSelected, this,
				&SavePicture::filterChanged );
	}


	SavePicture::~SavePicture ( void )
	{
		qDebug() << "stuff to go in SavePicture destructor?";
	}


	void
	SavePicture::initialise( void )
	{
		if ( m_bApplied ) {
			applyButton->setDown ( true );
			// don't think this is required -- can't have more than one down
			// embedButton->setDown ( false );
		} else {
			embedButton->setDown ( true );
			// don't think this is required -- can't have more than one down
			// applyButton->setDown ( false );
		}

		if (m_bEnableUseRect) {
			rectangle->setEnabled ( true );
			rectangle->setChecked ( true );
		} else {
			rectangle->setDisabled ( true );
		}

		// m_Embedded.GetWindowText(m_strSaveEmbed);

		noneButton->setChecked ( m_Compression == TC_NONE );
		zipButton->setChecked ( m_Compression == TC_DEFLATE );
		lzwButton->setChecked ( m_Compression == TC_LZW );

		applyButton->setToolTip ( tr ( "This option save the image a you see it\n"
				"Use it if you plan to do further processing in another software" ));

		embedButton->setToolTip ( tr ( "This option save the unprocessed image"
				"but embed the processing settings\nUse it if you plan to do all the "
				"processing in another software or if you plan to re-open the "
				"picture with DeepSkyStacker" ));
	

		//UpdateControls();
	}


	void
	SavePicture::nonePressed ( void )
	{
		m_Compression = TC_NONE;
	}


	void
	SavePicture::zipPressed ( void )
	{
		m_Compression = TC_DEFLATE;
	}


	void
	SavePicture::lzwPressed ( void )
	{
		m_Compression = TC_LZW;
	}

	void
	SavePicture::applyPressed ( void )
	{
		m_bApplied = true;
	}

	void
	SavePicture::embedPressed ( void )
	{
		m_bApplied = false;
	}


	void
	SavePicture::rectangleChanged ( int state )
	{
		m_bUseRect = state ? true : false;
	}

	void
	SavePicture::filterChanged ( const QString& newFilter )
	{
		//UpdateControls();
	}


	void
	SavePicture::setApplied ( bool applied )
	{
		m_bApplied = applied;
	}


	bool
	SavePicture::getApplied ( void )
	{
		return m_bApplied;
	}


	void
	SavePicture::setUseRect ( bool enable, bool use )
	{
		m_bEnableUseRect = enable;
		m_bUseRect = use;
	}


	bool
	SavePicture::getUseRect ( void )
	{
		return m_bUseRect;
	}


	void
	SavePicture::setCompression ( TIFFCOMPRESSION compression )
	{
		m_Compression = compression;
	}


	TIFFCOMPRESSION
	SavePicture::getCompression ( void )
	{
		return m_Compression;
	}
}

#if (0)


/* ------------------------------------------------------------------- */

void CSavePicture::UpdateControls()
{
	if (m_ofn.nFilterIndex>3)
	{
		m_Compression = TC_NONE;
		m_CompressionNone.SetCheck(true);
		m_CompressionLZW.SetCheck(false);
		m_CompressionZIP.SetCheck(false);
		m_CompressionLZW.EnableWindow(false);
		m_CompressionZIP.EnableWindow(false);
		CString			strText;

		strText.LoadString(IDS_SAVENOADJUSTMENT);
		m_Embedded.SetWindowText(strText);
	}
	else
	{
		m_CompressionLZW.EnableWindow(true);
		m_CompressionZIP.EnableWindow(true);
		m_Embedded.SetWindowText(m_strSaveEmbed);
	};
};
#endif
