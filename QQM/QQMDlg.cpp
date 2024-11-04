
// QQMDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "QQM.h"
#include "QQMDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

struct Vertex
{
	Vertex() {}
	Vertex(float x, float y, float z, D3DCOLOR c = D3DCOLOR_XRGB(0, 0, 0))
	{
		_x = x;  _y = y;  _z = z;
		_color = c;
	}
	
	Vertex operator+(Vertex &v)
	{
		Vertex temp;
		temp._x = this->_x + v._x;
		temp._y = this->_y + v._y;
		temp._z = this->_z + v._z;
		temp._color = this->_color;
		return Vertex(temp._x, temp._y, temp._z, temp._color);
	}
	Vertex operator/(int i)
	{
		Vertex temp;
		temp._x = this->_x / i;
		temp._y = this->_y / i;
		temp._z = this->_z / i;
		temp._color = this->_color;
		return Vertex(temp._x, temp._y, temp._z, temp._color);
	}
	Vertex zhongdian(Vertex &v1, Vertex &v2)
	{
		Vertex temp;
		temp._x = (v1._x + v2._x) / 2;
		temp._y = (v1._y + v2._y) / 2;
		temp._z = (v1._z + v2._z) / 2;
		temp._color = this->_color;
		return Vertex(temp._x, temp._y, temp._z, temp._color);
	}
	float _x, _y, _z;
	D3DCOLOR _color;
	static const DWORD FVF;
};
D3DCOLOR cc = D3DCOLOR_XRGB(0, 0, 0);
Vertex convert(float r, float Cta, float fai, D3DCOLOR c = cc)
{
	float x = -r * cos(Cta)*cos(fai);
	float y = r * cos(Cta)*sin(fai);
	float z = r * sin(Cta);
	return Vertex(x, y, z, c);
}
Vertex midVertex(Vertex &v1, Vertex &v2)
{
	Vertex temp;
	temp._x = (v1._x + v2._x) / 2;
	temp._y = (v1._y + v2._y) / 2;
	temp._z = (v1._z + v2._z) / 2;
	temp._color = v1._color;
	return Vertex(temp._x, temp._y, temp._z, temp._color);
}

const DWORD Vertex::FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE;

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:

};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	
END_MESSAGE_MAP()


// CQQMDlg 对话框



CQQMDlg::CQQMDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_QQM_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CQQMDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDRETRY, isok);
	DDX_Control(pDX, IDC_EDIT1, m_edit);
	DDX_Control(pDX, IDCANCEL, paintpaper);
}

BEGIN_MESSAGE_MAP(CQQMDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDCANCEL, &CQQMDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDRETRY, &CQQMDlg::OnBnClickedRetry)
	ON_WM_MOUSEWHEEL()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_EN_CHANGE(IDC_EDIT1, &CQQMDlg::OnEnChangeEdit1)
END_MESSAGE_MAP()


// CQQMDlg 消息处理程序

BOOL CQQMDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	//下边这两个函数获取的是真正屏幕的大小：屏幕分辨率
	int nWidth = GetSystemMetrics(SM_CXSCREEN);  //屏幕宽度    
	int nHeight = GetSystemMetrics(SM_CYSCREEN); //屏幕高度

	MoveWindow(500, 20, 1000, 900, true);
	
	int iImgWidth = 1600, iImgHeight = 1600;
	int iImgZoomWidth = iImgWidth / 2, iImgZoomHeight = iImgHeight / 2; 
	CRect rectPic;
	GetDlgItem(IDC_STATIC)->GetWindowRect(&rectPic); // IDC_PICTURE 是 picture control 的 ID 
	ScreenToClient(&rectPic);
	GetDlgItem(IDC_STATIC)->MoveWindow(rectPic.left, rectPic.top, iImgZoomWidth, iImgZoomHeight, true);


	InitD3D();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CQQMDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CQQMDlg::OnPaint()
{

	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
		Display(0);
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CQQMDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

/*------------——————————————————————————————*/

HRESULT CQQMDlg::InitD3D()
{
	m_hwndRender = GetDlgItem(IDC_STATIC)->GetSafeHwnd();

	//创建Direct3D对象, 该对象用来创建Direct3D设备对象
	if (NULL == (g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
		return E_FAIL;

	//设置D3DPRESENT_PARAMETERS结构, 准备创建Direct3D设备对象
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.hDeviceWindow = m_hwndRender;

	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_hwndRender,/*D3DCREATE_FPU_PRESERVE|*/ D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &Device)))
	{
		return E_FAIL;
	}

	Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	//关闭光照处理，默认情况下启用光照处理
	//Device->SetRenderState(D3DRS_LIGHTING, FALSE);

	//设置观察和投影矩阵
	SetupViewandProjMatrices();

	return S_OK;
}

