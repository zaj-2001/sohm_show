
// QQMDlg.h: 头文件
//

#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "winmm.lib")
#include <Windows.h>
#include <MMSystem.h>
#include "afxwin.h"

// CQQMDlg 对话框
class CQQMDlg : public CDialogEx
{
// 构造
public:
	CQQMDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_QQM_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	LPDIRECT3D9		g_pD3D = NULL;
	IDirect3DDevice9* Device = 0;
	HWND m_hwndRender;
	const int Width = 640;
	const int Height = 480;
	//IDirect3DVertexBuffer9* VB = 0;
	D3DXVECTOR3 position = D3DXVECTOR3(0.0f, 150.0f, 0.0f);

	// the camera is targetted at the origin of the world
	D3DXVECTOR3 target = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// the worlds up vector
	D3DXVECTOR3 up = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	D3DXMATRIX proj;
	D3DXMATRIX V;
	// 顶点缓冲区对象
	LPDIRECT3DVERTEXBUFFER9 D3DVertexBuffer = NULL;
	// 索引缓冲区对象
	LPDIRECT3DINDEXBUFFER9 D3DIndexBuffer = NULL;

public:
	HRESULT InitD3D();
	void SetupViewandProjMatrices();
	void Cleanup();
	bool Setup(int level);
	int Display(int n);

	CButton isok;
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedRetry();

	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnEnChangeEdit1();

	CEdit m_edit;
	CButton paintpaper;

};
