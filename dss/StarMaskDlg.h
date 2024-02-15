#pragma once

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

private:
		void updateTexts ( void );

private slots:
		void updateStarShapePreview (int index );
		void thresholdUpdated ( int newVal );
		void minUpdated ( int newVal );
		void maxUpdated ( int newVal );
		void percentUpdated ( int newVal );
		void pixUpdated ( int newVal );
		void ok ( void );
		void cancel ( void );
	};
}

#if (0)
	virtual ~CStarMaskDlg();

	void	SetBaseFileName(LPCTSTR szOutputFile)
	{
		TCHAR				szDrive[1+_MAX_DRIVE];
		TCHAR				szDir[1+_MAX_DIR];

		_tsplitpath(szOutputFile, szDrive, szDir, nullptr, nullptr);

		m_strOutputFile = szDrive;
		m_strOutputFile += szDir;
		m_strOutputFile += "StarMask";
	};

	void	GetOutputFileName(CString & strOutputFile, bool & bFits)
	{
		strOutputFile = m_strOutputFile;
		bFits		  = m_bOutputFITS;
	};

// Dialog Data
	enum { IDD = IDD_STARMASK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnStarShapeChange( );

	virtual BOOL OnInitDialog();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()
private :
	void	UpdateTexts();
	void	UpdateStarShapePreview();
	bool	AskOutputFile();

private :
	CString					m_strOutputFile;
	bool					m_bOutputFITS;
	CString					m_StarThresholdMask;
	CString					m_MinSizeMask;
	CString					m_MaxSizeMask;
	CString					m_PercentMask;
	CString					m_PixelsMask;

	CComboBox				m_StarShape;
	CStatic					m_StarShapePreview;
	CStatic					m_StarThresholdText;
	CSliderCtrl				m_StarThreshold;
	CButton					m_HotPixels;
	CStatic					m_MinSizeText;
	CSliderCtrl				m_MinSize;
	CStatic					m_MaxSizeText;
	CSliderCtrl				m_MaxSize;
	CStatic					m_PercentText;
	CSliderCtrl				m_Percent;
	CStatic					m_PixelsText;
	CSliderCtrl				m_Pixels;
};
#endif