void CQQMDlg::SetupViewandProjMatrices()
{
}

bool CQQMDlg::Setup(int Level)
{
	// 关闭光照，顶点颜色才会起作用
	Device->SetRenderState(D3DRS_LIGHTING, FALSE);

	//
	// Create the vertex buffer.
	//

	Device->CreateVertexBuffer(
		10000000 * sizeof(Vertex), // size in bytes
		D3DUSAGE_WRITEONLY, // flags
		Vertex::FVF,        // vertex format
		D3DPOOL_MANAGED,    // managed memory pool
		&D3DVertexBuffer,          // return create vertex buffer
		0);                 // not used - set to 0

	// 构建立方体顶点数据
	Vertex* vertices;
	D3DVertexBuffer->Lock(0, 0, (void**)&vertices, 0);
	int v = 0;			//点数量
	float RR = 100;		//自定义球最外围半径
	float d_R = RR / (2 << Level);		//每层间隔

	for (int ud = -1; ud <= 1; ud += 2) {		//上下顶面分别绘制
		float R = 0;		//里面每层球面半径
		float mid_R = 0;	//缩减层的下一层半径：1，2，4，8，16		//
		int level = 0;		//当前球面的级别
		int i_h = 1;		//缩减层的高度
		for (int i = 1; i <= (2 << Level); i++) {		//i表示从最里面开始往外第i层
			R += d_R;
			mid_R = d_R * (i_h >> 1);
			float h_d_cta = (D3DX_PI / 6) / (1 << level);//级数与纬度变化关系
			
			if (level == 0) {	//第0级顶面——2个半六边形
				cc = D3DCOLOR_XRGB(0, 0, 0);
				for (int n = 0; n < 6; n++) {
					//极地外圈（纬线）
					vertices[v++] = convert(R, ((D3DX_PI / 2) - h_d_cta)*ud, n*(D3DX_PI / 3));
					vertices[v++] = convert(R, ((D3DX_PI / 2) - h_d_cta)*ud, ((n + 1) % 6)*(D3DX_PI / 3));
					//极地内圈（纬线）
					vertices[v++] = convert(pow(3, 0.5)*R / (2.0 * cos(D3DX_PI / 12)), ((D3DX_PI / 2) - h_d_cta / 2)*ud, n*(D3DX_PI / 3));
					vertices[v++] = convert(pow(3, 0.5)*R / (2.0 * cos(D3DX_PI / 12)), ((D3DX_PI / 2) - h_d_cta / 2)*ud, ((n + 1) % 6)*(D3DX_PI / 3));
					//极地经线
					vertices[v++] = convert(R, ((D3DX_PI / 2) - h_d_cta)*ud, n*(D3DX_PI / 3));
					vertices[v++] = convert(pow(3, 0.5)*R / (2.0 * cos(D3DX_PI / 12)), ((D3DX_PI / 2) - h_d_cta / 2)*ud, n*(D3DX_PI / 3));
					//极地径线
					vertices[v++] = convert(R, ((D3DX_PI / 2) - h_d_cta)*ud, n*(D3DX_PI / 3));
					vertices[v++] = convert(0, 0, 0);
					vertices[v++] = convert(R, ((D3DX_PI / 2) - h_d_cta)*ud, (n+1)*(D3DX_PI / 3));
					vertices[v++] = convert(0, 0, 0);

				}
				vertices[v++] = convert(R, ((D3DX_PI / 2) - h_d_cta)*ud, 0 * (D3DX_PI / 3));
				vertices[v++] = convert(R, ((D3DX_PI / 2) - h_d_cta)*ud, 3 * (D3DX_PI / 3));
			}
			cc = D3DCOLOR_XRGB(0, 0, 0);

			for (int k = 1; k <= level; k++) {		//level级别顶面60-90区域
				float h_cta_max = (D3DX_PI / 2) - h_d_cta * (1 << (k - 1));			//纬线最大值
				float h_cta_min = (D3DX_PI / 2) - h_d_cta * (1 << k);	//纬线最小值
				float h_d_afa = (D3DX_PI / (3 << (k - 1)));	//经度变化值
				int h_row = (1 << (k - 1));		//有多少行纬线
				int h_col = 2 * (3 << (k - 1));		//有多少列经线
				bool mid = true;
				//60-90纬线
				//纬线

				for (int m = 0; m <= h_row; m++) {
					if (k == 1&& R == 2 * mid_R && (R != RR)) {
						cc = D3DCOLOR_XRGB(0, 0, 0);
					}
					else {
						cc = D3DCOLOR_XRGB(0, 0, 0);
					}
					for (int n = 0; n < h_col; n++) {
						if (m == h_row) {
							if (k == 1) {
								if (mid) {
									if ((R == 2 * mid_R) && (R != RR)) {	//第1层极地分割线
										vertices[v++] = convert(R, (h_cta_min + (m + 0.5) * h_d_cta)*ud, 0 * h_d_afa);
										vertices[v++] = convert(R, (h_cta_min + (m + 0.5) * h_d_cta)*ud, h_col / 2 * h_d_afa);
									}
									else {
										vertices[v++] = convert(R, (h_cta_min + m * h_d_cta)*ud, 0 * h_d_afa);
										vertices[v++] = convert(R, (h_cta_min + m * h_d_cta)*ud, h_col / 2 * h_d_afa);
									}
									mid = false;
								}
								vertices[v++] = convert(R, (h_cta_min + m * h_d_cta)*ud, n*h_d_afa);
								vertices[v++] = convert(R, (h_cta_min + m * h_d_cta)*ud, ((n + 1) % h_col)*h_d_afa);
							}
							if ((R == 2 * mid_R) && (R != RR)) {	//网格收缩的痕迹
								vertices[v++] = convert(R, (h_cta_min + m * h_d_cta + h_d_cta / 2)*ud, n*h_d_afa);
								vertices[v++] = convert(R, (h_cta_min + m * h_d_cta + h_d_cta / 2)*ud, ((n + 1) % h_col)*h_d_afa);	//纬线痕迹
								vertices[v++] = convert(R, (h_cta_min + m * h_d_cta)*ud, n*h_d_afa);
								vertices[v++] = convert(R, (h_cta_min + m * h_d_cta + h_d_cta / 2)*ud, n*h_d_afa);	//经线痕迹
							}
						}
						else {
							vertices[v++] = convert(R, (h_cta_min + m * h_d_cta)*ud, n*h_d_afa);
							vertices[v++] = convert(R, (h_cta_min + m * h_d_cta)*ud, ((n + 1) % h_col)*h_d_afa);
						}
					}
				}
				cc = D3DCOLOR_XRGB(0, 0, 0);
				//60-90经线
				//经线
				for (int n = 0; n < h_col; n++) {
					for (int m = 0; m < h_row; m++) {
						if (k == 1 && R == 2 * mid_R && (R != RR)) {
							cc = D3DCOLOR_XRGB(0, 0, 0);
						}
						else {
							cc = D3DCOLOR_XRGB(0, 0, 0);
						}
						if ((n & 1) && (m == h_row - 1) && (k != 1)) {
							vertices[v++] = convert(R, (h_cta_min + m * h_d_cta)*ud, n*h_d_afa);
							Vertex v1(convert(R, (h_cta_min + (m + 1) * h_d_cta)*ud, (n - 1)*h_d_afa));
							Vertex v2(convert(R, (h_cta_min + (m + 1) * h_d_cta)*ud, (n + 1)*h_d_afa));
							vertices[v++] = midVertex(v1, v2);
						}
						else {
							vertices[v++] = convert(R, (h_cta_min + m * h_d_cta)*ud, n*h_d_afa);
							vertices[v++] = convert(R, (h_cta_min + (m + 1) * h_d_cta)*ud, n*h_d_afa);
						}
					}
				}

				//60-90球径线
				//球径线
				for (int m = 0; m <= h_row; m++) {
					for (int n = 0; n < h_col; n++) {
						//上下两层网格不是缩进的
						if ((R - d_R) != mid_R) {
							if (!(n & 1)) {		//偶数列
								vertices[v++] = convert(R, (h_cta_min + m * h_d_cta)*ud, n*h_d_afa);
								vertices[v++] = convert(R - d_R, (h_cta_min + m * h_d_cta)*ud, n*h_d_afa);
							}
							else if ((n & 1) && (m == h_row) && (k != 1)) {
								Vertex v1(convert(R, (h_cta_min + m * h_d_cta)*ud, (n - 1)*h_d_afa));
								Vertex v2(convert(R, (h_cta_min + m * h_d_cta)*ud, (n + 1)*h_d_afa));
								vertices[v++] = midVertex(v1, v2);
								v1 = (convert(R - d_R, (h_cta_min + m * h_d_cta)*ud, (n - 1)*h_d_afa));
								v2 = (convert(R - d_R, (h_cta_min + m * h_d_cta)*ud, (n + 1)*h_d_afa));
								vertices[v++] = midVertex(v1, v2);
							}
							else {
								vertices[v++] = convert(R, (h_cta_min + m * h_d_cta)*ud, n*h_d_afa);
								vertices[v++] = convert(R - d_R, (h_cta_min + m * h_d_cta)*ud, n*h_d_afa);
							}
						}
						else {		//上下两层网格收缩
							if ((n & 1) && k != 1) {	//奇数经列

								if (m != h_row) {	//不是最靠里边的纬层
									
									vertices[v++] = convert(R, (h_cta_min + m * h_d_cta)*ud, n*h_d_afa);
									Vertex v1(convert(mid_R, (h_cta_min + m * h_d_cta)*ud, (n - 1)*h_d_afa));
									Vertex v2(convert(mid_R, (h_cta_min + m * h_d_cta)*ud, (n + 1)*h_d_afa));
									vertices[v++] = midVertex(v1, v2);
									//
									cc = D3DCOLOR_XRGB(0, 0, 0);
									v1=(convert(mid_R, (h_cta_min + m * h_d_cta)*ud, (n - 1)*h_d_afa));
									v2=(convert(mid_R, (h_cta_min + m * h_d_cta)*ud, (n + 1)*h_d_afa));
									//
									Vertex v3(convert(mid_R, (h_cta_min + (m + 1) * h_d_cta)*ud, (n - 1)*h_d_afa));	//收缩痕迹经线
									Vertex v4(convert(mid_R, (h_cta_min + (m + 1) * h_d_cta)*ud, (n + 1)*h_d_afa));
									vertices[v++] = midVertex(v1, v2);
									vertices[v++] = midVertex(v3, v4);
									cc = D3DCOLOR_XRGB(0, 0, 0);
									if (!(m & 1)) {		//收缩痕迹纬线，并且防止多次生成
										if (R != 2 * mid_R) {
											cc = D3DCOLOR_XRGB(0, 0, 0);
										}
										else {
											cc = D3DCOLOR_XRGB(0, 0, 0);
										}
										cc = D3DCOLOR_XRGB(0, 0, 0);
										v1 = (convert(mid_R, (h_cta_min + m * h_d_cta)*ud, (n - 1)*h_d_afa));
										v2 = (convert(mid_R, (h_cta_min + (m + 2) * h_d_cta)*ud, (n - 1)*h_d_afa));
										v3 = (convert(mid_R, (h_cta_min + m * h_d_cta)*ud, (n + 1)*h_d_afa));
										v4 = (convert(mid_R, (h_cta_min + (m + 2) * h_d_cta)*ud, (n + 1)*h_d_afa));
										vertices[v++] = midVertex(v1, v2);
										vertices[v++] = midVertex(v3, v4);
										cc = D3DCOLOR_XRGB(0, 0, 0);
									}
								}
								else {	//最里边的一条纬边
									Vertex v3(convert(R, (h_cta_min + m * h_d_cta)*ud, (n - 1)*h_d_afa));
									Vertex v4(convert(R, (h_cta_min + m * h_d_cta)*ud, (n + 1)*h_d_afa));
									vertices[v++] = midVertex(v3, v4);
									Vertex v1(convert(mid_R, (h_cta_min + m * h_d_cta)*ud, (n - 1)*h_d_afa));
									Vertex v2(convert(mid_R, (h_cta_min + m * h_d_cta)*ud, (n + 1)*h_d_afa));
									vertices[v++] = midVertex(v1, v2);
								}
							}
							else {	//偶数经度列
								if (R - d_R == d_R) {	//球心极地部分球径线
									if (m==0) {
										vertices[v++] = convert(R, (h_cta_min + m * h_d_cta)*ud, n*h_d_afa);
										vertices[v++] = convert(R - d_R, (h_cta_min + m * h_d_cta)*ud, n*h_d_afa);
									}
									else {
										vertices[v++] = convert(R, (h_cta_min + m * h_d_cta)*ud, n*h_d_afa);
										vertices[v++] = convert((R - d_R)*pow(3, 0.5) / (2.0 * cos(D3DX_PI / 12)), (h_cta_min + m * h_d_cta)*ud, n*h_d_afa);
									}
								}
								else {
									vertices[v++] = convert(R, (h_cta_min + m * h_d_cta)*ud, n*h_d_afa);
									vertices[v++] = convert(R - d_R, (h_cta_min + m * h_d_cta)*ud, n*h_d_afa);
								}
							}
						}
					}
				}

			}
		
			if (ud == -1) {
				//纬线0~60随级别的变化
				float cta_max = D3DX_PI / 3;
				float cta_min = -D3DX_PI / 3;
				float d_cta = (cta_max - cta_min) / 2 / (2 << level);
				float d_afa = D3DX_PI / (3 << level);
				int row = 2 * (2 << level);
				int col = 2 * (3 << level);
				
				//纬线	
				for (int m = 0; m < row; m++) {
					//如果是第0级，最靠近极点的纬线要画出来，否则不画，因为内层的一圈会画出来。
					for (int n = 0; n < col; n++) {
						
						//画出球心径线
						if (R == d_R) {
							vertices[v++] = convert(R, cta_min + m * d_cta, n*d_afa);
							vertices[v++] = convert(0, 0, 0);
						}
						
						vertices[v++] = convert(R, cta_min + m * d_cta, n*d_afa);
						vertices[v++] = convert(R, cta_min + m * d_cta, (n + 1)*d_afa);
						
					}
				}
				//经线
				for (int n = 0; n <= col; n++) {
					for (int m = 0; m < row; m++) {
						//如果是第0级，不需要取中点。如果是最靠近极点的经线则需要求出中点位置
						if ((n & 1) && (m == row - 1) && (R != d_R)) {
							vertices[v++] = convert(R, cta_min + m * d_cta, n*d_afa);
							Vertex v1(convert(R, cta_min + (m + 1) * d_cta, (n - 1)*d_afa));
							Vertex v2(convert(R, cta_min + (m + 1) * d_cta, (n + 1)*d_afa));
							vertices[v++] = midVertex(v1, v2);
						}
						else {
							vertices[v++] = convert(R, cta_min + m * d_cta, n*d_afa);
							vertices[v++] = convert(R, cta_min + (m + 1) * d_cta, n*d_afa);
						}
					}
				}
				//球径线
				for (int m = 0; m <= row && level != 0; m++) {
					for (int n = 0; n <= col; n++) {
						
						//偶数纬行
						if (!(m & 1) && (n & 1)) {		//奇数列
							if (m == row) {
								Vertex v1(convert(R, cta_min + m * d_cta, (n - 1)*d_afa));
								Vertex v2(convert(R, cta_min + m * d_cta, (n + 1)*d_afa));
								vertices[v++] = midVertex(v1, v2);
							}
							else {
								vertices[v++] = convert(R, cta_min + m * d_cta, n*d_afa);
							}
							Vertex v1(convert(mid_R, cta_min + (m / 2) * d_cta * 2, (n / 2)*d_afa * 2));
							Vertex v2(convert(mid_R, cta_min + (m / 2) * d_cta * 2, (n / 2 + 1)*d_afa * 2));
							vertices[v++] = midVertex(v1, v2);
						}
						else if (!(m & 1) && !(n & 1)) {	//偶数列
							vertices[v++] = convert(R, cta_min + m * d_cta, n*d_afa);
							vertices[v++] = convert(mid_R, cta_min + m * d_cta, n*d_afa);
						}
						//奇数纬行
						else if ((m & 1) && (n & 1)) {	//奇数列
							
							Vertex v1(convert(mid_R, cta_min + (m / 2) * d_cta * 2, (n / 2)*d_afa * 2));
							Vertex v2(convert(mid_R, cta_min + (m / 2) * d_cta * 2, (n / 2 + 1)*d_afa * 2));
							Vertex v3(midVertex(v1, v2));
							v1 = convert(mid_R, cta_min + (m / 2 + 1) * d_cta * 2, (n / 2)*d_afa * 2);
							v2 = convert(mid_R, cta_min + (m / 2 + 1) * d_cta * 2, (n / 2 + 1)*d_afa * 2);
							Vertex v4(midVertex(v1, v2));
							if (i == i_h) {	//4个面（立方体）缩减成一个面（立方体）
								
								vertices[v++] = v3;
								vertices[v++] = v4;
								
								v1 = (convert(mid_R, cta_min + (m / 2) * d_cta * 2, (n / 2)*d_afa * 2));
								v2 = convert(mid_R, cta_min + (m / 2 + 1) * d_cta * 2, (n / 2)*d_afa * 2);
								v3 = (midVertex(v1, v2));
								v1 = (convert(mid_R, cta_min + (m / 2) * d_cta * 2, (n / 2 + 1)*d_afa * 2));
								v2 = convert(mid_R, cta_min + (m / 2 + 1) * d_cta * 2, (n / 2 + 1)*d_afa * 2);
								v4 = (midVertex(v1, v2));
								vertices[v++] = v3;
								vertices[v++] = v4;
							}

							vertices[v++] = convert(R, cta_min + m * d_cta, n*d_afa);
							vertices[v++] = midVertex(v3, v4);
						}
						else if ((m & 1) && !(n & 1)) {	//偶数列
							vertices[v++] = convert(R, cta_min + m * d_cta, n*d_afa);
							Vertex v1(convert(mid_R, cta_min + (m / 2) * d_cta * 2, (n / 2)*d_afa * 2));
							Vertex v2(convert(mid_R, cta_min + (m / 2 + 1) * d_cta * 2, (n / 2)*d_afa * 2));
							vertices[v++] = midVertex(v1, v2);
						}
					}
				}
			}
			
			//1:0, 2:1, 3-4:2, 5-8:3, 9-16:4
			if (i == i_h) {
				i_h = i_h << 1;
				level++;
			}
		}
	}
	
	D3DVertexBuffer->Unlock();

	//
	// Set the projection matrix.
	//

	D3DXMATRIX proj;
	D3DXMatrixPerspectiveFovLH(
		&proj,                        // result
		D3DX_PI * 0.5f,               // 90 - degrees
		(float)Width / (float)Height, // aspect ratio
		1.0f,                         // near plane
		10000.0f);                     // far plane
	Device->SetTransform(D3DTS_PROJECTION, &proj);

	//
	// Set wireframe mode render state.
	//
	
	Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	return true;
}
void CQQMDlg::Cleanup()
{
	if (D3DVertexBuffer != NULL)
		D3DVertexBuffer->Release();
}

int CQQMDlg::Display(int level)
{

	if (Device)
	{
		// Animate the camera:
		// The camera will circle around the center of the scene.  We use the
		// sin and cos functions to generate points on the circle, then scale them
		// by 10 to further the radius.  In addition the camera will move up and down
		// as it circles about the scene.

		Device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xffffffff, 1.0f, 0);
		Device->BeginScene();
		
		Setup(level);

		Device->SetStreamSource(0, D3DVertexBuffer, 0, sizeof(Vertex));
		Device->SetFVF(Vertex::FVF);

		Device->DrawPrimitive(D3DPT_LINELIST, 0, 100000);

		Device->EndScene();
		Device->Present(0, 0, 0, 0);
	}
	return true;
}


void CQQMDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void CQQMDlg::OnBnClickedRetry()
{
	// TODO: 在此添加控件通知处理程序代码
	
	int level = 0;

	level = GetDlgItemInt(IDC_EDIT1);

	Display(level);// TODO: 在此添加控件通知处理程序代码

}

BOOL CQQMDlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	Device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xffffffff, 1.0f, 0);
	//position += D3DXVECTOR3(float(-zDelta)/20,float(-zDelta)/20,float(-zDelta)/20); //zDelta一单位为120
	position -= position / zDelta * 5;
	D3DXMatrixLookAtLH(&V, &position, &target, &up);
	Device->SetTransform(D3DTS_VIEW, &V);
	D3DXMatrixPerspectiveFovLH(&proj, D3DX_PI / 4, 1.0f, 0.0f, 60.0f);
	Device->SetTransform(D3DTS_PROJECTION, &proj);

	Device->BeginScene();

	// Set the world matrix that positions the object.

	// Draw the object using the previously set world matrix.
	Device->SetStreamSource(0, D3DVertexBuffer, 0, sizeof(Vertex));
	Device->SetFVF(Vertex::FVF);

	Device->DrawPrimitive(D3DPT_LINELIST, 0, 100000);

	Device->EndScene();
	Device->Present(0, 0, 0, 0);
	return CDialogEx::OnMouseWheel(nFlags, zDelta, pt);
}

bool m_bIsLButtonDown;
CPoint m_curPoint;
void CQQMDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CRect rect;
	GetDlgItem(IDC_STATIC)->GetWindowRect(&rect);
	// 将屏幕坐标切换至客户坐标
	ScreenToClient(&rect);
	if (point.x >= rect.left && point.x <= rect.right && point.y >= rect.top && point.y <= rect.bottom)
	{
		point.x -= rect.left;
		point.y -= rect.top;
		if (m_bIsLButtonDown)
		{
			CSize rotate = m_curPoint - point;
			m_curPoint = point;//设定鼠标点,这样物体看上去不会旋转得很凌乱
			
			//响应键盘按键
			if (::GetAsyncKeyState('W') & 0x8000f) {	//视角上移
				position += D3DXVECTOR3(0.0f, 0.0f, 5.0f);
			}
			else if (::GetAsyncKeyState('S') & 0x8000f) {	//视角下移
				position -= D3DXVECTOR3(0.0f, 0.0f, 5.0f);
			}
			else if (::GetAsyncKeyState('I') & 0x8000f) {	//物体上移
				target -= D3DXVECTOR3(0.0f, 0.0f, 1.0f);
			}
			else if (::GetAsyncKeyState('K') & 0x8000f) {	//物体下移
				target += D3DXVECTOR3(0.0f, 0.0f, 1.0f);
			}
			else if (::GetAsyncKeyState('A') & 0x8000f) {	//物体左移
				target -= D3DXVECTOR3(0.0f, 5.0f, 0.0f);
			}
			else if (::GetAsyncKeyState('D') & 0x8000f) {	//物体右移
				target += D3DXVECTOR3(0.0f, 5.0f, 0.0f);
			}
			//不响应键盘时
			else {
				position += D3DXVECTOR3(rotate.cx*1.0f, -rotate.cy*1.0f, 0.0f);
			}
			
			D3DXMatrixLookAtLH(&V, &position, &target, &up);
			Device->SetTransform(D3DTS_VIEW, &V);

			D3DXMatrixPerspectiveFovLH(&proj, D3DX_PI / 4, 1.0f, 0.0f, 60.0f);
			Device->SetTransform(D3DTS_PROJECTION, &proj);
			Device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xffffffff, 1.0f, 0);
			if (SUCCEEDED(Device->BeginScene()))
			{

				Device->SetStreamSource(0, D3DVertexBuffer, 0, sizeof(Vertex));
				Device->SetFVF(Vertex::FVF);

				Device->DrawPrimitive(D3DPT_LINELIST, 0, 100000);

				Device->EndScene();
				Device->Present(0, 0, 0, 0);
			}
		}
		CDialogEx::OnMouseMove(nFlags, point);
	}
}

void CQQMDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_bIsLButtonDown = true;
	m_curPoint = point;
	CDialogEx::OnLButtonDown(nFlags, point);
}


void CQQMDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_bIsLButtonDown = FALSE;
	CDialogEx::OnLButtonUp(nFlags, point);
}


void CQQMDlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
